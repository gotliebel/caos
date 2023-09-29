#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void* decrease(void* arg)
{
    int* fd = arg;
    for (;;) {
        int buffer[1];
        read(fd[1], buffer, 4);
        if (buffer[0] > 100) {
            break;
        }
        buffer[0] -= 3;
        printf("%d\n", buffer[0]);
        if (buffer[0] == 0) {
            write(fd[1], buffer, 4);
            break;
        }
        write(fd[1], buffer, 4);
    }
    return NULL;
}

void* increase(void* arg)
{
    int* fd = arg;
    for (;;) {
        int buffer[1];
        read(fd[0], buffer, 4);
        if (buffer[0] == 0) {
            break;
        }
        buffer[0] += 5;
        printf("%d\n", buffer[0]);
        if (buffer[0] > 100) {
            write(fd[0], buffer, 4);
            break;
        }
        write(fd[0], buffer, 4);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    pthread_t pthread_decrease;
    pthread_t pthread_increase;
    int fd[2];
    socketpair(AF_LOCAL, SOCK_STREAM, 0, fd);
    int buf[1] = {n};
    write(fd[0], buf, 4);
    pthread_create(&pthread_decrease, NULL, decrease, &fd);
    pthread_create(&pthread_increase, NULL, increase, &fd);
    pthread_join(pthread_decrease, NULL);
    pthread_join(pthread_increase, NULL);
    return 0;
}