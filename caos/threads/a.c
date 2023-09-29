#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void* thread_routine(void* arg)
{
    int value = 0;
    if (1 != scanf("%d", &value)) {
        return NULL;
    }
    pthread_t next;
    pthread_create(&next, NULL, thread_routine, 0);
    pthread_join(next, NULL);
    printf("%d\n", value);
    return NULL;
}

int main()
{
    pthread_t pthread;
    pthread_create(&pthread, NULL, thread_routine, 0);
    pthread_join(pthread, NULL);
    return 0;
}