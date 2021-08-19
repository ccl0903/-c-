#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXN 20	
#define MAXSIZE 10 /* 存储空间初始分配量 */

typedef int KeyType;

typedef struct {
	KeyType key;     //关键字域
}Elemtype;

typedef struct {
	Elemtype* R;	//存储空间的值
	int length;   //当前长度
}SSTable;

//顺序查找
int Search_Seq(int* arr, int n,int key) {
	int i;
	for ( i = 0; i < n; i++)
	{
		if (arr[i] == key)
			return i;
	}
	return 0;
}

//哨兵顺序查找   (返回值为0表示找不到该元素)
int Search_Seq_Sentry(int *arr,int n,int key) {
	arr[0] = key;  //将预留的头元素置为要查找的元素
	int i = n; //从尾部开始查找
	while (arr[i] != key)
		i--;
	return i;
}

/*===================有序线性表====================*/	
//二分查找
int Binary_Search(int *arr,int n,int key) {
	int left, right, mid;
	left = 0;
	right = n - 1;
	while (left <= right)
	{
		mid = (left + right) / 2;  /* 折半去中值 */
		if (key > arr[mid])
			left = mid + 1;
		else if (key < arr[mid])
			right = mid - 1;
		else
			return mid;
	}
	return -1;    //返回-1代表查询不到
}

//插值寻找  （适用于查找表中的数据比较均匀，波动幅度不是特别大时，效率比二分查找优异）
int Interpolation_Search(int* arr, int n, int key) {
	int left, right, mid;
	left = 0;
	right = n - 1;
	while (left <= right)
	{
		mid = left+(right - left)*(key-arr[left])/(arr[right] - arr[left]);  /* 插值 */
		if (key > arr[mid])
			left = mid + 1;
		else if (key < arr[mid])
			right = mid - 1;
		else
			return mid;
	}
	return -1;    //返回-1代表查询不到
}

int main_search(void)
{
	int i, res,key,k;
	int arr[MAXSIZE] = { 1,16,24,35,47,59,62,73,88,99};
	int arr1[MAXSIZE+1] = { 0,1,16,24,35,47,59,62,73,88,99 };  //预留第一个元素作为哨兵

	key = 47;
	res = Search_Seq(arr,MAXSIZE,key);
	printf("通过顺序查找，找到元素%d在数组arr的第%d个位置\n", key, res);

	key = 2;
	res = Search_Seq_Sentry(arr1,MAXSIZE,key);
	printf("通过哨兵顺序查找，找到元素%d在数组arr的第%d个位置\n", key, res);   //下标为0表示查找不到

	key = 62;
	res = Binary_Search(arr,MAXSIZE,key);
	printf("通过二分查找，找到元素%d在数组arr的第%d个位置\n", key, res);
	key = -90;
	res = Binary_Search(arr, MAXSIZE, key);
	printf("通过二分查找，找到元素%d在数组arr的第%d个位置\n", key, res);

	key = 62;
	res = Interpolation_Search(arr, MAXSIZE, key);
	printf("通过插值查找，找到元素%d在数组arr的第%d个位置\n", key, res);
	key = -90;
	res = Interpolation_Search(arr, MAXSIZE, key);
	printf("通过插值查找，找到元素%d在数组arr的第%d个位置\n", key, res);

	int a[13] = { 5, 15, 19, 20, 25, 31, 38, 41, 45, 49, 52, 55, 57 };
	key = 57;
	res = Fibo_Search(a, 13, key);
	printf("通过斐波那契查找，找到元素%d在数组arr的第%d个位置\n", key, res);

	return 0;
}
