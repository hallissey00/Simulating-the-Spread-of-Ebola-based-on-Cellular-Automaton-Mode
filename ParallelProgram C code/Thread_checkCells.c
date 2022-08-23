#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <memory.h>
#include "timer.h"
#include <pthread.h>
#include "header.h"

void Thread_checkCells(long my_rank){
    long long i;
    long long my_n = SIZE/thread_count;
    long long my_first_i = my_n*my_rank;
    long long my_last_i = my_first_i + my_n;

    bool newInfected = false;
    int randomInfected;
    int chanceToInfect = 0;
    //Splitting up row evenly so each thread gets the same amount of rows
       for (int row = my_first_i; row < my_last_i; row++) {
           for (int col = 0; col < SIZE; col++) {
               if (firstGrid[row][col] == 'E' && currentGeneration % durationExposed_generations == 0) {
                   nextGrid[row][col] = 'i';
                   continue;
               }

               if (firstGrid[row][col] == 'i' && currentGeneration % 3 == 0) {
                   randomInfected = rand() % (100);

                   if (randomInfected <= randomFactorToRecover_max) {
                       nextGrid[row][col] = 'R';
                   } else {
                       nextGrid[row][col] = 'X';
                   }
                   continue;
               }

               if (firstGrid[row][col] != '.') {
                   continue;
               }

               for (int nrow = -1; nrow < 2; nrow++) {
                   for (int ncol = -1; ncol < 2; ncol++) {
                       // if cell is on the border, don't check outside the border
                       if ((row == 0 && nrow == -1) || (row == SIZE - 1 && nrow == 1) || (col == 0 && ncol == -1) ||
                           (col == SIZE - 1 && ncol == 1)) {
                           continue;
                       }
                       // continue if cell is the middle cell itself
                       if (ncol == 0 && nrow == 0) {
                           continue;
                       }
                       // if neighbour cell is infected and the cell itself is not infected
                       if (firstGrid[row + nrow][col + ncol] == 'i' && firstGrid[row][col] != 'i') {
                           chanceToInfect += factorInfectedNeighbour;
                       }
                       // if neighbour cell is dead and the cell itself is susceptible
                       if (firstGrid[row + nrow][col + ncol] == 'X' && firstGrid[row][col] != 'X') {
                           chanceToInfect += factorDeadNeighbour;
                       }
                   }
               }

               randomInfected = rand() % (randomFactorToInfect_max);

               if (chanceToInfect > 0 && chanceToInfect + randomInfected > riskToInfected_percent) {
                   newInfected = true;
               }
               //pthread_mutex_lock(&mutex);
               nextGrid[row][col] = newInfected ? 'E' : firstGrid[row][col];
               //pthread_mutex_unlock(&mutex);

               newInfected = false;
               chanceToInfect = 0;
           }
       }
       //When the thread finishes, it updates the finished array 
       finished[my_rank] = 1;
   }
