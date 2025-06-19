#include "part_6_graph_algorithms/25_bipartite_matching/bipartite_matching.h"

#pragma region Gale-Shapley Algorithm

StableMarriageInstance* stable_marriage_init(int n) {
    if (n <= 0 || n >= MAX_PEOPLE) return NULL;

    StableMarriageInstance* instance = (StableMarriageInstance*)safe_malloc(sizeof(StableMarriageInstance));
    instance->n = n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            instance->menPref[i][j] = -1;
            instance->womenPref[i][j] = -1;
            instance->womenRanking[i][j] = -1;
        }
    }

    printf("Stable marriage instance initialized for %d couples\n", n);
    return instance;
}

void stable_marriage_set_men_prefs(
    StableMarriageInstance* 
    instance, 
    int man, 
    int prefs[]
) {
    if (!instance || man < 0 || man >= instance->n) return;

    for (int rank = 0; rank < instance->n; rank++) {
        instance->menPref[man][rank] = prefs[rank];
    }
}

void stable_marriage_set_women_prefs(
    StableMarriageInstance* 
    instance, 
    int woman, 
    int prefs[]
) {
    if (!instance || woman < 0 || woman >= instance->n) return;

    for (int rank = 0; rank < instance->n; rank++) {
        instance->womenPref[woman][rank] = prefs[rank];
        instance->womenRanking[woman][prefs[rank]] = rank;
    }
}

