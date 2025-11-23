#include "part_7_selected_topics/32_string-matching/32_string-matching.h"

// 32.2-1
int rabin_karp_matcher(char* T, char* P, int n, int m, int d, int q) {
    unsigned char *tptr = (unsigned char*)T;
    unsigned char *pptr = (unsigned char*)P;

    int h = (int)modular_exponentation(d, m - 1, q);
    
    int p = 0;
    int t = 0;
    for (int i = 0; i < m; ++i) {
        p = (d * p + pptr[i]) % q;
        t = (d * t + tptr[i]) % q;
    }

    printf("Pattern P = \"%s\"\n", P);
    printf("Pattern hash p = %d\n", p);
    printf("Initial text window = \"%.*s\"\n", m, T);
    printf("Initial hash t = %d\n\n", t);

    int matches = 0;
    int falseAlarms = 0;

    for (int s = 0; s <= n - m; ++s) {
        printf("[shift %d] window \"%.*s\" hash t = %d\n",
               s, m, T + s, t);
        if (p == t) {
            printf("Hash match detected\n");
            int match = 1;

            for (int j = 0; j < m; ++j) {
                if (tptr[s + j] != pptr[j]) {
                    match = 0;
                    break;
                }
            }

            if (match) {
                printf("Pattern occurs at shift %d\n", s);
                matches++;
            } else {
                printf("False alarm %d at shift %d\n", ++falseAlarms, s); 
            }
        }

        if (s < n - m) {
            t = (d * (t - tptr[s] * h) + tptr[s + m]) % q;
            if (t < 0) t += q;
        }
    }

    return matches;
}

void test_rabin_karp_matcher(void) {
    char T[] = "314159265358973";
    char P[] = "26";
    int n = (int)strlen(T);
    int m = (int)strlen(P);
    int d = 10; // Alphabet size
    int q = 11; // Prime modulus
    printf("Total matches: %d\n", rabin_karp_matcher(T, P, n, m, d, q));
}

