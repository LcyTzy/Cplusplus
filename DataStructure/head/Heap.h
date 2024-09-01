#pragma once

#include <vector>
#include <algorithm>

using namespace std;

// 返回父节点下标
int Parent(int i) {
    return (i - 1) / 2;
}

// 返回左孩子下标
int Left(int i) {
    return 2 * i + 1;
}

// 返回右孩子下标
int Right(int i) {
    return 2 * i + 2;
}

// 维护最大堆性质
void MaxHeapify(vector<int> &A, int i, int heapSize) {
    int l = Left(i);
    int r = Right(i);
    int largest = i;
    
    if (l < heapSize && A[l] > A[i]) 
        largest = l;
    
    if (r < heapSize && A[r] > A[largest]) 
        largest = r;
    
    if (largest != i) {
        swap(A[i], A[largest]);
        MaxHeapify(A, largest, heapSize);
    }
}

// 维护最小堆性质
void MinHeapify(vector<int> &A, int i, int heapSize) {
    int l = Left(i);
    int r = Right(i);
    int smallest = i;
    
    if (l < heapSize && A[l] < A[i])
        smallest = l;
    
    if (r < heapSize && A[r] < A[smallest])
        smallest = r;
    
    if (smallest != i) {
        swap(A[i], A[smallest]);
        MinHeapify(A, smallest, heapSize);
    }
}

// 建堆
void BuildMaxHeap(vector<int> &A) {
    for (int i = A.size() / 2 - 1; i >= 0; --i) {
        MaxHeapify(A, i, A.size());
    }
}

// 堆排序
vector<int> HeapSort(vector<int> &A) {
    BuildMaxHeap(A);
    int heapSize = A.size();
    for (int i = heapSize - 1; i > 0; --i) {
        swap(A[0], A[i]);
        --heapSize;
        MaxHeapify(A, 0, heapSize);
    }
    return A;
}

// // 测试函数
// int main() {
//     vector<int> A = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
//     vector<int> sorted = HeapSort(A);

//     cout << "Sorted array: ";
//     for (int i : sorted) {
//         cout << i << " ";
//     }
//     cout << endl;

// }