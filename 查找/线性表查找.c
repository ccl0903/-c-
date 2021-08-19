#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXN 20	
#define MAXSIZE 10 /* �洢�ռ��ʼ������ */

typedef int KeyType;

typedef struct {
	KeyType key;     //�ؼ�����
}Elemtype;

typedef struct {
	Elemtype* R;	//�洢�ռ��ֵ
	int length;   //��ǰ����
}SSTable;

//˳�����
int Search_Seq(int* arr, int n,int key) {
	int i;
	for ( i = 0; i < n; i++)
	{
		if (arr[i] == key)
			return i;
	}
	return 0;
}

//�ڱ�˳�����   (����ֵΪ0��ʾ�Ҳ�����Ԫ��)
int Search_Seq_Sentry(int *arr,int n,int key) {
	arr[0] = key;  //��Ԥ����ͷԪ����ΪҪ���ҵ�Ԫ��
	int i = n; //��β����ʼ����
	while (arr[i] != key)
		i--;
	return i;
}

/*===================�������Ա�====================*/	
//���ֲ���
int Binary_Search(int *arr,int n,int key) {
	int left, right, mid;
	left = 0;
	right = n - 1;
	while (left <= right)
	{
		mid = (left + right) / 2;  /* �۰�ȥ��ֵ */
		if (key > arr[mid])
			left = mid + 1;
		else if (key < arr[mid])
			right = mid - 1;
		else
			return mid;
	}
	return -1;    //����-1�����ѯ����
}

//��ֵѰ��  �������ڲ��ұ��е����ݱȽϾ��ȣ��������Ȳ����ر��ʱ��Ч�ʱȶ��ֲ������죩
int Interpolation_Search(int* arr, int n, int key) {
	int left, right, mid;
	left = 0;
	right = n - 1;
	while (left <= right)
	{
		mid = left+(right - left)*(key-arr[left])/(arr[right] - arr[left]);  /* ��ֵ */
		if (key > arr[mid])
			left = mid + 1;
		else if (key < arr[mid])
			right = mid - 1;
		else
			return mid;
	}
	return -1;    //����-1�����ѯ����
}

int main_search(void)
{
	int i, res,key,k;
	int arr[MAXSIZE] = { 1,16,24,35,47,59,62,73,88,99};
	int arr1[MAXSIZE+1] = { 0,1,16,24,35,47,59,62,73,88,99 };  //Ԥ����һ��Ԫ����Ϊ�ڱ�

	key = 47;
	res = Search_Seq(arr,MAXSIZE,key);
	printf("ͨ��˳����ң��ҵ�Ԫ��%d������arr�ĵ�%d��λ��\n", key, res);

	key = 2;
	res = Search_Seq_Sentry(arr1,MAXSIZE,key);
	printf("ͨ���ڱ�˳����ң��ҵ�Ԫ��%d������arr�ĵ�%d��λ��\n", key, res);   //�±�Ϊ0��ʾ���Ҳ���

	key = 62;
	res = Binary_Search(arr,MAXSIZE,key);
	printf("ͨ�����ֲ��ң��ҵ�Ԫ��%d������arr�ĵ�%d��λ��\n", key, res);
	key = -90;
	res = Binary_Search(arr, MAXSIZE, key);
	printf("ͨ�����ֲ��ң��ҵ�Ԫ��%d������arr�ĵ�%d��λ��\n", key, res);

	key = 62;
	res = Interpolation_Search(arr, MAXSIZE, key);
	printf("ͨ����ֵ���ң��ҵ�Ԫ��%d������arr�ĵ�%d��λ��\n", key, res);
	key = -90;
	res = Interpolation_Search(arr, MAXSIZE, key);
	printf("ͨ����ֵ���ң��ҵ�Ԫ��%d������arr�ĵ�%d��λ��\n", key, res);

	int a[13] = { 5, 15, 19, 20, 25, 31, 38, 41, 45, 49, 52, 55, 57 };
	key = 57;
	res = Fibo_Search(a, 13, key);
	printf("ͨ��쳲��������ң��ҵ�Ԫ��%d������arr�ĵ�%d��λ��\n", key, res);

	return 0;
}
