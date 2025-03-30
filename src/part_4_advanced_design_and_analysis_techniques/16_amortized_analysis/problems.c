#include <stdio.h>

#define TASK 1

/*
    16-1: Binary Grya codes.
*/
static inline unsigned int gray_code(unsigned int i) {
    return i ^ (i >> 1);
}

void generate_gray_codes(int k) {
    unsigned int n = 1 << k;
    unsigned int i, j, gray;
    printf("<");

    for (i = 0; i < n; i++) {
        gray = gray_code(i);

        for (int j = k - 1; j >= 0; j--) printf("%u", (gray >> j) & 1);

        if (i < n - 1) printf(", ");
    }
    printf(">\n");
}

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 16.1
            unsigned int k1 = 3;
            generate_gray_codes(k1);

            break;
        }
        
        default:
            break;
    }
    
    return 0;
}