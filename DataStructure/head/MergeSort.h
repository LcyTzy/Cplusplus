#pragma once
 
#include "vector"
using namespace std;

void merge(vector<int> &A, int start, int mid, int end) {
    int i = start, j = mid + 1;
    int k = 0;
    vector<int> v(end - start + 1);
    while (i <= mid && j <= end) {
        if (A[i] < A[j]) {
            v[k++] = A[i++];
        } else {
            v[k++] = A[j++];
        }
    }
    while (i <= mid)    v[k++] = A[i++];
    while (j <= end)      v[k++] = A[j++];
    for (int i = start, j = 0; i < end + 1; ++i, ++j) {
        A[i] = v[j]; 
    }
}

void merge_sort(vector<int> &A, int start, int end) {
    if (start >= end) {
        return;
    }
    int mid = (start + end) / 2;
    merge_sort(A, start, mid);
    merge_sort(A, mid + 1, end);
    merge(A, start, mid, end);
}