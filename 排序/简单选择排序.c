#include <stdio.h>
#include <stdlib.h>

//简单选择排序(找最小值)   简单选择排序的时间复杂度为o(n*n),当整体上的性能优于冒泡排序
void SelectSort(int *arr,int n) {
	int i, j, min,temp;
	for (i = 0; i < n;i++) {
		min = i;			//指向最小值的下标
		for (j = i + 1; j < n; j++)
			if (arr[min] > arr[j])		//发现比数组中当前最小值还小的数，min下标指向发现的最小值
				min = j;
		if (min != i) {		//min改变，需要进行最小值交换
			temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
}

//int main() {
//	int i, n = 10;
//	int arr[10] = {0,50,10,90,30,70,40,80,60,20 };
//
//	printf("before sort:");
//	for ( i = 0; i < n; i++)
//	{
//		printf("%d ",arr[i]);
//	}
//
//	SelectSort(arr,10);
//
//	printf("\nafter  sort:");
//	for (i = 0; i < n; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	return 0;
//}