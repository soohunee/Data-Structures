#include <stdio.h> 
#include <stdlib.h>

typedef struct _Node
{
	int data;
	struct _Node* next;
}Node;

void printList(Node* head)
{
	Node* ptr = head;
	while (ptr)
	{
		printf("%d ", ptr->data);
		printf("-> ");
		ptr = ptr->next;
	}
	printf("NULL");
	printf("\n");
}

void push(Node** head, int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = *head;
	*head = newNode;
}

void Remove(Node* head)
{
	Node* cur, *cur2, *temp;
	temp = head;
	cur = head;
	cur2 = cur->next;

	for (cur = head; cur != NULL; cur = cur->next)
	{
		for (cur2 = cur->next; cur2 != NULL; cur2 = cur2->next)
		{
			if (cur->data == cur2->data)
			{
				while (temp->next != cur2)
					temp = temp->next;

				cur2 = temp;
				cur2->next = cur2->next->next;
				temp = head;
			}

		}
	}
	/*while (cur != NULL)
	{
		while (cur2 != NULL)
		{
			if (cur->data == cur2->data)
			{
				while (temp -> next != cur2)
				{
					temp = temp->next;
				}
				
				cur2 = temp;
				cur2->next = cur2->next->next;
				temp = head;
			}
			cur2 = cur2->next;
		}

		cur = cur->next;
		cur2 = cur->next;
	}*/

}

int main()
{
	int N, list[100];
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);

	Node* head = NULL;

	for (int i = N - 1; i >= 0; i--)
		push(&head, list[i]);
	
	printList(head);
	Remove(head);
	printList(head);

	return 0;
}