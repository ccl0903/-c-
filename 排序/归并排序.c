#include <stdio.h>
#include <stdlib.h>

// 数组长度
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )
#define swap(a,b) (a^=b,b^=a,a^=b)

//合并数组，将一个数组中的两个相邻有序区间合并成一个
void merge(int *arr,int start,int mid,int end) {
	int* temp = (int*)malloc(sizeof(int) * (end-start+1));  //开劈临时数组汇总2个有序区间
	int i = start;		//第1个区间的下标
	int j = mid + 1;	//第2个区间的下标
	int k = 0;		//temp的辅助下标

	while (i <= mid && j <= end) {
		if (arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}

	//当第2区间的数据全部添加到temp中，直接将第一个区间的剩余元素全部加入temp中
	while (i <= mid)
		temp[k++] = arr[i++];

	//将第2区间剩余元素全部加入temp中
	while (j <= end)
		temp[k++] = arr[j++];
	
	//将temp中的数据整合到数组arr中
	for (i = 0; i < k; i++)
		arr[start + i] = temp[i];

	free(temp);		//释放空间
}

//void MergeSort(int *arr,int start,int end) {
//	if (arr != NULL && start >= end)
//		return;
//
//	int mid = (end + start) / 2;
//	MergeSort(arr,start,mid);
//	MergeSort(arr, mid + 1, end);
//
//	merge(arr,start,mid,end);
//}
//
//
//int main() {
//	int i;
//	int arr[10] = { 100,50,10,90,30,70,40,80,60,20 };
//	int len = LENGTH(arr);
//
//	printf("before sort:");
//	for (i = 0; i < len; i++)
//		printf("%d ",arr[i]);
//	printf("\n");
//
//	MergeSort(arr,0,len-1);
//	
//	printf("before sort:");
//	for (i = 0; i < len; i++)
//		printf("%d ", arr[i]);
//	printf("\n");
//
//	return 0;
//}