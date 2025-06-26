#include "part_1_foundations/2_getting_started/getting_started.h"
#include "common.h"

int find_highest_degree(const char *polynomial) {
    int i = 0, maxExponent = 0;

    while (polynomial[i] != '\0') {
        int exponent = 0;
        while (polynomial[i] != 'x' && polynomial[i] != '\0') i++;

        if (polynomial[i] == 'x') {
            i++;
            if (polynomial[i] == '^') {
                i++;
                while (isdigit(polynomial[i])) {
                    exponent = exponent * 10 + (polynomial[i] - '0');
                    i++;
                }
            }
            else exponent = 1;
        }
        if (exponent > maxExponent) maxExponent = exponent;
        while (polynomial[i] != '+' && polynomial[i] != '-' && polynomial[i] != '\0') 
            i++;
    }

    return maxExponent;
}

void determine_big_o(int maxExponent) {
    if (maxExponent == 0) printf("O(1)\n");
    else printf("O(n^%d)\n", maxExponent);
}

void selection_sort(int arr[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        if (min_idx != i) {
            int temp;
            SWAP(arr[min_idx], arr[i], temp);
        }
    }
}