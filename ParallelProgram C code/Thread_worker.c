#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <memory.h>
#include "timer.h"
#include <pthread.h>
#include "header.h"

void* Thread_worker(void* rank){
    char tempGrid[SIZE][SIZE];
    long my_rank=(long)rank;
    int i = 0;

    for (i; i < generations; ++i) {
      //If the thread is not finished, run Thread_checkCells method
        if (finished[my_rank]!=1) {
              Thread_checkCells(my_rank);
              finishedCurrent = 0;
        }

       /* while(finished[my_rank] != 1){
            printf("%d %d %d %d \n", finished[0], finished[1], finished[2], finished[3]);
        }
        */
	
	//If all threads finished
	//Make sure to assign as many finished[x] checks as there are threads
	
        if(finished[0]==1 && finished[1]==1 && finished[2]==1 && finished[3]==1){
            //printf("*All have finished, I was the last * Thread: %d Generation:%d\n",my_rank,i);
            //printf("*Now print the current, swap memory of grids and start with next generation* Thread: %d Generation:%d\n",my_rank,i);

	    //reset thread finish array
            memset(finished, 0, sizeof(finished));
	    
            //Critical section
	    //Dont want more than one thread trying to swap grids
            pthread_mutex_lock(&mutex);
            //swapping the current grid and the nextGrid --> NextGrid becomes the current grid for Next Generation
            memcpy(tempGrid, nextGrid, SIZE * SIZE * sizeof(char));
            memcpy(firstGrid, tempGrid, SIZE * SIZE * sizeof(char));

            pthread_mutex_unlock(&mutex);
            //------------------------------------------------------------------------------
            currentGeneration = i;
            printGeneration(i, firstGrid);
            finishedCurrent = 1;


        }
        /*
        else{
            printf("Waiting for other to finish, Thread: %d\n",my_rank);
            while(finishedCurrent != 1);
            printf("Starting next %d\n", my_rank);

        }
        */
    }

}

