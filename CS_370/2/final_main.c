#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/* Global storage for arguments */
struct
{
    int threads;
    int limit;
} args;

// global declaration
// global declaration
pthread_mutex_t mutexLock;   // mutex variable for array
pthread_mutex_t lockCounter; // mutex to count nums

int *Array = NULL;      // global arr
const int BLOCK = 1000; // block size
int narcs = 0;          // narcs number
int range = 0;          // counter for 1000x

/**
 * @brief count how many digits given number have
 *
 * @param number - number to check
 * @return int
 */
int countDigits(int number)
{
    int count = 0;
    // check until none of the digits can be count
    while (number != 0)
    {
        // split the number into digits
        number /= 10;
        count++;
    }
    return count;
}

/**
    @brief check to see whether the number is narissistic or not
/// @param number
/// @return true or false
*/
bool isNumber(int number)
{
    // check if number is narissistic or not
    // obtain digit for sum
    int digits = countDigits(number);
    // copy the number to split number
    int copy = number;
    int rem = 0;
    int sum = 0;
    // loop until number can't be split
    while (copy != 0)
    {
        // calculate the rem and sum
        rem = copy % 10;
        sum = sum + pow(rem, digits);
        // split number
        copy = copy / 10;
    }

    // check for narNum

    return (sum == number) ? true : false;
}

/**
 * @brief check arguments
 *
 * @param argc
 * @param argv
 */
void checkArguments(int argc, char *argv[])
{
    // if not enough arguments
    if (argc != 5)
    {
        printf("Usage: ./narCount -th <threadCount> -lm <limitValue>\n");
        exit(1);
    }
    else
    {

        // check string or spcifier
        if (strcmp(argv[1], "-th") == 0)
        {
            char *c;
            // call function to convert
            long int threadCount = strtol(argv[2], &c, 10);

            // err case
            if (argv[2] == c || '\0' != *c)
            {
                printf("Error, invalid thread count value.\n");
                exit(1);
            }

            else if (threadCount < 1 || threadCount > 30)
            {
                printf("Error, thread count must be >= 1 and <= 30.\n");
                exit(1);
            }
        }
        else
        {
            printf("Error, invalid thread count specifier.\n");
            exit(1);
        }

        // same thing for above
        if (strcmp(argv[3], "-lm") == 0)
        {
            char *c;
            long int limitValue = strtol(argv[4], &c, 10);

            if (argv[4] == c || '\0' != *c)
            {
                printf("Error, invalid limit value.\n");
                exit(1);
            }

            else if (limitValue < 100)
            {
                printf("Error, limit must be > 100.\n");
                exit(1);
            }
        }
        else
        {
            printf("Error, invalid limit specifier.\n");
            exit(1);
        }
    }
}

/**
 * @brief check number + add into array
 *
 * @param number
 */
void found(int number)
{
    // call function to check for narNum
    bool narNum = isNumber(number);

    if (narNum == true)
    {
        // lock mutex
        pthread_mutex_lock(&mutexLock);
        // initialize array
        narcs++;
        Array = (int *)realloc(Array, narcs * sizeof(int));
        // add number into array
        Array[narcs - 1] = number;
        // unlock mutex
        pthread_mutex_unlock(&mutexLock);
    }
}

/**
 * @brief check nars num in range
 *
 * @param number
 */
void narcRange(int start, int end)
{
    // loop range to cehck
    for (int i = start; i < end; i++)
    {
        found(i);
    }
}

/**
 * @brief thread function to deal with multithread (f this function)
 *
 * @param arg
 * @return void*
 */
void *do_process(void *arg)
{
    // index for loop
    int i = 0;
    // loop until end of limit

    // access limit -> lock it
    pthread_mutex_lock(&lockCounter);
    int max = args.limit;
    pthread_mutex_unlock(&lockCounter);

    while (i <= max)
    {

        // check to see whether pass limit or not
        if (range <= max)
        {
            // lock and unlock due to write range
            pthread_mutex_lock(&lockCounter);
            // set up localCount/start
            // update range/end for next thread
            // ex: thread 1: localCount/start = 0,  range/end = 1000
            // thread 2: localCount/start = 1000, range/end = 2000
            int localCount = range;
            range += BLOCK;
            pthread_mutex_unlock(&lockCounter);

            // call function to check in range
            // NOTE: localCount + BLOCK == range += BLOCK before line 211
            narcRange(localCount, localCount + BLOCK);
        }
        // increment counter/check next num
        i++;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    // validate arguments
    checkArguments(argc, argv);

    // set up thread & limit
    int threads = atoi(argv[2]);
    int limit = atoi(argv[4]);

    // print header information
    printf("CS 370 - Project #2\nNarcissistic Numbers Program\n\n");

    // find hardware cores of machine
    int processors = sysconf(_SC_NPROCESSORS_ONLN);

    printf("Hardware cores: %d\n", processors);
    printf("Thread Count: %d\n", threads);
    printf("Numbers Limit: %d\n", limit);
    printf("\nPlease wait.Running...\n\n");

    // check to see if mutex created or not
    if (pthread_mutex_init(&mutexLock, NULL) || pthread_mutex_init(&lockCounter, NULL))
        perror("Mutex initialization failed.\n");

    // print out header
    printf("Narcissistic Numbers\n");

    // pass validate -> set up args
    pthread_mutex_lock(&mutexLock);
    args.limit = limit;
    args.threads = threads;
    pthread_mutex_unlock(&mutexLock);

    // array of threads
    pthread_t threadArray[threads];

    // create threads
    for (int i = 0; i < threads; i++)
    {
        if (pthread_create(&threadArray[i], NULL, &do_process, NULL) != 0)
        {
            perror("Thread creation failed.\n");
            exit(1);
        };
    }

    // koin them
    for (int i = 0; i < threads; i++)
    {
        if (pthread_join(threadArray[i], NULL) != 0)
        {
            perror("Thread join failed.\n");
            exit(1);
        }
    }

    // print array result
    for (int i = 0; i < narcs; i++)
    {
        printf("     %d\n", Array[i]);
    }

    // deallocate the array
    free(Array);

    printf("\n");
    printf("Count of Narissistic numbers from 0 to %d is %d\n", args.limit, narcs);
    return 0;
}