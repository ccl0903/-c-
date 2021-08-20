#include <stdio.h>
#include <stdlib.h>

//直接插入排序
void InsertSort(int* arr, int n) {
	int i, j;
	for (i = 2; i <= n; i++)
	{
		if (arr[i] < arr[i - 1]) {	 //大于，需要将arr[i]插入到有序表中
			arr[0] = arr[i];		 //设置哨兵
			for (j = i - 1; arr[j] > arr[0]; j--) { // 从i - 1往前比较直到找到比r[0]小的位置后移就结束
				arr[j + 1] = arr[j];  //后移操作
			}
			arr[j + 1] = arr[0];	 //插入到正确的位置
		}
	}
}

//二分查找排序 (整体性能比直接查找排序优异一些，但时间复杂度仍然和直接插入排序一样为 O(n*n))
void BinarySort(int *arr,int n) {
	int i,j,left, right, mid;
	for ( i = 2; i <= n; i++)
	{
		left = 1; right = i - 1;	//置查找区间初值
		arr[0] = arr[i];			//哨兵设置
		while (left <= right) {
			mid = (left + right) / 2;  //二分
			if (arr[0] < arr[mid])
				right = mid - 1;
			else
				left = mid + 1;
		}
		for (j = i - 1; j >= right + 1; j--)
			arr[j + 1] = arr[j];
		arr[right + 1] = arr[0];
	}
}

void showArr(int* arr,int n) {
	int i;
	for (i = 1; i <= n; i++)
	{
		printf("%d ", arr[i]);
	}
}


//int main() {
//	int i, n = 9;
//	/* 因为加入哨兵机制后，把数组的第一个位置空着来临时存储哨兵*/
//	int arr[10] = { 0,50,10,90,30,70,40,80,60,20 };
//
//	printf("before sort:");
//	showArr(arr, n);
//
//	InsertSort(arr, n);		//直接插入排序
//	//BinarySort(arr, n);  //二分查找排序
//
//	printf("\nafter  sort:");
//	showArr(arr,n);
//
//	return 0;
//} 