#include <stdio.h>

#define MAX 300

int stack[MAX];
int top;

void init_stack(void) {
    top = -1;
}

int push(int t) {
    if (top >= MAX - 1) {
        //printf("\n스택 범위 벗어남");
        return -1;
    }

    stack[++top] = t;
    return t;
}

int pop(void) {
    if (top < 0) {
        //printf("\n빈 스택!!");
        return -1;
    }
    return stack[top--];
}

int get_stack_top(void) {
    if (top < 0)
        return -1;
    else
        return stack[top];
}

int is_stack_empty(void) {
    if (top < 0)
        return 1;
    else
        return 0;
}

int is_operator(int k) {
    if (k == '+' || k == '-' || k == '*' || k == '/')
        return 1;
    else
        return 0;
}

int is_legal(char* s) {
    int f = 0;
    while (*s) {
        while (*s == ' ') {
            s++;
        }

        if (is_operator(*s)) {
            f--;
        }
        else {
            f++;
            while (*s != ' ') {
                s++;
            }
        }
        if (f < 1) break;
        s++;
    }
    return (f == 1);
}

int precedence(int op) {
    if (op == '(')
        return 0;
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    else
        return 3;
}

void postfix(char* dst, char* src) {
    char c;
    init_stack();
    while (*src) {
        if (*src == '(') {
            push(*src);
            src++;
        }
        else if (*src == ')') {
            while (get_stack_top() != '(') {
                *dst++ = pop();
                *dst++ = ' ';
            }
            pop();
            src++;
        }
        else if (is_operator(*src)) {
            while (!is_stack_empty() &&
                precedence(get_stack_top()) >= precedence(*src)) {
                *dst++ = pop();
                *dst++ = ' ';
            }
            push(*src);
            src++;
        }
        else if ((*src >= '0' && *src <= '9') || *src == 'x') {
            ;
            do {
                *dst++ = *src++;
            } while ((*src >= '0' && *src <= '9') || *src == 'x');
            *dst++ = ' ';
        }
        else {
            src++;
        }
    }

    while (!is_stack_empty()) {
        *dst++ = pop();
        *dst++ = ' ';
    }
    dst--;
    *dst = 0;
}

int calc(char* p, int x) {
    int i;
    init_stack();
    while (*p) {
        if (*p >= '0' && *p <= '9') {
            i = 0;
            do {
                i = i * 10 + *p - '0';
                p++;
            } while (*p >= '0' && *p <= '9');
            push(i);
        }
        else if (*p == 'x') {
            push(x);
            p++;
        }
        else if (*p == '+') {
            push(pop() + pop());
            p++;
        }
        else if (*p == '*') {
            push(pop() * pop());
            p++;
        }
        else if (*p == '-') {
            i = pop();
            push(pop() - i);
            p++;
        }
        else if (*p == '/') {
            i = pop();
            push(pop() / i);
            p++;
        }
        else {
            p++;
        }
    }
    return pop();
}

int main() {

    int r;
    char exp[300];
    char pf[300];
    char* context;
    int M, P, i;

    scanf_s("%s", exp, sizeof(char) * 300);
    scanf_s("%d %d", &P, &M);

    postfix(pf, exp);

    for (i = 0; i < 1000; i++) {
        r = calc(pf, i);
        if (r % M == P)
            break;
    }
    printf("%d\n", i);

    return 0;
}