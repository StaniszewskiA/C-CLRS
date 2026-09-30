#include "part_7_selected_topics/33_machine_learning_algorithms/33_machine_learning_algorithms.h"

void weighted_majority(
    const int* preds,
    const int* outcomes,
    int T,
    int n,
    double gamma,
    double* weights,
    int* p
) {
    for (int i = 0; i < n; ++i) weights[i] = 1.0;

    for (int t = 0; t < T; ++t) {
        const int* q = &preds[t * n];

        double upweight = 0.0;
        double downweight = 0.0;

        for (int i = 0; i < n; ++i) {
            if (q[i] == 1) upweight += weights[i];
            else downweight += weights[i];
        }

        p[t] = upweight > downweight ? 1 : 0;

        for (int i = 0; i < n; ++i) {
            if (q[i] != outcomes[t]) weights[i] *= 1 - gamma;
        }
    }
}

static int mwu_count_mistakes(
    const int* guesses,
    const int* outcomes,
    int T,
    int stride
) {
    int mistakes = 0;
    for (int t = 0; t < T; ++t) {
        if (guesses[t * stride] != outcomes[t]) mistakes++;
    }
    return mistakes;
}

static void mwu_print_run(
    const int* preds,
    const int* outcomes,
    const int* p,
    const double* weights,
    int T,
    int n
) {
    printf("Round | ");
    for (int i = 0; i < n; ++i) printf("E%d ", i + 1);
    printf("| p | o\n");

    for (int t = 0; t < T; ++t) {
        printf("%5d | ", t + 1);
        for (int i = 0; i < n; ++i) printf("%2d ", preds[t * n + i]);
        printf("| %d | %d%s\n", p[t], outcomes[t], p[t] != outcomes[t] ? "  <- mistake" : "");
    }

    printf("Expert mistakes: ");
    for (int i = 0; i < n; ++i) {
        printf("E%d=%d ", i + 1, mwu_count_mistakes(&preds[i], outcomes, T, n));
    }
    if (weights != NULL) {
        printf("\nFinal weights:   ");
        for (int i = 0; i < n; ++i) printf("%.4f ", weights[i]);
    }
    printf("\nAlgorithm mistakes: %d\n", mwu_count_mistakes(p, outcomes, T, 1));
}

void test_weighted_majority(void) {
    int outcomes[MWU_N_ROUNDS] = {1, 0, 1, 1, 0, 0, 1, 0, 1, 1};
    int preds[MWU_N_ROUNDS][MWU_N_EXPERTS] = {
        {1, 0, 0, 1},
        {0, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 1, 0, 0}
    };

    int T = ARRAY_SIZE(outcomes);
    int n = ARRAY_SIZE(preds[0]);
    double weights[MWU_N_EXPERTS];
    int p[MWU_N_ROUNDS];

    print_separator("Weighted majority, gamma = 1/2");
    weighted_majority(&preds[0][0], outcomes, T, n, 0.5, weights, p);
    mwu_print_run(&preds[0][0], outcomes, p, weights, T, n);

    print_separator("Weighted majority, gamma = 1");
    weighted_majority(&preds[0][0], outcomes, T, n, 1.0, weights, p);
    mwu_print_run(&preds[0][0], outcomes, p, weights, T, n);
    printf("Lemma 33.3 bound floor(lg n): %d\n", (int)floor(log2(n)));
}

// 33.2-1
int halving_with_reset(
    const int* preds,
    const int* outcomes,
    int T,
    int n,
    int* p
) {
    int in_s[n];
    for (int i = 0; i < n; ++i) in_s[i] = 1;
    int s_size = n;

    int resets = 0;

    for (int t = 0; t < T; ++t) {
        const int* q = &preds[t * n];

        int up = 0;
        int down = 0;

        for (int i = 0; i < n; ++i) {
            if (!in_s[i]) continue;
            if (q[i] == 1) up++;
            else down++;
        }

        p[t] = up > down ? 1 : 0;

        for (int i = 0; i < n; ++i) {
            if (!in_s[i] || q[i] == outcomes[t]) continue;
            in_s[i] = 0;
            s_size--;
        }
        // this probably should be reverted later
        if (s_size != 0) continue;

        for (int i = 0; i < n; ++i) in_s[i] = 1;
        s_size = n;
        resets++;
    }

    return resets;
}

