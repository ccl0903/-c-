#include <stdio.h>
#include <stdlib.h>

/*
 * ϣ�������ʱ�临�Ӷ�Ϊ O(n��3/2�η�)),
 */
void ShellSort(int *arr,int n) {
	int i, j, gap;
	gap = n / 3 + 1;	
	while (gap >= 1)
	{
		for ( i = gap+1 ; i <= n; i++)   /*�����±��gap+1��ʼ����ֱ�Ӳ�������*/
		{
			arr[0] = arr[i]; //������
			j = i - gap;	//ȷ��Ҫ���бȽϵ�Ԫ�ص����ұ�λ��
			while ((j > 0) && arr[0] < arr[j]) {
				arr[j + gap] = arr[j];   //���ݺ���
				j = j - gap;			//�±�ǰ��
			}
			arr[j + gap] = arr[0];
		}
		gap = gap / 3;
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
//	ShellSort(arr,n);
//
//	printf("\nafter  sort:");
//	showArr(arr, n);
//
//}