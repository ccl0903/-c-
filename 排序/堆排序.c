#include <stdio.h>
#include <stdlib.h>

 // ���鳤��
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )
#define swap(a,b) (a^=b,b^=a,a^=b)

//��������
void HeadAdjust(int *arr,int start,int end) {
    int temp, j = 2 * start + 1;        //����ȡ�ӽڵ㣺 2*n+1����ڵ㣬2*n+2���ҽڵ㣬������̫һ��( 2*n����ڵ㣬2*n+1���ҽڵ�)
    temp = arr[start];
    for (j ; j <= end;j = j * 2 + 1) { // �عؼ��ֽϴ�ĺ��ӽ������ɸѡ 
        if (j < end && arr[j] < arr[j + 1])   //�Ƚ������ӽ�㣬�Ǹ��ӽ���jָ������±�      
            j++;
        if (temp > arr[j])       //�������ֵ�Ⱥ��ӽ���ѭ���˳�
            break;
        arr[start] = arr[j];    //������滻Ϊ���ֵ
        start = j;              //startָ��ղű��滻�����ֵ���ӽ��λ��
    }
    arr[start] = temp;          //�滻�ӽ��
}

// ������arr���ж�����  �������ʱ�临�Ӷ�Ϊo(nlogn)
void HeapSort(int *arr,int n) {
    //���鴫�ݹ���ֻ����Ԫ�صĵ�ַ
    int i = (n - 1) / 2 - 1;    //ָ�����һ��Ԫ�صĸ������±�
    for (i; i >= 0; i--)        //��������
        HeadAdjust(arr,i,n-1);
    //������
    for (i = n - 1; i > 0;i--) {   //i��ʼΪ���һ��Ԫ�ص��±�
        swap(arr[0],arr[i]);
        HeadAdjust(arr,0,i-1);
    }
}

//����С����
void HeadAdjust_down(int *arr,int start,int end) {
    int temp, j = 2 * start + 1;
    temp = arr[start];
    for (j; j <= end; j = j * 2 + 1) {
        if (j < end && arr[j] > arr[j + 1])
            j++;
        if (temp < arr[j])
            break;
        arr[start] = arr[j];
        start = j;
    }
    arr[start] = temp;
}

//���������
void HeapSort_desc(int *arr,int n) {
    int i = (n - 1) / 2 - 1;
    for (i; i >= 0; i--)
        HeadAdjust_down(arr,i,n-1);
    for (i = n - 1; i > 0;i--) {
        swap(arr[0],arr[i]);
        HeadAdjust_down(arr,0,i-1);
    }
}

//void main()
//{
//    int i;
//    int a[] = { 20,30,90,40,70,110,60,10,100,50,80 };
//    int len = LENGTH(a);
//
//    printf("before sort:");
//    for (i = 0; i < len; i++)
//        printf("%d ", a[i]);
//    printf("\n");
//
//   // HeapSort(a,len);
//    HeapSort_desc(a,len);
//
//    printf("after  sort:");
//    for (i = 0; i < len; i++)
//        printf("%d ", a[i]);
//    printf("\n");
//}