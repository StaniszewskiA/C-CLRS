#include <stdio.h>

#define TASK 1

/*
    16-1: Binary Grya codes.
*/
typedef unsigned int uint;

static inline unsigned int gray_code(uint i) {
    return i ^ (i >> 1);
}

void generate_gray_codes(int k) {
    uint n = 1 << k;
    uint i, j, gray;
    printf("<");

    for (i = 0; i < n; i++) {
        gray = gray_code(i);

        for (int j = k - 1; j >= 0; j--) printf("%u", (gray >> j) & 1);

        if (i < n - 1) printf(", ");
    }
    printf(">\n");
}

/*
    16.2: Making binary search dynamic.
*/

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 16.1
            uint k1 = 3;
            generate_gray_codes(k1);

            break;
        }

        case 2:{
            // 16.2
            break;
        }
        
        default:
            break;
    }
    
    return 0;
}