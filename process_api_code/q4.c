/**
 * Write a program that calls fork() and then calls some form of
 * exec()to run the program /bin/ls. See if you can try all of the
 * variants of exec(), including (on Linux) execl(), execle(),
 * execlp(), execv(), execvp(), and execvpe(). Why do
 * you think there are so many variants of the same basic call?
 * 
 * Answers:
 * - To provide flexibility on how the user wants to use exec
 * 
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
        char *const args[] = {"/bin/ls", "-l", NULL}; // 
        char *const path = "/bin/ls"; // Path to the executable
        char *envp[] = { "PATH=/bin:/usr/bin", NULL }; // Environment variables for the new process

        // int rc = execl(path, "/bin/ls", "-l", NULL);
        // int rc = execle(path, "/bin/ls", "-l", NULL, envp);
        // int rc = execlp("ls", "ls", "-l", NULL);

        int rc = execv(path, args);
        // int rc = execve(path, args, envp);
        // int rc = execvp("ls", args);

        if(rc == -1) {
            perror("exec failed");
            exit(EXIT_FAILURE);
        }

    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n", childPid, (int) getpid());
        
        int status;
        pid_t terminatedPid = waitpid(childPid, &status, 0);
        if (terminatedPid == -1) {
            perror("waitpid failed");
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
 * hello world (pid:92301)
 * hello, I am parent of 92302 (pid:92301)
 * hello, I am child (pid:92302)
 * total 352
 * -rw-r--r--@  1 addyvenkat  staff   2094 Oct 18 21:03 cmake_install.cmake
 * -rw-r--r--@  1 addyvenkat  staff  14518 Oct 18 16:16 CMakeCache.txt
 * drwxr-xr-x@ 16 addyvenkat  staff    512 Oct 18 21:03 CMakeFiles
 * -rw-r--r--@  1 addyvenkat  staff     51 Oct 18 16:29 example.txt
 * -rw-r--r--@  1 addyvenkat  staff   8091 Oct 18 21:03 Makefile
 * -rwxr-xr-x@  1 addyvenkat  staff  33648 Oct 18 21:02 q1
 * -rwxr-xr-x@  1 addyvenkat  staff  33856 Oct 18 21:02 q2
 * -rwxr-xr-x@  1 addyvenkat  staff  33680 Oct 18 21:02 q3
 * -rwxr-xr-x@  1 addyvenkat  staff  33904 Oct 18 21:03 q4
 * Child exited normally with status: 0
 */