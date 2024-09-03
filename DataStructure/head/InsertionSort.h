#pragma once
#include "vector"
using namespace std;

void sort(vector<int> &A) {
    int n = A.size();
    for (int j = 1; j < n; ++j) {
        int key = A[j];
        int i = j - 1;
        while (i > -1 and A[i] > key) {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = key;
    }
}

// 基于遗忘比较交换
void CompareExchange(vector<int> &A, int i, int j) {
    if (A[i] > A[j]) {
        swap(A[i], A[j]);
    }
}

void InsertionSort(vector<int> &A) {
    for (int j = 1; j < A.size(); ++j) {
        for (int i = j - 1; i >= 0; --i) {
            CompareExchange(A, i, i + 1);
        }
    }
}