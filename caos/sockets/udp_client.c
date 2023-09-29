#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  const char* port_str = argv[1];
  uint16_t port = htons(strtol(port_str, NULL, 10));
  int socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  const char* ip_addr = "127.0.0.1";
  in_addr_t ip = inet_addr(ip_addr);
  struct sockaddr_in ipv4_addr = {.sin_family = AF_INET, .sin_port = port, .sin_addr = ip};
  int32_t number = 0;
  while (scanf("%d", &number) != EOF) {
    sendto(socket_fd, &number, sizeof(number), 0, (struct sockaddr*)&ipv4_addr, sizeof(ipv4_addr));
    recvfrom(socket_fd, &number, sizeof(number), 0, NULL, 0);
    printf("%d\n", number);
    fflush(stdout);
  }
  shutdown(socket_fd, SHUT_RDWR);
  close(socket_fd);
  return 0;
}