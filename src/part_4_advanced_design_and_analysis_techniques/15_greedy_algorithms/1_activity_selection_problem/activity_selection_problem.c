#include "part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/greedy_algorithms.h"

void recursive_activity_selector(int s[], int f[], int k, int n) {
    int m = k + 1;

    while (m <= n && s[m] < f[k]) m++;

    if (m <= n) {
        printf("Chosen activity idx: %d\n", m);
        recursive_activity_selector(s, f, m, n);
    }
}

/*
    Θ(n)
*/
void greedy_activity_selector(int s[], int f[], int n) {
    int k = 0;

    for (int m = 1; m < n; m++) {
        if (s[m] >= f[k]) {
            printf("Chosen activity idx: %d\n", m);
            k = m;
        }
    }
}

/*
    15.1-1

    Ο(n^3)
*/
int dp1[MAX_N + 2][MAX_N + 2];
int act[MAX_N + 2][MAX_N + 2];

void print_activities(int i, int j) {
    if (dp1[i][j] > 0) {
        int k = act[i][j];
        if (k != 0) {
            printf("%d, ", k);
            print_activities(i, k);
            print_activities(k, j);
        }
    }
}

void dynamic_activity_selector(int s[], int f[], int n) {
    int i, l, j, k;

    for (i = 0; i <= n; i++) {
        dp1[i][i] = 0;
        dp1[i][i + 1] = 0;
    }
    // Base case
    dp1[n + 1][n + 1] = 0;

    for (l = 2; l <= n + 1; l++) {
        for (i = 0; i <= n - l + 1; i++) {
            j = i + l;
            dp1[i][j] = 0;
            k = j - 1;
            while (k > i && f[i] < f[k]) {
                if (f[i] <= s[k] && f[k] <= s[j]
                    && (dp1[i][k] + dp1[k][j] + 1 > dp1[i][j]))
                {
                    dp1[i][j] = dp1[i][k] + dp1[k][j] + 1;
                    act[i][j] = k;
                }
                k--;
            }
        }
    }

    printf("A maximum size set of mutually compatible activities has size %d\n", dp1[0][n + 1]);
    printf("The set contains: ");
    print_activities(0, n + 1);
    printf("\n");
}

/*
    15.1-4
*/
int compare_activities(const void *a, const void *b) {
    return ((Activity*)a)->start - ((Activity*)b)->start;
}

void max_halls(Activity activities[], int n) {
    int* freeHalls = (int*)malloc(n * sizeof(int));
    int* busyHalls = (int*)malloc(n * sizeof(int));
    int* hallNumbers = (int*)malloc(n * sizeof(int));

    if (!freeHalls || !busyHalls || !hallNumbers) {
        printf("Malloc failed!\n");
        free(freeHalls);
        free(busyHalls);
        free(hallNumbers);
        return;
    }

    int freeCount = 0, busyCount = 0;
    int i, j, hall;

    qsort(activities, n, sizeof(Activity), compare_activities);

    for (i = 0; i < n; i++) {
        j = 0;
        while (j < busyCount) {
            if (busyHalls[j] < activities[i].start) {
                freeHalls[freeCount++] = hallNumbers[j];
                busyHalls[j] = busyHalls[--busyCount];
                hallNumbers[j] = hallNumbers[busyCount];
            } else {
                j++;
            }
        }

        if (freeCount > 0) hall = freeHalls[--freeCount];
        else hall = busyCount + 1;

        busyHalls[busyCount] = activities[i].end;
        hallNumbers[busyCount] = hall;
        busyCount++;

        printf("Activity (%d, %d) assigned to Hall %d\n", 
            activities[i].start, activities[i].end, hall);
    }

    printf("Halls needed: %d\n", hallNumbers[j]);

    free(freeHalls);
    free(busyHalls);
    free(hallNumbers);
}

/*
    15.1-5

    O(n*log(n)), dominated by sorting time.
*/
int compare_activities_end(const void* a, const void* b) {
    return ((ValuedActivity*)a)->end - ((Activity*)b)->end;
}

int activities_binary_search(ValuedActivity activities[], int idx) {
    int low = 0, high = idx - 1, mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if (activities[mid].end <= activities[idx].start) {
            if (activities[mid + 1].end <= activities[idx].start) low = mid + 1;
            else return mid;
        } else high = mid - 1;
    }

    return -1;
}

int max_activity_value(ValuedActivity activities[], int n) {
    qsort(activities, n, sizeof(ValuedActivity), compare_activities_end);

    int* dp5 = (int*)malloc(n * sizeof(int));
    if (!dp5) {
        printf("Malloc failed!\n");
        return 0;
    }

    int i;

    // Base case
    dp5[0] = activities[0].value;

    for (i = 1; i < n; i++) {
        int includeValue = activities[i].value;
        int latestActivity = activities_binary_search(activities, i);
        
        if (latestActivity != -1) includeValue += dp5[latestActivity];
        
        int excludeValue = dp5[i - 1];

        dp5[i] = fmax(includeValue, excludeValue);
    }

    int result = dp5[n - 1];
    free(dp5);
    return result;
}
