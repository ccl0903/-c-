#include <stdio.h>

int m;  //执行次数

//搬动次数
void move(int n,char x, char y)
{
	m++;
	printf("第 %d 个盘子  %c--->%c\n",n, x, y);
}

/*
(1) 用 C 柱做过渡，将 A 柱上的(n-l)个盘子移到 B 柱上；
(2) 将 A 柱上最后一个盘子直接移到 C 柱上；
(3) 用 A 柱做过渡，将 B 柱上的(n-l)个盘子移到C柱上。
*/
void Hanoi(int n,char a,char b,char c) {
	//把塔A上的n个盘搬到C塔，用B塔做辅助塔
	if (n == 1)
		move(1,a,c); //将编号为1的圆盘从A移到c
	else
	{
		Hanoi(n-1,a,c,b);	//用 C 柱做过渡，将 A 柱上的(n-l)个盘子移到 B 柱上；
		move(n,a,c);		//将 A 柱上最后一个盘子直接移到 C 柱上；
		Hanoi(n-1,b,a,c);	//用 A 柱做过渡，将 B 柱上的(n-l)个盘子移到C柱上。
	}
}

int main_digui() {
	Hanoi(4,'A','B','C');
	printf("一共移动了 %d 次", m);
	return 0;
}