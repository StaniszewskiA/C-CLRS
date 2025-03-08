#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TASK 3

//----------Hash Table with Singly Linked List----------
#define TABLE_SIZE 100

typedef struct Node {
    // Deletions can be sped up by using Doubly Linked Lists
    char* key;
    int value;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node* buckets[TABLE_SIZE];
} HashTable;

unsigned int hash(const char* key) {
    unsigned long int hash_val = 0;
    while (*key)
        hash_val = (hash_val << 5) + *(key++);
    return hash_val % TABLE_SIZE;
}

HashTable* init_ht() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) {
        printf("Malloc failed\n");
        return NULL;
    }

    for (int i = 0; i < TABLE_SIZE; i++)
        ht->buckets[i] = NULL;

    return ht;
}

void insert_ht(HashTable* ht, const char* key, int val) {
    unsigned int idx = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Malloc failed\n");
        return;
    }

    newNode->key = strdup(key);  
    if (!newNode->key) {
        printf("Malloc failed for key\n");
        free(newNode);
        return;
    }

    newNode->value = val;
    newNode->next = ht->buckets[idx];
    ht->buckets[idx] = newNode;
}

int search_ht(HashTable* ht, const char* key, int *out_val) {
    unsigned int idx = hash(key);
    Node* node = ht->buckets[idx];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            *out_val = node->value;
            return 1;
        }
        node = node->next;
    }

    return 0;
}

void delete_ht(HashTable* ht, const char* key) {
    unsigned int idx = hash(key);
    Node* node = ht->buckets[idx];
    Node* prev = NULL;
    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) prev->next = node->next;
            else ht->buckets[idx] = node->next;
        }
        free(node->key);
        free(node);
        return;
    }
    prev = node;
    node = node->next;
}

void free_ht(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *node = ht->buckets[i];
        while (node) {
            Node* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(ht);
}

//----------Hash Table with Free Slots----------
typedef struct FreeSlot {
    int idx;
    struct FreeSlot *prev, *next;
} FreeSlot;

typedef struct FreeSlotsHashTable {
    Node* buckets[TABLE_SIZE];
    int flags[TABLE_SIZE]; // 1 - occupied, 0 - free
    FreeSlot* free_list_head;
} FreeSlotsHashTable;

FreeSlotsHashTable* init_fsht() {
    FreeSlotsHashTable* fsht = (FreeSlotsHashTable*)malloc(
        sizeof(FreeSlotsHashTable)
    );
    if (!fsht) {
        printf("Malloc failed.\n");
        return NULL;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        fsht->buckets[i] = NULL;
        fsht->flags[i] = 0;
    }

    FreeSlot *prev = NULL;
    for (int i = 0; i < TABLE_SIZE; i++) {
        FreeSlot *slot = (FreeSlot *)malloc(sizeof(FreeSlot));
        slot->idx = i;
        slot->prev = prev;
        slot->next = NULL;
        if (prev) prev->next = slot;
        else fsht->free_list_head = slot;
        prev = slot;
    }

    return fsht;
}

void insert_fsht(FreeSlotsHashTable* fsht, const char* key, int val) {
    unsigned int idx = hash(key);

    if (fsht->flags[idx] == 0) {
        FreeSlot* slot = fsht->free_list_head;
        if (slot) {
            fsht->free_list_head = slot->next;
            if (fsht->free_list_head)
                fsht->free_list_head->prev = NULL;  
            free(slot);
        }
        fsht->flags[idx] = 1;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = val;
    newNode->next = fsht->buckets[idx];
    fsht->buckets[idx] = newNode;
}

void delete_fsht(FreeSlotsHashTable* fsht, const char* key) {
    unsigned int idx = hash(key);
    Node* node = fsht->buckets[idx], *prev = NULL;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) prev->next = node->next;
            else fsht->buckets[idx] = node->next;

            free(node->key);
            free(node);

            if (!fsht->buckets[idx]) {
                fsht->flags[idx] = 0;

                FreeSlot* slot = (FreeSlot*)malloc(sizeof(FreeSlot));
                slot->idx = idx;
                slot->next = fsht->free_list_head;
                
                if (fsht->free_list_head) 
                    fsht->free_list_head->prev = slot;

                fsht->free_list_head = slot;
                slot->prev = NULL;  
            }
            return;
        }
        prev = node;
        node = node->next;
    }
}

void free_fsht(FreeSlotsHashTable* fsht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = fsht->buckets[i];
        while (node) {
            Node *temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }

    FreeSlot* slot = fsht->free_list_head;
    while (slot) {
        FreeSlot* temp = slot;
        slot = slot->next;
        free(temp);
    }

    free(fsht);
}

//----------Fetching random key from Hash Table----------
char* get_random_key(HashTable* ht) {
    int non_empty_buckets[TABLE_SIZE];
    int count = 0;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->buckets[i]) non_empty_buckets[count++] = i;
    }

    if (count == 0) return NULL;    

    int rand_idx = non_empty_buckets[rand() % count];
    Node* node = ht->buckets[rand_idx];
    int length = 0;

    for (Node* temp = node; temp; temp = temp->next) {
        length++;
    }

    int chosen = rand() % length;

    for (int i = 0; i < chosen; i++) {
        node = node->next;
    }

    return node->key;
}

int main(void) {
    switch (TASK)
    {
        case 1: {
            HashTable* ht = init_ht();
            insert_ht(ht, "key1", 42);
            insert_ht(ht, "key2", 99);

            int val = 42;
            if (search_ht(ht, "key1", &val)) {
                printf("Found key1: %d\n", val);
            } else {
                printf("Key1 not found\n");
            }

            delete_ht(ht, "key1");
            if (search_ht(ht, "key1", &val)) {
                printf("Found key1: %d\n", val);
            } else {
                printf("Key1 not found\n");
            }

            free_ht(ht);

            break;
        }    
        case 2: {
            FreeSlotsHashTable* fsht = init_fsht();

            insert_fsht(fsht, "key1", 42);
            insert_fsht(fsht, "key1", 99);

            delete_fsht(fsht, "key1");

            free_fsht(fsht);

            break;
        }
        case 3: {
            srand(time(NULL));
            HashTable* ht = init_ht();

            insert_ht(ht, "key1", 10);
            insert_ht(ht, "key2", 20);
            insert_ht(ht, "key3", 30);

            char* random_key = get_random_key(ht);

            if (random_key) {
                printf("Random key: %s\n", random_key);
            } else {
                printf("HashTable is empty\n");
            }
            free_ht(ht);

            break;
        }
        default:
            break;
    }
    return 0;
}