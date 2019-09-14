#include "stdio.h"
#include "stdint.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"

const char *DESC = "DESC";
const char *ASC = "ASC";

enum {
    ascending = 0,
    descending = 1
} TYPE_SORT;

enum {
    argCommand = 1,
    argType = 2
} ARGS_ATTRIBUTES;

void selectionSort(int *array, const int size, const char* type) {
    for (int i = 0; i < size; i++) {
        int valueIndex = i;
        for (int j = i; j < size; j++) {
            if (!strcmp(type, DESC)) {
                if (array[valueIndex] < array[j])
                    valueIndex = j;
            } else {
                if (array[valueIndex] > array[j])
                    valueIndex = j;
            }
        }

        if (valueIndex != i) {
            int temp = array[i];
            array[i] = array[valueIndex];
            array[valueIndex] = temp;
        }
    }
}

int main(int argc, char *argv[]) {
    char usage[] = "usage: selecetionSort -t <DESC|ORD> <[array of numbers]>\n -t type of sort\n";
    char badType[] = "bad format of a number(must by int): ";
    if (argc >= 2) {
        const char *commandTypeSort = "-t";
        const int sizeOfArray = argc - 3;
        const char *typeSort = argv[argType];
        if (!strcmp(argv[argCommand], commandTypeSort)) {
            if (!strcmp(typeSort, DESC) || !strcmp(typeSort, ASC)) {
                int array[sizeOfArray];
                for (int i = 3; i < argc; i++) {
                    if (atoi(argv[i])) {
                        array[i - 3] = atoi(argv[i]);
                    }
                    else {
                        printf("%s %s", badType, argv[i]);
                    }
                }
                for (int i = 0; i < sizeOfArray; i++)
                    printf("%d ", array[i]);
                printf("\n");
                selectionSort(&array[0], sizeOfArray, typeSort);
                for (int i = 0; i < sizeOfArray; i++)
                    printf("%d ", array[i]);
                printf("\n");
            } else {
                printf("%s\n", usage);
            }
            
        }
        else {
            printf("%s\n", usage);
        }
    }
    else {
        printf("%s\n", usage);
    }
    return 0;
    const int size = 5;
    int array[] = {2, 3, 4, 0, 1};
    
    
    return 0;
}