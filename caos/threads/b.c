#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_routine(void* arg)
{
    long long value = 0;
    long long sum = 0;
    while (EOF != scanf("%lld", &value)) {
        sum += value;
    }
    return (void*)sum;
}

int main(int argc, char* argv[])
{
    long long n = atoll(argv[1]);
    long long sum = 0;
    pthread_attr_t pthread_attr;
    pthread_attr_init(&pthread_attr);
    pthread_attr_setstacksize(&pthread_attr, 1);
    pthread_t* pthreads = (pthread_t*)malloc(sizeof(pthread_t) * n);
    for (int i = 0; i < n; i++) {
        pthread_create(&pthreads[i], &pthread_attr, &thread_routine, NULL);
    }
    for (int i = 0; i < n; i++) {
        void* part_sum;
        pthread_join(pthreads[i], &part_sum);
        sum += (long long)part_sum;
    }
    printf("%lld\n", sum);
    free(pthreads);
    return 0;
}