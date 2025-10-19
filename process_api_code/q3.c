/**
 * Write another program using fork(). The child process should
 * print “hello”; the parent process should print “goodbye”. You should
 * try to ensure that the child process always prints first; can you do
 * this without calling wait() in the parent?
 * 
 * Answers:
 * - Inducing delay to parent, so that child gets to print
 *   before parent does.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    pid_t childPid = fork();
    if (childPid < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    } else if (childPid == 0) {
        // child (new process)
        printf("Child (pid:%d) : Hello!\n", (int) getpid());
    } else {
        // parent goes down this path (original process)
        
        // inducing delay to ensure child prints first then parent
        sleep(1);
        
        printf("Parent of %d (pid:%d) : Goodbye!\n", childPid, (int) getpid());
    }
    return 0;
}

/**********
 * OUTPUT
 **********
 * hello world (pid:89598)
 * Child (pid:89599) : Hello!
 * Parent of 89599 (pid:89598) : Goodbye!
 */