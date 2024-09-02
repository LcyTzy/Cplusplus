#pragma once

#include "vector"
#include "algorithm"

using namespace std;


int ParTition(vector<int> &A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; ++j) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}


void QuickSort(vector<int> &A, int p, int r) {
    if (p < r) {
        int q = ParTition(A, p, r);
        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
}

// // 测试函数
// int main() {
//     vector<int> A = {2, 8, 7, 1, 3, 5, 6, 4};    
//     QuickSort(A, 0, A.size() - 1);
//     for (auto i : A) {
//         cout << i << " ";
//     }
// }


// 采用随机抽样
int RandomizedPartition(vector<int> &A, int p, int r) {
    int i = (rand() % r - p + 1) + p;
    swap(A[r], A[i]);
    return ParTition(A, p, r);
}

void RandomizedQuickSort(vector<int> &A, int p, int r) {
    if (p < r) {
        int q = RandomizedPartition(A, p, r);
        RandomizedQuickSort(A, p, q - 1);
        RandomizedQuickSort(A, q + 1, r);
    }
}