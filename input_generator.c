#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(NULL));
    int size = 100, n, k;

    FILE *output = fopen("input.txt", "w+"); //creates or writes input.txt from scratch
    printf("Generating random input.\n");

    for (int ii = 0; ii < 3; ii++) {
        size *= 10; //increases input size of n
        k = rand() % size; //chooses k to select
        fprintf(output, "%d\n", k); //writes to input.txt file
        for (int jj = 0; jj < size; jj++) {
            n = rand() % 10; //chooses a random number, each one is written into the file.
            fprintf(output, "%d", n);
        }
        fputs("\n", output); //adds a newline to the end of the array in the file.
    }
    
    fclose(output);
    printf("Random input generation complete.\n");
    return (0);
}