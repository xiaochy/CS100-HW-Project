/*#include <stdio.h>
#include <stdlib.h>

void FindSecondMaxAndMin(int numbers[], int size, int* secondMax, int* secondMin){
    int i, j;
    int k;
    for (i = 0; i < size; i++) {
        k = 0;
        for (j = 0; j < size; j++) {
            if (numbers[i] > numbers[j]) {
                k++;
            }
        }
        if (k == size - 2) {
            *secondMax =numbers[i];
        }
        else if (k == 1) {
            *secondMin = numbers[i];
        }
    }
}

#define SIZE 8

int main(){
    int secondMax, secondMin;
    int numbers[SIZE] = {2, 3, 4, 7, 6, 10, 9, 8};
    FindSecondMaxAndMin(numbers, SIZE, &secondMax, &secondMin);
    printf("%d %d\n", secondMax, secondMin);
    return 0;
}
*/