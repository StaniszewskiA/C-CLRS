#include <stdio.h>
#include <stdlib.h>

#define TASK 1
#define TABLE_SIZE 10
#define EMPTY -1

typedef struct HashItem {
    int key;
    int value;
} HashItem;

typedef struct HashTable {
    HashItem items[TABLE_SIZE];
} HashTable;

HashTable init_ht() {
    HashTable ht;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht.items[i].key = EMPTY;
        ht.items[i].value = 0;
    }
    return ht;
}

int hash_function(int key) {
    return key % TABLE_SIZE;
}

void linear_probing_insert(HashTable* ht, int key, int value) {
    int idx = hash_function(key);
    int original_idx = idx;

    while (ht->items[idx].key != EMPTY && ht->items[idx].key != key) {
        idx = (idx + 1) % TABLE_SIZE;
        if (idx == original_idx) {
            printf("Hash table overflow\n");
            return;
        }
    }
    ht->items[idx].key = key;
    ht->items[idx].value = value;
}

int linear_probing_search(HashTable* ht, int key) {
    int idx = hash_function(key);
    int original_idx = idx;

    while (ht->items[idx].key != EMPTY) {
        if (ht->items[idx].key == key) return idx;
        idx = (idx + 1) % TABLE_SIZE;
        if (idx == original_idx) break;
    }

    return -1;
}

void linear_probing_delete(HashTable* ht, int key) {
    int q = linear_probing_search(ht, key);
    if (q == -1) {
        printf("Element not found\n");
        return;
    }

    ht->items[q].key = EMPTY;
    ht->items[q].value = 0;

    int q_prime = q;
    while (1) {
        q_prime = (q_prime + 1) % TABLE_SIZE;
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

void print_ht(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->items[i].key == EMPTY) printf("Idx: %d: EMPTY\n", i);
        else printf("Idx %d: Key %d, Value %d\n", i, ht->items[i].key, ht->items[i].value);
    }
    printf("\n");
}

int main(void) {
    switch (TASK)
    {
        case 1: {
            HashTable ht = init_ht();

            linear_probing_insert(&ht, 10, 100);
            linear_probing_insert(&ht, 20, 200);
            linear_probing_insert(&ht, 30, 300);
            linear_probing_insert(&ht, 40, 400);
            linear_probing_insert(&ht, 50, 500);
            linear_probing_insert(&ht, 60, 600);
 
            printf("Hash Table before deletion:\n");
            print_ht(&ht);

            printf("Deleting key 30...\n");
            linear_probing_delete(&ht, 30);
            print_ht(&ht);

            break;
        }
        default:
            break;
    }

    return 0;
}