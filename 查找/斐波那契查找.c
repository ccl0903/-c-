#include <stdio.h>  
#include <stdlib.h>  
#define _CRT_SECURE_NO_WARNINGS 1
#define MAXN 20	
#define MAXSIZE 10 /* �洢�ռ��ʼ������ */

//����쳲���������
void Fibonacci(int* f)
{
	int i;
	f[0] = 0;
	f[1] = 1;
	for (i = 2; i < MAXN; ++i)
		f[i] = f[i - 2] + f[i - 1];
}

//쳲����������ڲ����������С����Сֵ�Ĳ����ڵ���ʱ�����ܲ���ȶ��ֲ������죬�����Ұ����ʹ������ֵ�����ڵ���ʱ�����ܱȶ��ֲ�������
int Fibo_Search(int* arr, int n, int key) {
	int left, right, mid, i, k;
	left = 0;
	right = n - 1;
	k = 0;
	//����쳲���������
	int F[MAXN];
	Fibonacci(F);
	// �������ݳ���n��Ӧ쳲���������Ԫ��
	while (n > F[k] - 1)
		k++;
	// �����ݽ������,��nһֱ��䵽쳲�������ֵF[k]-1λ�������Ϊԭ��������ֵarr[n-1]
	for (i = n; i < F[k] - 1; i++)
		//arr[i] = arr[right];
	// �����䲻�Ϸָ�
	while (left <= right && k > 0) {
		mid = left + F[k - 1] - 1;
		if (key > arr[mid]) {		// Ŀ��ֵ���м�ֵ�ұߣ�������߽�
			left = mid + 1;
			k = k - 2;
		}
		else if (key < arr[mid]) {	// Ŀ��ֵ���м�ֵ��ߣ������ұ߽�
			right = mid - 1;
			k = k - 1;
		}
		else {
			if (mid <= n - 1)			//���mid >= n˵���ǲ�ȫ��ֵ������n-1
				return mid;
			else
				return n - 1;

		}
	}
	return -1;  //�Ҳ���
}
int main12()
{
    int a[13] = { 5, 15, 19, 20, 25, 31, 38, 41, 45, 49, 52, 55, 57 };
    int k, res = 0;
	int len = sizeof(a)/ sizeof(a[1]);
	//printf("%d\n", len);
    for (int i = 0; i < 13; i++) {
        k = a[i];
        res = Fibo_Search(a, 13, k);
        if (res != -1)
            printf("������ĵ�%d��λ���ҵ�Ԫ��:%d\n", res + 1, k);
        else
            printf("δ���������ҵ�Ԫ��:%d\n", k);
    }

	k = -20;
	res = Fibo_Search(a, 13, k);
	if (res != -1)
		printf("������ĵ�%d��λ���ҵ�Ԫ��:%d\n", res + 1, k);
	else
		printf("δ���������ҵ�Ԫ��:%d\n", k);

}