void test_halving_with_reset(void) {
    int outcomes[MWU_N_ROUNDS] = {1, 0, 1, 1, 0, 0, 1, 0, 1, 1};
    int preds[MWU_N_ROUNDS][MWU_N_EXPERTS] = {
        {1, 0, 0, 1},
        {1, 1, 0, 0},
        {1, 1, 1, 0},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 1, 0, 1},
        {0, 0, 1, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 0}
    };

    int T = ARRAY_SIZE(outcomes);
    int n = ARRAY_SIZE(preds[0]);
    int p[MWU_N_ROUNDS];

    print_separator("Halving with reset (33.2-1)");
    int resets = halving_with_reset(&preds[0][0], outcomes, T, n, p);
    mwu_print_run(&preds[0][0], outcomes, p, NULL, T, n);

    int m = 0;
    for (int i = 0; i < n; ++i) m += mwu_count_mistakes(&preds[0][i], outcomes, T, n);

    printf("Resets of S: %d\n", resets);
    printf("Bound m * ceil(lg n) = %d * %d = %d\n", m, (int)ceil(log2(n)), m * (int)ceil(log2(n)));

}

// 33.2-3
void randomized_halving(
    const int* preds,
    const int* outcomes,
    int T,
    int n,
    int* p
) {
    int in_s[n];
    for (int i = 0; i < n; ++i) in_s[i] = 1;
    int s_size = n;

    for (int t = 0; t < T; ++t) {
        const int* q = &preds[t * n];

        // pick the r-th expert uniformly as random
        int r = rand() % s_size;
        int chosen = -1;
        for (int i = 0; i < n; ++i) {
            if (!in_s[i]) continue;
            if (r-- == 0) {
                chosen = i;
                break;
            }
        }

        p[t] = q[chosen];

        for (int i = 0; i < n; ++i) {
            if (!in_s[i] || q[i] == outcomes[t]) continue;
            in_s[i] = 0;
            s_size--;
        }
    }
}

void test_randomized_halving(void) {
    srand(time(NULL));

    int outcomes[MWU_N_ROUNDS] = {1, 0, 1, 1, 0, 0, 1, 0, 1, 1};
    int preds[MWU_N_ROUNDS][MWU_N_EXPERTS] = {
        {1, 0, 0, 1},
        {0, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 1, 0, 0}
    };

    int T = ARRAY_SIZE(outcomes);
    int n = ARRAY_SIZE(preds[0]);
    int p[MWU_N_ROUNDS];

    print_separator("Randomized halving (33.2-3), single run");
    randomized_halving(&preds[0][0], outcomes, T, n, p);
    mwu_print_run(&preds[0][0], outcomes, p, NULL, T, n);

    long totalMistakes = 0;
    for (int trial = 0; trial < MWU_N_TRIALS; ++trial) {
        randomized_halving(&preds[0][0], outcomes, T, n, p);
        totalMistakes += mwu_count_mistakes(p, outcomes, T, 1);
    }

    int in_s[MWU_N_EXPERTS];
    for (int i = 0; i < n; ++i) in_s[i] = 1;
    int s_size = n;
    double expected = 0.0;

    for (int t = 0; t < T; ++t) {
        int wrong = 0;
        for (int i = 0; i < n; ++i) {
            if (in_s[i] && preds[t][i] != outcomes[t]) wrong++;
        }
        expected += (double)wrong / s_size;

        for (int i = 0; i < n; ++i) {
            if (in_s[i] && preds[t][i] != outcomes[t]) in_s[i] = 0;
        }
        s_size -= wrong;
    }

    double harmonic = 0.0;
    for (int j = 2; j <= n; ++j) harmonic += 1.0 / j;

    print_separator("Randomized halving (33.2-3), expectation");
    printf("Average mistakes over %d runs: %.4f\n", 
        MWU_N_TRIALS, (double)totalMistakes / MWU_N_TRIALS
    );
    printf("Exact E[mistakes] = sum b_t / s_t: %.4f\n", expected);
    printf("H_n - 1: %.4f\n", harmonic);
    printf("ln n: %.4f\n", log(n));
    printf("ceil(lg n): %d\n", (int)ceil(log2(n)));
}

