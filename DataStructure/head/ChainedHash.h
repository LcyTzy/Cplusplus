#pragma once
#include "malloc.h"
#include "iostream"

using namespace std;

typedef int KeyType;

typedef struct node {
    KeyType key;
    struct node *next;
} NodeType;

typedef struct {
    NodeType *firstp;
} HashTable;


// 插入及建表
void InsertHT(HashTable ha[], int &n, int m, KeyType k) {
    int adr;
    adr = k % m;
    NodeType *q;
    q = (NodeType *) malloc (sizeof(NodeType));
    q->key = k;
    q->next = NULL;
    if (ha[adr].firstp == NULL) {
        ha[adr].firstp = q;
    } else {
        q->next = ha[adr].firstp;
        ha[adr].firstp = q;
    }
    ++n;
}

void CreateHT(HashTable ha[], int &n, int m, KeyType keys[], int total) {
    for (int i = 0; i < m; ++i) {
        ha[i].firstp = NULL;
    }
    n = 0;
    for (int i = 0; i < total; ++i) {
        InsertHT(ha, n, m, keys[i]);
    }
}

// 删除
bool DelectHT(HashTable ha[], int &n, int m, KeyType k) {
    int adr;
    adr = k % m;
    NodeType *q, *preq;
    q = ha[adr].firstp;
    if (q == NULL) {
        return false;
    }
    if (q->key == k) {
        ha[adr].firstp = q->next;
        free(q);
        n--;
        return true;
    }
    preq = q;
    q = q->next;
    while (q != NULL && q->key != k) {
        preq = q;
        q = q->next;
    }
    if (q != NULL) {
        preq->next = q->next;
        free(q);
        --n;
        return true;
    }
    else return false;
}

// 查找
void SearchHT(HashTable ha[], int m, KeyType k) {
    int cnt = 0, adr;
    adr = k % m;
    NodeType *q;
    q = ha[adr].firstp;
    while (q != NULL) {
        cnt++;
        if (q->key == k)
            break;
        q = q->next;
    }
    if (q != NULL) 
        cout << "成功：关键字 " << k << " ，比较 " << cnt << " 次。" << endl;
    else 
        cout << "失败：关键字 " << k << " ，比较 " << cnt << " 次。" << endl;
}

// 性能分析
void ASL(HashTable ha[], int n, int m) {
    int succ = 0, unsucc = 0, s;
    NodeType *q;
    for (int i = 0; i < m; ++i) {
        s = 0;
        q = ha[i].firstp;
        while (q != NULL) {
            q = q->next;
            ++s;
            succ += s;
        }
        unsucc += s;
    }
    cout << "成功情况下 ASL(" << n << ") = " << succ * 1.0 / n << endl;
    cout << "不成功情况下 ASL(" << n << ") = " << succ * 1.0 / n << endl;
}