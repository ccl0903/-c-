#include <stdio.h>
#include <stdlib.h>

//��ѡ������(����Сֵ)   ��ѡ�������ʱ�临�Ӷ�Ϊo(n*n),�������ϵ���������ð������
void SelectSort(int *arr,int n) {
	int i, j, min,temp;
	for (i = 0; i < n;i++) {
		min = i;			//ָ����Сֵ���±�
		for (j = i + 1; j < n; j++)
			if (arr[min] > arr[j])		//���ֱ������е�ǰ��Сֵ��С������min�±�ָ���ֵ���Сֵ
				min = j;
		if (min != i) {		//min�ı䣬��Ҫ������Сֵ����
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