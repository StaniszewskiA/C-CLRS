#include "part_2_sorting_and_order_statistics/8_sorting_in_linear_time/sorting_in_linear_time.h"

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
    int k = find_max(A, n);
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

void radix_sort2(int A[], int n) {
    int max = find_max(A, n);

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
        int len = count_digits(A[i]);
        buckets[len][sizes[len]++] = A[i];
    }

    int idx = 0;
    for (int i = 1; i <= MAX_DIGITS; i++) {
        if (sizes[i] > 0) {
            radix_sort2(buckets[i], sizes[i]);  
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
    if (n <= 1 || depth >= MAX_LENGTH - 1) return;

    Ex3BBucket buckets[ALPHABET_SIZE_2] = {0};
    char emptyWords[MAX_WORDS][MAX_LENGTH];
    int emptyCount = 0;

    for (int i = 0; i < n; i++) {
        int word_len = (int)strlen(words[i]);
        if (word_len <= depth) { 
            strcpy(emptyWords[emptyCount++], words[i]); 
        } else {
            char ch = words[i][depth];
            int idx = -1;
            
            if (ch >= 'a' && ch <= 'z') {
                idx = ch - 'a';
            } else if (ch >= 'A' && ch <= 'Z') {
                idx = ch - 'A';
            }
            
            if (idx >= 0 && idx < ALPHABET_SIZE_2) { 
                strcpy(buckets[idx].words[buckets[idx].size++], words[i]);
            } else {
                strcpy(emptyWords[emptyCount++], words[i]);
            }
        }
    }

    int pos = 0;

    for (int i = 0; i < emptyCount; i++)
        strcpy(words[pos++], emptyWords[i]);

    for (int i = 0; i < ALPHABET_SIZE_2; i++) {
        if (buckets[i].size > 0) {
            ex3b(buckets[i].words, buckets[i].size, depth + 1);
            for (int j = 0; j < buckets[i].size; j++)
                strcpy(words[pos++], buckets[i].words[j]);
        }
    }
}

int main(void) {
    int arr2a[] = {1, 0, 1, 0, 0, 1, 1, 0};
    int n2a = sizeof(arr2a) / sizeof(arr2a[0]);
    int *result2a = (int*)malloc(n2a * sizeof(int));
    
    printf("Original: ");
    print_arr(arr2a, n2a);
    
    ex2a(arr2a, n2a, result2a);
    
    printf("Sorted:   ");
    print_arr(result2a, n2a);
    free(result2a);
    
    int arr2b[] = {1, 0, 1, 0, 0, 1, 1, 0};
    int n2b = sizeof(arr2b) / sizeof(arr2b[0]);
    
    printf("Original: ");
    print_arr(arr2b, n2b);
    
    ex2b(arr2b, n2b);
    
    printf("Sorted:   ");
    print_arr(arr2b, n2b);
    
    int arr2e[] = {4, 2, 2, 8, 3, 3, 1};
    int n2e = sizeof(arr2e) / sizeof(arr2e[0]);
    
    printf("Original: ");
    print_arr(arr2e, n2e);
    
    ex2e(arr2e, n2e);
    
    printf("Sorted:   ");
    print_arr(arr2e, n2e);
    
    int arr3a[] = {329, 457, 657, 839, 436, 720, 355, 12, 5, 1000, 99};
    int n3a = sizeof(arr3a) / sizeof(arr3a[0]);
    
    printf("Original: ");
    print_arr(arr3a, n3a);
    
    ex3a(arr3a, n3a);
    
    printf("Sorted:   ");
    print_arr(arr3a, n3a);

    char words[][MAX_LENGTH] = {
        "cat", "dog", "elephant", "bat", "car", "application", 
        "bat", "a", "zoo", "apple", "cake"
    };
    int n3b = sizeof(words) / sizeof(words[0]);
    
    printf("Original strings:\n");
    for (int i = 0; i < n3b; i++) {
        printf("  %s\n", words[i]);
    }
    
    ex3b(words, n3b, 0);
    
    printf("Sorted strings:\n");
    for (int i = 0; i < n3b; i++) {
        printf("  %s\n", words[i]);
    }
}