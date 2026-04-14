#include "kernel/types.h"
#include "user/user.h"

void burn_cpu() {
    volatile int dummy = 0;
    for(int i = 0; i < 50000000; i++) {
        dummy = dummy + 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Error: Please provide priorities for 3 children.\n");
        printf("Usage: testpriority <priority1> <priority2> <priority3>\n");
        exit(1);
    }

    int prio1 = atoi(argv[1]);
    int prio2 = atoi(argv[2]);
    int prio3 = atoi(argv[3]);

    int pid1, pid2, pid3;

    printf("Starting Priority Test with priorities: %d, %d, %d\n", prio1, prio2, prio3);

    pid1 = fork();
    if (pid1 < 0) {
        printf("fork failed for child 1\n");
        exit(1);
    }
    if (pid1 == 0) {
        set_priority(getpid(), prio1);
        burn_cpu();
        printf("Child 1 (Priority %d) finished!\n", prio1);
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0) {
        printf("fork failed for child 2\n");
        exit(1);
    }
    if (pid2 == 0) {
        set_priority(getpid(), prio2);
        burn_cpu();
        printf("Child 2 (Priority %d) finished!\n", prio2);
        exit(0);
    }

    pid3 = fork();
    if (pid3 < 0) {
        printf("fork failed for child 3\n");
        exit(1);
    }
    if (pid3 == 0) {
        set_priority(getpid(), prio3);
        burn_cpu();
        printf("Child 3 (Priority %d) finished!\n", prio3);
        exit(0);
    }

    wait(0); wait(0); wait(0);
    
    printf("All children finished.\n");
    exit(0);
}