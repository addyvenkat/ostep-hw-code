/**
 * Now write a program that uses wait()to wait for the child process
 * to finish in the parent. What does wait()return? What happens if
 * you use wait()in the child?
 * 
 * Answers:
 * - wait() : on success, returns the pid of the terminated child
 *            on failure, returns -1
 * 
 * - wait() in child: returns with status -1, doesn't block. If there is no child of child
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

        int status;
        pid_t terminatedPid = wait(&status);
        if (terminatedPid == -1) {
            perror("wait failed in child");
            exit(EXIT_FAILURE);
        }

    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n", childPid, (int) getpid());
        
        int status;
        pid_t terminatedPid = wait(&status);
        if (terminatedPid == -1) {
            perror("wait failed in parent");
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
 * hello world (pid:93169)
 * hello, I am parent of 93170 (pid:93169)
 * hello, I am child (pid:93170)
 * wait failed in child: No child processes
 * Child exited normally with status: 1
 */