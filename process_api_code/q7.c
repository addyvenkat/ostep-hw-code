/**
 * Write a program that creates a child process, and then in the child
 * closes standard output (STDOUT_FILENO). What happens if the child
 * calls printf()to print some output after closing the descriptor?
 * 
 * Answers:
 * - printf() after closing stdout leads to error : Bad file descriptor
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    printf("hello world (pid:%d)\n", (int) getpid());
    pid_t childPid = fork();
    if (childPid < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } else if (childPid == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());

        if (close(STDOUT_FILENO) == -1) {
            perror("Error closing stdout");
            exit(EXIT_FAILURE);
        }

        int rc = printf("Child writing to stdout after closing it\n");
        if(rc == -1) {
            perror("Expected error writing to stdout after close");
            exit(EXIT_SUCCESS);
        }

    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n", childPid, (int) getpid());
        
        int status;
        pid_t terminatedPid = waitpid(childPid, &status, 0);
        if (terminatedPid == -1) {
            perror("waitpid failed in parent");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("Child exited normally with status: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child terminated by signal: %d\n", WTERMSIG(status));
        }

    }
    return 0;
}

/**********
 * OUTPUT
 **********
 * hello world (pid:94186)
 * hello, I am parent of 94187 (pid:94186)
 * hello, I am child (pid:94187)
 * Expected error writing to stdout after close: Bad file descriptor
 * Child exited normally with status: 0
 */