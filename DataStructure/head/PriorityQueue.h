#pragma once

#include "vector"
#include "algorithm"
#include "limits.h"
#include "Heap.h"

using namespace std;

// 最大堆实现最大优先队列
int HeapMaximum(vector<int> &A) {
    return A[0];
}

int HeapExtractMax(vector<int> &A) {
    if (A.size() < 1)
        throw "heap underflow";
    int Max = A[0];
    A[0] = A[A.size() - 1];
    A.pop_back();
    MaxHeapify(A, 0, A.size());
    return Max;
}

void HeapIncreaseKey(vector<int> &A, int i, int key) {
    if (key < A[i]) {
        throw "new key is smaller than current key";
    }
    A[i] = key;
    while (i > 0 && A[Parent(i)] < A[i]) {
        swap(A[i], A[Parent(i)]);
        i = Parent(i);
    }
}

void MaxHeapInsert(vector<int> &A, int key) {
    A.push_back(INT_MIN);
    HeapIncreaseKey(A, A.size() - 1, key);
}

// 测试函数
// int main() {
//     vector<int> A = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
//     cout << HeapExtractMax(A) << endl;
//     for (auto i : A) {
//         cout << i << " ";
//     }
//     cout << endl;

//     A = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
//     MaxHeapInsert(A, 10);
//     for (auto i : A) {
//         cout << i << " ";
//     }
//     cout << endl;
// }


// 最小堆实现最小优先队列
int HeapMinmum(vector<int> &A) {
    return A[0];
}

int HeapExtractMin(vector<int> &A) {
    if (A.size() < 1) {
        throw "heap underflow";
    } 
    int Min = A[0];
    A[0] = A[A.size() - 1];
    A.pop_back();
    MinHeapify(A, 0, A.size());
    return Min;
}

void HeapDecreaseKey(vector<int> &A, int i, int key) {
    if (key > A[i]) {
        throw "new key is larger than current key";
    }
    A[i] = key;
    while (i > 0 && A[Parent(i)] > A[i]) {
        swap(A[i], A[Parent(i)]);
        i = Parent(i);
    }
}

void MinHeapInsert(vector<int> &A, int key) {
    A.push_back(INT_MAX);
    HeapDecreaseKey(A, A.size() - 1, key);
}