// libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdbool.h>

// global const and vars
const unsigned int REFILL_SIZE = 5;
const unsigned int MAX_REFILLS = 5;
unsigned int currPotServings;
unsigned int currPotRefills;

// semaphore
sem_t studentMtx;
sem_t emptyPot;
sem_t fullPot;

// validate function
void validate(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./main <number of students>");
        exit(1);
    }

    if (atoi(argv[1]) < 3 || atoi(argv[1]) > 20)
    {
        printf("Number of students must be between 3 and 20");
        exit(1);
    }
}

/*putServingsInPot()
◦ update currPotServings by REFILL_SIZE
◦ increment potReFills
◦ display pot refilled message (see example)
◦ wait a random amount of time (while pot is re-filled and re-heated)
▪ usleep(rand() % 500000)

*/
void putServingsInPot()
{
    currPotServings += REFILL_SIZE;
    currPotRefills++;
    printf("\033[0;31mOK, fine, here are some more Ramen Noodles (5)...\033[0m\n");
    usleep(rand() % 500000);
}

/*studentEats()
◦ display student eats message with student number
 ◦ waits a random amount of time (while student eats)
▪ usleep(rand() % 1000000)
*/
void studentEats(int studentNumber)
{
    printf("\033[0;32mStudent %d eating, yum...\033[0m\n", studentNumber);
    usleep(rand() % 1000000);
}

/*getServingFromPot()
◦ decrements current pot servings
◦ wait a random amount of time (to get a serving)
▪ usleep(rand() % 1000);
 */
void getServingFromPot()
{
    currPotServings--;
    usleep(rand() % 1000);
}

/*
Constrain: •if the pot is empty then call putServingsInPot()
count the number of times the pot has been re-filled.
When the pot has been re-filled MAX_REFILLS times
and make sure that all threads pass through all the sem_wait() calls ,
then terminate function
The RA() function will perform the following actions:
while true
  P(emptyPot) -> wait
  putServingsInPot()
  V(fullPot) ->post
 */
void *RA(void *arg)
{
    while (true)
    {
        sem_wait(&emptyPot);
        putServingsInPot();
        sem_post(&fullPot);

        // check to see whether it max or not
        if (currPotRefills == MAX_REFILLS)
        {
            printf("\033[0;31mHey, this is the last of the Ramen Noodles...\033[0m\n");
            return NULL;
        }
    }
    return NULL;
}

/*Constrains:
if pot is empty -> call RA to refill the pot and wait for it to be fullPot
if not empty -> call getServingsFromPot()
count the number of times the pot has been re-filled.
When the pot has been re-filled MAX_REFILLS times, terminate function
The hungryStudents() function should perform the following actions.
  while true
    P(studentMtx)
        if currPotServings == 0
            V(emptyPot)
            P(fullPot)
        getServingFromPot()
    V(studentMtx)
    studentEats(studentNumber)
 */
void *hungryStudents(void *arg)
{
    // get student id
    int studentNumber = (uintptr_t)arg;

    while (true)
    {
        sem_wait(&studentMtx);

        if (currPotServings == 0)
        {
            sem_post(&emptyPot);
            sem_wait(&fullPot);
        }
        else
            getServingFromPot();

        sem_post(&studentMtx);

        // if still have foods -> serve
        if (currPotServings != 0)
            studentEats(studentNumber);

        // if not and reach max refills -> terminate
        if (currPotRefills == MAX_REFILLS && currPotServings == 0)
        {
            // have full pot ready
            sem_post(&fullPot);
            return NULL;
        }
    }
    return NULL;
}

/**The main() function should perform the following actions:
•Get and validate student count
◦must be between 3 and 20 (inclusive)
◦An array for threads must be used
▪Thread array must be dynamically allocated (i.e., use malloc()).
•Initialize semaphores
◦the student semaphore initialized to 1
◦the empty pot and fill pot semaphores initialized to 0
•Create one RA thread
•Create student count student threads
•Wait for the appropriate threads to complete
*/

int main(int argc, char *argv[])
{
    // validate arguments
    validate(argc, argv);
    // convert for studentCount
    int studentCount = atoi(argv[1]);
    // create threads array and RA thread
    pthread_t *studentThreads = (pthread_t *)malloc(sizeof(pthread_t) * studentCount);
    pthread_t raThread;

    // init semaphores
    sem_init(&studentMtx, 0, 1);
    sem_init(&emptyPot, 0, 0);
    sem_init(&fullPot, 0, 0);

    // header
    printf("Hungry Students\n");
    printf("  Student Count: %d\n", studentCount);
    printf("  Refill Count: %d\n", REFILL_SIZE);

    // create RA thread
    pthread_create(&raThread, NULL, &RA, NULL);

    // create array of student threads
    for (int i = 0; i < studentCount; i++)
        // also convert int -> void*
        pthread_create(&studentThreads[i], NULL, &hungryStudents, (void *)(uintptr_t)i);

    // join RA thread
    pthread_join(raThread, NULL);

    // join array of student threads
    for (int i = 0; i < studentCount; i++)
        pthread_join(studentThreads[i], NULL);

    // destroy all and clean up
    sem_destroy(&studentMtx);
    sem_destroy(&emptyPot);
    sem_destroy(&fullPot);
    free(studentThreads);
    printf("\nGame over, thank you for playing.\n");

    return 0;
}
