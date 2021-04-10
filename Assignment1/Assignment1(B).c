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
        s1[i] = 0; //�ߺ��� ���ĺ� �� �迭 s1 ���� �� 0���� �ʱ�ȭ
    scanf("%s", s1); // ���ڿ� �Է¹ޱ�

    int len = 0;
    for (int i = 0; s1[i] != 0; i++)
        len++; //���ڿ� ���� �˾Ƴ���

    for (int i = 0; s1[i] != 0; i++)
    {
        for (int j = i+1; s1[j] != 0; j++)
        {
            if (s1[i] == s1[j] & s1[i]!=1)
            {
                Push(&_stack, s1[i]);
                EnQueue(&_queue, s1[i]);
                s1[i] = s1[j] = 1;
            }
        }
    } //���ڿ� �ȿ� ���� ���ĺ� �ΰ��� ������ stack�� �ϳ��� �ֱ� (���� �ڸ��� 1)

    char s2[MAX];
    for (int i = 0; i < MAX; i++)
        s2[i] = 0; // �ߺ����� �ʴ� ���ĺ� �� �迭 s2 ���� �� 0���� �ʱ�ȭ

    for (int i = 0; s1[i] != 0; i++)
    {
        if (s1[i] != 1)
        {
            s2[0] = s1[i];
            break;
        }
    } //�ߺ����� ���� ���ĺ� �ϳ� s2[0]�� �Է� ���ٸ� break

    if (s2[0] == 0) //������� ¦������ ���ĺ����� �̷���� ���
    {
        while (!IsEmpty_s(&_stack))
        {
            printf("%c", Peek_s(&_stack));
            Pop(&_stack);
        }
        while (!IsEmpty_q(&_queue))
        {
            printf("%c", Peek_q(&_queue));
            DeQueue(&_queue);
        }
    }
    if (s2[0]!=0) // ������� Ȧ������ ���ĺ����� �̷���� ���
    {
        while (!IsEmpty_s(&_stack))
        {
            printf("%c", Peek_s(&_stack));
            Pop(&_stack);
        }

        printf("%c", s2[0]);

        while (!IsEmpty_q(&_queue))
        {
            printf("%c", Peek_q(&_queue));
            DeQueue(&_queue);
        }
    }

}