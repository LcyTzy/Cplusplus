#pragma once

#include "vector"
#include "algorithm"

using namespace std;

void bubble_sort(vector<int> &A) {
    for (int i = 0; i < A.size(); ++i) {
        for (int j = A.size() - 1; j > i; --j) {
            if (A[j] < A[j - 1]) {
                swap(A[j], A[j - 1]);
            }
        }
    }
} 