#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

/*
    31.1-8
*/

static uint64_t pow_uint64(uint64_t base, uint64_t exp) {
    uint64_t res = 1;

    while (exp) {
        if (exp & 1) res *= base;
        exp >>= 1;
        if (exp) base *= base;
    }

    return res;
}

int is_perfect_kth_power(uint64_t n, uint64_t k, uint64_t* root) {
    uint64_t left = 0;
    uint64_t right = n;

    while (left <= right) {
        uint64_t mid = left + (right - left) / 2;
        uint64_t midPow = pow_uint64(mid, k);

        if (midPow == n) {
            if (root) *root = mid;
            return 1;
        } else if (midPow < n) { 
            left = mid + 1;
        } else {
            if (mid == 0) break;
            right = mid - 1;
        }
    }
    
    return 0;
}

void test_is_perfect_kth_power(void) {
    int n = 81;
    int beta = get_num_bits(n);
    int found = 0;

    for (uint64_t k = 2; k <= (uint64_t)beta; ++k) {
        uint64_t root = 0;
        if (!is_perfect_kth_power(n, k, &root)) continue;
        printf("n is a perfect %lluth power: %llu^%llu = %llu\n", k, root, k, (uint64_t)n);
        found = 1;
    }

    if (!found) printf("n is not a perfect k-th power for k in [2, %d]\n", beta);
}

/*
    31.1-12
*/

void long_division(
    uint64_t n,
    uint64_t d,
    uint64_t* quotient,
    uint64_t* remainder 
) {
    uint64_t q = 0;
    uint64_t r = 0;

    for (int i = 63; i >= 0; --i) {
        r = (r << 1) | ((n >> i) & 1);
        if (r < d) continue;
        r -= d;
        q |= (1ULL << i);
    }

    if (quotient) *quotient = q;
    if (remainder) *remainder = r;
}

void test_long_division(void) {
    uint64_t n = 81;
    uint64_t d = 9;
    uint64_t q = 0;
    uint64_t r = 0;

    long_division(n, d, &q, &r);
    printf("%llu / %llu = %llu, remainder = %llu\n", n, d, q, r);
}

/*
    31.1-13
*/

static void precompute_powers_of_two(uint64_t* powers, int maxBits) {
    powers[0] = 1;
    for (int i = 1; i <= maxBits; ++i) powers[i] = powers[i - 1] * 2;
}

static char* pad_to_power_of_two(const char* bin, int* outLen) {
    int len = strlen(bin);
    int pow2 = 1;

    while (pow2 < len) pow2 <<= 1;
    *outLen = pow2;

    char* padded = safe_malloc(pow2 + 1);
    int padLen = pow2 - len;
    for (int i = 0; i < padLen; ++i) padded[i] = '0';
    strcpy(padded + padLen, bin);
    padded[pow2] = '\0';

    return padded;
}

uint64_t bin_to_dec(const char* bin, int len, const uint64_t* powers) {
    if (len == 0) return 0;
    if (len == 1) return bin[0] == '1' ? 1 : 0;

    int mid = len / 2;

    uint64_t left = bin_to_dec(bin, mid, powers);
    uint64_t right = bin_to_dec(bin + mid, len - mid, powers);

    return left * powers[len - mid] + right;
}

void test_bin_to_dec(void) {
    const char* bin = "1010001";
    int paddedLen;
    char* padded = pad_to_power_of_two(bin, &paddedLen);

    uint64_t* powers = safe_malloc((paddedLen + 1) * sizeof(uint64_t));
    precompute_powers_of_two(powers, paddedLen);

    uint64_t dec = bin_to_dec(padded, paddedLen, powers);

    printf("Binary: %s\n", bin);
    printf("Padded binary: %s\n", padded);
    printf("Decimal: %llu\n", dec);

    safe_free(padded);
    safe_free(powers);
}

/*
    31.1-14
*/

void print_on_bulbs(int n) {
    printf("Indices of turned-on bulb after %d iterations:\n", n);
    for (int i = 1; i * i <= n; ++i) printf("%d ", i * i);
    printf("\n");
}

void test_print_on_bulbs(void) {
    int n = 100;
    print_on_bulbs(n);
}
