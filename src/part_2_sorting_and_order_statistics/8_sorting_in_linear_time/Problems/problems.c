#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAX_DIGITS 10
#define ALPHABET_SIZE 26
#define MAX_WORDS 1000
#define MAX_LENGTH 50

void ex2a(int A[], int n, int C[]);
void ex2b(int A[], int n);
void ex2e(int A[], int n);
int findMax(int A[], int n);
int countDigits(int num);
void radixSort(int A[], int n);
void ex3a(int A[], int n);

void ex2a(int A[], int n, int C[]) {
    int idx = 0;

    for (int i = 0; i < n; i++) {
        if (A[i] == 0) {
            C[idx] = A[i];
            idx++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (A[i] == 1) {
            C[idx] = A[i];
            idx++;
        }
    }
}

void ex2b(int A[], int n) {
    int idx = 0;

    for (int i = 0; i< n; i++) {
        if (A[i] == 0) {
            if (i != idx) {
                int temp = A[i];
                A[i] = A[idx];
                A[idx] = temp;
            }
            idx++;
        }
    }
}

void ex2e(int A[], int n) {
    int k = findMax(A, n);
    int *C = (int * )calloc(k + 1, sizeof(int));

    for (int i = 0; i < n; i++) 
        C[A[i]]++;

    for (int i = 1; i <= k; i++)
        C[i] += C[i - 1];

    int *B = (int *)malloc(n * sizeof(int));

    for (int i = n - 1; i >= 0; i--) {
        B[C[A[i]] - 1] = A[i];
        C[A[i]]--;
    }

    for (int i = 0; i < n; i++)
        A[i] = B[i];

    free(C);
    free(B);
}

int findMax(int A[], int n) {
    int max = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > max) {
            max = A[i];
        }
    }
    return max;
}

int countDigits(int num) {
    if (num == 0) return 1;
    return (int)log10(abs(num)) + 1;
}

void radixSort(int A[], int n) {
    int max = findMax(A, n);

    for (int exp = 1; max / exp > 0; exp *= 10) {
        int output[n], count[10] = {0};

        for (int i = 0; i < n; i++)
            count[(A[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            output[count[(A[i] / exp) % 10] - 1] = A[i];
            count[(A[i] / exp) % 10]--;
        }

        for (int i = 0; i < n; i++)
            A[i] = output[i];
    }
}

void ex3a(int A[], int n) {
    int *buckets[MAX_DIGITS + 1];  
    int sizes[MAX_DIGITS + 1] = {0};

    for (int i = 0; i <= MAX_DIGITS; i++)
        buckets[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int len = countDigits(A[i]);
        buckets[len][sizes[len]++] = A[i];
    }

    int idx = 0;
    for (int i = 1; i <= MAX_DIGITS; i++) {
        if (sizes[i] > 0) {
            radixSort(buckets[i], sizes[i]);  
            for (int j = 0; j < sizes[i]; j++)
                A[idx++] = buckets[i][j];
        }
    }

    for (int i = 0; i <= MAX_DIGITS; i++)
        free(buckets[i]);
}

typedef struct {
    char words[MAX_WORDS][MAX_LENGTH];
    int size;
} Ex3BBucket;

void ex3b(char words[][MAX_LENGTH], int n, int depth) {
    if (n <= 1) return;

    Ex3BBucket buckets[ALPHABET_SIZE] = {0};
    char emptyWords[MAX_WORDS][MAX_LENGTH];
    int emptyCount = 0;

    for (int i = 0; i < n; i++) {
        if (strlen(words[i]) == depth) { 
            strcpy(emptyWords[emptyCount++], words[i]); 
        } else {
            int idx = tolower(words[i][depth]) - 'a';
            if (idx >= 0 && idx < ALPHABET_SIZE) { 
                strcpy(buckets[idx].words[buckets[idx].size++], words[i]);
            }
        }
    }

    int pos = 0;

    for (int i = 0; i < emptyCount; i++)
        strcpy(words[pos++], emptyWords[i]);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (buckets[i].size > 0) {
            ex3b(buckets[i].words, buckets[i].size, depth + 1);
            for (int j = 0; j < buckets[i].size; j++)
                strcpy(words[pos++], buckets[i].words[j]);
        }
    }
}

int main(void) {
    return 0;
}