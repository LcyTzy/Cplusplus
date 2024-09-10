#pragma once

#include "malloc.h"
#include "iostream"

using namespace std;

typedef int KeyType;
typedef int InfoType;
typedef struct node {
    KeyType key;
    InfoType data;
    struct node *lchild, *rchild;
}BSTNode;

BSTNode* InsertBST(BSTNode *bt, KeyType k) {
    if (bt == NULL) {
        bt = (BSTNode *)malloc(sizeof(BSTNode));
        bt->key = k;
        bt->lchild = bt->rchild = NULL;
    } else if (k < bt->key) {
        bt->lchild = InsertBST(bt, k);
    } else if (k > bt->key) {
        bt->rchild = InsertBST(bt, k);
    }
    return bt;
}

BSTNode* CreateBST(KeyType a[], int n) {
    BSTNode *bt = NULL;
    int i = 0;
    while (i < n) {
        bt = InsertBST(bt, a[i]);
        ++i;
    }
    return bt;
}

BSTNode* SearchBST(BSTNode *bt, KeyType k) {
    if (bt == NULL || bt->key == k)     return bt;
    if (k < bt->key)    return SearchBST(bt->lchild, k);
    else    return SearchBST(bt->rchild, k);
}

BSTNode* SearchBST1(BSTNode *bt, KeyType k) {
    BSTNode *p = bt;
    while (p != NULL) {
        if (p->key == k)    break;
        else if (k < p->key)    p = p->lchild;
        else    p = p->rchild;
    }
    return p;
}

KeyType maxnode(BSTNode *p) {
    while (p->rchild != NULL) {
        p = p->rchild;
    }
    return p->data;
}

KeyType minnode(BSTNode *p) {
    while (p->lchild != NULL) {
        p = p->lchild;
    }
    return p->data;
}



void maxminnode(BSTNode *p) {
    if (p != NULL) {
        if (p->lchild != NULL) 
            cout << "左子树的最大结点为 " << maxnode(p->lchild) << endl;
        if (p->rchild != NULL) 
            cout << "左子树的最大结点为 " << maxnode(p->lchild) << endl;
    }
}


BSTNode* DeleteBST(BSTNode *bt, KeyType k) {
    if (bt == NULL) return bt;
    BSTNode *p = bt;
    BSTNode *f = NULL;
    while (p != NULL) {
        if (p->key == k)    break;
        f = p;
        if (k < p->key)     p = p->lchild;
        else                p = p->rchild;
    }
    if (p == NULL)  return bt;
    if (p->lchild == NULL && p->rchild == NULL) {
        if (p == bt)    bt = NULL;
        else {
            if (f->lchild == p) f->lchild = NULL;
            else f->rchild = NULL;
        }
        free(p);
    } else if (p->rchild == NULL) {
        if (f == NULL) bt = bt->lchild;
        else {
            if (f->lchild == p) f->lchild = p->lchild;
            else f->rchild = p->lchild;
        }
        free(p);
    } else if (p->lchild == NULL) {
        if (f == NULL) bt = bt->rchild;
        else {
            if (f->lchild == p) f->lchild = p->rchild;
            else f->rchild = p->rchild;
        }
        free(p);
    } else {
        BSTNode *q = p->lchild;
        f = p;
        while (q->rchild != NULL) {
            f = q;
            q = q->rchild;
        }
        p->key = q->key;
        if (q == f->lchild) f->lchild = q->lchild;
        else f->rchild = q->lchild;
        free(q);
    }
    return bt;
}