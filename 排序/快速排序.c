#include <stdio.h>
#include <stdlib.h>

// 数组长度
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )


//快速排序
void QuickSort(int arr[], int left, int right) {
	int i, j;
	i = left;	 // 将每组首个元素赋给i
	j = right;	 //将每组末尾元素赋给j
	arr[0] = arr[i];		//中心点
	while (i < j) {
			while (i < j &&  arr[0] <= arr[j])
				j--;	 //位置左移
			if (i < j) {
				arr[i] = arr[j];   
				i++;
			}
			while (i < j && arr[i] < arr[0])
				i++;
			if (i < j) {
				arr[j] = arr[i];
				j--;
			}
		}
		arr[i] = arr[0];  //arr[j] = arr[0] 也可以 
		if(left < i)
			QuickSort(arr,left,j-1);
		if(i < right)
			QuickSort(arr, j+1, right);
}

//快速排序优化版本
int QuickSort2(int arr[], int left, int right) {
	/* 可以选择使用3分中法选择中轴点pivotkey*/
	int pivotkey = arr[left];
	arr[0] = pivotkey;
	while (left <right) {
		while (left < right && arr[right] >= pivotkey)
			right--;
		arr[left] = arr[right];  //采用替换
		while (left < right && arr[left] <= pivotkey)
			left++;
		arr[right] = arr[left];
	}
	arr[left] = arr[0];
	return left;
}

/* 尾递归 */
void QSort(int *arr,int left,int right) {
	int pivot; 
	while (left<right)
	{
		pivot = QuickSort2(arr, left, right);
		QSort(arr,left,pivot-1);
		left = pivot + 1;  //尾递归
	}

}

//int main() {
//		int i, n = 9;
//		int arr[10] = {0,50,10,90,30,70,40,80,60,20 };
//	
//		printf("before sort:");
//		showArr(arr, n);
//	
//		//QuickSort(arr,1,n);
//		QSort(arr,1,n);
//
//		printf("\nafter  sort:");
//		showArr(arr,n);
//		return 0; 
//	
//}
