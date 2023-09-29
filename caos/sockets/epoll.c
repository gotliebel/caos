#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <resolv.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t must_exit = 0;
volatile sig_atomic_t num = 0;

struct client_struct {
    char buffer[4096];
    int buffer_len;
    int fd;
};

void handle_sigterm(int signum)
{
    must_exit = 1;
    if (num == 0) {
        exit(0);
    }
}

struct client_struct* init(int fd)
{
    struct client_struct* client = malloc(sizeof(struct client_struct));
    client->fd = fd;
    client->buffer_len = 0;
    return client;
}

void clear_client(struct client_struct* client)
{
    close(client->fd);
    free(client);
    fflush(stdout);
}

int main(int argc, char** argv)
{
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
    int number_fds = 0;
    int epoll_fd = 0;
    struct epoll_event event;
    struct epoll_event events[100];
    event.data.ptr = init(socket_fd);
    event.events = EPOLLIN;
    epoll_fd = epoll_create1(0);
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event);
    while (!must_exit) {
        sigset_t sigset;
        sigfillset(&sigset);
        sigdelset(&sigset, SIGTERM);
        number_fds = epoll_pwait(epoll_fd, events, 100, -1, &sigset);
        if (number_fds == -1) {
            break;
        }
        for (int i = 0; i < number_fds; ++i) {
            struct client_struct* connected = events[i].data.ptr;
            if (connected->fd != socket_fd) {
                if (events[i].events & EPOLLIN) {
                    int attempt = read(connected->fd, connected->buffer, 4096);
                    if (attempt > 0) {
                        for (int j = 0; j < attempt; ++j) {
                            connected->buffer[j] =
                                (char)toupper(connected->buffer[j]);
                        }
                        connected->buffer_len = attempt;
                        events[i].events |= EPOLLOUT;
                        epoll_ctl(
                            epoll_fd, EPOLL_CTL_MOD, connected->fd, &events[i]);
                    } else {
                        clear_client(connected);
                        --num;
                        continue;
                    }
                } else if (events[i].events & EPOLLOUT) {
                    if (connected->fd == -1) {
                        clear_client(connected);
                        --num;
                        continue;
                    }
                    if (connected->buffer_len > 0) {
                        int attempt = write(
                            connected->fd,
                            connected->buffer,
                            connected->buffer_len);
                        if (attempt == -1) {
                            clear_client(connected);
                            --num;
                            continue;
                        }
                        connected->buffer_len -= attempt;
                    }
                    if (connected->buffer_len == 0) {
                        events[i].events &= ~EPOLLOUT;
                        epoll_ctl(
                            epoll_fd, EPOLL_CTL_MOD, connected->fd, &events[i]);
                    }
                } else {
                    clear_client(connected);
                    --num;
                }
            } else {
                struct sockaddr_in client_addr;
                socklen_t client_addr_len;
                int socket_connection = accept(
                    socket_fd,
                    (struct sockaddr*)&client_addr,
                    &client_addr_len);
                int flags1 = fcntl(socket_connection, F_GETFL);
                flags1 |= O_NONBLOCK;
                fcntl(socket_connection, F_SETFL, flags1);
                ++num;
                struct client_struct* client = init(socket_connection);
                event.data.ptr = client;
                event.events = EPOLLIN;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_connection, &event);
            }
        }
        num = 0;
    }
    close(socket_fd);
    return 0;
}