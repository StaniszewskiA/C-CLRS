#ifndef MERGE_INSERTION_SORT_H
#define MERGE_INSERTION_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void mergeInsertionSort(int arr[], int left, int right, int k);
void printArray(int arr[], int size);

#endif 
