#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

void rsa_generate_keys(int64_t p, int64_t q, int64_t* n, int64_t* e, int64_t* d) {
    *n = p * q;
    int64_t phi = (p - 1) * (q - 1);
    *e = 3;
    while (euclid_gcd(*e, phi) != 1) (*e)++;
    *d = modular_inverse(*e, phi);
}

int64_t rsa_encrypt(int64_t m, int64_t e, int64_t n) {
    return modular_exponentation(m, e, n);
}

int64_t rsa_decrypt(int64_t c, int64_t d, int64_t n) {
    return modular_exponentation(c, d, n);
}

void test_simple_rsa(void) {
    int64_t p = 61;
    int64_t q = 53;
    int64_t n, e, d;
    rsa_generate_keys(p, q, &n, &e, &d);

    printf("RSA keys:\n");
    printf("p = %lld, q = %lld\n", p, q);
    printf("n = %lld\n", n);
    printf("e = %lld (public)\n", e);
    printf("d = %lld (private)\n", d);

    int64_t msg = 65;
    int64_t encrypted = rsa_encrypt(msg, e, n);
    int64_t decrypted = rsa_decrypt(encrypted, d, n);

    printf("Original message: %lld\n", msg);
    printf("Encrypted: %lld\n", encrypted);
    printf("Decrypted: %lld\n", decrypted);
}