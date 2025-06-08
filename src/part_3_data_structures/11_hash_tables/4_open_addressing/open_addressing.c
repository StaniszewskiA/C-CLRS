#include "part_3_data_structures/11_hash_tables/hash_tables.h"

HashTable2 ht2_init() {
    HashTable2 ht;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht.items[i].key = EMPTY;
        ht.items[i].value = 0;
    }
    return ht;
}

void linear_probing(HashTable2* ht, int key, int val) {
    int idx = hash_function(key);
    int original_idx = idx;

    while (ht->items[idx].key != EMPTY) {
        idx = (idx + 1) % HASH_TABLE_SIZE;
        if (idx == original_idx) {
            printf("Hash table is full!\n");
            return;
        }
    }

    ht->items[idx].key = key;
    ht->items[idx].value = val;
}

void quadratic_probing(HashTable2* ht, int key, int val) {
    int idx = hash_function(key);
    int i = 0;

    while (ht->items[(idx + i * i) % HASH_TABLE_SIZE].key != EMPTY) {
        i++;
        if (i == HASH_TABLE_SIZE) {
            printf("Hash table is full!\n");
            return;
        }
    }

    idx = (idx + i * i) % HASH_TABLE_SIZE;
    ht->items[idx].key = key;
    ht->items[idx].value = val;
}

int ht2_search(HashTable2* ht, int key) {
    int idx = hash_function(key);
    int i = 0;
    
    while (ht->items[(idx + i * i) % HASH_TABLE_SIZE].key != EMPTY) {
        int newIdx = (idx + i * i) % HASH_TABLE_SIZE;
        if (ht->items[newIdx].key == key) {
            return ht->items[newIdx].value;
        }
        i++;
        if (i == HASH_TABLE_SIZE) break;
    }
    return -1;
}

void ht2_display(HashTable2 *ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (ht->items[i].key == EMPTY) {
            printf("Index %d: EMPTY\n", i);
        } else if (ht->items[i].key == DELETED) {
            printf("Index %d: DELETED\n", i);
        } else {
            printf("Index %d: Key %d, Value %d\n", i, ht->items[i].key, ht->items[i].value);
        }
    }
}

//-----Hash insert/delete-----
int hash_shift(int key, int i) {
    return (key + i) % HASH_TABLE_SIZE;
}

void hash_insert(HashTable2 *ht, int key, int value) {
    int i = 0;
    int idx;

    while (i < HASH_TABLE_SIZE) {
        idx = hash_shift(key, i);
        if (ht->items[idx].key == EMPTY || ht->items[idx].key == DELETED) {
            ht->items[idx].key = key;
            ht->items[idx].value = value;
            return;
        }
        i++;
    }
    printf("Hash table overflow\n");
}

int hash_delete(HashTable2* ht, int key) {
    int i = 0;
    int idx;

    while (i < HASH_TABLE_SIZE) {
        idx = hash_shift(key, i);
        if (ht->items[idx].key == key) {
            ht->items[idx].key = DELETED;
            return idx;
        }
        if (ht->items[idx].key == EMPTY) {
            break;
        }
        i++;
    }
    printf("Element not found\n");
    return -1;
}