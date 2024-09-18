#pragma once

#include "cmath"
#include "vector"
#include "limits.h"
#include "iostream"

using namespace std;

int cut_rod(vector<int> p, int n) {
    if (n == 0) return 0;
    int q = INT_MIN;
    for (int i = 1; i <= n; ++i) {
        q = max(q, p[i] + cut_rod(p, n - i));
    }
    return q;
}

// 测试函数
// int main() {
//     vector<int> v = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
//     for (int i = 1; i < v.size(); ++i) {
//         cout << cut_rod(v, i) << endl;
//     }
// }

// 自顶向下
int memoized_cut_rod_aux(vector<int> p, int n, vector<int>& r) {
    if (r[n] >= 0) return r[n];
    int q = INT_MIN;
    if (n == 0) q = 0;
    else {
        for (int i = 1; i <= n; ++i) {
            q = max(q, p[i] + memoized_cut_rod_aux(p, n - i, r));
        }
    }
    r[n] = q;
    return q;
}

int memoized_cut_rod(vector<int> p, int n) {
    vector<int> r(n + 1, INT_MIN);
    return memoized_cut_rod_aux(p, n, r);
}

// 测试函数
// int main() {
//     vector<int> v = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
//     for (int i = 1; i < v.size(); ++i) {
//         cout << memoized_cut_rod(v, i) << endl;
//     }
// }


// 自底向上
int bottom_up_cut_rod(vector<int> p, int n) {
    vector<int> r(n + 1, 0);
    int q = INT_MIN;
    for (int i = 1; i <= n; ++i) {
        q = INT_MIN;
        for (int j = 1; j <= i; ++j) {
            q = max(q, p[j] + r[i - j]);
        }
        r[i] = q;
    }
    return r[n];
}

// 测试函数
// int main() {
//     vector<int> v = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
//     for (int i = 1; i < v.size(); ++i) {
//         cout << bottom_up_cut_rod(v, i) << endl;
//     }
// }


// 重构解
vector<int> extended_bottom_up_cut_rod(vector<int> p, int n, vector<int> &s) {
    vector<int> r(n + 1, 0);
    int q = INT_MIN;
    for (int i = 1; i < n + 1; ++i) {
        q = INT_MIN;
        for (int j = 1; j <= i; ++j) {
            if (q < p[j] + r[i - j]) {
                q = p[j] + r[i - j];
                s[i] = j;
            }
        }
        r[i] = q;
    }
    return r;
}

void print_cut_rod_solution(vector<int> p, int n) {
    vector<int> s(n + 1, 0);
    vector<int> r = extended_bottom_up_cut_rod(p, n, s);
    while (n > 0) {
        cout << s[n] << " ";
        n -= s[n];
    }
}

// 测试函数
// int main() {
//     vector<int> v = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
//     for (int i = 1; i < v.size(); ++i) {
//         cout << bottom_up_cut_rod(v, i) << endl;
//         print_cut_rod_solution(v, i);
//         cout << endl;
//     }
// }