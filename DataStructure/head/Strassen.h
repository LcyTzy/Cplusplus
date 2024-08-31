#pragma once


// 矩阵规模为2的n次幂
// 注释了的是错误的，待改正
// vector<vector<int>> Strassen(vector<vector<int>> &A, vector<vector<int>> &B) {
//     int n = A.size();
//     if (n == 1) {
//         vector<vector<int>> C = {{A[0][0] * B[0][0]}};
//         return C;
//     }
//     vector<vector<int>> A11(n / 2, vector<int>(n / 2));
//     vector<vector<int>> A12(n / 2, vector<int>(n / 2));
//     vector<vector<int>> A21(n / 2, vector<int>(n / 2));
//     vector<vector<int>> A22(n / 2, vector<int>(n / 2));
//     vector<vector<int>> B11(n / 2, vector<int>(n / 2));
//     vector<vector<int>> B12(n / 2, vector<int>(n / 2));
//     vector<vector<int>> B21(n / 2, vector<int>(n / 2));
//     vector<vector<int>> B22(n / 2, vector<int>(n / 2));
//     for (int i = 0; i < n / 2; ++i) {
//         for (int j = 0; j < n / 2; ++j) {
//             A11[i][j] = A[i][j];
//             B11[i][j] = B[i][j];
//         }
//         for (int j = n / 2; j < n; ++j) {
//             A12[i][j - n / 2] = A[i][j];
//             B12[i][j - n / 2] = B[i][j];
//         }
//     }
//     for (int i = n / 2; i < n; ++i) {
//         for (int j = 0; j < n / 2; ++j) {
//             A21[i - n / 2][j] = A[i][j];
//             B21[i - n / 2][j] = B[i][j];
//         }
//         for (int j = n / 2; j < n; ++j) {
//             A22[i - n / 2][j - n / 2] = A[i][j];
//             B22[i - n / 2][j - n / 2] = B[i][j];
//         }
//     }
//     vector<vector<int>> S1(n / 2, vector<int>(n / 2));
//     vector<vector<int>> S2(n / 2, vector<int>(n / 2));
//     vector<vector<int>> S3(n / 2, vector<int>(n / 2));
//     vector<vector<int>> S4(n / 2, vector<int>(n / 2));
//     vector<vector<int>> S5(n / 2, vector<int>(n / 2));
//     vector<vector<int>> S6(n / 2, vector<int>(n / 2));
//     vector<vector<int>> S7(n / 2, vector<int>(n / 2));
//     vector<vector<int>> S8(n / 2, vector<int>(n / 2));
//     vector<vector<int>> S9(n / 2, vector<int>(n / 2));
//     vector<vector<int>> S10(n / 2, vector<int>(n / 2));
//     for (int i = 0; i < n / 2; ++i) {
//         for (int j = 0; j < n / 2; ++j) {
//             S1[i][j] = B12[i][j] - B22[i][j];
//             S2[i][j] = A11[i][j] + A12[i][j];
//             S3[i][j] = A21[i][j] + A22[i][j];
//             S4[i][j] = B21[i][j] - B11[i][j];
//             S5[i][j] = A11[i][j] + A22[i][j];
//             S6[i][j] = B11[i][j] + B22[i][j];
//             S7[i][j] = A12[i][j] - A22[i][j];
//             S8[i][j] = B21[i][j] + B22[i][j];
//             S9[i][j] = A11[i][j] - A21[i][j];
//             S10[i][j] = B11[i][j] + B12[i][j];
//         }
//     }
//     vector<vector<int>> P1 = Strassen(A11, S1);
//     vector<vector<int>> P2 = Strassen(S1, B22);
//     vector<vector<int>> P3 = Strassen(S3, B11);
//     vector<vector<int>> P4 = Strassen(A22, S4);
//     vector<vector<int>> P5 = Strassen(S5, S6);
//     vector<vector<int>> P6 = Strassen(S7, S8);
//     vector<vector<int>> P7 = Strassen(S9, S10);
//     vector<vector<int>> C11(n / 2, vector<int>(n / 2));
//     vector<vector<int>> C12(n / 2, vector<int>(n / 2));
//     vector<vector<int>> C21(n / 2, vector<int>(n / 2));
//     vector<vector<int>> C22(n / 2, vector<int>(n / 2));
//     for (int i = 0; i < n / 2; ++i) {
//         for (int j = 0; j < n / 2; ++j) {
//             C11[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
//             C12[i][j] = P1[i][j] + P2[i][j];
//             C21[i][j] = P3[i][j] + P4[i][j];
//             C22[i][j] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
//         }
//     }
//     vector<vector<int>> C(n, vector<int>(n));
//     for (int i = 0; i < n / 2; ++i) {
//         for (int j = 0; j < n / 2; ++j) {
//             C[i][j] = C11[i][j];
//             C[i][j + n / 2] = C12[i][j];
//             C[i + n / 2][j] = C21[i][j];
//             C[i + n / 2][j + n / 2] = C22[i][j];
//         }
//     }
//     return C;
// }


