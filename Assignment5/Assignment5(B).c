#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#define MAX_HEAP 100

typedef enum { false, true } bool;

typedef struct {
	char small;
	char middle;
	char large;
} Penta_num;

typedef struct {
	Penta_num data; // This is a priority as well as data
} PNode;

typedef struct {
	PNode items[MAX_HEAP + 1];
	int num;
} Heap;

void InitHeap(Heap* pheap);
bool IsEmpty(Heap* pheap);
bool IsFull(Heap* pheap);
void Insert(Heap* pheap, Penta_num data);
Penta_num Delete(Heap* pheap);
void HeapSort(Penta_num a[], int n);
Penta_num* CreatePentaNum(int n);
void GetInput();

int main() {
	GetInput(); /* 5 0E0 321 EEE CCC 3D0 */
	return 0;
}

void HeapSort(Penta_num a[], int n) {
	Heap heap;
	InitHeap(&heap);
	// Insert all elements to the heap.
	for (int i = 0; i < n; i++)
		Insert(&heap, a[i]);
	// Remove all elements from the heap.
	for (int i = 0; i <= n - 1; i++)
		a[i] = Delete(&heap);

	for (int i = 0; i < n; i++)
		printf("%c%c%c\n", a[i].large, a[i].middle, a[i].small);
}

Penta_num* CreatePentaNum(int n) {
	char a[4];
	Penta_num* res = (Penta_num*)malloc(sizeof(Penta_num) * (n));
	for (int i = 0; i < n; i++) {
		scanf("%s", a);
		res[i].large = a[0];
		res[i].middle = a[1];
		res[i].small = a[2];
	}
	return res;
}
void GetInput() {
	int n;
	Penta_num* data;
	scanf("%d", &n);
	data = CreatePentaNum(n);
	HeapSort(data, n);
} /* Modify from here */

int PentaToInt(Penta_num data)
{
	int result = 0;
	if (data.small >= '0' && data.small <= '9')
		result += data.small - '0';
	if (data.small >= 'A' && data.small <= 'E')
		result += data.small - '7';
	if (data.middle >= '0' && data.middle <= '9')
		result += (data.middle - '0') * 15;
	if (data.middle >= 'A' && data.middle <= 'E')
		result += (data.middle - '7') * 15;
	if (data.large >= '0' && data.large <= '9')
		result += (data.large - '0') * 225;
	if (data.large >= 'A' && data.large <= 'E')
		result += (data.large - '7') * 225;

	return result;
}
void InitHeap(Heap* pheap)
{
	pheap->num = 0;
}
bool IsEmpty(Heap* pheap)
{
	return pheap->num == 0;

}
bool IsFull(Heap* pheap)
{
	return pheap->num == MAX_HEAP;
}
void Insert(Heap* pheap, Penta_num data)
{
	PNode newNode;
	int idx = pheap->num + 1;
	if (IsFull(pheap))
		exit(1);

	while (idx > 1)
	{
		int intdata = PentaToInt(data);
		
		int parent = idx / 2;
		int intparent = PentaToInt(pheap->items[parent].data);
		if (intdata < intparent)
		{
			pheap->items[idx] = pheap->items[parent];
			idx = parent;
		}
		else
			break;
			
	}
	newNode.data = data;
	pheap->items[idx] = newNode;
	pheap->num++;
}
int GetHighPriorityChild(Heap* pheap, int idx)
{
	if (idx * 2 > pheap->num)
		return 0;
	else if (idx * 2 == pheap->num)
		return idx * 2 ;
	else
	{
		int left = idx * 2, right = idx * 2 + 1;
		int intleft = PentaToInt(pheap->items[left].data);
		int intright = PentaToInt(pheap->items[right].data);

		if (intleft > intright)
			return right;
		else
			return left;
	}
}
Penta_num Delete(Heap* pheap)
{
	Penta_num min = pheap->items[1].data;
	PNode last = pheap->items[pheap->num];
	int parent = 1, child;

	while (child = GetHighPriorityChild(pheap, parent)) 
	{
		if (PentaToInt(last.data) > PentaToInt(pheap->items[child].data)) {
			pheap->items[parent] = pheap->items[child];
			parent = child;
		}
		else
			break;
	}
	pheap->items[parent] = last;
	pheap->num--;
	
	return min;
}
/* Modify to here*/

