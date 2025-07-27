#include "part_7_selected_topics/27_online_algorithms/27_online_algorithms.h"

int fifo_cache(const int* requests, int numRequests, int cacheSize) {
    int cache[CACHE_SIZE] = {0};
    int head = 0;
    int cnt = 0;
    int misses = 0;

    for (int i = 0; i < numRequests; ++i) {
        int found = 0;
        for (int j = 0; j < cnt; ++j) if (cache[j] == requests[i]) { found = 1; break; }
        if (found) continue;
        misses++;
        if (cnt < cacheSize) cache[cnt++] = requests[i];
        else {
            cache[head] = requests[i];
            head = (head + 1) % cacheSize;
        }
    }

    return misses;
}

int lifo_cache(const int* requests, int numRequests, int cacheSize) {
    int cache[CACHE_SIZE] = {0};
    int cnt = 0;
    int misses = 0;

    for (int i = 0; i < numRequests; ++i) {
        int found = 0;
        for (int j = 0; j < cnt; ++j) if (cache[j] == requests[i]) { found = 1; break; }
        if (found) continue;
        misses++;
        if (cnt < cacheSize) cache[cnt++] = requests[i];
        else cache[cnt - 1] = requests[i];
    }

    return misses;
}

int lru_cache(const int* requests, int numRequests, int cacheSize) {
    CacheEntry cache[CACHE_SIZE] = {0};
    int time = 0;
    int cnt = 0;
    int misses = 0;

    for (int i = 0; i < numRequests; ++i, ++time) {
        int found = 0;

        for (int j = 0; j < cnt; ++j) {
            if (!cache[j].valid || cache[j].page != requests[i]) continue;
            found = 1;
            cache[j].time = time;
            break;
        }

        if (found) continue;
        misses++;
        if (cnt < cacheSize) {
            cache[cnt].page = requests[i];
            cache[cnt].time = time;
            cache[cnt].valid = 1;
            cnt++;
        } else {
            int lru = 0;
            for (int j = 1; j < cacheSize; ++j)
                if (cache[j].time < cache[lru].time) lru = j;
            cache[lru].page = requests[i];
            cache[lru].time = time;
        }
    }

    return misses;
}

int lfu_cache(const int* requests, int numRequests, int cacheSize) {
    CacheEntry cache[CACHE_SIZE] = {0};
    int cnt = 0;
    int misses = 0;

    for (int i = 0; i < numRequests; ++i) {
        int found = 0;
        for (int j = 0; j < cnt; ++j) {
            if (!cache[j].valid || cache[j].page != requests[i]) continue;
            found = 1;
            cache[j].freq++;
            break;
        }
        if (found) continue;;
        misses++;
        if (cnt < cacheSize) {
            cache[cnt].page = requests[i];
            cache[cnt].freq = 1;
            cache[cnt].valid = 1;
            cnt++;
        } else {
            int lfu = 0;
            for (int j = 1; j < cacheSize; ++j)
                if (cache[j].freq < cache[lfu].freq) lfu = j;
            cache[lfu].page = requests[i];
            cache[lfu].freq = 1;
        }
    }

    return misses;
}

static void print_cache_result(
    const char* name,
    CacheSimFn fn,
    const int* req,
    int n,
    int cacheSize
) {
    printf("%s misses: %d\n", name, fn(req, n, cacheSize));
}

void test_deterministic_caches(void) {
    int request[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int numRequest = ARRAY_SIZE(request);
    int cacheSize = 4;

    printf("Initialized tests with %d request and a cache of size %d\n", 
        numRequest, cacheSize);

    print_cache_result("FIFO", fifo_cache, request, numRequest, cacheSize);
    print_cache_result("LIFO", lifo_cache, request, numRequest, cacheSize);
    print_cache_result("LRU",  lru_cache,  request, numRequest, cacheSize);
    print_cache_result("LFU",  lfu_cache,  request, numRequest, cacheSize);
}

static void unmark_all(MarkedCacheEntry* cache, int cacheSize) {
    for (int i = 0; i < cacheSize; ++i) cache[i].marked = 0;
}

int randomized_marking_cache(const int* requests, int numRequests, int cacheSize) {
    MarkedCacheEntry cache[CACHE_SIZE] = {0};
    int cnt = 0;
    int misses = 0;

    srand((uint)time(NULL));

    for (int i = 0; i < numRequests; ++i) {
        int found = 0;
        for (int j = 0; j < cnt; ++j) {
            if (!cache[j].valid || cache[j].page != requests[i]) continue;
            found = 1;
            cache[j].marked = 1;
            break;
        }
        if (found) continue;
        misses++;

        if (cnt < cacheSize) {
            cache[cnt].page = requests[i];
            cache[cnt].marked = 1;
            cache[cnt].valid = 1;
            cnt++;
            continue;
        }

        int allMarked = 1;
        for (int j = 0; j < cacheSize; ++j) 
            if (!cache[j].marked) { allMarked = 0; break; }

        if (allMarked) unmark_all(cache, cacheSize);

        int unmarkedIndices[CACHE_SIZE];
        int unmarkedCnt = 0;

        for (int j = 0; j < cacheSize; ++j)
            if (!cache[j].marked) unmarkedIndices[unmarkedCnt++] = j;

        int toDelete = unmarkedIndices[rand() % unmarkedCnt];
        cache[toDelete].page = requests[i];
        cache[toDelete].marked = 1;
        cache[toDelete].valid = 1;
    }

    return misses;
}

void test_non_deterministic_caches(void) {
    int request[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int numRequest = ARRAY_SIZE(request);
    int cacheSize = 4;

    printf("Initialized tests with %d request and a cache of size %d\n", 
        numRequest, cacheSize);

    print_cache_result("Randomized marking", randomized_marking_cache, request, numRequest, cacheSize);
}