// 32.2-2
int rabin_karp_multi_matcher(
    char* T, 
    PatternHash* patterns, 
    int patternCnt, 
    int n,
    int d, 
    int q
) {
    unsigned char* tptr = (unsigned char*)T;

    int maxLengths = 0;
    for (int i = 0; i < patternCnt; ++i)
        if (patterns[i].length > maxLengths) maxLengths = patterns[i].length;

    for (int i = 0; i < patternCnt; ++i) {
        patterns[i].hash = 0;
        unsigned char* pptr = (unsigned char*)patterns[i].pattern;
        for (int j = 0; j < patterns[i].length; ++j) 
            patterns[i].hash = (patterns[i].hash + pptr[j] * modular_exponentation(d, patterns[i].length - 1 - j, q)) % q;
        printf("Pattern[%d] = \"%s\", length=%d, hash=%d\n", 
            i, patterns[i].pattern, patterns[i].length, patterns[i].hash);
    }
    printf("\n");

    int matches = 0;
    int falseAlarms = 0;

    for (int winLen = 1; winLen <= maxLengths; ++winLen) {
        int lenCnt = 0;
        for (int i = 0; i < patternCnt; ++i)
            if (patterns[i].length == winLen) lenCnt++;

        if (lenCnt == 0) continue;

        PatternHash* lenGroup = (PatternHash*)safe_malloc(sizeof(PatternHash) * lenCnt);
        int idx = 0;
        for (int i = 0; i < patternCnt; ++i)
            if (patterns[i].length == winLen) lenGroup[idx++] = patterns[i];

        int h = (int)modular_exponentation(d, winLen - 1, q);
        int t = 0;

        if (n < winLen) continue;

        for (int i = 0; i < winLen; ++i) t = (d * t + tptr[i]) % q;
        for (int s = 0; s <= n - winLen; ++s) {
            printf("[shift %d, length %d] window \"%.*s\" hash t = %d\n",
                       s, winLen, winLen, T + s, t);

            for (int patternIdx = 0; patternIdx < patternCnt; ++patternIdx) {
                if (t != lenGroup[patternIdx].hash) continue;
                printf("  Hash match with pattern \"%s\"\n", lenGroup[patternIdx].pattern);
                int match = 1;
                unsigned char* pptr = (unsigned char*)lenGroup[patternIdx].pattern;
                for (int j = 0; j < winLen; ++j) {
                    if (tptr[s + j] != pptr[j]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    printf("  Match at shift %d\n", s);
                    matches++;
                } else printf("  False alarm %d at shift %d\n", ++falseAlarms, s);
            }

            if (s < n - winLen) {
                t = (d * (t - tptr[s] * h) + tptr[s + winLen]) % q;
                if (t < 0) t += q;
            }
        }

        free(lenGroup);
        printf("\n");
    }

    printf("Total false alarms: %d\n", falseAlarms);
    return matches;
}

void test_rabin_karp_multi_matcher(void) {
    char* patterns[] = {"26", "53", "979"};
    int patternsCnt = ARRAY_SIZE(patterns);

    PatternHash ph[patternsCnt];
    for (int i = 0; i < patternsCnt; ++i) {
        ph[i].pattern = patterns[i];
        ph[i].length = (int)strlen(patterns[i]);
    }

    char T[] = "3141592653589793";
    int n = (int)strlen(T);
    int d = 10;
    int q = 1009;

    printf("Total matches: %d\n",
        rabin_karp_multi_matcher(T, ph, patternsCnt, n, d, q));
}

// 32.2-3
int rabin_karp_2d_matcher(char** T, char** P, int n, int m, int d, int q) {
    int colHash[m];
    int patternColHash[m];

    for (int j = 0; j < m; ++j) {
        patternColHash[j] = 0;
        for (int i = 0; i < m; ++i)
            patternColHash[j] = (patternColHash[j] + P[i][j] * modular_exponentation(d, m - 1 - i, q)) % q;
    }

    int patternHash = 0;
    for (int j = 0; j < m; ++j) patternHash = (patternHash * d + patternColHash[j]) % q;

    printf("Pattern column hashes: ");
    print_arr(patternColHash, m);
    printf("\nPattern hash = %d\n\n", patternHash);

    int matches = 0;
    int falseAlarms = 0;

    for (int rowShift = 0; rowShift <= n - m; ++rowShift) {
        for (int j = 0; j < m; ++j) {
            colHash[j] = 0;
            for (int i = 0; i < m; ++i) {
                colHash[j] = (colHash[j] + T[rowShift + i][0 + j] * modular_exponentation(d, m - 1 - i, q)) % q;
            }
        }

        for (int colShift = 0; colShift <= n - m; ++colShift) {
            int tHash = 0;
            for (int j = 0; j < m; ++j) tHash = (tHash * d + colHash[j]) % q;

            printf("[window at (%d, %d)] column hashes: ", rowShift, colShift);
            for (int j = 0; j < m; ++j) printf("%d ", colHash[j]);
            printf("  window hash = %d\n", tHash);

            if (tHash == patternHash) {
                int match = 1;
                for (int i = 0; i < m && match; ++i)
                    for (int j = 0; j < m; ++j)
                        if (T[rowShift + i][colShift + j] != P[i][j]) { match = 0; break; }

                if (match) printf("  Match %d at (%d, %d)\n", ++matches, rowShift, colShift);
                else printf("  False alarm %d at (%d, %d)\n", ++falseAlarms, rowShift, colShift);
            }

            if (colShift < n - m) {
                for (int j = 0; j < m - 1; ++j) colHash[j] = colHash[j + 1];

                int newCol = colShift + m;
                int newHash = 0;
                for (int i = 0; i < m; ++i) {
                    newHash = (newHash + T[rowShift + i][newCol] * modular_exponentation(d, m - 1 - i, q)) % q;
                }
                colHash[m - 1] = newHash;
            }
        } 
    }

    printf("Total false alarms: %d\n", falseAlarms);
    return matches;
}

void test_rabin_karp_2d_matcher(void) {
    int n = 5;
    int m = 2;
    char* T[] = {
        "26262",
        "53535",
        "26253",
        "53526",
        "26253"
    };
    char* P[] = {
        "26",
        "53"
    };
    int d = 10;
    int q = 1009;

    printf("Total matches: %d\n", rabin_karp_2d_matcher(T, P, n, m, d, q));
}
