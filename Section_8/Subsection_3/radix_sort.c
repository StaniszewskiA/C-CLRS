#include <stdio.h>
#include <string.h>

#define MAX_LEN 100  
#define ALPHABET_SIZE 256 

void count_sort(
    char A[][MAX_LEN], 
    int n, 
    int idx, 
    int max_length
) {
    char output[n][MAX_LEN];
    int count[ALPHABET_SIZE] = {0};

    for (int i = 0; i < n; i++) {
        int char_idx = (idx < strlen(A[i])) ? A[i][idx] : 0;
        count[char_idx]++;
    }

    for (int i = 1; i < ALPHABET_SIZE; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int char_idx = (idx < strlen(A[i])) ? A[i][idx] : 0;
        strcpy(output[count[char_idx] - 1], A[i]);
        count[char_idx]--;
    }

    for (int i = 0; i < n; i++) {
        strcpy(A[i], output[i]);
    }
}

void radix_sort(
    char A[][MAX_LEN], 
    int n
) {
    int max_length = 0;
    for (int i = 0; i < n; i++) {
        int len = strlen(A[i]);
        if (len > max_length) {
            max_length = len;
        }
    }

    for (int index = max_length - 1; index >= 0; index--) {
        count_sort(A, n, index, max_length);
    }
}

void print_arr(
    char A[][MAX_LEN], 
    int size
) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", A[i]);
    }
}

int main() {
    char words[][MAX_LEN] = {
        "COW",
        "DOG",
        "SEA",
        "RUG",
        "ROW",
        "MOB",
        "BOX",
        "TAB",
        "BAR",
        "EAR",
        "TAR",
        "DIG",
        "BIG",
        "TEA",
        "NOW",
        "FOX"
    };
    int n = sizeof(words) / sizeof(words[0]);

    radix_sort(words, n);
    print_arr(words, n);

    return 0;
}