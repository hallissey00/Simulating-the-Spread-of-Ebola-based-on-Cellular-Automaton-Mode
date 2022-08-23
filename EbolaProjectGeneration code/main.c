#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <memory.h>

#define SIZE 1000

void printGeneration(int gen, char currentGrid[][SIZE]);

void checkCells(char currentGrid[][SIZE], char nextGrid[][SIZE], int generation);

void initFiles();

void closeFiles();

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

int main() {
    char firstGrid[SIZE][SIZE];
    char nextGrid[SIZE][SIZE];
    int countRandom = SIZE / 5;
    int random[countRandom];
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

    char tempGrid[SIZE][SIZE];
    for (int generation = 0; generation <= generations; generation++) {
        checkCells(firstGrid, nextGrid, generation);
        fprintf(json, "    [ \n");
        printGeneration(generation, firstGrid);
        if (generation != generations) {
            fprintf(json, "], \n", generation);
        } else {
            fprintf(json, "] \n");
        }

        //swapping the current grid and the nextGrid --> NextGrid becomes the current grid for Next Generation
        memcpy(tempGrid, nextGrid, SIZE * SIZE * sizeof(char));
        memcpy(firstGrid, tempGrid, SIZE * SIZE * sizeof(char));
    }

    // close the filestreams
    closeFiles();
}

void checkCells(char currentGrid[][SIZE], char nextGrid[][SIZE], int generation) {
    bool newInfected = false;
    int randomInfected;
    int chanceToInfect = 0;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (currentGrid[row][col] == 'E' && generation % durationExposed_generations == 0) {
                nextGrid[row][col] = 'i';
                continue;
            }

            if (currentGrid[row][col] == 'i' && generation % 3 == 0) {
                randomInfected = rand() % (100);
                if (randomInfected <= randomFactorToRecover_max) {
                    nextGrid[row][col] = 'R';
                } else {
                    nextGrid[row][col] = 'X';
                }
                continue;
            }

            if (currentGrid[row][col] != '.') {
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
                    if (currentGrid[row + nrow][col + ncol] == 'i' && currentGrid[row][col] != 'i') {
                        chanceToInfect += factorInfectedNeighbour;
                    }
                    // if neighbour cell is dead and the cell itself is susceptible
                    if (currentGrid[row + nrow][col + ncol] == 'X' && currentGrid[row][col] != 'X') {
                        chanceToInfect += factorDeadNeighbour;
                    }
                }
            }

            randomInfected = rand() % (randomFactorToInfect_max);
            if (chanceToInfect > 0 && chanceToInfect + randomInfected > riskToInfected_percent) {
                newInfected = true;
            }

            nextGrid[row][col] = newInfected ? 'E' : currentGrid[row][col];
            newInfected = false;
            chanceToInfect = 0;
        }
    }
}

void printGeneration(int gen, char currentGrid[][SIZE]) {
    // reset cases per generation to 0
    memset(SEIRD, 0, sizeof(SEIRD));

    if (printConsole) printf("\n ------- %d. generation ------- \n", gen);
    fprintf(json, "    ");

    // iterate over cells in current generation
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (printConsole) printf(" %c ", currentGrid[row][col]);
    

            // increment the number of cases per generation
            switch (currentGrid[row][col]) {
                case '.':
                    SEIRD[0]++;
                    break;
                case 'E':
                    SEIRD[1]++;
                    break;
                case 'i':
                    SEIRD[2]++;
                    break;
                case 'R':
                    SEIRD[3]++;
                    break;
                default:
                    SEIRD[4]++;
                    break;
            }
        }
        if (printConsole) printf("\n");
    }
    // print the number of cases to the gnuplot.dat file
    fprintf(gnuplot, "%d %d %d %d %d %d\n", gen, SEIRD[0], SEIRD[1], SEIRD[2], SEIRD[3], SEIRD[4]);
}

void initFiles() {
    json = fopen("ebola.json", "w");
    if (json == NULL) //if file does not exist, create it
    {
        freopen("ebola.json", "w", json);
    }
    gnuplot = fopen("gnuplot.dat", "w");
    if (json == NULL) {
        freopen("gnuplot.dat", "w", json);
    }
    fprintf(json, "{\n");
    fprintf(json, "  \"generations\": [ \n");
}

void closeFiles() {
    // ends the current Json file
    fprintf(json, "  ]\n");
    fprintf(json, "}\n");

    //close the filestreams
    fclose(json);
    fclose(gnuplot);
}
