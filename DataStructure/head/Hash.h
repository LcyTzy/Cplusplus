#pragma once

#include "malloc.h"
#include "iostream"

using namespace std;

#define NULLKEY -1
typedef int KeyType;
typedef struct {
    KeyType key;
    int count;
} HashTable;

void InsertHT(HashTable ha[], int &n, int m, int p, KeyType k) {
    int i, adr;
    adr = k % p;
    if (ha[adr].key == NULLKEY) {
        ha[adr].key = k;
        ha[adr].count = 1;
    } else {
        int cnt = 1;
        do {
            adr = (adr + 1) % m;
            ++cnt;
        } while (ha[adr].key != NULLKEY);
        ha[adr].key = k;
        ha[adr].count = cnt;
    }
    ++n;
}

void CreateHT(HashTable ha[], int &n, int m, int p, KeyType keys[], int total) {
    for (int i = 0; i < m; ++i) {
        ha[i].key = NULLKEY;
        ha[i].count = 0;
    }
    n = 0;
    for (int i = 0; i < total; ++i) {
        InsertHT(ha, n, m, p, keys[i]);
    }
}

bool DeleteHT(HashTable ha[], int &n, int m, int p, KeyType k) {
    int adr;
    adr = k % p;
    while (ha[adr].key != NULLKEY && ha[adr].key != k)
        adr = (adr + 1) % m;
    if (ha[adr].key == k) {
        int j = (adr + 1) % m;
        while (ha[j].key != NULLKEY && ha[j].key % p == k % p) {
            ha[(j - 1 + m) % m].key = ha[j].key;
            j = (j + 1) % m;
        }
        ha[(j - 1 + m) % m].key = NULLKEY;
        ha[(j - 1 + m) % m].count = 0;
        --n;
        return true;
    } else return false;
}


void SearchHT(HashTable ha[], int m, int p, KeyType k) {
    int cnt = 1, adr;
    adr = k % p;
    while (ha[adr].key != NULLKEY && ha[adr].key != k) {
        cnt++;
        adr = (adr + 1) % m;
    }
    if (ha[adr].key == k) 
        cout << "成功：关键字 " << k << " ，比较 " << cnt << " 次。" << endl;
    else 
        cout << "失败：关键字 " << k << " ，比较 " << cnt << " 次。" << endl;
}

void ASL(HashTable ha[], int n, int m, int p) {
    int i, j;
    int succ = 0, unsucc = 0, s;
    for (i = 0; i < m; ++i) {
        if (ha[i].key != NULLKEY) {
            succ += ha[i].count;
        }
    }
    cout << "成功情况下 ASL(" << n << ") = " << succ * 1.0 / n << endl;
    for (i = 0; i < p; ++i) {
        s = 1;
        j = i;
        while (ha[j].key != NULLKEY) {
            ++s;
            j = (j + 1) % m;
        } 
        unsucc += s;
    }
    cout << "不成功情况下 ASL(" << n << ") = " << succ * 1.0 / n << endl;
}