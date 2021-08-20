#include <stdio.h>
#include <stdlib.h>

// 数组长度
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )

void Bubble_Sort(int* arr,int n) {
	int i, j, temp,flag; //temp为临时交换变量，flag未标记
	for ( i = 0; i < n; i++)
	{
		flag = 0;
		for (j = 0; j < n-1-i; j++)
		{
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				flag = 1;
			}
		}
		if (flag == 0)
			break;     //终止循环
	}
}

//int main() {
//	int i, n = 10;
//	int arr[10] = { 100,50,10,90,30,70,40,80,60,20 };
//
//	printf("before sort:");
//	for (i = 0; i < n; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//
//	Bubble_Sort(arr,n);
//
//	printf("\nafter  sort:");
//	for (i = 0; i < n; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//
//	return 0; 
//
//}