#include <stdio.h>
#include "stdlib.h"

int** MagicSquare(int n){
    int** arr, i, j;
    arr = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++)
    {
        arr[i] = (int*)malloc(n * sizeof(int));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            arr[i][j] = 0;
            //printf("%d\n", arr[i][j]);
        }
    }
    int number = 2;
    int k;
    int x = 0;
    int y = (n - 1) / 2;
    int f, g;
    arr[0][(n - 1) / 2] = 1;
    for (k = 1; k < n * n; k++) {
        if (x == 0 && y <= n - 2) {
            x = n - 1;
            y += 1;
        }
        else if ((y == n - 1) && (x >= 1)) {

            x -= 1;
            y = 0;

        }
        else {
           if ((number-1) % n == 0) {
                x += 1;           
            }
            else if ((number-1) % n != 0) {
                x -= 1;
                y += 1;
            }
        }

        arr[x][y] = number;
        number++;
    }
    return arr;
}

void FreeMagicSquare(int** magicSquare, int n){
    int k;
    /*for (k = 0; k < n; k++) {
        for (p = 0; p < n; p++) {
            free(magicSquare[k][p]);
        }
    }*/
    for (k = 0; k < n; k++) {
        free(magicSquare[k]);
    }

    free(magicSquare);
}

int main() {
    int n;
    scanf_s("%d", &n); // Please input a positive odd number.
    int** magicSquare = MagicSquare(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", magicSquare[i][j]);
        }
        printf("\n");
    }
    FreeMagicSquare(magicSquare, n);
    return 0;
}

