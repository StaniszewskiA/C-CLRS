#include <stdio.h>
#include <stdlib.h>

#define TASK 3
#define TABLE_SIZE 10
#define EMPTY -1
#define DELETED -2

//-----Probing-----
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

void linear_probing(HashTable* ht, int key, int val) {
    int idx = hash_function(key);
    int original_idx = idx;

    while (ht->items[idx].key != EMPTY) {
        idx = (idx + 1) % TABLE_SIZE;
        if (idx == original_idx) {
            printf("Hash table is full!\n");
            return;
        }
    }

    ht->items[idx].key = key;
    ht->items[idx].value = val;
}

void quadratic_probing(HashTable* ht, int key, int val) {
    int idx = hash_function(key);
    int i = 0;

    while (ht->items[(idx + i * i) % TABLE_SIZE].key != EMPTY) {
        i++;
        if (i == TABLE_SIZE) {
            printf("Hash table is full!\n");
            return;
        }
    }

    idx = (idx + i * i) % TABLE_SIZE;
    ht->items[idx].key = key;
    ht->items[idx].value = val;
}

int search(HashTable* ht, int key) {
    int idx = hash_function(key);
    int i = 0;
    
    while (ht->items[(idx + i * i) % TABLE_SIZE].key != EMPTY) {
        int newIdx = (idx + i * i) % TABLE_SIZE;
        if (ht->items[newIdx].key == key) {
            return ht->items[newIdx].value;
        }
        i++;
        if (i == TABLE_SIZE) break;
    }
    return -1;
}

void display_ht(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
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
    return (key + i) % TABLE_SIZE;
}

void hash_insert(HashTable *ht, int key, int value) {
    int i = 0;
    int idx;

    while (i < TABLE_SIZE) {
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

int hash_delete(HashTable* ht, int key) {
    int i = 0;
    int idx;

    while (i < TABLE_SIZE) {
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

int main(void) {
    switch (TASK)
    {
        case 1: {
            HashTable ht = init_ht();

            linear_probing(&ht, 10, 100);
            linear_probing(&ht, 20, 200);
            linear_probing(&ht, 30, 300);
            linear_probing(&ht, 40, 400);

            printf("Hash Table after Linear Probing Insertions:\n");
            display_ht(&ht);

            break;
        }
        case 2: {
            HashTable ht = init_ht();

            quadratic_probing(&ht, 10, 100);
            quadratic_probing(&ht, 20, 200);
            quadratic_probing(&ht, 30, 300);
            quadratic_probing(&ht, 40, 400);

            printf("Hash Table after Quadratic Probing Insertions:\n");
            display_ht(&ht);

            break;
        }
        case 3: {
            HashTable ht = init_ht();

            hash_insert(&ht, 10, 100);
            hash_insert(&ht, 20, 200);
            hash_insert(&ht, 30, 300);
            hash_insert(&ht, 40, 400);

            printf("Hash Table after Quadratic Probing Insertions:\n");
            display_ht(&ht);

            hash_delete(&ht, 20);
            hash_delete(&ht, 30);

            printf("\nHash Table after Deletions:\n");
            display_ht(&ht);

            break;
        }
        default:
            break;
    }

    return 0;
}