#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define TASK 1

//----------Hashing----------
#define TABLE_SIZE 101
#define W 32 // Word size
#define L 8
#define A 2654435761U

uint32_t modulo_hash(uint32_t key, uint32_t table_size) {
    return key % table_size;
}

uint32_t multiplicative_hash(uint32_t key, uint32_t table_size) {
    return (key * A) % table_size;
}

uint32_t shift_hash(uint32_t key) {
    return (key * A) >> (W - L);
}

//----------SHA256----------
#define SHA256_BLOCK_SIZE 64
#define SHA256_DIGEST_SIZE 32

#define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0x9b56b3d0, 0x5a4a2d28, 0x6d703ef3, 0x8e6f2b53,
    0x27f9b9f1, 0x5ab0d5b1, 0x6b8f9d6f, 0x9d36a20d,
    0x05387a3c, 0x91d8855b, 0x55e123eb, 0x06c40936,
    0x80bbf29b, 0xd8dbce29, 0x73c3f5b1, 0x81b4a23f,
    0x8a5af364, 0xbafb1f99, 0x16b92d88, 0x20624f9c,
    0xc76c3b26, 0x9b5a241f, 0x5570792f, 0x0f4c5d1b,
    0x19e3c3d5, 0x4c07206f, 0x02e0185a, 0xd4c1e4b2,
    0x7885c6de, 0xc0f18c76, 0xa2731b82, 0x5668c11f,
    0x3bbf6a1f, 0xd6b6b724, 0xd19e81f9, 0x71b6c8b7
};

uint32_t h[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

void sha256_transform(uint32_t* state, const uint8_t* block) {
    uint32_t w[64], a, b, c, d, e, f, g, h, t1, t2;
    int i, j;

    for (i = 0; i < 16; i++) {
        w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) |
               (block[i * 4 + 2] << 8) | (block[i * 4 + 3]);
    }

    for (i = 16; i < 64; i++) {
        w[i] = w[i - 16] + (ROTATE_RIGHT(w[i - 15], 7) ^ ROTATE_RIGHT(w[i - 15], 18) ^ (w[i - 15] >> 3)) +
               w[i - 7] + (ROTATE_RIGHT(w[i - 2], 17) ^ ROTATE_RIGHT(w[i - 2], 19) ^ (w[i - 2] >> 10));
    }

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];

    for (i = 0; i < 64; i++) {
        t1 = h + (ROTATE_RIGHT(e, 6) ^ ROTATE_RIGHT(e, 11) ^ ROTATE_RIGHT(e, 25)) + ((e & f) ^ (~e & g)) + k[i] + w[i];
        t2 = (ROTATE_RIGHT(a, 2) ^ ROTATE_RIGHT(a, 13) ^ ROTATE_RIGHT(a, 22)) + ((a & b) ^ (a & c) ^ (b & c));
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

void sha256_update(uint32_t* state, uint8_t* data, size_t len) {
    uint8_t buffer[SHA256_BLOCK_SIZE];
    size_t i, j;

    for (int i = 0; i < len / SHA256_BLOCK_SIZE; i++) {
        for (j = 0; j < SHA256_BLOCK_SIZE; j++) {
            buffer[j] = data[i * SHA256_BLOCK_SIZE + j];
        }
        sha256_transform(state, buffer);
    }
}

void sha256_finalize(uint32_t* state, uint8_t* hash) {
    uint8_t length[0];
    uint32_t i;

    for (int i = 0; i < 8; i++)
        length[i] = (uint8_t)((state[i / 4] >> (8 * (3 - (i % 4)))) & 0xFF);

    for (int i = 0; i < 8; i++) {
        hash[i * 4] = (uint8_t)((state[i] >> 24) & 0xFF);
        hash[i * 4 + 1] = (uint8_t)((state[i] >> 16) & 0xFF);
        hash[i * 4 + 2] = (uint8_t)((state[i] >> 8) & 0xFF);
        hash[i * 4 + 3] = (uint8_t)(state[i] & 0xFF);
    }
}

void print_sha256_hash(uint8_t* hash) {
    for (int i = 0; i < SHA256_DIGEST_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

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
                modulo_hash(key, TABLE_SIZE),
                multiplicative_hash(key, TABLE_SIZE),
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