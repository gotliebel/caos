#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct {
    double* array;
    pthread_mutex_t* mutex;
    pthread_t pthread;
    size_t n;
    size_t k;
    size_t index;
} context_t;

void* routine(void* arg)
{
    context_t* ctx = arg;
    size_t left = ((ctx->index == 0) ? ctx->k - 1 : ctx->index - 1);
    size_t right = ((ctx->index == ctx->k - 1) ? 0 : ctx->index + 1);
    for (size_t i = 0; i < ctx->n; i++) {
        pthread_mutex_lock(ctx->mutex);
        ctx->array[left] += 0.99;
        ctx->array[ctx->index] += 1;
        ctx->array[right] += 1.01;
        pthread_mutex_unlock(ctx->mutex);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    context_t threads[k];
    double array[k];
    memset(array, 0, sizeof(array));
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    pthread_attr_setguardsize(&attr, 0);
    for (size_t i = 0; i < k; i++) {
        threads[i].index = i;
        threads[i].mutex = &mutex;
        threads[i].k = k;
        threads[i].n = n;
        threads[i].array = array;
        pthread_create(&threads[i].pthread, &attr, routine, &threads[i]);
    }
    pthread_attr_destroy(&attr);
    for (size_t i = 0; i < k; i++) {
        pthread_join(threads[i].pthread, NULL);
    }
    for (size_t i = 0; i < k; i++) {
        printf("%.10g\n", array[i]);
    }
    return 0;
}