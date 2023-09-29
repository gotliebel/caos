#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t must_exit = 0;
volatile sig_atomic_t num = 0;

void handle_sigterm(int signum)
{
  must_exit = 1;
  if (num == 0) {
    exit(0);
  }
}

int main(int argc, char* argv[])
{

  struct sigaction action_term;
  memset(&action_term, 0, sizeof(action_term));
  action_term.sa_handler = handle_sigterm;
  action_term.sa_flags = SA_RESTART;
  sigaction(SIGTERM, &action_term, NULL);
  sigaction(SIGINT, &action_term, NULL);

  const char* path = argv[2];

  const char* ip_addr = "0.0.0.0";
  in_addr_t ip = inet_addr(ip_addr);

  const char* port_str = argv[1];
  int port = htons(strtol(port_str, NULL, 10));
  struct sockaddr_in server_addr = {
      .sin_family = AF_INET, .sin_port = port, .sin_addr = ip};

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) ==
      -1) {
    close(socket_fd);
    return -1;
  }
  if (listen(socket_fd, SOMAXCONN) == -1) {
    close(socket_fd);
    return -1;
  }

  while (true) {
    if (must_exit == 1) {
      break;
    }
    struct sockaddr_in client_addr;
    socklen_t len_client;
    int client_socket =
        accept(socket_fd, (struct sockaddr*)&client_addr, &len_client);
    if (client_socket == -1) {
      continue;
    } else {
      num++;
      char query[10000];
      long attempt_to_read = 10;
      long count_read = 0;
      int is_over = 1;
      char buffer[10];
      while (is_over == 1) {
        long previous = attempt_to_read;
        attempt_to_read = read(client_socket, buffer, 10);
        strncpy(query + count_read, buffer, attempt_to_read);
        count_read += attempt_to_read;
        if (previous != attempt_to_read) {
          is_over = 0;
        }
      }
      char file_name[1000];
      int index = 4;
      while (query[index] != 'H' && query[index + 1] != 'T' &&
          query[index + 2] != 'T' && query[index + 3] != 'P' &&
          query[index + 4] != '/' && query[index + 5] != '1' &&
          query[index + 6] != '.' && query[index + 7] != '1') {
        file_name[index - 4] = query[index];
        index++;
      }
      file_name[index - 4] = query[index];
      char file_path[10000];
      sprintf(file_path, "%s/%s", path, file_name);
      printf("%s", file_path);
      struct stat file_info;
      int status = stat(file_path, &file_info);
      write(client_socket, "HTTP/1.1 ", strlen("HTTP/1.1 "));
      if (status == -1) {
        if (errno == ENOENT) {
          write(
              client_socket,
              "404 Not Found\r\n",
              strlen("404 Not Found\r\n"));
        }
      } else {
        if (!(file_info.st_mode & S_IRUSR)) {
          write(
              client_socket,
              "403 Forbidden\r\n",
              strlen("403 Forbidden\r\n"));
        } else {
          write(client_socket, "200 OK\r\n", strlen("200 OK\r\n"));
          if (file_info.st_mode & S_IXUSR) {
            int pipe_fd[2];
            pipe(pipe_fd);
            pid_t pid = fork();
            if (pid > 0) {
              waitpid(pid, NULL, 0);
              close(pipe_fd[1]);
              char buffer1[10];
              long attempt_to_read1 = 10;
              bool is_over1 = true;
              long sum_bytes = 0;
              while (is_over1) {
                long previous = attempt_to_read1;
                attempt_to_read1 = read(pipe_fd[0], buffer1, 10);
                write(client_socket, buffer1, attempt_to_read1);
                sum_bytes += attempt_to_read1;
                if (previous != attempt_to_read1) {
                  is_over1 = false;
                }
              }
              close(pipe_fd[0]);
            } else {
              close(pipe_fd[0]);
              dup2(pipe_fd[1], 1);
              execlp(file_path, file_path, NULL);
              exit(0);
            }
          } else {
            write(
                client_socket,
                "Content-Length: ",
                strlen("Content-Length: "));
            int size = file_info.st_size;
            char file_size[10];
            sprintf(file_size, "%d", size);
            write(client_socket, file_size, strlen(file_size));
            write(client_socket, "\r\n\r\n", strlen("\r\n\r\n"));
            int open_fd = open(file_path, O_RDONLY);
            long attempt = 10;
            char buf[10];
            bool is_ov = false;
            while (!is_ov) {
              long prev = attempt;
              attempt = read(open_fd, buf, 10);
              write(client_socket, buf, attempt);
              if (prev != attempt) {
                is_ov = true;
              }
            }
            close(open_fd);
          }
        }
      }
      num--;
      close(client_socket);
    }
  }
  close(socket_fd);
  return 0;
}