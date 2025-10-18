/**
 * Write a program that calls fork(). Before calling fork(), have the
 * main process access a variable (e.g., x) and set its value to some-
 * thing (e.g., 100). What value is the variable in the child process?
 * What happens to the variable when both the child and parent change
 * the value of x?
 */

 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>

int main(int argc, char *argv[]) {

    printf("hello world (pid:%d)\n", (int) getpid());
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d) with x=%d\n", (int) getpid(), x);
    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d) with x=%d\n", rc, (int) getpid(), x);
    }
    return 0;
}

/**********
 * OUTPUT
 **********
 * hello world (pid:83594)
 * hello, I am parent of 83595 (pid:83594) with x=100
 * hello, I am child (pid:83595) with x=100
 */