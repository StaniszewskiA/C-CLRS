#ifndef ONLINE_ALGORITHMS_H
#define ONLINE_ALGORITHMS_H

#include "../../common.h"
#include "../part_7_commons.h"


#define THREAD_LIMIT 16

// ============================================================================
// CHAPTER 27.1: WAITING FOR AN ELEVATOR
// ============================================================================

typedef struct {
    int r;          // Daily cost
    int b;          // Buying cost
    int daysRented;
    int skisBought; // Could be boolean
} SkiStrategy;

void test_ski_strategy(void);

#define MAX_CARDS 100

typedef struct {
    int id;
    const char* value;
    int matched;
} Card;

typedef struct {
    int knownId;
    const char* value;
} Memory;

void test_memory_game(void);

// ============================================================================
// CHAPTER 27.2: MAINTAINING A SEARCH LIST
// ============================================================================

#define ALPHABET_SIZE 256
#define uchar unsigned char

void mft_list_init(uchar* list);
int move_to_front(uchar* list, uchar ch);
void test_move_to_front(void);

typedef struct {
    uchar ch;
    int cnt;
} FCEntry;

void fc_list_init(FCEntry* list);
int frequency_count(FCEntry* list, uchar ch);
void test_frequency_count(void);

// ============================================================================
// CHAPTER 27.3: ONLINE CACHE MANAGEMENT
// ============================================================================

#define CACHE_SIZE 4
#define MAX_REQUESTS 1024

typedef struct {
    int page;
    int time; 
    int freq;
    int valid;
} CacheEntry;

typedef int (*CacheSimFn)(const int*, int, int);

int fifo_cache(const int* requests, int numRequests, int cacheSize);
int lifo_cache(const int* requests, int numRequests, int cacheSize);
int lru_cache(const int* requests, int numRequests, int cacheSize);
int lfu_cache(const int* requests, int numRequests, int cacheSize);
void test_deterministic_caches(void);

typedef struct {
    int page;
    int marked;
    int valid;
} MarkedCacheEntry;

int randomized_marking_cache(const int* requests, int numRequests, int cacheSize);
void test_non_deterministic_caches(void);

// ============================================================================
// PROBLEMS
// ============================================================================


#endif 
