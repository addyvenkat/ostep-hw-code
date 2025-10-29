/**
 * Create a little program that uses a certain amount of memory,
 * called memory-user.c. This program should take one command-
 * line argument: the number of megabytes of memory it will use.
 * When run, it should allocate an array, and constantly stream through
 * the array, touching each entry. The program should do this indefi-
 * nitely, or, perhaps, for a certain amount of time also specified at the
 * command line.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // For time measurement
#include <unistd.h>

int main(int argc, char* argv[]) {

    printf("hello world (pid:%d)\n", (int) getpid());
    if(argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <megabytes_to_use> [seconds_to_run]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int megabytes = atoi(argv[1]);
    if(megabytes <= 0) {
        fprintf(stderr, "Error: Megabytes must be positive integer.\n");
        return EXIT_FAILURE;
    }

    size_t bytes_to_allocate = megabytes * 1024 * 1024;
    int* array = (int* )malloc(bytes_to_allocate);

    if(array == NULL) {
        fprintf(stderr, "Error: Could not allocate %d MB of memory.\n", megabytes);
        return EXIT_FAILURE;
    }

    printf("Allocated %d MB of memory. Streaming through the array...\n", megabytes);

    time_t start_time = time(NULL);
    int seconds_to_run = -1; // Default is infinite

    if(argc == 3) {
        seconds_to_run = atoi(argv[2]);
        if(seconds_to_run <= 0) {
            fprintf(stderr, "Error: Seconds to run must be positive integer.\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    int num_elements = bytes_to_allocate/sizeof(int);
    int i = 0;

    while (1) {
        // Access each element to ensure it's "touched" and potentially brought into cache/physical memory
        array[i % num_elements] = i;

        i++;

        if (seconds_to_run != -1 && (time(NULL) - start_time >= seconds_to_run)) {
            printf("Time limit reached. Exiting.\n");
            break;
        }
    }

    free(array);
    printf("Memory freed. Exiting.\n");

    return 0;
}