#include <stdio.h>
#include <string.h>

#define MAX_LEN 100  
#define ALPHABET_SIZE 256 

void count_sort(
    char src[][MAX_LEN], 
    char dest[][MAX_LEN],
    int n,
    int idx
) {
    int count[ALPHABET_SIZE] = {0};

    for (int i = 0; i < n; i++) {
        int char_idx = (idx < strlen(src[i])) ? src[i][idx] : 0;
        count[char_idx]++;
    }

    for (int i = 1; i < ALPHABET_SIZE; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int char_idx = (idx < strlen(src[i])) ? src[i][idx] : 0;
        strcpy(dest[count[char_idx] - 1], src[i]);
        count[char_idx]--;
    }
}

void radix_sort(
    char A[][MAX_LEN], 
    int n
) {
    int max_lenght = 0;
    for (int i = 0; i < n; i++) {
        int len = strlen(A[i]);
        if (len > max_lenght)
        max_lenght = len;
    }

    char B[MAX_LEN][MAX_LEN];
    char (*src)[MAX_LEN] = A, (*dest)[MAX_LEN] = B;

    for (int idx = max_lenght - 1; idx >= 0; idx--) {
        count_sort(src, dest, n, idx);
        char (*temp)[MAX_LEN] = src;
        src = dest;
        dest = temp;
    }

    if (src != A) {
        for (int i = 0; i < n; i++)
            strcpy(A[i], B[i]);
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