#include <vector>
#include <cmath>

// 辅助函数，用于矩阵相加
std::vector<std::vector<int>> addMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// 辅助函数，用于矩阵相减
std::vector<std::vector<int>> subtractMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// 辅助函数，用于矩阵的四分之一
std::vector<std::vector<int>> getQuadrant(const std::vector<std::vector<int>>& A, int startRow, int startCol, int size) {
    std::vector<std::vector<int>> quadrant(size / 2, std::vector<int>(size / 2));
    for (int i = 0; i < size / 2; ++i) {
        for (int j = 0; j < size / 2; ++j) {
            quadrant[i][j] = A[startRow + i][startCol + j];
        }
    }
    return quadrant;
}

// Strassen算法实现
std::vector<std::vector<int>> strassenMultiply(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    // 如果矩阵不是2的幂次方，填充到最接近的2的幂
    int newSize = 1;
    while (newSize < n) newSize *= 2;
    std::vector<std::vector<int>> Ap(newSize, std::vector<int>(newSize, 0));
    std::vector<std::vector<int>> Bp(newSize, std::vector<int>(newSize, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Ap[i][j] = A[i][j];
            Bp[i][j] = B[i][j];
        }
    }

    if (n <= 64) { // 对于小矩阵，使用传统的矩阵乘法
        std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    C[i][j] += Ap[i][k] * Bp[k][j];
                }
            }
        }
        return C;
    }

    // 分解矩阵
    int half = newSize / 2;
    std::vector<std::vector<int>> A11 = getQuadrant(Ap, 0, 0, newSize);
    std::vector<std::vector<int>> A12 = getQuadrant(Ap, 0, half, newSize);
    std::vector<std::vector<int>> A21 = getQuadrant(Ap, half, 0, newSize);
    std::vector<std::vector<int>> A22 = getQuadrant(Ap, half, half, newSize);
    std::vector<std::vector<int>> B11 = getQuadrant(Bp, 0, 0, newSize);
    std::vector<std::vector<int>> B12 = getQuadrant(Bp, 0, half, newSize);
    std::vector<std::vector<int>> B21 = getQuadrant(Bp, half, 0, newSize);
    std::vector<std::vector<int>> B22 = getQuadrant(Bp, half, half, newSize);

    // 计算7个子问题
    std::vector<std::vector<int>> P1 = strassenMultiply(A11, subtractMatrices(B12, B22));
    std::vector<std::vector<int>> P2 = strassenMultiply(addMatrices(A11, A12), B22);
    std::vector<std::vector<int>> P3 = strassenMultiply(addMatrices(A21, A22), B11);
    std::vector<std::vector<int>> P4 = strassenMultiply(A22, subtractMatrices(B21, B11));
    std::vector<std::vector<int>> P5 = strassenMultiply(addMatrices(A11, A22), addMatrices(B11, B22));
    std::vector<std::vector<int>> P6 = strassenMultiply(subtractMatrices(A12, A22), addMatrices(B21, B22));
    std::vector<std::vector<int>> P7 = strassenMultiply(subtractMatrices(A11, A21), addMatrices(B11, B12));

    // 合并结果
    std::vector<std::vector<int>> C11 = addMatrices(subtractMatrices(addMatrices(P5, P4), P2), P6);
    std::vector<std::vector<int>> C12 = addMatrices(P1, P2);
    std::vector<std::vector<int>> C21 = addMatrices(P3, P4);
    std::vector<std::vector<int>> C22 = subtractMatrices(subtractMatrices(addMatrices(P5, P1), P3), P7);

    // 构建最终结果矩阵
    std::vector<std::vector<int>> C(newSize, std::vector<int>(newSize, 0));
    for (int i = 0; i < half; ++i) {
        for (int j = 0; j < half; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }

    return C;
}

// int main() {
//     // 示例矩阵
//     std::vector<std::vector<int>> A = {{1, 2}, {3, 4}};
//     std::vector<std::vector<int>> B = {{5, 6}, {7, 8}};

//     std::vector<std::vector<int>> result = strassenMultiply(A, B);

//     // 打印结果
//     for (const auto& row : result) {
//         for (int val : row) {
//             std::cout << val << " ";
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }