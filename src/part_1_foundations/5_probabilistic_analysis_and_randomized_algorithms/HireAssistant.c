#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int hireAssistant(int* candidates, int size) {
    int bestSoFar = 0;
    for (int i = 0; i < size; i++) {
        if (candidates[i] > bestSoFar) {
            bestSoFar = candidates[i];
        }
    }

    return bestSoFar;
}

int main() {
    int candidates[] = {5, 7, 3, 8, 6};
    int size = sizeof(candidates) / sizeof(candidates[0]); 
    int best = hireAssistant(candidates, size);
    printf("Best candidate score: %d\n", best);
    return 0;
}