// 33.2-4
void randomized_weighted_majority(
    const int* preds,
    const int* outcomes,
    int T,
    int n,
    double epsilon,
    double* weights,
    int* p
) {
    for (int i = 0; i < n; ++i) weights[i] = 1.0;

    for (int t = 0; t < T; ++t) {
        const int* q = &preds[t * n];

        double total = 0.0;
        for (int i = 0; i < n; ++i) total += weights[i];

        // pick expert i with probability weights[i] / total
        double r = (double)rand() / ((double)RAND_MAX + 1.0) * total;
        int chosen = n - 1;
        for (int i = 0; i < n; ++i) {
            r -= weights[i];
            if (r < 0.0) {
                chosen = i;
                break;
            }
        }

        p[t] = q[chosen];

        for (int i = 0; i < n; ++i) {
            if (q[i] != outcomes[t]) weights[i] *= 1 - epsilon;
        }
    }
}

void test_randomized_weighted_majority(void) {
    srand(time(NULL));

    // no expert is always right
    int outcomes[MWU_N_ROUNDS] = {1, 0, 1, 1, 0, 0, 1, 0, 1, 1};
    int preds[MWU_N_ROUNDS][MWU_N_EXPERTS] = {
        {1, 0, 0, 1},
        {1, 1, 0, 0},
        {1, 1, 1, 0},
        {1, 0, 1, 0},
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 1, 0, 1},
        {0, 0, 1, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 0}
    };

    int T = ARRAY_SIZE(outcomes);
    int n = ARRAY_SIZE(preds[0]);
    double weights[MWU_N_EXPERTS];
    int p[MWU_N_ROUNDS];

    int mStar = T;
    for (int i = 0; i < n; ++i) {
        int mistakes = mwu_count_mistakes(
            &preds[0][i], outcomes, T, n
        );
        if (mistakes < mStar) mStar = mistakes;
    }

    print_separator("Randomized WM (33.2-4), single run, eps = 1/4");
    randomized_weighted_majority(&preds[0][0], outcomes, T, n, 0.25, weights, p);
    mwu_print_run(&preds[0][0], outcomes, p, weights, T, n);

    double epsilons[] = {0.1, 0.25, 0.4};
    int nEpsilons = ARRAY_SIZE(epsilons);

    print_separator("Randomized WM (33.2-4), expectation");
    printf("m* = %d, n = %d, %d runs per eps\n", mStar, n, MWU_N_TRIALS);
    printf("  eps | average | exact E[M] | (1 + eps) m* + ln(n) / eps\n");

    for (int e = 0; e < nEpsilons; ++e) {
        double eps = epsilons[e];

        long totalMistakes = 0;
        for (int trial = 0; trial < MWU_N_TRIALS; ++trial) {
            randomized_weighted_majority(
                &preds[0][0], outcomes, T, n, eps, weights, p
            );
            totalMistakes += mwu_count_mistakes(p, outcomes, T, 1);
        }

        double w[MWU_N_EXPERTS];
        for (int i = 0; i < n; ++i) w[i] = 1.0;
        double expected = 0.0;

        for (int t = 0; t < T; ++t) {
            double total = 0.0;
            double wrong = 0.0;

            for (int i = 0; i < n; ++i) {
                total += w[i];
                if (preds[t][i] != outcomes[t]) wrong += w[i];
            }
            expected += wrong / total;

            for (int i = 0; i < n; ++i) {
                if (preds[t][i] != outcomes[t]) w[i] *= 1 - eps;
            }
        }


        double bound = (1 + eps) * mStar + log(n) / eps;

        printf("%5.2f | %7.4f | %10.4f | %.4f\n",
            eps, (double)totalMistakes / MWU_N_TRIALS, expected, bound
        );
    }
}