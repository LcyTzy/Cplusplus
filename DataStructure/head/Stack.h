#pragma once

#include "malloc.h"

#define MaxSize 50
typedef int ElemType;

typedef struct {
    ElemType data[MaxSize]; // 存放栈中的数据元素
    int top;                // 栈顶元素，即存放栈顶元素在data数组中的下标
} SqStack;

// 初始化栈
void InitStack(SqStack *&s) {
    s = (SqStack *) malloc (sizeof(SqStack));
    s->top = -1;
}

// 销毁栈
void DestroyStack(SqStack *&s) {
    free(s);
}

// 判断栈是否为空
bool StackEmpty(SqStack *s) {
    return (s->top == -1);
}

// 进栈
bool Push(SqStack *&s, ElemType e) {
    if (s->top == MaxSize - 1) {    // 栈满的情况，即栈上溢出
        return false;
    }
    s->top++;
    s->data[s->top] = e;
    return true;
}

// 出栈
bool Pop(SqStack *&s, ElemType &e) {
    if (s->top == -1)
        return false;
    e = s->data[s->top];
    s->top--;
    return true;
}

// 取栈顶元素
bool GetTop(SqStack *s, ElemType &e) {
    if (s->top == -1) {
        return false;
    }
    e = s->data[s->top];
    return true;
}


/*链栈*/
typedef struct linknode {
    ElemType data;
    struct linknode * next;
}LinkStNode;

// 初始化栈
void InitStack(LinkStNode *&s) {
    s = (LinkStNode *) malloc (sizeof(LinkStNode));
    s->next = NULL;
}

// 销毁栈
void DestroyStack(LinkStNode *&s) {
    LinkStNode *pre = s, *p = s->next;
    while (p != NULL) {
        free(pre);
        pre = p;
        p = pre->next;
    }
    free(pre);
}

// 判空
bool StackEmpty(LinkStNode *s) {
    return (s->next == NULL);
}

// 进栈
bool Push(LinkStNode *&s, ElemType e) {
    LinkStNode *p;
    p = (LinkStNode *) malloc (sizeof(LinkStNode));
    p->data = e;
    p->next = s->next;
    s->next = p;
    return true;
}

// 出栈
bool Pop(LinkStNode *&s, ElemType &e) {
    LinkStNode *p;
    if (s->next == NULL) {
        return false;
    }
    p = s->next;
    e = p->data;
    s->next = p->next;
    free(p);
    return true;
}

// 取栈顶元素
bool GetTop(LinkStNode *s, ElemType &e) {
    if (s->next == NULL)
        return false;
    e = s->next->data;
    return false;
}