#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <memory.h>
#include "header.h"

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
