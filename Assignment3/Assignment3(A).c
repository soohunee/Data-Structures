#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
typedef struct {
	int x;
	int y;
} Coord;
typedef struct _Node
{
	Coord pt;
	int distance;
	struct _Node* next;
}Node;
typedef struct {
	Node* front, * rear;
	int size;
} queue;
void InitQueue(queue* pqueue)
{
	pqueue->front = NULL;
	pqueue->rear = NULL;
	pqueue->size = 0;
}
bool IsEmpty(queue* pqueue)
{
	if (pqueue -> size != 0)
		return false;
	else
		return true;
}
void EnQueue(queue* pqueue, Coord c, int dist)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->pt = c;
	newNode->distance = dist;
	newNode->next = NULL;

	if (!IsEmpty(pqueue))
	{
		pqueue->rear-> next = newNode;
		pqueue->rear = newNode;
	}
	else
		pqueue->front = pqueue->rear = newNode;
	pqueue->size++;
}

int DeQueue(queue* pqueue)
{
	Node* temp = pqueue->front;
	pqueue->front = pqueue->front->next;
	int dist = temp->distance;
	free(temp);
	pqueue->size--;
	return dist;
}

bool IsValid(int row, int col, int x_end, int y_end)
{
	if (row >= 0 && row<x_end && col >= 0 && col<y_end)
		return true;
	else
		return false;
}

int BFS(int** mtx, Coord start, Coord dest, int x_end, int y_end)
{
	int RowNum[] = { -1,0,0,1 };
	int ColNum[] = { 0,-1,1,0 };

	if (mtx[start.x][start.y] == 1 || mtx[dest.x][dest.y] == 1)
		return -1;

	//visited 배열 만들기
	int** visited = (int**)malloc(sizeof(int*) * y_end);
	for (int i = 0; i < y_end; i++)
		visited[i] = (int*)malloc(sizeof(int) * x_end);

	//visited 배열 초기화
	for (int i = 0; i < y_end; i++)
	{
		for (int j = 0; j < x_end; j++)
			visited[j][i] = 0;
	}

	visited[0][0] = 1;

	queue* que = (queue*)malloc(sizeof(queue));

	InitQueue(que);
	EnQueue(que, start, 0);

	while (!IsEmpty(que))
	{
		Node* cur = que->front;
		Coord point = cur->pt;

		if (cur->pt.x == x_end-1 && cur->pt.y == y_end-1)
			return (cur->distance);

		int curdist = DeQueue(que);
		
		for (int i = 0; i < 4; i++)
		{
			int row = point.x + RowNum[i];
			int col = point.y + ColNum[i];
			
			if (IsValid(row, col, x_end, y_end) && mtx[row][col] == 0 && visited[row][col] == 0)
			{
				visited[row][col] = 1;
				Coord pt;
				pt.x = row;
				pt.y = col;

				EnQueue(que, pt, curdist + 1);
				
				
			}
		}
	}
	return -1;
}
int main()
{
	//N, M값 입력
	int N, M;
	scanf("%d %d", &N, &M);


	//NxM 크기의 2차원 배열
	int** mtx = malloc(sizeof(int*) * N);

	for (int i = 0; i < N; i++)
		mtx[i] = malloc(sizeof(int) * M);

	//각 줄의 입력값 문자열 배열로 입력 받기
	char ch[10];
	int ar[10];

	//문자열 배열을 2차 배열에 int형으로 한 줄씩 넣기
	for (int i = 0; i < N; i++)
	{
		scanf("%s", ch);
		for (int j = 0; j < M; j++)
		{
			mtx[j][i] = ch[j] - '0';
		}
	}
	Coord start;
	start.x = 0;
	start.y = 0;

	Coord dest;
	dest.x = M - 1;
	dest.y = N - 1;

	int max = -1;



	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			
			int temp = mtx[j][i];
			mtx[j][i] = 0;
			int dist = BFS(mtx, start, dest, M, N);

			
			if (dist != -1 && max == -1)
				max = dist;

			if (dist < max && dist != -1)
				max = dist;
			mtx[j][i] = temp;
		}
	}



	if (max != -1)
		printf("%d \n", max + 1);
	else
		printf("%d \n", max);

	return 0;


}
