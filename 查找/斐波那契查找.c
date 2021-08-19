#include <stdio.h>  
#include <stdlib.h>  
#define _CRT_SECURE_NO_WARNINGS 1
#define MAXN 20	
#define MAXSIZE 10 /* 存储空间初始分配量 */

//产生斐波那契数列
void Fibonacci(int* f)
{
	int i;
	f[0] = 0;
	f[1] = 1;
	for (i = 2; i < MAXN; ++i)
		f[i] = f[i - 2] + f[i - 1];
}

//斐波那契查找在查找左半区和小于最小值的不存在的数时，性能不会比二分查找优异，但在右半区和大于最大值不存在的数时，性能比二分查找优异
int Fibo_Search(int* arr, int n, int key) {
	int left, right, mid, i, k;
	left = 0;
	right = n - 1;
	k = 0;
	//创建斐波那契数列
	int F[MAXN];
	Fibonacci(F);
	// 计算数据长度n对应斐波那契数列元素
	while (n > F[k] - 1)
		k++;
	// 对数据进行填充,从n一直填充到斐波那契数值F[k]-1位，填充数为原数组的最大值arr[n-1]
	for (i = n; i < F[k] - 1; i++)
		//arr[i] = arr[right];
	// 对区间不断分割
	while (left <= right && k > 0) {
		mid = left + F[k - 1] - 1;
		if (key > arr[mid]) {		// 目标值在中间值右边，更新左边界
			left = mid + 1;
			k = k - 2;
		}
		else if (key < arr[mid]) {	// 目标值在中间值左边，更新右边界
			right = mid - 1;
			k = k - 1;
		}
		else {
			if (mid <= n - 1)			//如果mid >= n说明是补全数值，返回n-1
				return mid;
			else
				return n - 1;

		}
	}
	return -1;  //找不到
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
            printf("在数组的第%d个位置找到元素:%d\n", res + 1, k);
        else
            printf("未在数组中找到元素:%d\n", k);
    }

	k = -20;
	res = Fibo_Search(a, 13, k);
	if (res != -1)
		printf("在数组的第%d个位置找到元素:%d\n", res + 1, k);
	else
		printf("未在数组中找到元素:%d\n", k);

}
