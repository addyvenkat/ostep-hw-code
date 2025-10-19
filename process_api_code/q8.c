/**
 * Write a program that creates two children, and connects the standard
 * output of one to the standard input of the other, using the
 * pipe()system call.
 */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    printf("hello world (pid:%d)\n", (int) getpid());

    int pipefd[2]; // pipefd[0] is for reading, pipefd[1] is for writing
    
    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t readChildPid = fork();
    if (readChildPid < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } 
    else if (readChildPid == 0) {
        // child (new process)
        printf("hello, I am read-only child (pid:%d)\n", (int) getpid());

        // Close the pipe that involves writing
        if (close(pipefd[1]) == -1) {
            perror("Error closing pipefd[1] in read-only child");
            exit(EXIT_FAILURE);
        }

        // Redirect standard input to the read end of the pipe
        if(dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2 failed in read-only child");
            exit(EXIT_FAILURE);
        }

        // Close the original read end of the pipe
        if (close(pipefd[0]) == -1) {
            perror("Error closing stale pipefd[0] in read-only child");
            exit(EXIT_FAILURE);
        }

        // Command that reads from standard input
        execlp("wc", "wc", "-l", NULL); // Word count reading lines
        perror("execlp wc"); // Should not reach here
        exit(EXIT_FAILURE);
    } 
    
    pid_t writeChildPid = fork();
    if (writeChildPid < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } 
    else if (writeChildPid == 0) {
        // child (new process)
        printf("hello, I am write-only child (pid:%d)\n", (int) getpid());

        // Close the pipe that involves reading
        if (close(pipefd[0]) == -1) {
            perror("Error closing pipefd[0] in write-only child");
            exit(EXIT_FAILURE);
        }

        // Redirect standard output to the write end of the pipe
        if(dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2 failed in write-only child");
            exit(EXIT_FAILURE);
        }

        // Close the original write end of the pipe
        if (close(pipefd[1]) == -1) {
            perror("Error closing stale pipefd[1] in write-only child");
            exit(EXIT_FAILURE);
        }

        // Command that writes to standard output
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls"); // Should not reach here
        exit(EXIT_FAILURE);
    }
    
    // parent goes down this path (original process)
    printf("hello, I am the parent (pid:%d)\n", (int) getpid());
    
    // Parent doesn't use the pipes
    if (close(pipefd[0]) == -1) {
        perror("Error closing pipefd[0] in parent");
        exit(EXIT_FAILURE);
    }
    if (close(pipefd[1]) == -1) {
        perror("Error closing pipefd[1] in parent");
        exit(EXIT_FAILURE);
    }

    // Wait for both child processes to end
    int status;
    pid_t terminatedPid = waitpid(writeChildPid, &status, 0);
    if (terminatedPid == -1) {
        perror("waitpid failed in parent");
        exit(EXIT_FAILURE);
    }

    if (WIFEXITED(status)) {
        printf("Write-only child exited normally with status: %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Write-only child terminated by signal: %d\n", WTERMSIG(status));
    }

    terminatedPid = waitpid(readChildPid, &status, 0);
    if (terminatedPid == -1) {
        perror("waitpid failed in parent");
        exit(EXIT_FAILURE);
    }

    if (WIFEXITED(status)) {
        printf("Read-only child exited normally with status: %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Read-only child terminated by signal: %d\n", WTERMSIG(status));
    }

    return 0;
}

/**********
 * OUTPUT
 **********
 * hello world (pid:97220)
 * hello, I am read-only child (pid:97221)
 * hello, I am the parent (pid:97220)
 * hello, I am write-only child (pid:97222)
 *       14
 * Write-only child exited normally with status: 0
 * Read-only child exited normally with status: 0
 */