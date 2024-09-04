#pragma once

#include "vector"
#include "QuickSort.h"

using namespace std;


// 返回第i小的元素
int RandomizedSelect01(vector<int> &A, int p, int r, int i) {
    if (p == r) return A[p];
    int q = RandomizedPartition(A, p, r);
    int k = q - p + 1;
    if (i == k) return A[q];
    else if (i < k) return RandomizedSelect01(A, p, q - 1, i);
    else    return RandomizedSelect01(A, q + 1, r, i - k);
}

// 测试函数
// int main() {
// 	vector<int> A = {5, 2, 8, 10, 4, 9, 3, 7, 6};
//     cout << RandomizedSelect01(A, 0, A.size() - 1, 3);
// }

// 基于循环的版本
int RandomizedSelect02(vector<int> &A, int p, int r, int i) {
    while (true) {
        if (p == r) return A[p];
        int q = RandomizedPartition(A, p, r);
        int k = q - p + 1;
        if (i == k) return A[q];
        if (i < k)  r = q - 1;
        else {
            p = q + 1;
            i -= k;
        }
    }
}
 
// 测试函数
// int main() {
// 	vector<int> A = {5, 2, 8, 10, 4, 9, 3, 7, 6};
//     cout << RandomizedSelect02(A, 0, A.size() - 1, 3);
// }