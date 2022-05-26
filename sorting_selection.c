#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

clock_t startm, stopm;
#define START if ((startm = clock()) == -1) {printf("Error calling clock. Exiting.\n");exit(1);}
#define STOP if ((stopm = clock()) == -1) {printf("Error calling clock. Exiting.\n");exit(1);}
#define PRINT_TIME printf("%6.3f seconds.\n", ((double)stopm-startm)/CLOCKS_PER_SEC);

void quicksort(int arr[], int first, int last);
int partition(int arr[], int first, int last);
int selection(int arr[], int first, int last, int k);

int main (void) {
    char confirm = 'N';
    /*printf("Please confirm that you have \"input_generator.c\" in the same folder as this program.\nInput \"Y\" if this is the case, or \"N\" if it is not in the same folder.\n");
    scanf(" %c", &confirm); //Confirms that the user has placed the input generation program source code in the same folder. Necessary for proper sorting later on.
    if (confirm != 'Y') {
        printf("Please place \"input_generator.c\" in the same folder as this program, then run it again. Exiting.\n");
        return (1);
    }*/

    printf("Initializing random input generation program.\n");
    int status = system("gcc input_generator.c -o input_generator && ./input_generator");
    /*
    system() is somewhat insecure, but it should be fine for this application. It is meant
    to automatically compile and run the other program in the linux terminal.
    */
    if (status != 0) {
        printf("Sorting program compilation/running failed. Exiting.\n");
        return (1);
    }
    printf("Successful return to sorting program.\n");

    FILE *input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Error opening input.txt. Exiting.\n");
        return (1);
    }

    char buf[100001], arrc[3][100001];
    int k[3];

    fgets(buf, 100001, input);
    strtok(buf, "\n");
    k[0] = atoi(buf);
    //printf("k[0]: %d\n", k[0]);
    fgets(buf, 100001, input);
    strtok(buf, "\n");
    strcpy(arrc[0], buf);
    //printf("arr[0]: %s\n", arr[0]);

    fgets(buf, 100001, input);
    strtok(buf, "\n");
    k[1] = atoi(buf);
    //printf("k[1]: %d\n", k[1]);
    fgets(buf, 100001, input);
    strtok(buf, "\n");
    strcpy(arrc[1], buf);
    //printf("arr[1]: %s\n", arr[1]);

    fgets(buf, 100001, input);
    strtok(buf, "\n");
    k[2] = atoi(buf);
    //printf("k[2]: %d\n", k[2]);
    fgets(buf, 100001, input);
    strtok(buf, "\n");
    strcpy(arrc[2], buf);
    //printf("arr[2]: %s\n", arr[2]);

    fclose(input);

    int arr[3][100000], loop = 100;

    for (int ii = 0; ii < 3; ii++) {
        loop *= 10;
        for (int jj = 0; jj < loop; jj++)
            arr[ii][jj] = (int)arrc[ii][jj];
    }

    printf("Input saved to memory. Time to sort!\n");

    START
    /*
    quicksort(arr[0], 0, 999);
    printf("K of sorted 1000: %d\n", arr[0][k[0]]);
    */
    printf("K of sorted 1000: %d\n", selection(arr[0], 0, 999, k[0]));
    STOP
    PRINT_TIME

    START
    /*
    quicksort(arr[1], 0, 9999);
    printf("K of sorted 10000: %d\n", arr[1][k[1]]);
    */
    printf("K of sorted 10000: %d\n", selection(arr[1], 0, 9999, k[1]));
    STOP
    PRINT_TIME

    START
    /*
    quicksort(arr[2], 0, 99999);
    printf("K of sorted 100000: %d\n", arr[2][k[2]]);
    */
    printf("K of sorted 100000: %d\n", selection(arr[2], 0, 99999, k[2]));
    STOP
    PRINT_TIME

    return (0);
}

void quicksort(int arr[], int first, int last) {
    int ii, jj, pivot, temp;

    if (first < last) {
        pivot = first;
        ii = first;
        jj = last;

        while (ii < jj) {
            while (arr[ii] <= arr[pivot] && ii < last)
                ii++;
            while (arr[jj] > arr[pivot])
                jj--;
            if (ii < jj) {
                temp = arr[ii];
                arr[ii] = arr[jj];
                arr[jj] = temp;
            }
        }
    temp = arr[pivot];
    arr[pivot] = arr[jj];
    arr[jj] = temp;
    quicksort(arr, first, jj - 1);
    quicksort(arr, jj + 1, last);
    }
}

int partition(int arr[], int first, int last) {
    int hold = arr[last], ii = first, temp;
    for (int jj = first; jj <= last - 1; jj++) {
        if (arr[jj] <= hold) {
            temp = arr[ii];
            arr[ii] = arr[jj];
            arr[jj] = temp;
            ii++;
        }
    }
    temp = arr[ii];
    arr[ii] = arr[last];
    arr[last] = temp;
    return ii;
}

int selection(int arr[], int first, int last, int k) {
    if (k > 0 && k <= last - first + 1) {
        int index = partition(arr, first, last);
        if (index - first == k - 1)
            return arr[index];
        if (index - first > k - 1)
            return selection(arr, first, index - 1, k);
        return selection(arr, index + 1, last, k - index + first - 1);
    }
    return 999999;
}