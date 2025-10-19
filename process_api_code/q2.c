/**
 * Write a program that opens a file (with the open() system call)
 * and then calls fork()to create a new process. Can both the child
 * and parent access the file descriptor returned by open()? What
 * happens when they are writing to the file concurrently, i.e., at the
 * same time?
 * 
 * Answers:
 * - Both child and parent can access the file descriptor
 * - When both child and parent write to the file concurrently, 
 *   the outcome is a race-condition where the order of writes is 
 *   non-determinitic
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {

    printf("hello world (pid:%d)\n", (int) getpid());

    const char* filename = "example.txt";

    // Open the file for writing. Create it if it doesn't exist, or truncate it if it does.
    // O_WRONLY: Open for writing only.
    // O_CREAT: Create the file if it does not exist.
    // O_TRUNC: Truncate the file to zero length if it exists.
    // 0644: File permissions (read/write for owner, read for group and others). Read(4) + Write(2) + Execute(1)
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    printf("File %s opened successfully with file descriptor: %d\n", filename, fd);

    pid_t childPid = fork();
    if (childPid < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } else if (childPid == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d) with fd=%d\n", (int) getpid(), fd);
        
        const char *data_to_write = "Hello, world! - by child\n";
        ssize_t bytes_written;

        bytes_written = write(fd, data_to_write, strlen(data_to_write));

        if (bytes_written == -1) {
            perror("Error writing to file");
            close(fd); // Close the file descriptor before exiting
            exit(EXIT_FAILURE);
        } else if (bytes_written != strlen(data_to_write)) {
            fprintf(stderr, "Warning: Not all data was written to the file.\n");
        } else {
            printf("Child successfully wrote %zd bytes to %s\n", bytes_written, filename);
        }

    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d) with fd=%d\n", childPid, (int) getpid(), fd);
        
        const char *data_to_write = "Hello, world! - by parent\n";
        ssize_t bytes_written;

        bytes_written = write(fd, data_to_write, strlen(data_to_write));

        if (bytes_written == -1) {
            perror("Error writing to file");
            close(fd); // Close the file descriptor before exiting
            exit(EXIT_FAILURE);
        } else if (bytes_written != strlen(data_to_write)) {
            fprintf(stderr, "Warning: Not all data was written to the file.\n");
        } else {
            printf("Parent successfully wrote %zd bytes to %s\n", bytes_written, filename);
        }
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/**********
 * OUTPUT
 **********
 * hello world (pid:86265)
 * File example.txt opened successfully with file descriptor: 3
 * hello, I am parent of 86266 (pid:86265) with fd=3
 * Parent successfully wrote 26 bytes to example.txt
 * hello, I am child (pid:86266) with fd=3
 * Child successfully wrote 25 bytes to example.txt
 */ 