#pragma once

#include "vector"
using namespace std;

int iterative_binary_search(vector<int> &A, int v, int low, int high) {
    while (low <= high) {
        int mid = (low + high) / 2;
        if (v == A[mid]) {
            return mid;
        } else if (v > A[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int becursive_binary_search(vector<int> &A, int v, int low, int high) {
    if (low > high) {
        return -1;
    }
    int mid = (low + high) / 2;
    if (v == A[mid]) {
        return mid;
    } else if (v > A[mid]) {
        return becursive_binary_search(A, v, mid + 1, high);
    } else {
        return becursive_binary_search(A, v, low, mid - 1);
    }
}