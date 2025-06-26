#include "part_3_data_structures/11_hash_tables/hash_tables.h"

#define TASK 1

int main(void) {
    switch (TASK)
    {
        case 1: {
            HashTable2 ht = ht2_init();

            linear_probing(&ht, 10, 100);
            linear_probing(&ht, 20, 200);
            linear_probing(&ht, 30, 300);
            linear_probing(&ht, 40, 400);

            printf("Hash Table after Linear Probing Insertions:\n");
            ht2_display(&ht);

            break;
        }
        case 2: {
            HashTable2 ht = ht2_init();

            quadratic_probing(&ht, 10, 100);
            quadratic_probing(&ht, 20, 200);
            quadratic_probing(&ht, 30, 300);
            quadratic_probing(&ht, 40, 400);

            printf("Hash Table after Quadratic Probing Insertions:\n");
            ht2_display(&ht);

            break;
        }
        case 3: {
            HashTable2 ht = ht2_init();

            hash_insert(&ht, 10, 100);
            hash_insert(&ht, 20, 200);
            hash_insert(&ht, 30, 300);
            hash_insert(&ht, 40, 400);

            printf("Hash Table after Quadratic Probing Insertions:\n");
            ht2_display(&ht);

            hash_delete(&ht, 20);
            hash_delete(&ht, 30);

            printf("\nHash Table after Deletions:\n");
            ht2_display(&ht);

            break;
        }
        default:
            break;
    }

    return 0;
}