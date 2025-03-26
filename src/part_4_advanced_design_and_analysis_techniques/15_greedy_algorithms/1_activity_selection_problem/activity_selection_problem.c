#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TASK 5

void recursive_activity_selector(int s[], int f[], int k, int n)  {
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
#define MAX_N 100

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
typedef struct Activity {
    int start, end;
} Activity; 

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
typedef struct ValuedActivity {
    int start, end, value;
} ValuedActivity;

int compare_activities_end(const void* a, const void* b) {
    return ((ValuedActivity*)a)->end - ((Activity*)b)->end;
}

int bin_search(ValuedActivity activities[], int idx) {
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
        int latestActivity = bin_search(activities, i);
        
        if (latestActivity != -1) includeValue += dp5[latestActivity];
        
        int excludeValue = dp5[i - 1];

        dp5[i] = fmax(includeValue, excludeValue);
    }

    int result = dp5[n - 1];
    free(dp5);
    return result;
}

int main(void) {
    int s[] = {0, 1, 3, 5, 8, 5};  
    int f[] = {0, 2, 4, 7, 9, 9};  
    int n = sizeof(s) / sizeof(s[0]) - 1;

    switch (TASK)
    {
        case 1: {
            recursive_activity_selector(s, f, 0, n);
            break;
        }

        case 2: {
            greedy_activity_selector(s, f, n);
            break;
        }

        case 3: {
            // 15.1-1
            dynamic_activity_selector(s, f, n);
            break;
        }

        case 4: {
            // 15.1-4
            Activity activities[] = {
                {30, 75}, {0, 50}, {60, 150}, {10, 20}, {80, 120}
            };
            int n4 = sizeof(activities) / sizeof(activities[0]);
            max_halls(activities, n);

            break;
        }

        case 5: {
            // 15.1-5
            ValuedActivity activity[] = {
                {1, 3, 50}, {2, 5, 20}, {6, 9, 100}, {3, 8, 200}, {9, 10, 150}
            };
            int n = sizeof(activity) / sizeof(activity[0]);

            printf("Max total value: %d\n",
                max_activity_value(activity, n));

            break;
        }
        
        default:
            break;
    }
}