#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct {
    long long a;
    long long b;
    long long current_value;
    int n;
    pthread_t pthread;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} context_t;

bool IsPrime(const long long number)
{
    long long d = 2;
    while (d * d <= number) {
        if (number % d != 0) {
            d += 1;
        } else {
            return false;
        }
    }
    return true;
}

void* routine(void* arg)
{
    context_t* context = arg;
    int number_prime_numbers = 0;
    pthread_mutex_lock(&context->mutex);
    for (long long i = context->a; i <= context->b; i++) {
        if (IsPrime(i)) {
            context->current_value = i;
            pthread_cond_signal(&context->cond);
            number_prime_numbers++;
            if (number_prime_numbers == context->n) {
                return NULL;
            }
            pthread_cond_wait(&context->cond, &context->mutex);
        }
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    long long a = atoll(argv[1]);
    long long b = atoll(argv[2]);
    int n = atoi(argv[3]);
    pthread_t pthread;
    context_t context;
    context.a = a;
    context.b = b;
    context.n = n;
    pthread_mutex_init(&context.mutex, NULL);
    pthread_cond_init(&context.cond, NULL);
    pthread_create(&pthread, NULL, routine, &context);
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    for (int i = 0; i < n; i++) {
        pthread_cond_wait(&context.cond, &mutex);
        printf("%lld\n", context.current_value);
        pthread_cond_signal(&context.cond);
    }
    pthread_mutex_unlock(&mutex);
    pthread_join(pthread, NULL);
    pthread_cond_destroy(&context.cond);
    pthread_mutex_destroy(&context.mutex);
    pthread_mutex_destroy(&mutex);
    return 0;
}