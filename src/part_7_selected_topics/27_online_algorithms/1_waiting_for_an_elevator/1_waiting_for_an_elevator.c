#include "part_7_selected_topics/27_online_algorithms/27_online_algorithms.h"

static void init_ski_strategy(SkiStrategy* strategy, int rentalCost, int buyCost) {
    strategy->r = rentalCost;
    strategy->b = buyCost;
    strategy->daysRented = 0;
    strategy->skisBought = 0;
}

static void ski_one_day(SkiStrategy* strategy) {
    if (strategy->skisBought) return;
    if (strategy->r * strategy->daysRented >= strategy->b) {
        strategy->skisBought = 1;
        printf("Skis bought\n");
    } else {
        strategy->daysRented++;
        if (strategy->r * strategy->daysRented >= strategy->b) {
            strategy->skisBought = 1;
            printf("Skis bought\n");
        }
    }
}

static int get_total_ski_strategy_cost(const SkiStrategy* strategy) {
    int rentalCost = strategy->r * strategy->daysRented;
    int buyCost = strategy->skisBought ? strategy->b : 0;
    return rentalCost + buyCost;
}

void test_ski_strategy(void) {
    SkiStrategy strategy;
    const int r = 10;
    const int b = 70;
    const int days = 10;
    init_ski_strategy(&strategy, r, b);

    for (int day = 1; day <= days; ++day) {
        ski_one_day(&strategy);
        printf("Day %d, total cost = %d\n", 
            day, get_total_ski_strategy_cost(&strategy));
    }
}

static void shuffle(Card* cards, int size) {
    for (int i = size - 1; i >= 0; --i) {
        int j = random_int(0, i + 1);
        Card tmp = cards[i];
        cards[i] = cards[j];
        cards[j] = tmp;
    }
}

static int find_known_pair(
    Card* cards, 
    Memory* memory, 
    int memorySize,
    int* outFirst,
    int* outSecond
) {
    for (int i = 0; i < memorySize; ++i) {
        for (int j = i + 1; j < memorySize; ++j) {
            if (cards[memory[i].knownId].matched ||
                cards[memory[j].knownId].matched ||
                strcmp(memory[i].value, memory[j].value) != 0) continue;
            *outFirst = memory[i].knownId;
            *outSecond = memory[j].knownId;
            return 1;
        }
    }
    return 0;
}

static int is_in_memory(int idx, Memory* memory, int memorySize) {
    for (int i = 0; i < memorySize; ++i) if (memory[i].knownId == idx) return 1;
    return 0;
}

void test_memory_game(void) {
    const char* animals[] = {"rabbit", "squirrel", "fox", "deer", "bear", "owl"};
    const int n = 6;
    const int totalCards = n * 2;

    Card cards[MAX_CARDS];
    Memory memory[MAX_CARDS];

    int memorySize = 0;
    int rounds = 0;

    // Prepare the deck
    for (int i = 0; i < n; ++i) {
        cards[2 * i].value = animals[i];
        cards[2 * i].id = 2 * i;
        cards[2 * i].matched = 0;

        cards[2 * i + 1].value = animals[i];
        cards[2 * i + 1].id = 2 * i + 1;
        cards[2 * i + 1].matched = 0;
    }

    srand((unsigned int)time(NULL));
    shuffle(cards, totalCards);

    while (1) {
        int unmatched = 0;
        for (int i = 0; i < totalCards; ++i) if(!cards[i].matched) unmatched++;
        if (unmatched == 0) break;
        rounds++;

        int i1 = -1;
        int i2 = -1;

        if (find_known_pair(cards, memory, memorySize, &i1, &i2)) {
            printf("Round %d: Found pair (%d, %d) -> [%s]\n",
                rounds + 1, i1, i2, cards[i1].value);
            cards[i1].matched = 1;
            cards[i2].matched = 1;
        } else {
            do { i1 = random_int(0, totalCards - 1); } while (cards[i1].matched);
            do { i2 = random_int(0, totalCards - 1); } while (cards[i2].matched || i2 == i1);

            printf("Round %d: uncovered (%d, %d) -> [%s, %s]\n",
                rounds + 1, i1, i2, cards[i1].value, cards[i2].value);

            if (strcmp(cards[i1].value, cards[i2].value) == 0) {
                cards[i1].matched = 1;
                cards[i2].matched = 1;
                printf("         => It's a match\n");
            } else {
                if (!is_in_memory(i1, memory, memorySize)) {
                    memory[memorySize].knownId = i1;
                    memory[memorySize].value = cards[i1].value;
                    memorySize++;
                }
                if (!is_in_memory(i2, memory, memorySize)) {
                    memory[memorySize].knownId = i2;
                    memory[memorySize].value = cards[i2].value;
                    memorySize++;
                }
            }

        }
    }

    printf("Ended in %d rounds. with optimum being %d\n", rounds, n);
}
