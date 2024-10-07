#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pattern.h"

int main(int argc, char *argv[]) {
    srand(time(NULL)); // seed rng
    int min; // take in our vars
    int max;
    int pattern;
    sscanf(argv[1], "%d", &min);
    sscanf(argv[2], "%d", &max);
    sscanf(argv[3], "%d", &pattern);

    int things = min + (rand() % (max - min + 1)); // get a random number between min and max

    if (pattern == 1) {
        parallel(things);
    } else if (pattern == 2) {
        sequential(things);
    }
}
