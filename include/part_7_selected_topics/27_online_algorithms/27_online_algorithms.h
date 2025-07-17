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



// ============================================================================
// CHAPTER 27.3: ONLINE CACHE MANAGEMENT
// ============================================================================



// ============================================================================
// PROBLEMS
// ============================================================================


#endif 
