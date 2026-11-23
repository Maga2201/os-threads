#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *print_numbers(void *arg)
{
    int thread_number = *(int *)arg;
    unsigned long id = (unsigned long)pthread_self();

    for (int n = 1; n <= 5; n++) {
        printf("Thread %d (ID %lu): %d\n", thread_number, id, n);
    }
    return NULL;
}

int main(void)
{
    pthread_t threads[3];
    int numbers[] = {1, 2, 3};
    int created = 0;

    for (int i = 0; i < 3; i++) {
        int rc = pthread_create(&threads[i], NULL, print_numbers, &numbers[i]);
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

    return created == 3 ? EXIT_SUCCESS : EXIT_FAILURE;
}
