#include "part_2_sorting_and_order_statistics/9_medians_and_order_statistics/medians_and_order_statistics.h"

int median(int X[], int Y[], int n) {
    if (n == 1) return (X[0] < Y[0]) ? X[0] : Y[0];

    int mid = n / 2;

    if (X[mid] < Y[mid]) 
        return median(X + mid, Y, n - mid);
    else 
        return median(X, Y + mid, n - mid);
}