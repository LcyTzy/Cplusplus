#pragma once

#include "vector"
#include "algorithm"

using namespace std;


void RadixSort(vector<int>& arr) {
	int max = *max_element(arr.begin(), arr.end());
	// 获取最大数的位数d
	int d = 0;
	while (max) {
		max /= 10;
		d++;
	}
 
	int* count = new int[10];  // 计数器，也就是0~9共10个桶 
	int* tem = new int[arr.size()];  // 临时数组，和计数排序的临时数组作用一样 
 
	int radix = 1;
	for (int i = 0; i < d; i++) {// 可以看成进行了d次计数排序，以下代码和基数排序万分相像 
		// 每次将计数器清零
		for (int j = 0; j < 10; j++) {
			count[j] = 0;
		}
		for (int j = 0; j < arr.size(); j++) {
			// 计数，方便后续获得每个数的index 
			count[(arr[j] / radix) % 10]++;
		}
		for (int j = 1; j < 10; j++) {
			count[j] += count[j - 1];
		}
		for (int j = arr.size() - 1; j >= 0; j--) {
			// 将桶里的元素取出来 
			int index = count[(arr[j] / radix) % 10] - 1;
			tem[index] = arr[j];
			count[(arr[j] / radix) % 10]--;
		}
		for (int j = 0; j < arr.size(); j++) {
			arr[j] = tem[j];
		}
 
		radix *= 10;
	}
 
}

// 测试函数
// int main() {
 
// 	vector<int> arr = {61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 62};
 
// 	RadixSort(arr);
 
// 	for (int nums : arr) {
// 		cout << nums << " ";
// 	}
 
// 	return 0;
// }