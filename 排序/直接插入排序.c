#include <stdio.h>
#include <stdlib.h>

//ֱ�Ӳ�������
void InsertSort(int* arr, int n) {
	int i, j;
	for (i = 2; i <= n; i++)
	{
		if (arr[i] < arr[i - 1]) {	 //���ڣ���Ҫ��arr[i]���뵽�������
			arr[0] = arr[i];		 //�����ڱ�
			for (j = i - 1; arr[j] > arr[0]; j--) { // ��i - 1��ǰ�Ƚ�ֱ���ҵ���r[0]С��λ�ú��ƾͽ���
				arr[j + 1] = arr[j];  //���Ʋ���
			}
			arr[j + 1] = arr[0];	 //���뵽��ȷ��λ��
		}
	}
}

//���ֲ������� (�������ܱ�ֱ�Ӳ�����������һЩ����ʱ�临�Ӷ���Ȼ��ֱ�Ӳ�������һ��Ϊ O(n*n))
void BinarySort(int *arr,int n) {
	int i,j,left, right, mid;
	for ( i = 2; i <= n; i++)
	{
		left = 1; right = i - 1;	//�ò��������ֵ
		arr[0] = arr[i];			//�ڱ�����
		while (left <= right) {
			mid = (left + right) / 2;  //����
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
//	/* ��Ϊ�����ڱ����ƺ󣬰�����ĵ�һ��λ�ÿ�������ʱ�洢�ڱ�*/
//	int arr[10] = { 0,50,10,90,30,70,40,80,60,20 };
//
//	printf("before sort:");
//	showArr(arr, n);
//
//	InsertSort(arr, n);		//ֱ�Ӳ�������
//	//BinarySort(arr, n);  //���ֲ�������
//
//	printf("\nafter  sort:");
//	showArr(arr,n);
//
//	return 0;
//} 