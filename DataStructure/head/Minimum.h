#pragma once

#include "vector"
#include "algorithm"

using namespace std;

int Minimum(vector<int> &A) {
    int Min = A[0];
    for (int i = 1; i < A.size(); ++i) {
        Min = min(Min, A[i]);
    }
    return Min;
}


// 测试函数
// int main() {
 
// 	vector<int> A = {5, 2, 8, 10, 1, 2};
//     cout << Minimum(A);
// }