#pragma once

typedef int ElemType;
#define MaxSize 50

#include "malloc.h"

typedef struct {
    ElemType data[MaxSize]; // 存放队中元素
    int front, rear;        // 队头和队尾的指针
}SqQueue;

// 初始化
void InitQueue(SqQueue *&q) {
    q = (SqQueue *) malloc (sizeof(SqQueue));
    q->front = q->rear = -1;
} 

// 销毁
void DestroyQueue(SqQueue *&q) {
    free(q);
}

// 判空
bool QueueEmpty(SqQueue *q) {
    return (q->front == q->rear);
}

// 进队列
bool enQueue(SqQueue *&q, ElemType e) {
    if (q->rear == MaxSize - 1) 
        return false;
    q->rear++;
    q->data[q->rear] = e;
    return true;
}

// 出队列
bool deQueue(SqQueue *&q, ElemType &e) {
    if (q->front == q->rear) {
        return false;
    }
    q->front++;
    e = q->data[q->front];
    return true;
}

/*环形队列*/

// 初始化队列
void InitQueue01(SqQueue *&q) {
    q = (SqQueue *) malloc (sizeof(SqQueue));
    q->front = q->rear = 0;
}

// 销毁队列
void DestroyQueue01(SqQueue *&q) {
    free(q);
}

// 判空
bool QueueEmpty01(SqQueue *q) {
    return (q->front == q->rear);
}

// 进队列
bool enQueue01(SqQueue *&q, ElemType e) {
    if ((q->rear + 1) % MaxSize == q->front)
        return false;
    q->rear = (q->rear + 1) % MaxSize;
    q->data[q->rear] = e;
    return true;
}

// 出队列
bool deQueue01(SqQueue *&q, ElemType &e) {
    if (q->front == q->rear) 
        return false;
    q->front = (q->front + 1) % MaxSize;
    e = q->data[q->front];
    return true;
}

// 求队列中元素的个数
int Count(SqQueue *q) {
    return(q->rear - q->rear + MaxSize) % MaxSize;
}


/*链式存储*/


typedef struct qnode {
    ElemType data;
    struct qnode * next;
}DataNode;

typedef struct {
    DataNode * front;
    DataNode * rear;
}LinkQuNode;

// 初始化
void InitQueue(LinkQuNode *&q) {
    q = (LinkQuNode *) malloc (sizeof(LinkQuNode));
    q->front = q->rear = NULL;
}

// 销毁队列
void DestroyQueue(LinkQuNode *&q) {
    DataNode *pre = q->front, *p;
    if (pre != NULL) {
        p = pre->next;
        while (p != NULL) {
            free(pre);
            pre = p;
            p = p->next;
        }
        free(pre);
    }
    free(q);
}

// 判空
bool QueueEmpty(LinkQuNode *q) {
    return (q->rear == NULL);
}

// 进队列
bool enQueue(LinkQuNode *&q, ElemType e) {
    DataNode *p;
    p = (DataNode *) malloc (sizeof(DataNode));
    p->data = e;
    p->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = p;
    } else {
        q->rear->next = p;
        q->rear = p;
    }
    return true;
}

// 出队列
bool deQueue(LinkQuNode *&q, ElemType &e) {
    DataNode *t;
    if (q->rear == NULL) {
        return false;
    }
    t = q->front;
    if (q->front == q->rear) {
        q->front = q->rear = NULL;
    } else {
        q->front = q->front->next;
    }
    e = t->data;
    free(t);
    return true;
}