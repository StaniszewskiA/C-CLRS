#include "part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/greedy_algorithms.h"

int main(void) {
    Queue* q = queue_init(Q_CAPACITY);
    Hash* hash = hash_init(HASH_CAPACITY);

    ref_page(q, hash, 1);
    ref_page(q, hash, 2);
    ref_page(q, hash, 3);
    ref_page(q, hash, 1);
    ref_page(q, hash, 4);
    ref_page(q, hash, 5);

    printf ("%d ", q->front->pageNum);
    printf ("%d ", q->front->next->pageNum);
    printf ("%d ", q->front->next->next->pageNum);
    printf ("%d ", q->front->next->next->next->pageNum);

    return 0;
}