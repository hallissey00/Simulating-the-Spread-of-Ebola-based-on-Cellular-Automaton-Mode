#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <memory.h>
#include "timer.h"
#include <pthread.h>
#include "header.h"

void printGeneration(int gen, char currentGrid[][SIZE]) {
    // reset cases per generation to 0
    memset(SEIRD, 0, sizeof(SEIRD));

    if (printConsole) printf("\n ------- %d. generation ------- \n", gen);
    fprintf(json, "    ");

    // iterate over cells in current generation
    for (int row = 0; row < SIZE; row++) {
        fprintf(json, "  [");
        for (int col = 0; col < SIZE; col++) {
            if (printConsole) printf(" %c ", currentGrid[row][col]);
            fprintf(json, "\"%c\"", currentGrid[row][col]);

            // if the last cell of row is reached, dont print a comma at the end
            if (col != SIZE - 1) {
                fprintf(json, ",");
            }

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
        if (row != SIZE - 1) {
            fprintf(json, "],\n    ");
        } else {
            fprintf(json, "]\n    ");
        }
    }
    // print the number of cases to the gnuplot.dat file
    fprintf(gnuplot, "%d %d %d %d %d %d\n", gen, SEIRD[0], SEIRD[1], SEIRD[2], SEIRD[3], SEIRD[4]);
}
