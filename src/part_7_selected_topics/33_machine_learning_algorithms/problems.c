#include "part_7_selected_topics/33_machine_learning_algorithms/33_machine_learning_algorithms.h"

#define TASK 1

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

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_newton_method();
            break;
        }

        default:
            break;
    }

    return 0;
}
