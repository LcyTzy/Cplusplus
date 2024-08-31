/*顺序表*/
#pragma once

#include <stdlib.h>
#include "iostream"

using namespace std;
#define MaxSize 50

typedef int ElemType;

typedef struct {
    ElemType data[MaxSize];     // 存放线性表中的元素
    int length;                 // 存放线性表的长度
} SqList;                       // 顺序表类型

/*建立顺序表*/
void CreateList(SqList *&L, ElemType a[], int n) {
    int i = 0, k = 0;
    L = (SqList *)malloc(sizeof(SqList));
    while (i < n) {
        L->data[k] = a[i];
        k++;
        i++;
    }
    L->length = k;
}

/*初始化线性表*/
void InitList(SqList *&L) {
    L = (SqList *)malloc(sizeof(SqList));
    L->length = 0;
}

/*销毁线性表*/
void DestroyList(SqList *&L) {
    free(L);
}

/*判空*/
bool ListEmpty(SqList *L) {
    return(L->length == 0);
}

/*长度*/
int ListLength(SqList *L) {
    return (L->length);
}

/*输出线性表*/
void DispList(SqList *L) {
    for (int i = 0; i < L->length; ++i) {
        cout << L->data[i] << " ";
    }
    cout << endl;
}

/*按序号求线性表中的元素*/
bool GetElem(SqList *L, int i, ElemType &e) {
    if (i < 1 || i > L->length) {
        return false;
    }
    e = L->data[i - 1];
    return true;
}

/*按元素值查找*/
int LocateElem(SqList *L, ElemType e) {
    int i = 0;
    while (i < L->length && L->data[i] != e) {
        i++;
    }
    if (i >= L->length)
        return 0;
    else
        return i + 1;
}

/*插入数据元素*/
bool ListInsert(SqList *&L, int i, ElemType e) {
    int j;
    if (i < 1 || i > L->length + 1 || L->length == MaxSize) {
        return false;
    }
    i--;
    for (j = L->length; j > i; --j) {
        L->data[j] = L->data[j - 1];
    }
    L->data[i] = e;
    L->length++;
    return true;
}

/*删除数据元素*/
bool ListDelete(SqList *&L, int i, ElemType &e) {
    int j;
    if (i < 1 || i > L->length) {
        return false;
    }
    i--;
    e = L->data[i];
    for (int j = i; j < L->length - 1; ++j) {
        L->data[j] = L->data[j + 1];
    }
    L->length--;
    return true;
}

/*假设一个线性表采用顺序表表示，设计一个算法，删除其中所以值等于x的元素，要求算法的时间复杂度为O(n)，空间复杂度为O(1)。*/
void delnode1(SqList *&L, ElemType x) {
    int k = 0, i;
    for (i = 0; i < L->length; ++i) {
        if (L->data[i] != x) {
            L->data[k] = L->data[i];
            k++;
        }
    }
    L->length = k;
}

void delnode2(SqList *&L, ElemType x) {
    int k = 0, i = 0;
    while (i < L->length) {
        if (L->data[i] == x) {
            k++;
        } else {
            L->data[i - k] = L->data[i];
        }
        i++;
    }
    L->length -= k;
}

/*有一个顺序表L，假设元素类型ElemType为整形，设计一个尽可能高效的算法，以第一个元素为分界线（基准），将所有小于或等于它的元素移到该基准的前面，将所有大于它的元素移到该基准的后面*/
void partition1(SqList *&L) {
    int i = 0, j = L->length - 1;
    ElemType base = L->data[0];
    while (i < j) {
        while (i < j && L->data[j] > base) {
            j--;
        }
        while (i < j && L->data[i] <= base) {
            i++;
        }
        if (i < j) {
            swap(L->data[i], L->data[j]);
        }
    }
    swap(L->data[0], L->data[i]);
} 

void partition2(SqList *&L) {
    int i = 0, j = L->length - 1;
    ElemType base = L->data[0];
    while (i < j) {
        while (j > i && L->data[j] > base) {
            j--;
        }
        L->data[i] = L->data[j];
        while (i < j && L->data[i] <= base) {
            i++;
        }
        L->data[j] = L->data[i];
    }
    L->data[i] = base;
}

/*有一个顺序表L，假设元素类型ElemType为整形，设计一个尽可能高效的算法将所有奇数移到偶数的前面*/
void move1(SqList *&L) {
    int i = 0, j = L->length - 1;
    while (i < j) {
        while (i < j && L->data[j] % 2 == 0) {
            j--;
        }
        while (i < j && L->data[i] % 2 == 1) {
            i++;
        }
        if (i < j) {
            swap(L->data[i], L->data[j]);
        }
    }
}

void move2(SqList *&L) {
    int i = -1, j;
    for (j = 0; j < L->length - 1; ++j) {
        if (L->data[j] % 2 == 1) {
            i++;
            if (i != j) {
                swap(L->data[i], L->data[j]);
            }
        }
    }
}

/*
#include "iostream"
#include "head/SequentialList.h"

using namespace std;

int main() {
    SqList *L;
    int a[] = {1, 2, 3, 4, 5};
    CreateList(L, a, 5);
    DispList(L);
    ElemType e;
    GetElem(L, 2, e);
    cout << e << endl;
    ListInsert(L, 2, e);
    DispList(L);
    ListDelete(L, 2, e);
    DispList(L);
    L->data[0] = 3;
    L->data[2] = 1;
    DispList(L);
    partition1(L);
    DispList(L);
    move1(L);
    DispList(L);
}
*/