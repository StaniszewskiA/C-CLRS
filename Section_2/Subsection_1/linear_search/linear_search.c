#include <stdio.h>

int linearSearch(int *arr, int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }

    return -1;
}

int main() {
    int arr[] = {5, 8, 12, 20, 25, 32, 40};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 20;

    int index = linearSearch(arr, size, target);

    if (index != -1) {
        printf("Element %d found at index %d.\n", target, index);
    } else {
        printf("Element %d not found in the array.\n", target);
    }

    return 0;
}
