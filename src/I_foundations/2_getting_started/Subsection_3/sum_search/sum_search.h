#ifndef SUM_SEARCH
#define SUM_SEARCH

bool binarySearch(int arr[], int left, int right, int target);
bool sumSearch(int arr[], int size, int target);

void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);
void printArray(int arr[], int size);
void printArraySlice(int arr[], int left, int right);

#endif