void print_stable_marriage_instance(StableMarriageInstance* instance) {
    if (!instance) return;

    printf("Stable marriange instance\n");
    printf("Number of couples: %d\n\n", instance->n);

    printf("Men's preferences:\n");
    for (int man = 0; man < instance->n; man++) {
        printf(" Man %d: ", man);
        for (int rank = 0; rank < instance->n; rank++) {
            printf("Woman %d ", instance->menPref[man][rank]);
        }
        printf("\n");
    }

    printf("Women's preferences:\n");
    for (int woman = 0; woman < instance->n; woman++) {
        printf(" Woman %d: ", woman);
        for (int rank = 0; rank < instance->n; rank++) {
            printf("Woman %d ", instance->womenPref[woman][rank]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_stable_marriage_result(StableMarriageResult* res) {
    if (!res) return;

    printf("Stable marriage result\n");
    printf("Matching:\n");
    for (int man = 0; man < res->n; man++) {
        if (res->manPartner[man] == -1) continue;
        printf(" Man %d -- Woman %d\n", man, res->manPartner[man]);
    }
    printf("\n");
}

int woman_prefers(
    StableMarriageInstance* instance, 
    int woman, 
    int man1, 
    int man2
) {
    if (!instance || woman < 0 || woman >= instance->n) return 0;
    if (man1 < 0 || man1 >= instance->n || man2 < 0 || man2 >= instance->n) return 0;

    return instance->womenRanking[woman][man1] < instance->womenRanking[woman][man2];
}

StableMarriageResult* gale_shapley(StableMarriageInstance* instance) {
    if (!instance) return NULL;

    printf("Start the Gale-Shapley algorithm...\n");

    int n = instance->n;
    StableMarriageResult* res = (StableMarriageResult*)safe_malloc(sizeof(StableMarriageResult));
    res->n = n;

    // Init as unmatched
    for (int i = 0; i < n; i++) {
        res->manPartner[i] = -1;
        res->womanPartner[i] = -1;
    }

    int nextProposal[MAX_PEOPLE];
    for (int man = 0; man < n; man++) {
        nextProposal[man] = 0;
    }

    int freeManCnt = n;
    int iters = 0;

    while (freeManCnt > 0) {
        iters++;
        printf("\n--- Iteration %d ---\n", iters);

        int currFreeMan = -1;
        for (int man = 0; man < n; man++) {
            if (res->manPartner[man] == -1) {
                currFreeMan = man;
                break;
            }
        }

        if (currFreeMan == -1) break;

        int currWoman = instance->menPref[currFreeMan][nextProposal[currFreeMan]];
        nextProposal[currFreeMan]++;

        printf("Man %d proposes to Woman %d\n", currFreeMan, currWoman);

        if (res->womanPartner[currWoman] == -1) {
            // Non-engaged woman
            res->manPartner[currFreeMan] = currWoman;
            res->womanPartner[currWoman] = currFreeMan;
            freeManCnt--;
            printf("  Woman %d accepts (was free)\n", currWoman);
            printf("  Current free men count: %d\n", freeManCnt);
            continue;
        }

        int currPartner = res->womanPartner[currWoman];

        if (woman_prefers(instance, currWoman, currFreeMan, currPartner)) {
            // Woman prefers the new man
            res->manPartner[currPartner] = -1;
            res->manPartner[currFreeMan] = currWoman;
            res->womanPartner[currWoman] = currFreeMan;
            printf("  Woman %d accepts Man %d (breaks with Man %d)\n", 
               currWoman, currFreeMan, currPartner);
        } else {
            // Woman prefers current partner
            printf("  Woman %d rejects Man %d (prefers current partner Man %d)\n", 
               currWoman, currFreeMan, currPartner);
        }
        printf("  Current free men count: %d\n", freeManCnt);
    }

    printf("\nGale-Shapley completed in %d iterations\n", iters);
    return res;
}

int verify_stability(
    StableMarriageInstance* instance, 
    StableMarriageResult* res
) {
    if (!instance || !res) return 0;

    printf("Veryfying stability...\n");
    int n = instance->n;
    int blockingPairs = 0;

    for (int man = 0; man < n; man++) {
        int hisPartner = res->manPartner[man];
        for (int woman = 0; woman < n; woman++) {
            if (hisPartner == woman) continue;
            int herPartner = res->womanPartner[woman];
            int manPrefersWoman = 0;

            for (int rank = 0; rank < n; rank++) {
                int preferred = instance->menPref[man][rank];
                if (preferred == woman) {
                    manPrefersWoman = 1;
                    break;
                }
                if (preferred == hisPartner) {
                    break;
                }
            }
            if (!manPrefersWoman) continue;
            if (!woman_prefers(instance, woman, man, herPartner)) continue;

            printf("  BLOCKING PAIR: Man %d and Woman %d\n", man, woman);
            printf("    Man %d prefers Woman %d over his partner Woman %d\n", 
                   man, woman, hisPartner);
            printf("    Woman %d prefers Man %d over her partner Man %d\n", 
                   woman, man, herPartner);
            blockingPairs++;
        }
    }

    if (blockingPairs == 0) {
        printf("Macthing is stable\n");
        return 1;
    }

    printf("Matching is unstable. Found %d blocking pair(s)\n", blockingPairs);
    return 0;
}

void test_gale_shapley_algorithm(void) {
    const char* title = "Gale-Shapley algorithm";
    print_separator(title);

    int n = 4;
    StableMarriageInstance* instance = stable_marriage_init(n);

    int menPrefs[4][4] = {
        {0, 1, 2, 3},  // Man 0: Woman 0 > Woman 1 > Woman 2 > Woman 3
        {1, 0, 3, 2},  // Man 1: Woman 1 > Woman 0 > Woman 3 > Woman 2  
        {2, 1, 0, 3},  // Man 2: Woman 2 > Woman 1 > Woman 0 > Woman 3
        {3, 2, 1, 0}   // Man 3: Woman 3 > Woman 2 > Woman 1 > Woman 0
    };

    int womenPrefs[4][4] = {
        {3, 2, 1, 0},  // Woman 0: Man 3 > Man 2 > Man 1 > Man 0
        {2, 3, 0, 1},  // Woman 1: Man 2 > Man 3 > Man 0 > Man 1
        {1, 0, 3, 2},  // Woman 2: Man 1 > Man 0 > Man 3 > Man 2
        {0, 1, 2, 3}   // Woman 3: Man 0 > Man 1 > Man 2 > Man 3
    };

    for (int i = 0; i < n; i++) {
        stable_marriage_set_men_prefs(instance, i, menPrefs[i]);
        stable_marriage_set_women_prefs(instance, i, womenPrefs[i]);
    }

    print_stable_marriage_instance(instance);

    StableMarriageResult* res = gale_shapley(instance);

    if (res) {
        print_stable_marriage_result(res);
        verify_stability(instance, res);
        safe_free(res);
    }

    safe_free(instance);
    printf("\n");
}

#pragma endregion Gale-Shapley Algorithm

#pragma region NRMP problem

NRMPInstance* nrmp_init(int numStudents, int numHospitals) {
    if (numStudents <= 0 || numHospitals <= 0 ||
        numStudents >= MAX_PEOPLE || numHospitals >= MAX_PEOPLE) return NULL;

    NRMPInstance* instance = (NRMPInstance*)safe_malloc(sizeof(NRMPInstance));
    instance->numStudents = numStudents;
    instance->numHospitals = numHospitals;

    for (int h = 0; h < numHospitals; h++) {
        instance->hospitalCapacity[h] = 1;
    }

    for (int i = 0; i < MAX_PEOPLE; i++) {
        for (int j = 0; j < MAX_PEOPLE; j++) {
            instance->studentPref[i][j] = -1;
            instance->hospitalPref[i][j] = -1;
            instance->hospitalRanking[i][j] = -1;
        }
    }

    printf("NRMP instantiated for %d students and %d hospitals",
        numStudents, numHospitals);
    return instance;
}

void nrmp_set_hospital_capacity(
    NRMPInstance* instance, 
    int hospital, 
    int capacity
) {
    if (!instance || hospital < 0 || hospital >= instance->numHospitals 
        || capacity <= 0) return;
    instance->hospitalCapacity[hospital] = capacity;
}

void nrmp_set_student_prefs(NRMPInstance* instance, int student, int prefs[]) {
    if (!instance || student < 0 || student >= instance->numStudents) return;

    for (int rank = 0; rank < instance->numHospitals; rank++) {
        instance->studentPref[student][rank] = prefs[rank];
    }
}

void nrmp_set_hospital_prefs(NRMPInstance* instance, int hospital, int prefs[]) {
    if (!instance || hospital < 0 || hospital >= instance->numHospitals) return;

    for (int rank = 0; rank < instance->numStudents; rank++) {
        instance->hospitalPref[hospital][rank] = prefs[rank];
        instance->hospitalRanking[hospital][prefs[rank]] = rank;
    }
}

void print_nrmp_instance(NRMPInstance* instance) {
    if (!instance) return;

    printf("NRMP instance\n");
    printf("Students: %d, Hospitals: %d\n\n", instance->numStudents, instance->numHospitals);

    printf("Hospital capacities:\n");
    for (int h = 0; h < instance->numHospitals; h++) {
        printf(" Hospital %d: capacity %d\n", h, instance->hospitalCapacity[h]);
    }
    printf("\n");

    printf("Student preferences:\n");
    for (int s = 0; s < instance->numStudents; s++) {
        printf(" Student %d: ", s);
        for (int rank = 0; rank < instance->numHospitals; rank++) {
            printf("Hospital %d ", instance->studentPref[s][rank]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Hospital preferences:\n");
    for (int h = 0; h < instance->numHospitals; h++) {
        printf(" Hospital %d: ", h);
        for (int rank = 0; rank < instance->numStudents; rank++) {
            printf("Student %d ", instance->hospitalPref[h][rank]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_nrmp_result(NRMPResult* res) {
    if (!res) return;

    printf("NRMP matching result\n");
    printf("Student assignments:\n");
    for (int s = 0; s < res->numStudents; s++) {
        if (res->studentsHospital[s] != -1) {
            printf(" Student %d -> Hospital %d\n", s, res->studentsHospital[s]);
        } else {
            printf(" Student %d -> UNMATCHED\n", s);
        }
    }

    printf("\nHospital assignments:\n");
    for (int h = 0; h < res->numHospitals; h++) {
        printf(" Hospital %d (%d capacity): ", h, res->hospitalCapacity[h]);
        if (res->hospitalCapacity[h] > 0) {
            for (int i = 0; i < res->hospitalCapacity[h]; i++) {
                printf("Student %d ", res->hospitalsStudents[h][i]);
            }
        } else {
            printf("EMPTY");
        }
        printf("\n");
    }
    printf("\n");
}

int hospital_prefers_student(
    NRMPInstance* instance,
    int hospital,
    int student1,
    int student2
) {
    if (!instance || hospital < 0 || hospital >= instance->numHospitals) 
        return 0;
    if (student1 < 0 || student1 >= instance->numStudents ||
        student2 < 0 || student2 >= instance->numStudents) return 0;

    return instance->hospitalRanking[hospital][student1] < instance->hospitalRanking[hospital][student2];
}

int find_worst_student_in_hospital(
    NRMPInstance* instance, 
    NRMPResult* res, 
    int hospital
) {
    if (!instance || !res || hospital < 0 || hospital >= instance->numHospitals) return -1;
    if (res->hospitalCapacity[hospital] == 0) return -1;

    int worstStudent = -1;
    int worstRank = -1;

    for (int i = 0; i < res->hospitalCapacity[hospital]; i++) {
        int student = res->hospitalsStudents[hospital][i];
        int rank = instance->hospitalRanking[hospital][student];

        if (rank <= worstRank) continue;

        worstRank = rank;
        worstStudent = student;
    }

    return worstStudent;
}

void remove_student_from_hospital(
    NRMPResult* res,
    int student,
    int hospital
) {
    if (!res || student < 0 || hospital < 0) return;
    res->studentsHospital[student] = -1;

    for (int i = 0; i < res->hospitalCapacity[hospital]; i++) {
        if (res->hospitalsStudents[hospital][i] != student) continue;
        for (int j = i; j < res->hospitalCapacity[hospital] - 1; j++) {
            res->hospitalsStudents[hospital][j] = res->hospitalsStudents[hospital][j + 1];
        }
        res->hospitalsStudents[hospital][res->hospitalCapacity[hospital] - 1] = -1;
        res->hospitalCapacity[hospital]--;
        break;
    }
}

void add_student_to_hospital(
    NRMPResult* res,
    int student,
    int hospital
) {
    if (!res || student < 0 || hospital < 0) return;

    res->studentsHospital[student] = hospital;
    res->hospitalsStudents[hospital][res->hospitalCapacity[hospital]] = student;
    res->hospitalCapacity[hospital]++;
}

NRMPResult* nrmp_gale_shapley(NRMPInstance* instance) {
    if (!instance) return NULL;

    printf("Starting the NRMP solver...\n");

    int numStudents = instance->numStudents;
    int numHospitals = instance->numHospitals;

    NRMPResult* res = (NRMPResult*)safe_malloc(sizeof(NRMPResult));
    res->numStudents = numStudents;
    res->numHospitals = numHospitals;

    for (int s = 0; s < numStudents; s++) {
        res->studentsHospital[s] = -1;
    }

    for (int h = 0; h < numHospitals; h++) {
        res->hospitalCapacity[h] = 0;
        for (int i = 0; i < MAX_RESIDENTS_PER_HOSPITAL; i++) {
            res->hospitalsStudents[h][i] = -1;
        }
    }

    int nextProposal[MAX_PEOPLE];
    for (int s = 0; s < numStudents; s++) {
        nextProposal[s] = 0;
    }

    int currFreeStudents = numStudents;
    int iters = 0;

    while (currFreeStudents > 0) {
        iters++;
        printf("\n--- Iteration %d ---\n", iters);

        int currStudent = -1;
        for (int s = 0; s < numStudents; s++) {
            if (res->studentsHospital[s] == -1) {
                currStudent = s;
                break;
            }
        }

        if (currStudent == -1) break;

        if (nextProposal[currStudent] >= numHospitals) {
            currFreeStudents--;
            continue;
        }

        int targetHospital = instance->studentPref[currStudent][nextProposal[currStudent]];
        nextProposal[currStudent]++;

        printf("Student %d proposes to Hospital %d\n", currStudent, targetHospital);

        if (res->hospitalCapacity[targetHospital] < instance->hospitalCapacity[targetHospital]) {
            // Hospital has a vacancy - accept
            add_student_to_hospital(res, currStudent, targetHospital);
            currFreeStudents--;
            printf("  Hospital %d accepts Student %d (had free capacity)\n", 
                   targetHospital, currStudent);
        } else {
            // Hospital is full
            int worstStudent = find_worst_student_in_hospital(instance, res, targetHospital);
            if (hospital_prefers_student(
                instance, targetHospital, currStudent, worstStudent)) {
                // Replace
                remove_student_from_hospital(res, worstStudent, targetHospital);
                add_student_to_hospital(res, currStudent, targetHospital);

                printf("  Hospital %d accepts Student %d (replaces Student %d)\n", 
                       targetHospital, currStudent, worstStudent);
            } else {
                // Reject
                printf("  Hospital %d rejects Student %d\n", targetHospital, currStudent);
            }
        }

        printf("  Current free students count: %d\n", currFreeStudents);
    }

    printf("\nNRMP Gale-Shapley completed in %d iterations\n", iters);
    return res;
}

int verify_nrmp_stability(NRMPInstance* instance, NRMPResult* res) {
    if (!instance || !res) return 0;

    printf("Verifying NRMP stability...\n");
    int numStudents = instance->numStudents;
    int numHospitals = instance->numHospitals;
    int blockingPairs = 0;

    for (int s = 0; s < numStudents; s++) {
        int currHospital = res->studentsHospital[s];
        for (int h = 0; h < numHospitals; h++) {
            if (h == currHospital) continue;
            int studentPrefersH = 0;
            if (currHospital == -1) {
                studentPrefersH = 1; // Unmatched student
            } else {
                for (int rank = 0; rank < numHospitals; rank++) {
                    int preferred = instance->studentPref[s][rank];
                    if (preferred == h) {
                        studentPrefersH = 1;
                        break;
                    }
                    if (preferred == currHospital) {
                        break;
                    }
                }
            }

            if (!studentPrefersH) continue;

            // Can hospital fit a new student?
            if (res->hospitalCapacity[h] < instance->hospitalCapacity[h] ||
                hospital_prefers_student(instance, h, s, find_worst_student_in_hospital(instance, res, h))) {
                    printf("  BLOCKING PAIR: Student %d and Hospital %d\n", s, h);
                    printf("    Student %d prefers Hospital %d over current assignment\n", s, h);
                    printf("    Hospital %d can accept Student %d\n", h, s);
                    blockingPairs++;
                }
        }
    }

    if (blockingPairs == 0) {
        printf("NRMP matching is stable");
        return 1;
    }

    printf("NRMP matching is unstable. Found %d blocking pair(s)",
        blockingPairs);
    return 0;
}

void test_nrmp_solver(void) {
    const char* title = "NRMP Solver";
    print_separator(title);

    int numStudents = 5;
    int numHospitals = 3;
    NRMPInstance* instance = nrmp_init(numStudents, numHospitals);

    nrmp_set_hospital_capacity(instance, 0, 2);
    nrmp_set_hospital_capacity(instance, 1, 2);
    nrmp_set_hospital_capacity(instance, 2, 1);

    int studentPrefs[5][3] = {
        {0, 1, 2},  // Student 0: Hospital 0 > Hospital 1 > Hospital 2
        {1, 0, 2},  // Student 1: Hospital 1 > Hospital 0 > Hospital 2
        {0, 2, 1},  // Student 2: Hospital 0 > Hospital 2 > Hospital 1
        {1, 2, 0},  // Student 3: Hospital 1 > Hospital 2 > Hospital 0
        {2, 0, 1}   // Student 4: Hospital 2 > Hospital 0 > Hospital 1
    };

    int hospitalPrefs[3][5] = {
        {0, 2, 1, 3, 4},  // Hospital 0: Student 0 > Student 2 > Student 1 > Student 3 > Student 4
        {1, 3, 0, 4, 2},  // Hospital 1: Student 1 > Student 3 > Student 0 > Student 4 > Student 2
        {4, 2, 0, 1, 3}   // Hospital 2: Student 4 > Student 2 > Student 0 > Student 1 > Student 3
    };

    for (int s = 0; s < numStudents; s++) {
        nrmp_set_student_prefs(instance, s, studentPrefs[s]);
    }

    for (int h = 0; h < numHospitals; h++) {
        nrmp_set_hospital_prefs(instance, h, hospitalPrefs[h]);
    }

    print_nrmp_instance(instance);

    NRMPResult* res = nrmp_gale_shapley(instance);

    if (res) {
        print_nrmp_result(res);
        verify_nrmp_stability(instance, res);
        safe_free(res);
    }

    safe_free(instance);
    printf("\n");
}

#pragma endregion NRMP problem
