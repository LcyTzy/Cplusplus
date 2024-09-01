# 算法导论

## 第二章 算法基础

### 伪代码约定

```
INSERTION-SORT(A)
for j = 2 to A.length
	key = A[j]
	// Insert A[j] into the sorted sequence A[1..j-1].
	i = j - 1
	while i > 0 and A[i] > key
		A[i + 1] = A[i]
		i = i - 1
	A[i + 1] = key
```

- 缩进表示块结构
- **while**、**for** 与 **repeat-until** 等循环结构以及 **if-else** 等条件结构与 C、C++、Java、Python和Pascal中的那些结构具有类似的解释。不像某些出现于C、C++、Java和Pascal中的情况，本书中在退出循环后，循环计数器保持其值。
- 符号“//”表示该行后面部分是个注释。
- 形如 i = j = e 的多重赋值将表达式e的值赋给变量 i 和 j；它应被处理成等价于赋值 j = e 后跟着赋值 i = j。
- 变量（如 i、j 和 key）是局部于给定过程的。若无显示说明，我们不使用全局变量。
- 数组元素通过“数组名[下标]”这样的形式来访问。例如：A[1..j]。
- 复合数据通常被组织成**对象**，对象又由**属性**组成。
- 我们**按值**把参数传递给过程：被调用过程接收其参数自身的副本。
- 一个**return**语句立即将控制返回到调用过程的调用点。
- 布尔运算符“and”和“or”都是**短路** 的。
- 关键词**error**表示因为已被调用的过程情况不对而出现了一个错误。

### 2.1. 插入排序

```
INSERTION-SORT(A)
for j = 2 to A.length
	key = A[j]
	// Insert A[j] into the sorted sequence A[1..j-1].
	i = j - 1
	while i > 0 and A[i] > key
		A[i + 1] = A[i]
		i = i - 1
	A[i + 1] = key
```

```c++
void sort(vector<int> &A) {
    int n = A.size();
    for (int j = 1; j < n; ++j) {
        int key = A[j];
        int i = j - 1;
        while (i > -1 and A[i] > key) {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = key;
    }
}
```

### 2.3. 设计算法

#### 2.3.1. 分治法

将原问题分解为几个规模较小但类似于原问题的子问题，递归的求解这些子问题，然后再合并这些子问题的解来建立原问题的解。

​	分治模式在每层递归时都有三个步骤：

- **分解**原问题为若干子问题，这些子问题是原问题的规模较小的实例。
- **解决**这些子问题，递归地求解各子问题。然而，若子问题的规模足够小，则直接求解。
- 合并这些子问题的解成原问题的解

​	**归并排序**算法完全遵循分治模式

- **分解：**分解待排序的n个元素的序列成各具 n / 2 个元素的两个子序列。
- **解决：**使用归并排序递归的排序两个子序列。
- **合并：**合并两个已排序的子序列以产生已排序的答案。

#### 归并排序

```
// 有哨兵
MERGE(A, p, q, r)
n1 = q - p + 1
n2 = r - q
let L[1 ... n1 + 1] and R[1 ... n2 + 1] be new arrays
for i = 1 to n1
	L[i] = A[p + i - 1]
for j = 1 to n2
	R[j] = A[q + j]
L[n1 + 1] = ∞
R[n2 + 1] = ∞
i = 1
j = 1
for k = p to r
	if L[i] <= R[j]
		A[k] = L[i]
		i = i + 1
	else A[k] = R[j]
		j = j + 1
```

```
// 无哨兵
MERGE(A, p, q, r)
    n1 = q - p + 1
    n2 = r - q
    let L[1..n1] and R[1..n2] be new arrays
    for i = 1 to n1
        L[i] = A[p + i - 1]
    for j = 1 to n2
        R[j] = A[q + j]
    i = 1
    j = 1
    for k = p to r
        if i > n1
            A[k] = R[j]
            j = j + 1
        else if j > n2
            A[k] = L[i]
            i = i + 1
        else if L[i] ≤ R[j]
            A[k] = L[i]
            i = i + 1
        else
            A[k] = R[j]
            j = j + 1
```



