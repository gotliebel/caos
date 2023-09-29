#include <limits.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct Item {
    struct Item* next;
    int64_t value;
} item_t;

_Atomic(item_t*) end = NULL;
int64_t iterations = 0;

void* routine(void* arg)
{
    int64_t index = (int64_t)arg;
    for (int64_t i = index * iterations; i < (index + 1) * iterations; i++) {
        item_t* new_node = malloc(sizeof(item_t));
        new_node->value = i;
        new_node->next = NULL;
        item_t* prev = atomic_exchange(&end, new_node);
        new_node->next = prev;
    }
    return NULL;
}
int main(int argc, char* argv[])
{
    int64_t n = atoll(argv[1]);
    int64_t k = atoll(argv[2]);
    iterations = k;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    pthread_attr_setguardsize(&attr, 0);
    pthread_t threads[n];
    for (int64_t i = 0; i < n; i++) {
        pthread_create(&threads[i], &attr, routine, (void*)i);
    }
    pthread_attr_destroy(&attr);
    for (int64_t i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    item_t* node = end;
    int64_t number_elements = n * k;
    while (node != NULL && number_elements > 1) {
        printf("%ld\n", node->value);
        node = node->next;
        number_elements--;
    }
    printf("%ld\n", node->value);
    node = end;
    while (node != NULL) {
        item_t* tmp = node;
        node = node->next;
        free(tmp);
    }
    return 0;
}