#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{

    // take two command line argument “-c <int>” and “-i <int>”,
    // specifying the number of CPU bound processes and I/O bound processes, respectively.
    if (argc != 5)
    {
        printf("Usage: schTest -c <int> -i <int>\n");
        exit(1);
    }

    // error check for -c and -i
    if (strcmp(argv[1], "-c") != 0 || strcmp(argv[3], "-i") != 0)
    {
        printf("Usage: schTest -c <int> -i <int>\n");
        exit(1);
    }

    // check to see if argv[2] and argv[4] are integers
    int cpu = atoi(argv[2]);
    int io = atoi(argv[4]);

    if (cpu < 0 || io < 0)
    {
        printf("Must be more than 0\n");
        exit(1);
    }

    unsigned int rTime = 0;
    unsigned int wTime = 0;
    int totRunTime = 0;
    int totWaitTime = 0;
    int max = cpu + io;

    // check bound of processes
    if (max > 60)
    {
        printf("Max number of processes is 60\n");
        exit(1);
    }

    // create a set of child using fork()
    // The children will be used to simulate both CPU-bound and I/O bound processes.
    // We will need to call wait for each child created.
    // Each process should print : printf("\nProcess %d finished", n);
    // Before the final exit() system call.

    // create cpu bound processes and io bound processes
    for (int i = 0; i < max; i++)
    {
        int pid = fork();
        if (pid < 0)
        {
            printf("fork failed\n");
            exit(1);
        }
        else if (pid == 0)
        {
            // cpu bound = lower priority
            // io bound = higher priority
            // need to make sure the io bound has higher priority by determine the time slice
            // cpu bound processes
            if (i < cpu)
            {
                for (int j = 0; j < 1000000000; j++)
                {
                    // do nothing
                }
                printf("Process %d finished\n", i);
                exit(0);
            }
            // io bound processes
            else
            {
                sleep(200);
                printf("Process %d finished\n", i);
                exit(0);
            }
        }
    }

    for (int n = max; n > 0; n--)
    {
        // printf("\nProcess %d: run time = %d, wait time = %d", n, rTime, wTime);
        if (waitStats(0, &rTime, &wTime) >= 0)
        {
            totRunTime += rTime;
            totWaitTime += wTime;
        }
    }

    // print out the average run time and average wait time
    printf("\nAverage rtime  %d, wtime  %d\n", totRunTime / max, totWaitTime / max);

    exit(0);
}