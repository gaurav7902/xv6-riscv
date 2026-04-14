#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if(argc <= 1){
        printf("Error: Please provide the max number of children.\n");
        printf("Usage: testforklimit <limit>\n");
        exit(1);
    }

    int limit = atoi(argv[1]);
    if(limit < 0){
        printf("Error: limit must be non-negative.\n");
        exit(1);
    }

    printf("Setting fork limit to %d...\n", limit);
    fork_with_limit(limit);

    int attempts = limit + 2;
    int success = 0;
    int failed = 0;

    for(int i = 1; i <= attempts; i++) {
        int pid = fork();
        
        if (pid < 0) {
            printf("Fork %d failed! Limit of %d reached.\n", i, limit);
            failed++;
        } else if (pid == 0) {
            pause(20);
            exit(0); 
        } else {
            success++;
            printf("Fork %d successful! Child PID: %d\n", i, pid);
        }
    }

    for(int i = 0; i < success; i++)
        wait(0);

    printf("Summary: success=%d failed=%d\n", success, failed);
    
    exit(0);
}