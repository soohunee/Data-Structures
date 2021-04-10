#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100


typedef char Data;
typedef struct
{
    Data items[MAX];
    int top;
} stack;

void InitStack(stack* pstack)
{
    for (int i = 0; i < MAX; i++)
        pstack->items[i] = 0;

    pstack->top = -1;
}

bool IsFull_s(stack* pstack)
{
    return pstack->top == MAX - 1;
}

bool IsEmpty_s(stack* pstack)
{
    return pstack->top == -1;
}

void Push(stack* pstack, Data item)
{
    if (IsFull_s(pstack))
        return;
    else
        pstack->items[(pstack->top) + 1] = item;
    (pstack->top)++;
}

void Pop(stack* pstack)
{
    if (IsEmpty_s(pstack))
        return;

    else
        pstack->top -= 1;
}

Data Peek_s(stack* pstack)
{
    if (IsEmpty_s(pstack))
        return 0;

    return pstack->items[pstack->top];
}

typedef struct
{
    int front, rear;
    Data items[MAX];
} queue;

void InitQueue(queue* pqueue)
{
    for (int i = 0; i < MAX; i++)
        pqueue->items[i] = 0;

    pqueue->front = pqueue->rear = 0;
}

bool IsFull_q(queue* pqueue)
{
    return pqueue->front == (pqueue->rear + 1) % MAX;
}

bool IsEmpty_q(queue* pqueue)
{
    return pqueue->front == pqueue->rear;
}

void EnQueue(queue* pqueue, Data item)
{
    if (IsFull_q(pqueue))
        return;
    else
    {
        pqueue->items[pqueue->rear] = item;
        pqueue->rear = (pqueue->rear + 1) % MAX;
    }


}

void DeQueue(queue* pqueue)
{
    if (IsEmpty_q(pqueue))
        return;
    else
    {
        pqueue->front = (pqueue->front + 1) % MAX;
    }
}

Data Peek_q(queue* pqueue)
{
    if (IsEmpty_q(pqueue))
        return 0;

    return pqueue->items[pqueue->front];
}

int main()
{
    stack _stack;
    queue _queue;

    InitStack(&_stack);
    InitQueue(&_queue);

    char s1[MAX];
    for (int i = 0; i < MAX; i++)
        s1[i] = 0;

    int len = 0;

    scanf("%s", s1);
    for (int i = 0; s1[i] != 0; i++)
        len++;


    for (int i = 0; i < len; i++)
    {
        Push(&_stack, s1[i]);
        EnQueue(&_queue, s1[i]);
    }

    int out = 0;

    while (!IsEmpty_s(&_stack))
    {
        if (Peek_s(&_stack) == Peek_q(&_queue))
        {
            Pop(&_stack);
            DeQueue(&_queue);
        }
        else if (Peek_s(&_stack) != Peek_q(&_queue))
        {
            out++;
            Pop(&_stack);
            DeQueue(&_queue);
        }
    }

    printf("%d", out);
}