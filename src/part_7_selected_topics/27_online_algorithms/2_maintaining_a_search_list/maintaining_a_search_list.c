#include "part_7_selected_topics/27_online_algorithms/27_online_algorithms.h"

void mft_list_init(uchar* list) {
    for (int i = 0; i < ALPHABET_SIZE; ++i) list[i] = (uchar)i;
}

int move_to_front(uchar* list, uchar ch) {
    int idx = 0;
    while (list[idx] != ch && idx < ALPHABET_SIZE) ++idx;

    for (int i = idx; i > 0; --i) list[i] = list[i - 1];
    list[0] = ch;

    return idx;
}

void test_move_to_front(void) {
    uchar mftList[ALPHABET_SIZE];
    mft_list_init(mftList);
    const char* testInput = "testtest";

    for (size_t i = 0; i < strlen(testInput); ++i) {
        uchar ch = (uchar)testInput[i];
        int idx = move_to_front(mftList, ch);
        printf("Character '%c' -> index %d\n", ch, idx);
    }
}

void fc_list_init(FCEntry* list) {
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        list[i].ch = (uchar)i;
        list[i].cnt = 0;
    }
}

int frequency_count(FCEntry* list, uchar ch) {
    int idx = 0;

    while (idx < ALPHABET_SIZE && list[idx].ch != ch) ++idx;

    list[idx].cnt++;

    while (idx > 0 && list[idx].cnt > list[idx - 1].cnt) {
        FCEntry tmp = list[idx];
        list[idx] = list[idx - 1];
        list[idx - 1] = tmp;
        --idx;
    }

    return idx;
}

void test_frequency_count(void) {
    FCEntry fcList[ALPHABET_SIZE];
    fc_list_init(fcList);

    const char* testInput = "testtest";

    for (size_t i = 0; i < strlen(testInput); ++i) {
        uchar ch = (uchar)testInput[i];
        int idx = frequency_count(fcList, ch);
        printf("Character '%c' -> index %d\n", ch, idx);
    }

    printf("Final list state:\n");
    for (int i = 0; i < 10; ++i) 
        printf("Char '%c', count %d\n", fcList[i].ch, fcList[i].cnt);
}
