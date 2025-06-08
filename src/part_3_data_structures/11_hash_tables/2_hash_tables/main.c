#include "part_3_data_structures/11_hash_tables/hash_tables.h"

#define TASK 3




int main(void) {
    switch (TASK)
    {
        case 1: {
            HashTable* ht = ht_init();
            ht_insert(ht, "key1", 42);
            ht_insert(ht, "key2", 99);

            int val = 42;
            if (ht_search(ht, "key1", &val)) {
                printf("Found key1: %d\n", val);
            } else {
                printf("Key1 not found\n");
            }

            ht_delete(ht, "key1");
            if (ht_search(ht, "key1", &val)) {
                printf("Found key1: %d\n", val);
            } else {
                printf("Key1 not found\n");
            }

            ht_free(ht);

            break;
        }    
        case 2: {
            FreeSlotsHashTable* fsht = fsht_init();

            fsht_insert(fsht, "key1", 42);
            fsht_insert(fsht, "key1", 99);

            fsht_delete(fsht, "key1");

            fsht_free(fsht);

            break;
        }
        case 3: {
            srand(time(NULL));
            HashTable* ht = ht_init();

            ht_insert(ht, "key1", 10);
            ht_insert(ht, "key2", 20);
            ht_insert(ht, "key3", 30);

            char* random_key = ht_get_random_key(ht);

            if (random_key) {
                printf("Random key: %s\n", random_key);
            } else {
                printf("HashTable is empty\n");
            }
            ht_free(ht);

            break;
        }
        default:
            break;
    }
    return 0;
}