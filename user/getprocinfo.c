#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"

char *get_state_name(int state)
{
    switch (state) {
    case 0:
        return "UNUSED";
    case 1:
        return "USED";
    case 2:
        return "SLEEPING";
    case 3:
        return "RUNNABLE";
    case 4:
        return "RUNNING";
    case 5:
        return "ZOMBIE";
    default:
        return "UNKNOWN";
    }
}

// Helper function to convert flag to state code.
int get_state_from_flag(char *flag)
{
    if (strcmp(flag, "-r") == 0)
        return 4; // RUNNING
    if (strcmp(flag, "-s") == 0)
        return 2; // SLEEPING
    if (strcmp(flag, "-u") == 0)
        return 0; // UNUSED
    if (strcmp(flag, "-z") == 0)
        return 5; // ZOMBIE
    if (strcmp(flag, "-n") == 0)
        return 3; // RUNNABLE
    return -1;
}

static void
print_header(void)
{
    printf("PID\tSTATE\tSIZE\tPARENT\tPRIORITY\n");
    printf("----------------------------------------\n");
}

int main(int argc, char *argv[])
{
    struct procinfo info;

    if (argc == 1) {
        print_header();

        for (int i = 1; i < NPROC; i++) {
            if (getprocinfo(i, &info) == 0) {
                printf("%d\t%s\t%d\t%d\t%d\n", info.pid, get_state_name(info.state),
                             info.sz, info.parent_pid, info.priority);
            }
        }
        exit(0);
    }

    if (argc == 2) {
        int state_filter = get_state_from_flag(argv[1]);

        if (state_filter != -1) {
            print_header();

            for (int i = 1; i < NPROC; i++) {
                if (getprocinfo(i, &info) == 0 && info.state == state_filter) {
                    printf("%d\t%s\t%d\t%d\t%d\n", info.pid,
                                 get_state_name(info.state), info.sz, info.parent_pid,
                                 info.priority);
                }
            }
            exit(0);
        } else {
            int pid = atoi(argv[1]);

            if (pid <= 0) {
                printf("Invalid pid\n");
                exit(1);
            }

            if (getprocinfo(pid, &info) == 0) {
                print_header();

                printf("%d\t%s\t%d\t%d\t%d\n", info.pid, get_state_name(info.state),
                             info.sz, info.parent_pid, info.priority);
            } else {
                printf("Process not found\n");
            }
            exit(0);
        }
    }

    printf("Usage:\n");
    printf("  getprocinfo        (show all)\n");
    printf("  getprocinfo -r     (show only RUNNING processes)\n");
    printf("  getprocinfo <pid>  (specific process)\n");

    exit(0);
}
