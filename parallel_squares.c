#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *print_square(void *arg)
{
    int number = *(int *)arg;
    printf("Square of %d is %d\n", number, number * number);
    return NULL;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5};
    enum { count = sizeof(numbers) / sizeof(numbers[0]) };
    pthread_t threads[count];
    int created = 0;

    for (int i = 0; i < count; i++) {
        int rc = pthread_create(&threads[i], NULL, print_square, &numbers[i]);
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

    return created == count ? EXIT_SUCCESS : EXIT_FAILURE;
}
