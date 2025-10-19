#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

int64_t modular_inverse(int64_t a, int64_t m) {
    int64_t x, y;
    uint64_t gcd = extended_euclid_gcd(a, m, &x, &y);
    if (gcd != 1) return -1;
    return (x % m + m) % m;
}

int64_t crt(int64_t* remainders, int64_t* moduli, int numEqs) {
    int64_t M = 1;
    for (int i = 0; i < numEqs; ++i) M *= moduli[i];

    int64_t res = 0;
    for (int i = 0; i < numEqs; ++i) {
        int64_t M_i = M / moduli[i];
        int64_t y_i = modular_inverse(M_i, moduli[i]);

        if (y_i == -1) {
            printf("Error: modular inverse does not exist\n");
            return -1;
        }
        res = (res + remainders[i] * M_i * y_i) % M;
    }

    return (res + M) % M;
}

static int factorize(int n, int64_t* factors, int64_t* powers) {
    int count = 0;
    
    if (n % 2 == 0) {
        factors[count] = 2;
        powers[count] = 0;
        while (n % 2 == 0) {
            powers[count]++;
            n /= 2;
        }
        count++;
    }
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            factors[count] = i;
            powers[count] = 0;
            while (n % i == 0) {
                powers[count]++;
                n /= i;
            }
            count++;
        }
    }
    
    if (n > 1) {
        factors[count] = n;
        powers[count] = 1;
        count++;
    }
    
    return count;
}

static int64_t power(int64_t base, int64_t exp) {
    int64_t res = 1;

    while (exp > 0) {
        if (exp % 2 == 1) res *= base;
        base *= base;
        exp /= 2;
    }

    return res;
}

int64_t modular_linear_equation_solver_crt(int a, int b, int n) {
    printf("Solving %dx = %d (mod %d) using CRT:\n", a, b, n);

    // Factorize n
    int64_t factors[20];
    int64_t powers[20];
    int numFactors = factorize(n, factors, powers);

    printf("Prime factorization of %d: ", n);
    for (int i = 0; i < numFactors; ++i) {
        printf("%lld^%lld", factors[i], powers[i]);
        if (i < numFactors - 1) printf(" * ");
    }
    printf("\n");

    // Create moduli array
    int64_t moduli[20];
    int64_t remainders[20];
    for (int i = 0; i < numFactors; ++i) {
        moduli[i] = power(factors[i], powers[i]);
        
        int64_t x, y;
        uint64_t d = extended_euclid_gcd(a, moduli[i], &x, &y);
        
        if (b % d != 0) {
            printf("No solution: gcd(%d, %lld) = %llu does not divide %d\n", 
                   a, moduli[i], d, b);
            return -1;
        }
        
        int64_t aReduced = a / d;
        int64_t bReduced = b / d;
        int64_t modReduced = moduli[i] / d;
        
        int64_t inv = modular_inverse(aReduced, modReduced);
        if (inv == -1) {
            printf("Error: inverse calculation failed\n");
            return -1;
        }
        
        int64_t x0 = (bReduced * inv) % modReduced;
        
        remainders[i] = x0;  
        
        printf("Subsystem %d: x = %lld (mod %lld)\n", i+1, remainders[i], moduli[i]);
    }

    int64_t solution = crt(remainders, moduli, numFactors);
    printf("CRT Solution: x = %lld (mod %d)\n", solution, n);
    
    // Verify
    printf("Verification: %d * %lld = %lld = %lld (mod %d)\n", 
           a, solution, (int64_t)a * solution, ((int64_t)a * solution) % n, n);
    
    return solution;
}

void test_modular_linear_equation_solver_crt(void) {
    int a = 14;
    int b = 30;
    int n = 100;
    modular_linear_equation_solver_crt(a, b, n);
}