```c++
#pragma once

#include "vector"
using namespace std;

void merge(vector<int> &A, int start, int mid, int end) {
    int i = start, j = mid + 1;
    int k = 0;
    vector<int> v(end - start + 1);
    while (i <= mid && j <= end) {
        if (A[i] < A[j]) {
            v[k++] = A[i++];
        } else {
            v[k++] = A[j++];
        }
    }
    while (i <= mid)    v[k++] = A[i++];
    while (j <= end)      v[k++] = A[j++];
    for (int i = start, j = 0; i < end + 1; ++i, ++j) {
        A[i] = v[j]; 
    }
}

void merge_sort(vector<int> &A, int start, int end) {
    if (start >= end) {
        return;
    }
    int mid = (start + end) / 2;
    merge_sort(A, start, mid);
    merge_sort(A, mid + 1, end);
    merge(A, start, mid, end);
}
```

#### 二分查找

**Iterative**:

```
ITERATIVE-BINARY-SEARCH(A, v, low, high)
	while low <= high
		mid = floor((low + high) / 2)
		if v == A[mid]
			return mid
		else if v > A[mid]
			low = mid + 1
		else high = mid - 1
	return NIL
```

Recurisive:

```
BECURSIVE-BINARY-SEARCH(A, v, low, high)
	if low > high
		return NIL
	mid = floor((low + high) / 2)
	if v == A[mid]
		return mid
	else if v > A[mid]
		return RECURSIVE-BINARY-SEARCH(A, v, mid + 1, high)
	else return RECURIVE-BINARY-SEARCH(A, v, low, mid - 1)
```

#### 冒泡排序

```
BUBBLESORT(A)
for i = 1 to A.length - 1
	for j = A.length downto i + 1
		if (A[j] < A[j - 1])
			exchange A[j] with A[j - 1]
```

## 第四章 分治算法

### 最大子数组问题

> 天数 	0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16
>
> 价格	100   113   110     85     105   102     86      63      81     101	94	106	101	79	94	90	97
>
> 变化		  13	-3    -25      20     -3       -16     -23    18       20        -7          12          -5       -22          15         -4       7

#### 使用分治策略的求解方法

A[low.. high]的任何连续子数组A[i.. j]所处的位置必然是以下三种情况之一：

- 完全处于子数组A[low.. mid]中，low<=i<=j<=mid
- 完全处于子数组A[mid+1.. high]中
- 跨越了中点

```
FIND-MAX-CROSSING-SUBARRAY(A, low, mid, high)
	left-sum = -∞
	sum = 0
	for i = mid downto low
		sum = sum + A[i]
		if sum > left-sum
			left-sum = sum
			max-left = i
	right-sum = -∞
	sum = 0
	for j = mid + 1 to high
		sum = sum + A[j]
		if sum > right-sum
			right-sum = sum
			max-right = j
	return (max-left, max-right, left-sum + right-sum)
```

```
FIND-MAXIMUM-SUBARRAY(A, low, high)
	if high == low
		return (low, high, A[low])
	else mid = [(low + high) / 2]
		(left-low, left-high, left-sum) = FIND-MAXIMUM-SUBARRAY(A, low, mid)
		(right-low, right-high, right-sum) = FIND-MAXIMUM-SUBARRAY(A, mid + 1, high)
		(cross-low, cross-high, cross-sum) = FIND-MAX-CROSSING-SUBARRAY(A, low, mid, high)
	if left-sum >= right-sum and left-sum >= cross-sum
		return (left-low, left-high, left-sum)
	elseif right-sum >= left-sum and right-sum >= cross-sum
		return (right-low, right-high, right-sum)
	else return (cross-low, cross-high, cross-sum)
```

