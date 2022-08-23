#include "header.h"
#include <stdio.h>

int currentGeneration = 0;
char firstGrid[SIZE][SIZE];
char nextGrid[SIZE][SIZE];
int MAX_THREADS=64;
long thread_count=THREADNUM;
//Assign as many zero as there are threads
int finished[THREADNUM] = {0,0,0,0};
int finishedCurrent = 0;
pthread_mutex_t mutex;
int riskToInfected_percent = 65;
int durationExposed_generations = 3;
int generations = 1000;
int randomFactorToInfect_max = 58;
int randomFactorToRecover_max = 50;
int factorInfectedNeighbour = 10;
int factorDeadNeighbour = 9;
bool printConsole = false;
FILE *json, *gnuplot;
int SEIRD[5];
