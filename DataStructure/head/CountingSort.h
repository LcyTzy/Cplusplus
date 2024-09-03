#pragma once

#include "vector"

using namespace std;

void CountingSort(vector<int> &A, vector<int> &B, int k) {
    vector<int> C(k + 1, 0);
    for (int j = 0; j < A.size(); ++j) {
        C[A[j]]++; 
    }
    for (int i = 1; i < k + 1; ++i) {
        C[i] += C[i - 1];
    }
    for (int j = A.size() - 1; j >= 0; --j) {
        B[C[A[j]] - 1] = A[j];
        C[A[j]]--;
    }
}

// 测试函数
// int main() {
//     vector<int> A = {2, 5, 3, 0, 2, 3, 0, 3};
//     vector<int> B(A.size(), 0);    
//     CountingSort(A, B, 5);
//     for (auto i : B) {
//         cout << i << " ";
//     }
// }