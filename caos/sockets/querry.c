#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  const char* ip_addr = argv[1];
  in_addr_t ip = inet_addr(ip_addr);
  const char* port_str = argv[2];
  uint16_t port = htons(strtol(port_str, NULL, 10));
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in ipv4_addr = {.sin_family = AF_INET, .sin_port = port, .sin_addr = ip};
  connect(socket_fd, (struct sockaddr*)&ipv4_addr, sizeof(ipv4_addr));
  write(socket_fd, "GET script HTTP/1.1\r\n", strlen("GET script HTTP/1.1\r\n"));
  write(socket_fd, "asdfasdf\r\n", strlen("asdfasdf\r\n"));
  write(socket_fd, "\r\n", strlen("\r\n"));
  long attempt = 10;
  int is_over = 1;
  long sum = 0;
  char buffer[10] = "";
  while (is_over == 1) {
    long prev = attempt;

    attempt = read(socket_fd, buffer, 10);
    //printf("%ld\n", attempt);
    sum += attempt;
    printf("%s", buffer);
    if (prev != attempt) {
      is_over = 0;
    }
  }
  //printf("%ld", sum);
  shutdown(socket_fd, SHUT_RDWR);
  close(socket_fd);
  return 0;
}