/**
 * Write a slight modification of the previous program, this time us-
 * ing waitpid() instead of wait(). When would waitpid() be
 * useful?
 * 
 * Answers:
 * - When the parent needs to be blocked on a specific child process
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
 * hello world (pid:93594)
 * hello, I am parent of 93595 (pid:93594)
 * hello, I am child (pid:93595)
 * Child exited normally with status: 0
 */