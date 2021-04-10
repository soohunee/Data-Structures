#include <stdio.h>
#include <stdlib.h>

void insert_max_heap(int item);
void print_heap_preorder(int travel);
int isNpossible(int N);
void set_left_right();
void swap(int* a, int* b);


int* heap;
int heap_size = 0;

int main() {

	int max, tmp, n, i, check = 0;

	scanf("%d", &max);
	heap = (int*)malloc(sizeof(int) * max * 2);
	for (i = 1; i <= max; i++) {
		scanf("%d", &tmp);
		insert_max_heap(tmp);
	}
	scanf("%d", &n);

	check = isNpossible(n);

	if (check == 1) {
		print_heap_preorder(1);
	}
	else {
		set_left_right(1);
		check = isNpossible(n);
	}

	free(heap);
}


void insert_max_heap(int item) {
	int i, tmp;
	i = ++(heap_size);
	while ((i != 1) && (item > heap[i / 2])) {
		tmp = heap[i];
		heap[i] = heap[i / 2];
		heap[i / 2] = tmp;
		i /= 2;
	}
	heap[i] = item;
}

int isNpossible(int N) {
	int i, j, sum = 0;
	for (i = heap_size; i >= 0; i--) {
		j = i;
		while (j > 0) {
			sum = sum + heap[j];
			j /= 2;
		}
		if (sum == N) {
			return 1;
		}
		sum = 0;
	}
	return 0;
}

void print_heap_preorder(int travel) {
	if (travel <= heap_size)
		printf("%d ", heap[travel]);
	if (2 * travel <= heap_size)
		print_heap_preorder(2 * travel);
	if (2 * travel + 1 <= heap_size)
		print_heap_preorder(2 * travel + 1);
}

void set_left_right(int root) {
	int tmp;
	if (root * 2 <= heap_size)
		set_left_right(root * 2);
	if (root * 2 + 1 <= heap_size)
		set_left_right(root * 2 + 1);

	if (root <= heap_size && root + 1 <= heap_size && heap[root] < heap[root + 1]) {
		swap(&heap[root], &heap[root + 1]);
	}
}

void swap(int* a, int* b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

