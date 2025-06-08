#ifndef HASH_TABLES_H
#define HASH_TABLES_H

#include "../../common.h"
#include "../part_3_commons.h"

// ============================================================================
// CHAPTER 11.1: DIRECT-ADDRESS TABLES
// ============================================================================

#define DAT_SIZE 1000

typedef struct {
    int value;
    int isPresent;
} DirectAccessTable;

void dat_init(DirectAccessTable* dat);
void dat_insert(DirectAccessTable* dat, int key, int value);
int dat_search(DirectAccessTable* dat, int key);
void dat_delete(DirectAccessTable* dat, int key);
int dat_find_max_key(DirectAccessTable* dat, int idx);
int dat_get_max_key(DirectAccessTable* dat);

#define BIT_VECTOR_SIZE 20

typedef unsigned int BitVector;

void bv_init(BitVector* bv);
void bv_set_bit(BitVector* bv, int idx);
void bv_clear_bit(BitVector* bv, int idx);
int bv_check_bit(BitVector bv, int idx);
void print_bit_vector(BitVector bv);

typedef struct DllDatElement {
    int satellite_data;
    struct DllDatElement* prev;
    struct DllDatElement* next;
} DllDatElement;

typedef struct DllDirectAccessTable {
    DllDatElement* head;
} DllDirectAccessTable;

void dll_dat_init(DllDirectAccessTable* dllDat);
void dll_dat_insert(DllDirectAccessTable* dllDat, int key, int sattelite_data);
DllDatElement* dll_dat_search(DllDirectAccessTable* dllDat, int key);
void dll_dat_delete(
    DllDirectAccessTable* dllDat, 
    int key, 
    DllDatElement* target
);
void print_dll_dat(DllDirectAccessTable* dllDat, int key);

typedef struct HugeArrayEntry {
    int key;
    int* stackPtr;
} HugeArrayEntry;

typedef struct  DirectAddressDict {
    HugeArrayEntry* arr;
    int* stack;
    int stack_size;
} DirectAddressDict;

void da_dict_init(DirectAddressDict* daDict);
void da_dict_insert(DirectAddressDict* daDict, int key);
int da_dict_search(DirectAddressDict* daDict, int key);
void da_dict_delete(DirectAddressDict* daDict, int key);
void print_da_dict(DirectAddressDict* daDict);

// ============================================================================
// CHAPTER 11.2: HASH TABLES
// ============================================================================

#define HASH_TABLE_SIZE 101

typedef struct CharNode {
    char* key;
    int value;
    struct CharNode* next;
} CharNode;

typedef struct HashTable {
    CharNode* buckets[HASH_TABLE_SIZE];
} HashTable;

unsigned int hash(const char* key);
HashTable* ht_init();
void ht_insert(HashTable* ht, const char* key, int val);
int ht_search(HashTable* ht, const char* key, int* outVal);
void ht_delete(HashTable* ht, const char* key);
void ht_free(HashTable* ht);

typedef struct FreeSlot {
    int idx;
    struct FreeSlot *prev, *next;
} FreeSlot;

typedef struct FreeSlotsHashTable {
    CharNode* buckets[HASH_TABLE_SIZE];
    int flags[HASH_TABLE_SIZE]; // 1 - occupied, 0 - free
    FreeSlot* free_list_head;
} FreeSlotsHashTable;

FreeSlotsHashTable* fsht_init();
void fsht_insert(FreeSlotsHashTable* fsht, const char* key, int val);
void fsht_delete(FreeSlotsHashTable* fsht, const char* key);
void fsht_free(FreeSlotsHashTable* fsht);

char* ht_get_random_key(HashTable* ht);

// ============================================================================
// CHAPTER 11.3: HASH FUNCTIONS
// ============================================================================

#define HASH_TABLE_SIZE 101
#define W 32 // Word size
#define L 8
#define A 2654435761U

int hash_function(int key);
uint32_t modulo_hash(uint32_t key, uint32_t table_size);
uint32_t multiplicative_hash(uint32_t key, uint32_t table_size);
uint32_t shift_hash(uint32_t key);

#define SHA256_BLOCK_SIZE 64
#define SHA256_DIGEST_SIZE 32

#define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

extern const uint32_t k[64];
extern const uint32_t h[8];

void sha256_transform(uint32_t* state, const uint8_t* block);
void sha256_update(uint32_t* state, uint8_t* data, size_t len);
void sha256_finalize(uint32_t* state, uint8_t* hash);
void print_sha256_hash(uint8_t* hash);

// ============================================================================
// CHAPTER 11.4: OPEN ADDRESSING
// ============================================================================

#define EMPTY -1
#define DELETED -2

typedef struct HashItem {
    int key;
    int value;
} HashItem;

typedef struct HashTable2 {
    HashItem items[HASH_TABLE_SIZE];
} HashTable2;

HashTable2 ht2_init();
void linear_probing(HashTable2* ht, int key, int val);
void quadratic_probing(HashTable2* ht, int key, int val);
int ht2_search(HashTable2* ht, int key);
void ht2_display(HashTable2 *ht);

int hash_shift(int key, int i);
void hash_insert(HashTable2 *ht, int key, int value);
int hash_delete(HashTable2* ht, int key);

// ============================================================================
// CHAPTER 11.5: PERFECT HASHING
// ============================================================================

void linear_probing_insert(HashTable2* ht, int key, int value);
int linear_probing_search(HashTable2* ht, int key);
void linear_probing_delete(HashTable2* ht, int key);
void print_ht2(HashTable2* ht);

#endif // HASH_TABLES_H