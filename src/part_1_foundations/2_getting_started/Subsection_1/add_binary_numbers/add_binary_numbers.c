#include "add_binary_numbers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* addBinaryNumbers(const int* A, int lenA, const int* B, int lenB, int* resultLen) {
    int maxLen = (lenA > lenB) ? lenA : lenB;
    int* result = (int*)malloc((maxLen + 1) * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        *resultLen = 0;
        return NULL;
    }

    int carry = 0;

    for (int i = 0; i < maxLen; i++) {
        int bitA = (i < lenA) ? A[lenA - 1 - i] : 0; 
        int bitB = (i < lenB) ? B[lenB - 1 - i] : 0;

        int sum = bitA + bitB + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }

    if (carry) {
        result[maxLen] = carry;
        *resultLen = maxLen + 1;
    } else {
        *resultLen = maxLen;
    }

    reverseArray(result, *resultLen);
    removeLeadingZeroes(result, resultLen);

    return result;
}

void printArray(const int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void removeLeadingZeroes(int* arr, int* len) {
    int startIndex = 0;
    while (startIndex < *len - 1 && arr[startIndex] == 0) {
        startIndex++;
    }

    *len -= startIndex;

    if (*len > 0) {
        memmove(arr, arr + startIndex, *len * sizeof(int));
    }
}

void reverseArray(int* arr, int len) {
    int start = 0;
    int end = len - 1;
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int main() {
    int A[] = {1, 0, 1, 0};
    int lenA = sizeof(A) / sizeof(A[0]);

    printf("Array A: ");
    printArray(A, lenA);

    int B[] = {1, 1, 0, 0};
    int lenB = sizeof(B) / sizeof(B[0]);

    printf("Array B: ");
    printArray(B, lenB);

    int resultLen = 0;
    int *result = addBinaryNumbers(A, lenA, B, lenB, &resultLen);

    if (result == NULL) {
        return -1;
    }

    printf("Result: ");
    printArray(result, resultLen);

    free(result);
    return 0;
}
