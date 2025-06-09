#include "part_4_advanced_design_and_analysis_techniques/16_amortized_analysis/amortized_analysis.h"

#define TASK 4

int main(void) {
    int i;

    switch (TASK)
    {
        case 1: {
            // Mutlipop Heap
            MinHeap heap;
            heap.size = 0;

            heap_insert(&heap, 10);
            heap_insert(&heap, 20);
            heap_insert(&heap, 5);
            heap_insert(&heap, 30);
            heap_insert(&heap, 15);

            print_heap(&heap);

            heap_multipop(&heap, 3);
            print_heap(&heap);

            break;
        }
        
        case 2: {
            // Binary Counter
            BinaryCounter bCounter;
            binary_counter_init(&bCounter);

            printf("Initial bCounter:\n");
            print_counter(&bCounter);

            for (i = 0; i < 20; i++) {
                binary_counter_increment(&bCounter);
                print_counter(&bCounter);
            }

            binary_counter_reset(&bCounter);
            print_counter(&bCounter);

            break;
        }

        case 3: {
            // 16.3-5
            CreditsQueue q;
            credits_queue_init(&q);

            credits_enqueue(&q, 10);
            credits_enqueue(&q, 20);
            credits_enqueue(&q, 30);

            printf("Dequeued: %d\n\n", credits_dequeue(&q));
            printf("Dequeued: %d\n\n", credits_dequeue(&q));

            credits_enqueue(&q, 40);
            printf("Dequeued: %d\n\n", credits_dequeue(&q));
            printf("Dequeued: %d\n\n", credits_dequeue(&q));

            break;
        }

        case 4: {
            // 16.3-6 - Dynamic Multiset
            DynamicMultiset* dms = dms_init();

            dms_insert(dms, 5);
            dms_insert(dms, 2);
            dms_insert(dms, 8);
            dms_insert(dms, 1);
            dms_insert(dms, 10);
            dms_insert(dms, 7);

            print_dms(dms);

            dms_delete_larger_half(dms);

            print_dms(dms);

            dms_free(dms);

            break;
        }

        default:
            break;
    }

    return 0;
}