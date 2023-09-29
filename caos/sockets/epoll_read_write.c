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
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>
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

int main(int argc, char* argv[]) {
  struct sigaction action_term;
  memset(&action_term, 0, sizeof(action_term));
  action_term.sa_handler = handle_sigterm;
  action_term.sa_flags = SA_RESTART;
  sigaction(SIGTERM, &action_term, NULL);

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
  int flags = fcntl(socket_fd, F_GETFL);
  flags |= O_NONBLOCK;
  fcntl(socket_fd, F_SETFL, flags);

  int epoll_fd = epoll_create1(0);
  struct epoll_event events[1000];
  while (true) {
    if (must_exit == 1) {
      break;
    }
    int new_events_count = epoll_wait(epoll_fd, events, 1000, -1);

    char temp_buffer[4096];
    for (size_t i = 0; i < new_events_count; ++i) {

  }


  close(socket_fd);
  return 0;
}