```c++
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
```

### 矩阵乘法的Strassen算法

下面过程接受 n x n 矩阵A和B，返回它们的乘积— n x n 矩阵C

```
SQUARE-MATRIX-MULTIPLY(A, B)
	n = A.rows
	let C be a new n x n matrix
	for i = 1 to n
		for j = 1 to n
			cij = 0
			for k = 1 to n
				cij = cij + aik * bkj
	return C
```

```c++
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
```

#### 一个简单的分治

假定将 A、B、C 均分解为4个 n/2 x n/2 的子矩阵：

​	
$$
A = \left[
\matrix{
	A_{11}&A_{12}\\
	A_{21}&A_{22}\\
}
\right],
B = \left[
\matrix{
	B_{11}&B_{12}\\
	B_{21}&B_{22}\\
}
\right
] ,
C=\left[
\matrix{
	C_{11}&C_{12}\\
	C_{21}&C_{22}\\
}
\right
]
\space\space\space\space(4.9)
$$
因此可以将公式 C = A * B 改写为：
$$
\left[
\matrix{
	C_{11}&C_{12}\\
	C_{21}&C_{22}\\
}
\right
]=
\left[
\matrix{
A_{11}&A_{12}\\
A_{21}&A_{22}\\
}
\right
]*
\left[
\matrix{
B_{11}&B_{12}\\
B_{21}&B_{22}\\
}
\right
]
$$
等价于：
$$
C_{11} = A_{11}*B_{11}+A_{12}*B_{21}\\
C_{12} = A_{11}*B_{12}+A_{12}*B_{22}\\
C_{21} = A_{21}*B_{11}+A_{22}*B_{21}\\
C_{22} = A_{21}*B_{12}+A_{22}*B_{22}\\
$$
每个公式对应两对 n / 2 x n / 2 矩阵的乘法及 n / 2 x n / 2 积的加法。

```
SQUARE-MATRIX-MULTIPLY-RECURSIVE(A, B)
	n = A.rows
	let C be a new nxn matrix
	if n == 1
		c11 = a11 * b11
	else partition A, B and C as in equations
		C11 = SQUARE-MATRIX-MULTIPLY-RECURSIVE(A11, B11)
			+ SQUARE-MATRIX-MULTIPLY-RECURSIVE(A12, B21)
		c12 = SQUARE-MATRIX-MULTIPLY-RECURSIVE(A11, B12)
			+ SQUARE-MATRIX-MULTIPLY-RECURSIVE(A12, B22)
		C21 = SQUARE-MATRIX-MULTIPLY-RECURSIVE(A21, B11)
			+ SQUARE-MATRIX-MULTIPLY-RECURSIVE(A22, B21)
		C22 = SQUARE-MATRIX-MULTIPLY-RECURSIVE(A21, B12)
			+ SQUARE-MATRIX-MULTIPLY-RECURSIVE(A22, B22)
	return C
```

#### Strassen 方法

Strassen 算法的核心思想是令递归树稍微不那么旺盛一点，即递归7次而不是8次。

包含四个步骤：

- 按公式(4.9)将输入矩阵A、B和输出矩阵C分解为 n / 2 x n / 2 的子矩阵
- 创建10个 n / 2 x n / 2 的矩阵 S1，S2, ..., S10，每个矩阵保存步骤1中创建的两个子矩阵的和或差。
- 用步骤1中创建的子矩阵和步骤2中创建的10个矩阵，递归地计算7个矩阵积P1，P2，...，P7。每个矩阵Pi都是 n / 2 x n / 2 的。
- 通过Pi矩阵的不同组合进行加减运算，计算出结果矩阵C的子矩阵C11, C12, C21, C22.

 在步骤2中，创建如下10个矩阵：

