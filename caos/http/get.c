#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    struct hostent* host = gethostbyname(argv[1]);
    struct in_addr** addr_list = (struct in_addr**)host->h_addr_list;
    char* ip_string = inet_ntoa(*addr_list[0]);
    in_addr_t ip = inet_addr(ip_string);
    uint16_t port = htons(80);
    struct sockaddr_in ipv4_addr = {
        .sin_family = AF_INET, .sin_port = port, .sin_addr = ip};
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(socket_fd, (struct sockaddr*)&ipv4_addr, sizeof(ipv4_addr)) ==
        -1) {
        return 1;
    }
    char req[1000];
    sprintf(
        req,
        "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
        argv[2],
        argv[1]);
    write(socket_fd, req, strlen(req));
    char buf[1000];
    FILE* file = fdopen(socket_fd, "r");
    while (fgets(buf, sizeof(buf), file)) {
        if (strcmp(buf, "\r\n") == 0) {
            break;
        }
    }
    while (fgets(buf, sizeof(buf), file)) {
        printf("%s", buf);
    }
    fclose(file);
    close(socket_fd);
    return 0;
}