#include <stdio.h>
#include <stdlib.h>

 // 数组长度
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )
#define swap(a,b) (a^=b,b^=a,a^=b)

//构造大根堆
void HeadAdjust(int *arr,int start,int end) {
    int temp, j = 2 * start + 1;        //数组取子节点： 2*n+1是左节点，2*n+2是右节点，与树不太一样( 2*n是左节点，2*n+1是右节点)
    temp = arr[start];
    for (j ; j <= end;j = j * 2 + 1) { // 沿关键字较大的孩子结点向下筛选 
        if (j < end && arr[j] < arr[j + 1])   //比较两个子结点，那个子结点大，j指向大结点下标      
            j++;
        if (temp > arr[j])       //如果结点的值比孩子结点大，循环退出
            break;
        arr[start] = arr[j];    //父结点替换为最大值
        start = j;              //start指向刚才被替换的最大值的子结点位置
    }
    arr[start] = temp;          //替换子结点
}

// 对数组arr进行堆排序  堆排序的时间复杂度为o(nlogn)
void HeapSort(int *arr,int n) {
    //数组传递过来只是首元素的地址
    int i = (n - 1) / 2 - 1;    //指向最后一个元素的父结点的下标
    for (i; i >= 0; i--)        //构造大根堆
        HeadAdjust(arr,i,n-1);
    //排序步骤
    for (i = n - 1; i > 0;i--) {   //i初始为最后一个元素的下标
        swap(arr[0],arr[i]);
        HeadAdjust(arr,0,i-1);
    }
}

//构造小根堆
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

//降序堆排序
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