#pragma once

#include "vector"

using namespace std;

vector<vector<int>> SquareMatrixMultiply(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// #include <iostream>
// #include "vector"
// #include "head/SquareMatrixMultiply.h"
// using namespace std;


// int main() {
//     vector<vector<int>> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};    
//     vector<vector<int>> B = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//     vector<vector<int>> C(A.size(), vector<int>(A.size()));
//     C = SquareMatrixMultiply(A, B);
//     for (auto i : C) {
//         for (auto j : i) {
//             cout << j << " ";
//         }
//         cout << endl;
//     }
// }