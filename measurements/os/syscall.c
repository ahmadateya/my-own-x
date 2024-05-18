#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define ITERATIONS 1000000

int main() {
    int i;
    double total_time, elapsed_time;
    struct timeval start_time, end_time;

    // start_time and end_time are measured in microseconds (1e-6 seconds)
    gettimeofday(&start_time, NULL);
    gettimeofday(&end_time, NULL);

    // Measure system call overhead
    total_time = 0.0;
    for (i = 0; i < ITERATIONS; i++) {
        gettimeofday(&start_time, NULL);
        read(0, NULL, 0);  // Null byte read from stdin (descriptor 0)
        gettimeofday(&end_time, NULL);
        elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
        total_time += elapsed_time;
    }

    printf("Average system call overhead (null byte read): %.3f microseconds\n", total_time / ITERATIONS);

    return 0;
}
