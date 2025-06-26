#include "part_3_data_structures/11_hash_tables/hash_tables.h"

void linear_probing_insert(HashTable2* ht, int key, int value) {
    int idx = hash_function(key);
    int original_idx = idx;

    while (ht->items[idx].key != EMPTY && ht->items[idx].key != key) {
        idx = (idx + 1) % HASH_TABLE_SIZE;
        if (idx == original_idx) {
            printf("Hash table overflow\n");
            return;
        }
    }
    ht->items[idx].key = key;
    ht->items[idx].value = value;
}

int linear_probing_search(HashTable2* ht, int key) {
    int idx = hash_function(key);
    int original_idx = idx;

    while (ht->items[idx].key != EMPTY) {
        if (ht->items[idx].key == key) return idx;
        idx = (idx + 1) % HASH_TABLE_SIZE;
        if (idx == original_idx) break;
    }

    return -1;
}

void linear_probing_delete(HashTable2* ht, int key) {
    int q = linear_probing_search(ht, key);
    if (q == -1) {
        printf("Element not found\n");
        return;
    }

    ht->items[q].key = EMPTY;
    ht->items[q].value = 0;

    int q_prime = q;
    while (1) {
        q_prime = (q_prime + 1) % HASH_TABLE_SIZE;
        if (ht->items[q_prime].key == EMPTY) return;
        
        int k_prime = ht->items[q_prime].key;
        int correct_idx = hash_function(k_prime);

        if ((correct_idx <= q && q < q_prime) || (q_prime < correct_idx && correct_idx <= q)) {
            ht->items[q].key = ht->items[q_prime].key;
            ht->items[q].value = ht->items[q_prime].value;
            ht->items[q_prime].key = EMPTY;
            ht->items[q_prime].value = 0;
            q = q_prime;
        } 
    }
}

void print_ht2(HashTable2* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (ht->items[i].key == EMPTY) printf("Idx: %d: EMPTY\n", i);
        else printf("Idx %d: Key %d, Value %d\n", i, ht->items[i].key, ht->items[i].value);
    }
    printf("\n");
}