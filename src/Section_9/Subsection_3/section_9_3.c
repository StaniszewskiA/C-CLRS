#include <stdio.h>

int median(int X[], int Y[], int n) {
    if (n == 1) return (X[0] < Y[0]) ? X[0] : Y[0];

    int mid = n / 2;

    if (X[mid] < Y[mid]) 
        return median(X + mid, Y, n - mid);
    else 
        return median(X, Y + mid, n - mid);
}

int main(void) {
    int X[] = {1, 3, 5, 7, 9};
    int Y[] = {0, 2, 4, 6, 8};
    int n = sizeof(X) / sizeof(X[0]);

    printf("Median: %d\n", median(X, Y, n));
    return 0;
}