> ​	S1 = B12 - B22
>
> ​	S2 = A11 + A12
>
> ​	S3 = A21 + A22
>
> ​	S4 = B21 - B11
>
> ​	S5 = A11 + A22
>
> ​	S6 = B11 + B22
>
> ​	S7 = A12 - A22
>
> ​	S8 = B21 + B22
>
> ​	S9 = A11 - A21
>
> ​	S10 = B11 + B12

在步骤3中，递归地计算7次 n / 2 x n / 2 矩阵的乘法：

> P1 = A11 * S1 = A11 * B12 - A11 * B22
>
> P2 = S2 * B22
>
> P3 = S3 * B11
>
> P4 = A22 * S4
>
> P5 = S5 * S6
>
> P6 = S7 * S8
>
> P7 = S9 * S10

步骤4：

> C11 = P5 + P4 - P2 + P6
>
> C12 = P1 + P2
>
> C21 = P3 + P4
>
> C22 = P5 + P1 - P3 - P7

矩阵规模为2的n次幂

```
STRASSEN(A, B)
	n = A.rows
	if n == 1
		return A[1, 1] * B[1, 1]
	let C be a new n X n matrix
	A[1,1] = A[1..n/2][1..n/2]
	A[1,2] = A[1..n/2][n/2 + 1..n]
	A[2,1] = A[n/2 + 1..n][1..n / 2]
	A[2,2] = A[n/2 + 1..n][n/2 + 1..n]
	B[1,1] = B[1..n/2][1..n/2]
	B[1,2] = B[1..n/2][n/2 + 1..n]
	B[2,1] = B[n/2 + 1..n][1..n / 2]
	B[2,2] = B[n/2 + 1..n][n/2 + 1..n]
	S[1] = B[1, 2] - B[2, 2]
    S[2] = A[1, 1] + A[1, 2]
    S[3] = A[2, 1] + A[2, 2]
    S[4] = B[2, 1] - B[1, 1]
    S[5] = A[1, 1] + A[2, 2]
    S[6] = B[1, 1] + B[2, 2]
    S[7] = A[1, 2] - A[2, 2]
    S[8] = B[2, 1] + B[2, 2]
    S[9] = A[1, 1] - A[2, 1]
    S[10] = B[1, 1] + B[1, 2]
    P[1] = STRASSEN(A[1, 1], S[1])
    P[2] = STRASSEN(S[2], B[2, 2])
    P[3] = STRASSEN(S[3], B[1, 1])
    P[4] = STRASSEN(A[2, 2], S[4])
    P[5] = STRASSEN(S[5], S[6])
    P[6] = STRASSEN(S[7], S[8])
    P[7] = STRASSEN(S[9], S[10])
    C[1..n / 2][1..n / 2] = P[5] + P[4] - P[2] + P[6]
    C[1..n / 2][n / 2 + 1..n] = P[1] + P[2]
    C[n / 2 + 1..n][1..n / 2] = P[3] + P[4]
    C[n / 2 + 1..n][n / 2 + 1..n] = P[5] + P[1] - P[3] - P[7]
    return C
```

## 第六章 堆排序（heapsort）

### 堆

**二叉堆**是一个数组，它可以被看成是一个近似的完全二叉树。树上的每一个结点对应数组中的一个元素。除了最底层外，该树是完全充满的，而且是从左向右填充。

> **A.length**	数组元素的个数
>
> **A.heao-size**	表示有多少个堆元素存储在该数组中。

父节点、左孩子和右孩子：

```
PARENT(i)
	return i/2

LEFT(i)
	return 2i

RIGHT(i)
	return 2i + 1
```

**最大堆性质** : 是指除了根以外的所有结点i都要满足：
$$
A[PARENT(i)] \geq A[i]
$$
也就是说，某个节点的值至多与其父节点一样大。

**最小堆性质** : 是指除了根以外的所有结点i都有：
$$
A[PARENT(i)] \leq A[i]
$$

### 维护堆的性质

