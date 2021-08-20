#include <stdio.h>
#include <stdlib.h>

/*
 * 希尔排序的时间复杂度为 O(n的3/2次方)),
 */
void ShellSort(int *arr,int n) {
	int i, j, gap;
	gap = n / 3 + 1;	
	while (gap >= 1)
	{
		for ( i = gap+1 ; i <= n; i++)   /*数组下标从gap+1开始进行直接插入排序*/
		{
			arr[0] = arr[i]; //监视哨
			j = i - gap;	//确定要进行比较的元素的最右边位置
			while ((j > 0) && arr[0] < arr[j]) {
				arr[j + gap] = arr[j];   //数据后移
				j = j - gap;			//下标前移
			}
			arr[j + gap] = arr[0];
		}
		gap = gap / 3;
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
//	ShellSort(arr,n);
//
//	printf("\nafter  sort:");
//	showArr(arr, n);
//
//}