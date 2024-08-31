#pragma once

#include "limits.h"
#include "vector"

using namespace std;

void FindMaxCrossingSubarray(vector<int> &A, int low, int mid, int high, int &max_left, int &max_right, int &sums) {
    int left_sum = INT_MIN;
    int sum = 0;
    for (int i = mid; i >= low; --i) {
        sum += A[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }
    int right_sum = INT_MIN;
    sum = 0;
    for (int i = mid + 1; i <= high; ++i) {
        sum += A[i];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = i;
        }
    }
    sums = left_sum + right_sum;
}

void FindMaximumSubarray(vector<int> &A, int low, int high, int &lows, int &highs, int &sums) {
    if (high == low) {
        return;
    }
    int mid = (low + high) / 2;
    int left_low = 0, left_high = 0, left_sum = 0;
    int right_low = 0, right_high = 0, right_sum = 0;
    int cross_low = 0, cross_high = 0, cross_sum = 0;
    FindMaximumSubarray(A, low, mid, left_low, left_high, left_sum);
    FindMaximumSubarray(A, mid + 1, high, right_low, right_high, right_sum);
    FindMaxCrossingSubarray(A, low, mid, high, cross_low, cross_high, cross_sum);
    if (left_sum >= right_sum && left_sum >= cross_sum) {
        lows = left_low;
        highs = left_high;
        sums = left_sum;
        return;
    } else if (right_sum >= left_sum && right_sum >= cross_sum) {
        lows = right_low;
        highs = right_high;
        sums = right_sum;
        return;
    } else {
        lows = cross_low;
        highs = cross_high;
        sums = cross_sum;
        return;
    }
}

// #include <iostream>
// #include "vector"
// #include "head/FindMaximumSubarray.h"
// using namespace std;


// int main() {
//     vector<int> v = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
//     int low = 0, high = 0, sum = 0;
//     FindMaximumSubarray(v, 0, v.size() - 1, low, high, sum);
//     cout << "low: " << low + 1 << endl << "high: " << high + 1 << endl << "sum: " << sum << endl;
// }