**MAX-HEAPIFY**是用于维护最大堆性质的重要过程。

```
MAX-HEAPIFY(A, i)
	l = LEFT(i)
	r = RIGHT(i)
	if i <= A.heap-size and A[l] > A[i]
		largest = l
	else largest = i
	if r <= A.heap-size and A[r] > A[largest]
		largest = r
	if largest != i
		exchange A[i] withh A[largest]
		MAX-HEAPIFY(A, largest)
```

**MIN-HEAPIFY**

```
MIN-HEAPIFY(A, i)
    l = LEFT(i)
    r = RIGHT(i)
    if l ≤ A.heap-size and A[l] < A[i]
        smallest = l
    else smallest = i
    if r ≤ A.heap-size and A[r] < A[smallest]
        smallest = r
    if smallest != i
        exchange A[i] with A[smallest]
        MIN-HEAPIFY(A, smallest)
```

### 建堆

我们可以用自底向上的方法利用过程 **MAX-HEAPIFY** 把一个大小为 n = A.length 的数组 A[1.. n]转化为最大堆。

```
BUILE-MAX-HEAP(A)
	A.heap-size = A.length
	for i = [A.length/2] downto 1
		MAX-HEAPIFY(A, i)
```

### 堆排序算法

```
HEAPSORT(A)
	BUILE-MAX-HEAP(A)
	for i = A.length downto 2
		exchange A[i] with A[i]
		A.heap-size = A.heap-size - 1
		MAX-HEAPIFY(A, i)
```

```c++
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
```

### 优先队列

和堆一样，优先队列也有两种形式：最大优先队列和最小优先队列。这里，我们关注于如何基于最大堆实现最大优先队列。

**优先队列**是一种用来维护有一组元素构成的集合S的数据结构，其中的每一个元素都有一个相关的值，称为**关键字**。一个**最大优先队列**支持以下的操作：

> INSERT(S，x)：把元素x插入集合S中
>
> MAXIMUM(S)：返回S中具有最大键字的元素
>
> EXTRACT-MAX(S)：去掉并返回S中的具有最大键字的元素
>
> INCREASE-KEY(S，x，k)：将元素x的关键字值添加到k，这里假设k的值不小于x的原关键字值

```
HEAP-MAXIMUM(A)
	return A[1]

HEAP-EXTRACT-MAX(A)
	if A.heap-size < 1
		error "heap underflow"
	max = A[1]
	A[1] = A[A.heap-size]
	A.heap-size = A.heap.size - 1
	MAX-HEAPIFY(A, 1)
	return max
	
HEAP-INCREASE-KEY(A, i, key)
	if key < A[i]
		error "new key is smaller than current key"
	A[i] = key
	while i > 1 and A[PARENT(i)] < A[i]
		exchange A[i] with A[PARENT(i)]
		i = PARENT(i)
		
MAX-HEAP-INSERT(A, key)
	A.heap-size = A.heap-size + 1
	A[A.heap-size] = -∞
	HEAP-INCREASE-KEY(A, A.heap-size, key)
```

**最小堆实现最小优先队列**

```
HEAP-MINIMUM(A)
    return A[1]

HEAP-EXTRACT-MIN(A)
    if A.heap-size < 1
        error "heap underflow"
    min = A[1]
    A[1] = A[A.heap-size]
    A.heap-size = A.heap-size - 1
    MIN-HEAPIFY(A, 1)
    return min

HEAP-DECREASE-KEY(A, i, key)
    if key > A[i]
        error "new key is larger than current key"
    A[i] = key
    while i > 1 and A[PARENT(i)] > A[i]
        exchange A[i] with A[PARENT(i)]
        i = PARENT(i)

MIN-HEAP-INSERT(A, key)
    A.heap-size = A.heap-size + 1
    A[A.heap-size] = ∞
    HEAP-DECREASE-KEY(A, A.heap-size, key)
```

```c++
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
```

