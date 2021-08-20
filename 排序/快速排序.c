#include <stdio.h>
#include <stdlib.h>

// ���鳤��
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )


//��������
void QuickSort(int arr[], int left, int right) {
	int i, j;
	i = left;	 // ��ÿ���׸�Ԫ�ظ���i
	j = right;	 //��ÿ��ĩβԪ�ظ���j
	arr[0] = arr[i];		//���ĵ�
	while (i < j) {
			while (i < j &&  arr[0] <= arr[j])
				j--;	 //λ������
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
		arr[i] = arr[0];  //arr[j] = arr[0] Ҳ���� 
		if(left < i)
			QuickSort(arr,left,j-1);
		if(i < right)
			QuickSort(arr, j+1, right);
}

//���������Ż��汾
int QuickSort2(int arr[], int left, int right) {
	/* ����ѡ��ʹ��3���з�ѡ�������pivotkey*/
	int pivotkey = arr[left];
	arr[0] = pivotkey;
	while (left <right) {
		while (left < right && arr[right] >= pivotkey)
			right--;
		arr[left] = arr[right];  //�����滻
		while (left < right && arr[left] <= pivotkey)
			left++;
		arr[right] = arr[left];
	}
	arr[left] = arr[0];
	return left;
}

/* β�ݹ� */
void QSort(int *arr,int left,int right) {
	int pivot; 
	while (left<right)
	{
		pivot = QuickSort2(arr, left, right);
		QSort(arr,left,pivot-1);
		left = pivot + 1;  //β�ݹ�
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
