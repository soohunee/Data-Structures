#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
typedef struct _Node
{
	int coef;
	int exp;
	struct _Node* next;
} Node;

typedef struct _Polynomial
{
	Node* head;
	int len;
} Poly;

void InitPoly(Poly* poly)
{
	poly->head = (Node*)malloc(sizeof(Node));
	poly->head ->next = NULL;
	poly->len = 0;
}

void Insert(int coef, int exp, Poly* poly)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->coef = coef;
	newnode->exp = exp;
	
	//if poly was empty
	if (poly->head->next == NULL)
	{
		newnode->next = NULL;
		poly->head->next = newnode;
		poly->len++;
	}
	//it poly was not empty
	else
	{
		newnode->next = poly->head->next;
		poly->head->next = newnode;
		poly->len++;
	}
}

void PrintPoly(Poly* poly) {
	
	Node* cur = poly->head->next;
	printf("%dx^%d", cur->coef, cur->exp);
	for (cur = cur->next; cur != NULL; cur = cur->next)
	{
		if (cur->coef > 0)
		{
			printf("+%dx^%d", cur->coef, cur->exp);

		}
		else if (cur->coef == 0)
		{
			return;
		}
		else
		{
			printf("%dx^%d", cur->coef, cur->exp);
		}
		
	}
}

int CharToInt(int start, int end, char* s1)
{
	int result = 0;
	while (start != end)
	{
		result *= 10;
		result += s1[start] - '0';
		start++;
	}
	return result;
}

void CharToPoly(char* s1, Poly* poly, int* A[])
{
	int start = 0, end = 0;
	for (; s1[end] != NULL; end++)
	{
		if (s1[end] == 'x')
		{
			if (s1[start] == '+')
			{
				int coef = CharToInt(start+1,end,s1);
				A[0] = (0 + coef);
			}
			else if (s1[start] == '-')
			{
				int coef = CharToInt(start + 1, end, s1);
				A[0] = (0 - coef);
			}
			else
			{
				int coef = CharToInt(start, end, s1);
				A[0] = coef;
			}
		}
		else if (s1[end] == '^')
		{
			start = end + 1;
		}
		else if (s1[end] == '+' || s1[end] == '-')
		{
			int exp = CharToInt(start, end, s1);
			start = end;
			A[1] = exp;
			Insert(A[0], A[1], poly);
		}
		else if (s1[end + 1] == NULL)
		{
			int exp = CharToInt(start, end + 1, s1);
			A[1] = exp;
			Insert(A[0], A[1], poly);
		}
	}

}
int Compare(int a, int b)
{
	if (a > b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}
void Add(Poly* poly1, Poly* poly2, Poly* result)
{
	Node* cur2 = (Node*)malloc(sizeof(Node));
	cur2 = poly2->head->next;
	Node* cur1 = (Node*)malloc(sizeof(Node));
	cur1 = poly1->head->next;
	while(cur1&& cur2)
	{
		switch (Compare(cur1->exp, cur2->exp))
		{
		case -1: //a>b
			Insert(cur2->coef, cur2->exp, result);
			cur2 = cur2->next;
			break;
		case 0: // a=b
			Insert(cur1->coef + cur2->coef, cur1->exp, result);
			cur1 = cur1->next;
			cur2 = cur2->next;
			break;
		case 1: // a<b 
			Insert(cur1->coef, cur1->exp, result);
			cur1 = cur1->next;
			break;
		}
	}
	while (cur1 != NULL)
	{
		Insert(cur1->coef, cur1->exp, result);
		cur1 = cur1->next;
	}
	while (cur2 != NULL)
	{
		Insert(cur2->coef, cur2->exp, result);
		cur2 = cur2->next;
	}
}


int main()
{
	Poly first,  second, result;
	InitPoly(&first);
	InitPoly(&second);
	InitPoly(&result);
	int* A[2] = { 0 }, * B[2] = { 0 };
	char s1[50] = { 0 };
	char s2[50] = { 0 };
	scanf("%s %s", s1, s2);


	CharToPoly(s1, &first, A);
	CharToPoly(s2, &second, B);

	Add(&first, &second, &result);

	PrintPoly(&result);

	return;
}