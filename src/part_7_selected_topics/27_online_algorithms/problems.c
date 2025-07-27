#include "part_7_selected_topics/27_online_algorithms/27_online_algorithms.h"

#define TASK 2

// --- The cow-path problem ---

void find_pasture(double pasturePos) {
    double currPoss = 0.0;
    double step = 1.0;
    int direction = 1;
    double traveled = 0.0;

    printf("Starting search for pasture (it is hidden at position %.2f)\n", 
        pasturePos);

    while (1) {
        double destination = currPoss + direction * step;
        printf("Going from %.2f to %.2f\n", currPoss, destination);
        traveled += fabs(destination - currPoss);

        if ((direction == 1 && pasturePos >= currPoss && pasturePos <= destination) ||
            (direction == -1 && pasturePos <= currPoss && pasturePos >= destination)
            ) {
                traveled += fabs(pasturePos - destination);
                printf("Found pasture!\n");
                printf("Total distance: %.2f, ratio: %.2f", 
                    traveled, traveled / fabs(pasturePos));
                break;
            }

        currPoss = destination;
        direction *= -1;
        step *= 2;
    }
}

// --- Online scheduling minimizing mean completion time ---

int compare_by_processing_time(const void* a, const void* b) {
    Task* t1 = (Task*)a;
    Task* t2 = (Task*)b;
    return t1->processingTime - t2->processingTime;
}

int compare_by_remaining_time(const void* a, const void* b) {
    Task* t1 = (Task*)a;
    Task* t2 = (Task*)b;
    return t1->remainingTime - t2->remainingTime;
}

int compare_by_finish_time(const void* a, const void* b) {
    Task* t1 = (Task*)a;
    Task* t2 = (Task*)b;
    return t1->finishTime - t2->finishTime;
}

void spt_schedule(Task* tasks, int n) {
    int currTime = 0;
    int completed = 0;

    while (completed < n) {
        Task available[100];
        int cnt = 0;

        for (int i = 0; i < n; ++i)
            if (!tasks[i].completed && tasks[i].releaseTime <= currTime)
                available[cnt++] = tasks[i];

        if (cnt == 0) {
            currTime++;
            continue;
        }

        qsort(available, cnt, sizeof(Task), compare_by_processing_time);

        int selectedIdx = -1;
        for (int i = 0; i < n; ++i) {
            if (!tasks[i].completed && tasks[i].id == available[0].id) {
                selectedIdx = i;
                break;
            }
        }

        Task* t = &tasks[selectedIdx];
        t->startTime = currTime;
        t->finishTime = currTime + t->processingTime;
        currTime += t->processingTime;
        t->completed = 1;
        completed++;

        printf("Task %d executed: start=%d finish=%d\n", t->id, t->startTime, t->finishTime);
    }

    double total = 0;
    for (int i = 0; i < n; ++i) total += tasks[i].finishTime;

    printf("Average completion time: %.2f\n", total / n);
}

void srpt_schedule(Task* tasks, int n) {
    int currTime = 0;
    int completed = 0;

    while (completed < n) {
        Task available[100];
        int cnt = 0;

        for (int i = 0; i < n; ++i)
            if (!tasks[i].completed && tasks[i].releaseTime <= currTime)
                available[cnt++] = tasks[i];

        if (cnt == 0) {
            currTime++;
            break;
        }

        qsort(available, cnt, sizeof(Task), compare_by_remaining_time);

        int selectedIdx = 0;
        for (int i = 0; i < n; ++i) {
            if (!tasks[i].completed && tasks[i].id == available[0].id) {
                selectedIdx = i;
                break;
            }
        }

        if (tasks[selectedIdx].remainingTime == tasks[selectedIdx].processingTime)
            tasks[selectedIdx].startTime = currTime;

        tasks[selectedIdx].remainingTime--;
        currTime++;

        if (tasks[selectedIdx].remainingTime == 0) {
            tasks[selectedIdx].completed = 1;
            tasks[selectedIdx].finishTime = currTime;
            completed++;
            printf("Task %d completed: start=%d finish=%d\n",
                   tasks[selectedIdx].id,
                   tasks[selectedIdx].startTime,
                   tasks[selectedIdx].finishTime);
        }
    }

    double total = 0;
    for (int i = 0; i < n; ++i) total += tasks[i].finishTime;

    printf("Average completion time: %.2f\n", total / n);
}

void completion_time_schedule(Task* tasks, int n) {
    // Step 0: Copy the original data
    Task srptTasks[100];
    for (int i = 0; i < n; ++i) {
        srptTasks[i] = tasks[i];
        srptTasks[i].remainingTime = srptTasks[i].processingTime;
        srptTasks[i].completed = 0;
    }

    // Step 1: Use SRPT
    srpt_schedule(srptTasks, n);

    // Step 2: Sort by C_{i}^{P}
    qsort(srptTasks, n, sizeof(Task), compare_by_finish_time);

    // Step 3: Execute tasks non-preemptively in the SRPT order
    int currTime = 0;
    for (int i = 0; i < n; ++i) {
        int id = srptTasks[i].id;
        Task* t = NULL;

        for (int j = 0; j < n; ++j) {
            if (tasks[j].id == id) {
                t = &tasks[j];
                break;
            }
        }

        int start = currTime < t->releaseTime ? t->releaseTime : currTime;
        t->startTime = start;
        t->finishTime = start + t->processingTime;
        currTime = t->finishTime;

        printf("Task %d executed non-preemptively: start=%d finish=%d\n", 
            t->id, t->startTime, t->finishTime);
    }

    double total = 0;
    for (int i = 0; i < n; ++i) total += tasks[i].finishTime;
    
    printf("Average completion time: %.2f\n", total / n);
}

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 27-1
            double pasturePos = 300.00;
            find_pasture(pasturePos);
            break;
        }

        case 2: {
            // 27-2
            Task tasks[] = {
                { .id = 1, .releaseTime = 0, .processingTime = 10, .remainingTime = 10 },
                { .id = 2, .releaseTime = 2, .processingTime = 3,  .remainingTime = 3  },
                { .id = 3, .releaseTime = 3, .processingTime = 1,  .remainingTime = 1  },
            };

            int n = ARRAY_SIZE(tasks);
            printf("Number of test tasks: %d\n", n);

            Task tasksCopy1[100];
            Task tasksCopy2[100];
            Task tasksCopy3[100];
            for (int i = 0; i < n; ++i) {
                tasksCopy1[i] = tasks[i];
                tasksCopy2[i] = tasks[i];
                tasksCopy3[i] = tasks[i];
            }

            spt_schedule(tasksCopy1, n);
            srpt_schedule(tasksCopy2, n);
            completion_time_schedule(tasksCopy3, n);
            break;
        }

        default:
            break;
    }

    return 0;
}