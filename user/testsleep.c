#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if(argc <= 1){
        printf("Error: Please provide the number of ticks to sleep.\n");
        printf("Usage: testsleep <ticks>\n");
        exit(1);
    }

    int ticks = atoi(argv[1]);
    if(ticks < 0){
        printf("Error: ticks must be non-negative.\n");
        exit(1);
    }

    printf("Going to sleep for %d ticks...\n", ticks);
    
    sleep_for(ticks); 
    
    printf("Woke up!\n");
    
    exit(0);
}