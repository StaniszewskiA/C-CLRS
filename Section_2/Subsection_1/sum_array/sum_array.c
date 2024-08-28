#include <stdio.h>
#include "sum_array.h"

int sumArray(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    int sum = sumArray(arr, size);
    printf("Sum of array elements: %d\n", sum);

    return 0;
}