#include <arpa/inet.h>
#include <bits/time.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

struct packet_t {
    struct icmphdr header;
    char message[64 - sizeof(struct icmphdr)];
} __attribute__((__packed__));

unsigned short checksum(void* b, int len)
{
    unsigned short* buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int main(int argc, char* argv[])
{
    char* ip_addr = argv[1];
    in_addr_t ip = inet_addr(ip_addr);
    struct sockaddr_in ipv4_addr = {AF_INET, 0, ip};
    int socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    int timeout = atoi(argv[2]);
    int interval = atoi(argv[3]);
    int counter = 0;
    int counter_sent_messages = 0;
    struct timespec begin_time, current_time;
    struct timeval time_string;
    time_string.tv_usec = 0;
    time_string.tv_sec = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, &time_string, sizeof(time_string));
    clock_gettime(CLOCK_MONOTONIC, &begin_time);
    while (true) {
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        double time = current_time.tv_sec - begin_time.tv_sec + ((current_time.tv_nsec - begin_time.tv_nsec) / 1000000000.0);
        if (time > timeout) {
            break;
        }
        struct packet_t packet;
        memset(&packet, 0, sizeof(packet));
        packet.header.type = ICMP_ECHO;
        packet.header.code = 0;
        packet.header.un.echo.id = getpid();
        packet.header.un.echo.sequence = counter_sent_messages++;
        packet.header.checksum = checksum(&packet, sizeof(packet));
        sendto(
            socket_fd,
            &packet,
            sizeof(packet),
            0,
            (struct sockaddr*)&ipv4_addr,
            sizeof(ipv4_addr));
        int size = 0;
        if (recvfrom(
                socket_fd,
                &packet,
                sizeof(packet),
                0,
                (struct sockaddr*)&ipv4_addr,
                &size) > 0) {
            counter += 1;
        }
        usleep(interval);
    }
    printf("%d\n", counter);
    close(socket_fd);
    return 0;
}