#include "part_7_selected_topics/34_np-completeness/34_np-completeness.h"


// 34.3-4
static int cs_is_valid(const Circuit* c) {
    int nWires = c->nInputs + c->nGates;
    if (c->output < 0 || c->output >= nWires) return 0;

    for (int g = 0; g < c->nGates; ++g) {
        const Gate* gate = &c->gates[g];
        if (gate->fanIn < 1 || gate->fanIn > CS_MAX_FAN_IN) return 0;
        if (gate->type == GATE_NOT && gate->fanIn != 1) return 0;

        for (int j = 0; j < gate->fanIn; ++j)
            if (gate->inputs[j] < 0 || gate->inputs[j] >= nWires) return 0;
    }

    return 1;
}

static int cs_is_bit_string(
    const char* y,
    int k
) {
    if ((int)strlen(y) != k) return 0;

    for (int i = 0; i < k; ++i)
        if (y[i] != '0' && y[i] != '1') return 0;

    return 1;
}

static int cs_evaluate_gate(
    const Gate* gate,
    const int* values
) {
    if (gate->type == GATE_NOT) return !values[gate->inputs[0]];

    int result = gate->type == GATE_AND;
    for (int i = 0; i < gate->fanIn; ++i) {
        int v = values[gate->inputs[i]];
        result = gate->type == GATE_AND ? (result && v) : (result || v);
    }

    return result;
}

int verify_circuit_sat_inputs(
    const Circuit* c,
    const char* y
) {
    if (!cs_is_valid(c)) return 0;
    if (!cs_is_bit_string(y, c->nInputs)) return 0;

    int nWires = c->nInputs + c->nGates;
    int* values = safe_malloc(nWires * sizeof(int));
    int* missing = safe_malloc(c->nGates * sizeof(int));
    int* queue = safe_malloc(nWires * sizeof(int));

    for (int w = 0; w < nWires; ++w) values[w] = NIL;
    for (int g = 0; g < c->nGates; ++g) missing[g] = c->gates[g].fanIn;

    int head = 0;
    int tail = 0;
    for (int i = 0; i < c->nInputs; ++i) {
        values[i] = y[i] - '0';
        queue[tail++] = i;
    }

    while (head < tail) {
        int w = queue[head++];
        
        for (int g = 0; g < c->nGates; ++g) {
            const Gate* gate = &c->gates[g];
            
            for (int i = 0; i < gate->fanIn; ++i) {
                if (gate->inputs[i] != w) continue;
                if (--missing[g] > 0) continue;

                int out = c->nInputs + g;
                values[out] = cs_evaluate_gate(gate, values);
                queue[tail++] = out;
            }
        }
    }

    int result = tail == nWires && values[c->output] == 1;

    safe_free(values);
    safe_free(missing);
    safe_free(queue);

    return result;
}

static void cs_print_search(
    const char* name,
    const Circuit* c
) {
    int k = c->nInputs;
    char y[k + 1];
    char first[k + 1];
    y[k] = '\0';

    int satisfying = 0;
    for (int mask = 0; mask < (1 << k); ++mask) {
        for (int i = 0; i < k; ++i) y[i] = (char)('0' + ((mask >> (k - 1 - i)) & 1));
        if (!verify_circuit_sat_inputs(c, y)) continue;

        if (satisfying == 0) strcpy(first, y);
        satisfying++;
    }

    printf("%-22s | %d | %3d | %10d | %s\n",
        name, k, 1 << k, satisfying, satisfying > 0 ? first : "-"
    );
}

static void cs_print_verifier(
    const char* name,
    const Circuit* c,
    const char* y,
    const char* comment
) {
    printf("%-22s | %-4s | %6d | %s\n", name, y, verify_circuit_sat_inputs(c, y), comment);
}

void test_verify_circuit_sat_inputs(void) {
    Gate unsatGates[] = {
        {{7, 9, 8}, 3, GATE_AND},
        {{2}, 1, GATE_NOT},
        {{4}, 1, GATE_NOT},
        {{0, 1}, 2, GATE_OR},
        {{6, 5}, 2, GATE_AND},
        {{0, 4, 1}, 3, GATE_AND},
        {{5, 8}, 2, GATE_OR}
    };
    Circuit unsat = {
        .gates = unsatGates,
        .nGates = (int)ARRAY_SIZE(unsatGates),
        .nInputs = 3,
        .output = 3
    };

    Gate andNotGates[] = {
        {{0, 3}, 2, GATE_AND},
        {{1}, 1, GATE_NOT}
    };
    Circuit andNot = {
        .gates = andNotGates,
        .nGates = (int)ARRAY_SIZE(andNotGates),
        .nInputs = 2,
        .output = 2
    };

    Gate xorGates[] = {
        {{0, 1}, 2, GATE_OR},
        {{0, 1}, 2, GATE_AND},
        {{3}, 1, GATE_NOT},
        {{2, 4}, 2, GATE_AND}
    };
    Circuit xorCircuit = {
        .gates = xorGates,
        .nGates = (int)ARRAY_SIZE(xorGates),
        .nInputs = 2,
        .output = 5
    };

    Gate cyclicGates[] = {
        {{0, 1}, 2, GATE_AND}
    };
    Circuit cyclic = {
        .gates = cyclicGates,
        .nGates = (int)ARRAY_SIZE(cyclicGates),
        .nInputs = 1,
        .output = 1
    };

    print_separator("CIRCUIT-SAT, inputs as certificate (34.3-4)");

    printf("Trying every assignment of the inputs\n");
    printf("circuit                | k | 2^k | satisfying | first y\n");
    cs_print_search("34.3-1", &unsat);
    cs_print_search("x1 and not x2", &andNot);
    cs_print_search("x1 xor x2", &xorCircuit);
    cs_print_search("gate on a cycle", &cyclic);

    printf("\nSingle calls of the verifier\n");
    printf("circuit                | y    | A(x,y) | comment\n");
    cs_print_verifier("x1 xor x2", &xorCircuit, "10", "output 1");
    cs_print_verifier("x1 xor x2", &xorCircuit, "11", "output 0");
    cs_print_verifier("x1 xor x2", &xorCircuit, "1", "wrong length");
    cs_print_verifier("x1 xor x2", &xorCircuit, "1a", "not a bit string");
    cs_print_verifier("gate on a cycle", &cyclic, "1", "gate never evaluated");
}