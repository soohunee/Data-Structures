#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK 100

typedef enum { false, true } bool;
typedef struct {
	char small;
	char large;
	// *Variable "operator"
	// used in ConvInfixToPostfixfunction
	char operator;
}Penta_num; 
typedef struct {
	Penta_num items[MAX_STACK];
	int top;
}Stack;
Penta_num add(Penta_num b1, Penta_num b2);
Penta_num subtract(Penta_num b1, Penta_num b2);
Penta_num multiply(Penta_num b1, Penta_num b2);
Penta_num division(Penta_num b1, Penta_num b2);

void InitStack(Stack* pstack);
bool IsFull(Stack* pstack);
bool IsEmpty(Stack* pstack);
Penta_num Peek(Stack* pstack);
void Push(Stack* pstack, Penta_num item);
void Pop(Stack* pstack);
void ConvInfixToPostfix(char* exp, char* convExp, int len);
Penta_num EvalPostfix(char* exp, int len);
void print_Penta_num(Penta_num result);
int main() {
	char infix_exp[100];
	char postfix_exp[100];
	Penta_num result;
	scanf("%s", infix_exp);
	ConvInfixToPostfix(infix_exp, postfix_exp, strlen(infix_exp));
	printf("%s\n%s\n", infix_exp, postfix_exp);
	result = EvalPostfix(postfix_exp, strlen(postfix_exp));
	print_Penta_num(result);
	return 0;
}
int ConPentaDec(Penta_num p1)
{
	int result = 0;
	if (p1.small >= 'A')
		result += p1.small - 'A' + 10;
	else
		result += p1.small - '0';

	if (p1.large >= 'A')
		result += (p1.large - 'A' + 10) * 15;
	else
		result += (p1.large - '0') * 15;

	return result;
}
Penta_num ConDecPenta(int p1)
{
	Penta_num result;
	result.small = 0;
	result.large = 0;
	result.operator = 0;
	if (p1 % 15 <= 9)
		result.small += (p1 % 15) + '0';
	else
		result.small += (p1 % 15) + 'A' - 10;
	if (p1 / 15 <= 9)
		result.large += (p1 / 15) + '0';
	else
		result.large += (p1 / 15) + 'A' - 10;

	return result;
}
Penta_num add(Penta_num b1, Penta_num b2)
{
	int a1, a2;
	a1 = ConPentaDec(b1);
	a2 = ConPentaDec(b2);
	return ConDecPenta(a1 + a2);
}
Penta_num subtract(Penta_num b1, Penta_num b2)
{
	int a1, a2;
	a1 = ConPentaDec(b1);
	a2 = ConPentaDec(b2);
	return ConDecPenta(a1 - a2);
}
Penta_num multiply(Penta_num b1, Penta_num b2)
{
	int a1, a2;
	a1 = ConPentaDec(b1);
	a2 = ConPentaDec(b2);
	return ConDecPenta(a1 * a2);
}
Penta_num division(Penta_num b1, Penta_num b2)
{
	int a1, a2;
	a1 = ConPentaDec(b1);
	a2 = ConPentaDec(b2);
	return ConDecPenta(a1/a2);
}
void InitStack(Stack* pstack)
{
	pstack->top = -1;
}
bool IsFull(Stack* pstack)
{
	return pstack->top == MAX_STACK - 1;
}
bool IsEmpty(Stack* pstack)
{
	return pstack->top == -1;
}
Penta_num Peek(Stack* pstack)
{
	if (IsEmpty(pstack))
		exit(1);

	return pstack->items[pstack->top];
}
void Push(Stack* pstack, Penta_num item)
{
	if (IsFull(pstack))
		return;
	else
		pstack->items[(pstack->top) + 1] = item;
	(pstack->top)++;
}
void Pop(Stack* pstack)
{
	if (IsEmpty(pstack))
		return;

	else
		pstack->top -= 1;
}

int Priority(char a)
{
	if (a == '*' || a == '/')
		return 2;
	else if (a == '+' || a == '-')
		return 1;
	else
		return 0;
}
bool ComparePri(char a, char b)
{
	int Pri_a, Pri_b;
	Pri_a = Priority(a);
	Pri_b = Priority(b);
	
	return Pri_a >= Pri_b;

}
bool Operand(char a)
{
	return (a == '*' || a == '/' || a == '+' || a == '-');
}
	

void ConvInfixToPostfix(char* exp, char* convExp, int len)
{
	Stack _stack;
	InitStack(&_stack);
	int idx = 0;
	Penta_num oprd;
	for (int i = 0; i < len; i++)
	{
		if (!Operand(exp[i]))
			convExp[idx++] = exp[i];

		if (Operand(exp[i]))
		{
			while (!IsEmpty(&_stack) && ComparePri(Peek(&_stack).operator, exp[i])) {
				convExp[idx++] = Peek(&_stack).operator;
				Pop(&_stack);
			}
			oprd.operator = exp[i];
			Push(&_stack, oprd);
		}
	}

	while (!IsEmpty(&_stack)) {
		convExp[idx++] = Peek(&_stack).operator;
		Pop(&_stack);
	}

	convExp[idx] = '\0';

}
Penta_num EvalPostfix(char* exp, int len)
{
	Stack _stack;
	Penta_num oprd1, oprd2;
	Penta_num oprd;
	InitStack(&_stack);
	for (int i = 0; i < len; i++) {
		if (!Operand(exp[i])) 
		{
			oprd.large = exp[i];
			oprd.small = exp[++i];
			Push(&_stack, oprd);
		}
		if (Operand(exp[i]))
		{
			oprd2 = Peek (&_stack);
			Pop(&_stack);
			oprd1 = Peek(&_stack);
			Pop(&_stack);

			if (exp[i] == '+')
				Push(&_stack, add(oprd1, oprd2));

			else if (exp[i] == '-')
				Push(&_stack, subtract(oprd1, oprd2));

			else if (exp[i] == '*')
				Push(&_stack, multiply(oprd1, oprd2));

			else if (exp[i] == '/')
				Push(&_stack, division(oprd1, oprd2));

		}

	}
	return Peek(&_stack);
}
void print_Penta_num(Penta_num result)
{
	printf ("%c%c",result.large, result.small);
}

