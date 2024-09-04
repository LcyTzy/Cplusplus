#include "iostream"
using namespace std;
#include "malloc.h"
 
/*单链表*/
typedef int ElemType;

typedef struct LNode {
    ElemType data;      // 存放元素值
    struct LNode *next; // 指向后继节点
} LinkNode;             // 单链表结点类型

/*头插法*/
void CreateListF(LinkNode *&L, ElemType a[], int n) {
    LinkNode *s;
    L = (LinkNode *)malloc(sizeof(LinkNode));
    L->next = NULL;     // 创建头节点，将其next域置为NULL
    for (int i = 0; i < n; ++i) {   // 循环建立数据结点s
        s = (LinkNode *)malloc(sizeof(LinkNode));
        s->data = a[i];     // 创建数据结点s
        s->next = L->next;  // 将结点s插入原首结点前、头结点后
        L->next = s;
    }
}

/*尾插法*/
void CreateListR(LinkNode *&L, ElemType a[], int n) {
    LinkNode *s, *r;
    L = (LinkNode *)malloc(sizeof(LinkNode));   // 创建头结点
    r = L;                                      // r始终指向尾结点，初始时指向头结点
    for (int i = 0; i < n; ++i) {
        s = (LinkNode *)malloc(sizeof(LinkNode));
        s->data = a[i];
        r->next = s;
        r = s;
    }
    r->next = NULL;
}

/*初始化线性表*/
void InitList(LinkNode *&L) {
    L = (LinkNode *)malloc(sizeof(LinkNode));
    L->next = NULL;
}

/*销毁线性表*/
void DestroyList(LinkNode *&L) {
    LinkNode *pre = L, *p = L->next;
    while (p != NULL) {
        free(pre);
        pre = p;
        p = pre->next;
    }
    free(pre);
}

/*判断线性表是否为空表*/
bool ListEmpty(LinkNode *L) {
    return (L->next == NULL);
}

/*求线性表的长度*/
int ListLength(LinkNode *L) {
    int n = 0;
    LinkNode *p = L;
    while (p->next != NULL) {
        n++;
        p = p->next;
    }
    return n;
}

/*输出线性表*/
void DispList(LinkNode *L) {
    LinkNode *p = L->next;
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;   
}

/*按序号求线性表中元素*/
bool GetElem(LinkNode *L, int i, ElemType &e) {
    int j = 0;
    LinkNode *p = L;
    if (i <= 0) return false;
    while (j < i && p != NULL) {
        j++;
        p = p->next;
    }
    if (p == NULL) {
        return false;
    } else {
        e = p->data;
        return true;
    }
}

/*按元素值查找*/
int LicateElem(LinkNode *L, ElemType e) {
    int i = 1;
    LinkNode *p = L->next;
    while (p != NULL && p->data != e) {
        p = p->next;
        i++;
    }
    if (p == NULL) {
        return 0;
    } else {
        return i;
    }
}

/*插入数据元素*/
bool ListInsert(LinkNode *&L, int i, ElemType e) {
    int j = 0;
    LinkNode *p = L, *s;
    if (i <= 0) return false;
    while (j < i - 1 && p != NULL) {
        j++;
        p = p->next;
    }
    if (p == NULL) {
        return false;
    } else {
        s = (LinkNode *)malloc(sizeof(LinkNode));
        s->data = e;
        s->next = p->next;
        p->next = s;
        return true;
    }
}

/*删除数据元素*/
bool ListDelete(LinkNode *&L, int i, ElemType &e) {
    int j = 0;
    LinkNode *p = L, *q;
    if (i <= 0) return false;
    while (j < i - 1 && p != NULL) {
        j++;
        p = p->next;
    }
    if (p == NULL) {
        return false;
    } else {
        q = p->next;
        if (q == NULL) {
            return false;
        }
        e = q->data;
        p->next = q->next;
        free(q);
        return true;
    }
}