#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <memory.h>
#include "timer.h"
#include <pthread.h>
#include "header.h"
void closeFiles() {
    // ends the current Json file
    fprintf(json, "  ]\n");
    fprintf(json, "}\n");

    //close the filestreams
    fclose(json);
    fclose(gnuplot);
}
