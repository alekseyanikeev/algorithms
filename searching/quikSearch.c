#include <stdio.h>

int quikSearch(int *sortedArray, const int size, int index, const int value) {
    printf("\nvalue: %d\nsize: %d \nindex: %d\n\n", sortedArray[index], size, index);
    if (value == sortedArray[index]) {
        return index;
    }

    if (size <= 1)
        return -1;
    
    else if (value > sortedArray[index]) {
        printf("move to right");
         index = index + size / 2 ;
         return quikSearch(sortedArray, size / 2, index, value);
    } else {
        printf("move to left");
        index = size / 2 + index;
        return quikSearch(sortedArray, size / 2, index, value);
    }
}

int main(int argc, char *argv[]) {
    // int array[] = {52, 38, 28, 25, 7, 6, 5, 4, 0};
    int array[] = {1, 2, 5, 7, 9, 25, 88};
    int result = quikSearch(&array[0], 7, 0, 2);
    printf("index: %d\n", result);
    return 0;
}