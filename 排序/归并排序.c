#include <stdio.h>
#include <stdlib.h>

// ���鳤��
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )
#define swap(a,b) (a^=b,b^=a,a^=b)

//�ϲ����飬��һ�������е�����������������ϲ���һ��
void merge(int *arr,int start,int mid,int end) {
	int* temp = (int*)malloc(sizeof(int) * (end-start+1));  //������ʱ�������2����������
	int i = start;		//��1��������±�
	int j = mid + 1;	//��2��������±�
	int k = 0;		//temp�ĸ����±�

	while (i <= mid && j <= end) {
		if (arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}

	//����2���������ȫ����ӵ�temp�У�ֱ�ӽ���һ�������ʣ��Ԫ��ȫ������temp��
	while (i <= mid)
		temp[k++] = arr[i++];

	//����2����ʣ��Ԫ��ȫ������temp��
	while (j <= end)
		temp[k++] = arr[j++];
	
	//��temp�е��������ϵ�����arr��
	for (i = 0; i < k; i++)
		arr[start + i] = temp[i];

	free(temp);		//�ͷſռ�
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