#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


int main() {

	int size;
	char data[20];
	scanf("%d", &size);
	int* arr = (int*)malloc(sizeof(int) * (size + 1)); 

	arr[0] = 0;

	for (int i = 1; i < size + 1; i++) 
	{
		int temp;
		scanf("%s", data);
		if (data[0] == 'x')
		{
			temp = (int)data[0];
		}
		else
		{
			temp = atoi(data);
		}
		arr[i] = temp;          


	}

	int temp;
	int i = 2;
	while (i < size+1)
	{
		if (arr[i] != 120)
		{
			printf("%d ", arr[i]);
			i = 2 * i;
		}
		else if (arr[i] == 120)
		{
			temp = i;
			for (temp; temp < 2 * i;)
			{
				if (arr[temp] != 120)
				{
					printf("%d ", arr[temp]);
					temp = 2 * i;
				}
				else
				{
					temp++;
				}
			}
			i = 2 * i;
		}
	}
	printf("\n");
	i = 3;
	while (i < size)
	{
		if (arr[i] != 120)
		{
			printf("%d ", arr[i]);
			i = 2 * i + 1;
		}
		else if (arr[i] == 120)
		{
			temp = i;
			for (temp; temp > i/2;)
			{
				if (arr[temp])
				{
					printf("%d ", arr[temp]);
					temp = 0;
				}
				else
				{
					temp--;
				}
			}
			i = 2 * i+1;
		}
	}
	i = ((i - 1) / 2)+1;
	while (i < size+1)
	{
		if (arr[size] != 120)
		{
			printf("%d", arr[size]);
			size = 0;
		}
		else if (arr[size] == 120)
		{
			size--;
		}
	}
}