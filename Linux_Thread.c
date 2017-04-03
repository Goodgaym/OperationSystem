#include<stdio.h>
#include<error.h>
#include<stdlib.h>
#include<string.h>
#include<sys/utsname.h>
#include<linux/sched.h>
#include<signal.h>

#define STACK_SIZE (1024 * 1024)
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE);} while (0)
static int childFunc(void *arg){
    struct utsname uts;

    if(sethostname(arg, strlen(arg)) == -1)
        errExit("sethostname");
    if(uname(&uts) == -1)
        errExit("uname");
    printF("uts.nodename in child: %s\n", uts.nodename);
    sleep(200);
    return 0;
}

int main(int argc, char *argv[]){
    char *stack;
    char *stackTop;
    pid_t pid;
    struct utsname uts;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <child-hostname>\n", argv[0]);
        exit(EXIT_SUCCESS);
    }
    stack = malloc(STACK_SIZE);
    if (stack == NULL)
        errExit("malloc");
    stackTop = stack + STACK_SIZE;
    pid = clone(childFunc, stackTop, CLONE_NEWUTS | SIGCHLD, argv[1]);
    if (pid == -1)
        errExit("clone");
    printf("clone() returned %ld\n", (long) pid);
    sleep(1);
    if (uname(&uts) == -1)
        errExit("uname");
    printf("uts.nodename in parent: %s\n", uts.nodename);
    if (waitpid(pid, NULL, 0) == -1)
        errExit("waitpid");
    printf("child has terminated\n");
    exit(EXIT_SUCCESS);
}