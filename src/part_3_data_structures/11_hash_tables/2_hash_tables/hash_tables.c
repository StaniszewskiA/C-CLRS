#include "part_3_data_structures/11_hash_tables/hash_tables.h"

unsigned int hash(const char* key) {
    unsigned long int hash_val = 0;
    while (*key)
        hash_val = (hash_val << 5) + *(key++);
    return hash_val % HASH_TABLE_SIZE;
}

HashTable* ht_init() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) {
        printf("Malloc failed\n");
        return NULL;
    }

    for (int i = 0; i < HASH_TABLE_SIZE; i++)
        ht->buckets[i] = NULL;

    return ht;
}

void ht_insert(HashTable* ht, const char* key, int val) {
    unsigned int idx = hash(key);
    CharNode* newNode = (CharNode*)malloc(sizeof(CharNode));
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

int ht_search(HashTable* ht, const char* key, int* outVal) {
    unsigned int idx = hash(key);
    CharNode* node = ht->buckets[idx];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            *outVal = node->value;
            return 1;
        }
        node = node->next;
    }

    return 0;
}

void ht_delete(HashTable* ht, const char* key) {
    unsigned int idx = hash(key);
    CharNode* node = ht->buckets[idx];
    CharNode* prev = NULL;
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

void ht_free(HashTable* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        CharNode *node = ht->buckets[i];
        while (node) {
            CharNode* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(ht);
}

FreeSlotsHashTable* fsht_init() {
    FreeSlotsHashTable* fsht = (FreeSlotsHashTable*)malloc(
        sizeof(FreeSlotsHashTable)
    );
    if (!fsht) {
        printf("Malloc failed.\n");
        return NULL;
    }

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        fsht->buckets[i] = NULL;
        fsht->flags[i] = 0;
    }

    FreeSlot *prev = NULL;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
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

void fsht_insert(FreeSlotsHashTable* fsht, const char* key, int val) {
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

    CharNode* newNode = (CharNode*)malloc(sizeof(CharNode));
    newNode->key = strdup(key);
    newNode->value = val;
    newNode->next = fsht->buckets[idx];
    fsht->buckets[idx] = newNode;
}

void fsht_delete(FreeSlotsHashTable* fsht, const char* key) {
    unsigned int idx = hash(key);
    CharNode* node = fsht->buckets[idx], *prev = NULL;

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

void fsht_free(FreeSlotsHashTable* fsht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        CharNode* node = fsht->buckets[i];
        while (node) {
            CharNode *temp = node;
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

char* ht_get_random_key(HashTable* ht) {
    int non_empty_buckets[HASH_TABLE_SIZE];
    int count = 0;
    
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (ht->buckets[i]) {
            non_empty_buckets[count++] = i;
        }
    }

    if (count == 0) return NULL;    

    int rand_bucket_idx = non_empty_buckets[rand() % count];
    CharNode* node = ht->buckets[rand_bucket_idx];
    
    int length = 0;
    for (CharNode* temp = node; temp; temp = temp->next) {
        length++;
    }

    int chosen = rand() % length;
    for (int i = 0; i < chosen; i++) {
        node = node->next;
    }

    return node->key;
} 