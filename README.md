# POSIX Threads Exercises

Operating Systems homework by Margarita Harutyunyan. These four C programs use POSIX threads (`pthread`) and were run on the AUA Ubuntu server.

| Exercise | Source file | What the program does |
|---|---|---|
| 1. Basic Thread Creation | `basic_threads.c` | Creates three threads. Each prints its ID, and the main thread waits for all three to finish using `pthread_join`. |
| 2. Array Processing with Threads | `array_sum.c` | Splits the array `{1, 2, 3, 4, 5, 6, 7, 8}` between two threads. The first half sums to 10 and the second to 26. |
| 3. Printing Numbers with Threads | `print_numbers.c` | Creates three threads. Each prints its ID and counts from 1 to 5, producing 15 lines in total. |
| 4. Calculating Squares in Parallel | `parallel_squares.c` | Creates one thread for each integer from 1 to 5. Each thread prints the square of its assigned number. |

## Compile and run

Run these commands from the repository folder on Linux:

```bash
gcc -std=c11 -Wall -Wextra -pthread basic_threads.c -o basic_threads && ./basic_threads
gcc -std=c11 -Wall -Wextra -pthread array_sum.c -o array_sum && ./array_sum
gcc -std=c11 -Wall -Wextra -pthread print_numbers.c -o print_numbers && ./print_numbers
gcc -std=c11 -Wall -Wextra -pthread parallel_squares.c -o parallel_squares && ./parallel_squares
```

The order of output from different threads can vary between runs. In Exercise 3, each individual thread still prints its own numbers in order from 1 to 5.
