/**
 * Q2 Write the program, called tlb.c, that can roughly measure the cost
 * of accessing each page. Inputs to the program should be: the num-
 * ber of pages to touch and the number of trials.
 * 
 *      
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define PAGE_SIZE 4096 // 4KB page size

int main(int argc, char *argv[])
{
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_pages_to_touch> <number_of_trials>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int num_pages = atoi(argv[1]);
    int num_trials = atoi(argv[2]);

    size_t bytes_to_allocate = num_pages * PAGE_SIZE;
    volatile int* array = (volatile int* )malloc(bytes_to_allocate);

    // initialize
    for (int i = 0; i < bytes_to_allocate/sizeof(int); i++) {
        array[i] = 0;
    }

    struct timespec start, end;
    long long total_elapsed_time_ns = 0;

    for(int trial = 0; trial < num_trials; trial++) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        // One integer per page of the array is updated
        int jump = PAGE_SIZE/sizeof(int);
        for(int i = 0; i < num_pages * jump; i += jump) {
            array[i]++;
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        long long elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
        total_elapsed_time_ns += elapsed_ns;
    }

    // average time per page access
    double average_time_ns = (double)total_elapsed_time_ns / (num_trials * num_pages);

    printf("%.2f\n", average_time_ns);

    free((void*)array);
    return 0;
}


/**********
 * OUTPUT - Q3
 ********** 
./run_experiments.sh
Pages, AverageTimeNS
1, 23.55
2, 13.82
4, 8.79
8, 7.27
16, 6.84
32, 6.41
64, 6.28
128, 6.15
256, 6.17
512, 6.41
1024, 6.34
2048, 6.57
4096, 9.57
 */