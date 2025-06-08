#include "part_3_data_structures/11_hash_tables/hash_tables.h"

#define TASK 1

int main(void) {
    switch (TASK)
    {
    case 1: {
        const uint32_t keys[] = {123, 456, 789, 1024, 2048};
        const size_t n = sizeof(keys) / sizeof(keys[0]);

        printf("Key    Modular Multiplication Shift SHA-256\n");
        for (size_t i = 0; i < n; i++) {
            uint32_t key = keys[i];
            uint32_t state[8];
            memcpy(state, h, sizeof(h));

            printf("%-6u %-7u %-14u %-6u", key,
                modulo_hash(key, HASH_TABLE_SIZE),
                multiplicative_hash(key, HASH_TABLE_SIZE),
                shift_hash(key));

            uint8_t hash[SHA256_DIGEST_SIZE];
            sha256_update(state, (uint8_t*)&key, sizeof(key));
            sha256_finalize(state, hash);
            print_sha256_hash(hash);
        }

        break;
    }
    default:
        break;
    }

    return 0;
}