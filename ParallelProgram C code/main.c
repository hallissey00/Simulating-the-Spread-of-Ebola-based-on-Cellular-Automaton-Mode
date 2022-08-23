#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <memory.h>
#include "timer.h"
#include <pthread.h>
#include "header.h"

int main() {
    long long thread;
    pthread_t* thread_handles;
    thread_handles = malloc(thread_count*sizeof(pthread_t));

    int countRandom = SIZE / 5;
    int random[countRandom];
    double start, finish, elapsed;
    time_t t;
    srand((unsigned) time(&t));

    //init files to write the json and gnuplot data to, and create if not exists
    initFiles();

    // generate first world with <countRandom> numbers of infected
    for (int i = 0; i < countRandom; i++) {
        random[i] = rand() % (SIZE * SIZE);
    }
    int counter = 0;
    bool infectedFound = false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < countRandom; k++) {
                if (random[k] == counter) {
                    infectedFound = true;
                }
            }
            firstGrid[i][j] = infectedFound ? 'i' : '.';
            infectedFound = false;
            counter++;
        }
    }
    //TIMER START
    GET_TIME(start);
    pthread_mutex_init(&mutex,0);

    //create thread
    for(thread=0;thread<thread_count;thread++)
        pthread_create(&thread_handles[thread],NULL,Thread_worker,(void*)thread);
    //------------------------------------------------------------------------------------------
    //join threads
    for(thread=0;thread<thread_count;thread++)
        pthread_join(thread_handles[thread],NULL);
    //------------------------------------------------------------------------------------------
    pthread_mutex_destroy(&mutex);
    //TIMER STOPS
    GET_TIME(finish)
    elapsed = finish - start;
    //Print the time
    printf("Elapsed time = %e seconds using %d Threads\n",elapsed,thread_count);

    // close the filestreams
    closeFiles();
}
