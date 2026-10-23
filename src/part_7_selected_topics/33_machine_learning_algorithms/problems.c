#include "part_7_selected_topics/33_machine_learning_algorithms/33_machine_learning_algorithms.h"

#define TASK 2

// 33-1
int newton_method(
    RealFunc f,
    RealFunc fPrime,
    double x0,
    int T,
    double* xs
) {
    xs[0] = x0;

    for (int t = 0; t < T; ++t) {
        double slope = fPrime(xs[t]);
        if (slope == 0) return t;

        xs[t + 1] = xs[t] - f(xs[t]) / slope;
    }

    return T;
}

// f(x) = x^2 - 2, root sqrt(2)
static double newton_square(double x) {
    return x * x - 2.0;
}

static double newton_square_prime(double x) {
    return 2.0 * x;
}

// f(x) = cos(x) - x, root ~0.739085
static double newton_cosine(double x) {
    return cos(x) - x;
}

static double newton_cosine_prime(double x) {
    return -sin(x) - 1.0;
}

static void newton_print_run(
    const char* title,
    RealFunc f,
    RealFunc fPrime,
    double x0,
    double root
) {
    double xs[NEWTON_N_ITERS + 1];
    int steps = newton_method(
        f,
        fPrime,
        x0, 
        NEWTON_N_ITERS, 
        xs
    );

    print_separator(title);
    printf("t |                x(t) |         f(x(t)) | |x(t) - x*|\n");
    for (int t = 0; t <= steps; ++t) {
        printf("%d | %19.15f | %15.3e | %.3e\n", 
            t, xs[t], f(xs[t]), fabs(xs[t] - root)
        );
    }
    if (steps < NEWTON_N_ITERS) 
        printf(
            "stopped after %d steps: f'(x(%d)) = 0\n",
            steps, steps
        );
}

void test_newton_method(void) {
    newton_print_run("Newton, f(x) = x^2 - 2, x(0) = 1",
        newton_square, newton_square_prime, 1.0, sqrt(2.0)
    );
    newton_print_run("Newton, f(x) = cos(x) - x, x(0) = 1",
        newton_cosine, newton_cosine_prime, 1.0, 0.739085133215160642
    );
    newton_print_run("Newton, f(x) = x^2 - 2, x(0) = 0",
        newton_square, newton_square_prime, 0.0, sqrt(2.0)
    );
}

// 33-2
void hedge(
    const int* preds,
    const int* outs,
    int T,
    int n,
    double eps,
    double* weights,
    int* p
) {
    for (int i = 0; i < n; ++i) weights[i] = 1.0;
    double decay = exp(-eps);

    for (int t = 0; t < T; ++t) {
        const int* q = &preds[t * n];

        double Z = 0.0;
        for (int i = 0; i < n; ++i) Z += weights[i];

        // pick expert i with the probability p_i = w_i / Z
        double r = (double)rand() / ((double)RAND_MAX + 1.0) * Z;
        int chosen = n - 1;
        for (int i = 0; i < n; ++i) {
            r -= weights[i];
            if (r < 0.0) {
                chosen = i;
                break;
            }
        }

        p[t] = q[chosen];

        for (int i = 0; i < n; ++i)
            if (q[i] != outs[t]) weights[i] *= decay;
    }
}

static int hedge_count_mistakes(
    const int* guesses,
    const int* outs,
    int T,
    int stride
) {
    int mistakes = 0;
    for (int t = 0; t < T; ++t)
        if (guesses[t * stride] != outs[t]) mistakes++;

    return mistakes;
}

void test_hedge(void) {
    srand(time(NULL));

    int outs[MWU_N_ROUNDS] = {1, 0, 1, 1, 0, 0, 1, 0, 1, 1};
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

    int T = ARRAY_SIZE(outs);
    int n = ARRAY_SIZE(preds[0]);
    double weights[MWU_N_EXPERTS];
    int p[MWU_N_ROUNDS];

    int mStar = T;
    for (int i = 0; i < n; ++i) {
        int mistakes = hedge_count_mistakes(
                &preds[0][i],
                outs,
                T,
                n
            );
        if (mistakes < mStar) mStar = mistakes;
    }

    // eps = sqrt(ln n / T) balances ln(n) / eps and eps T
    double epss[] = {0.1, 0.25, sqrt(log(n) / T), 0.75};
    int nEpss = ARRAY_SIZE(epss);

    print_separator("Hedge (33-2)");
    printf("m* = %d, n = %d, T = %d, %d runs per eps\n",
        mStar, n, T, MWU_N_TRIALS
    );
    printf("  eps | average | exact E[M] | m* + ln(n) / eps + eps T\n");

    for (int e = 0; e < nEpss; ++e) {
        double eps = epss[e];

        long totalMistakes = 0;
        for (int trial = 0; trial < MWU_N_TRIALS; ++trial) {
            hedge(
                &preds[0][0],
                outs,
                T,
                n,
                eps,
                weights,
                p
            );
            totalMistakes += hedge_count_mistakes(p, outs, T, 1);
        }

        // weights do not depend on the random choices, so E[M] = sum of F_t
        double w[MWU_N_EXPERTS];
        for (int i = 0; i < n; ++i) w[i] = 1.0;
        double expected = 0.0;

        for (int t = 0; t < T; ++t) {
            double Z = 0.0;
            double wrong = 0.0;

            for (int i = 0; i < n; ++i) {
                Z += w[i];
                if (preds[t][i] != outs[t]) wrong += w[i];
            }

            expected += wrong / Z;

            for (int i = 0; i < n; ++i) {
                if (preds[t][i] != outs[t]) w[i] *= exp(-eps);
            }
        }

        double bound = mStar + log(n) / eps + eps * T;

        printf("%5.3f | %7.4f | %10.4f | %.4f\n",
            eps, (double)totalMistakes / MWU_N_TRIALS, expected, bound
        );
    }
}

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_newton_method();
            break;
        }

        case 2: {
            test_hedge();
            break;
        }

        default:
            break;
    }

    return 0;
}
