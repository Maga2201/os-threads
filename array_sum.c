#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int thread_number;
    const int *values;
    int start;
    int end;  /* First index after this thread's half */
} ArrayPart;

static void *sum_part(void *arg)
{
    const ArrayPart *part = arg;
    int sum = 0;

    for (int i = part->start; i < part->end; i++) {
        sum += part->values[i];
    }

    printf("Thread %d | indices %d to %d | partial sum = %d\n",
           part->thread_number, part->start, part->end - 1, sum);
    return NULL;
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int length = sizeof(values) / sizeof(values[0]);
    int midpoint = length / 2;

    ArrayPart parts[2] = {
        {1, values, 0, midpoint},
        {2, values, midpoint, length}
    };
    pthread_t threads[2];
    int created = 0;

    for (int i = 0; i < 2; i++) {
        int rc = pthread_create(&threads[i], NULL, sum_part, &parts[i]);
        if (rc != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(rc));
            break;
        }
        created++;
    }

    for (int i = 0; i < created; i++) {
        int rc = pthread_join(threads[i], NULL);
        if (rc != 0) {
            fprintf(stderr, "pthread_join: %s\n", strerror(rc));
            return EXIT_FAILURE;
        }
    }

    return created == 2 ? EXIT_SUCCESS : EXIT_FAILURE;
}
