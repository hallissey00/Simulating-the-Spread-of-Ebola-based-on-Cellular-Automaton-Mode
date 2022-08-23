#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define SIZE 1000
#define THREADNUM 4
extern char firstGrid[SIZE][SIZE];
extern char nextGrid[SIZE][SIZE];
extern int currentGeneration;
extern int MAX_THREADS;
extern long thread_count;
extern int finished[THREADNUM];
extern int finishedCurrent;
extern pthread_mutex_t mutex;
extern int riskToInfected_percent;
extern int durationExposed_generations;
extern int generations;
extern int randomFactorToInfect_max;
extern int randomFactorToRecover_max;
extern int factorInfectedNeighbour;
extern int factorDeadNeighbour;
extern bool printConsole;
extern FILE *json, *gnuplot;
extern int SEIRD[5];

void printGeneration(int gen, char currentGrid[][SIZE]);

void Thread_checkCells(long my_rank);

void* Thread_worker(void* rank);

void initFiles();

void closeFiles();
