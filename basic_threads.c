#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *print_message(void *arg)
{
    int number = *(int *)arg;
    printf("Thread %d (ID %lu) is running\n",
           number, (unsigned long)pthread_self());
    return NULL;
}

int main(void)
{
    pthread_t threads[3];
    int numbers[] = {1, 2, 3};
    int created = 0;

    for (int i = 0; i < 3; i++) {
        int rc = pthread_create(&threads[i], NULL, print_message, &numbers[i]);
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

    if (created != 3) {
        return EXIT_FAILURE;
    }

    puts("All three threads have finished.");
    return EXIT_SUCCESS;
}
