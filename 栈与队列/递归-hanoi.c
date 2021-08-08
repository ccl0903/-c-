#include <stdio.h>

int m;  //ִ�д���

//�ᶯ����
void move(int n,char x, char y)
{
	m++;
	printf("�� %d ������  %c--->%c\n",n, x, y);
}

/*
(1) �� C �������ɣ��� A ���ϵ�(n-l)�������Ƶ� B ���ϣ�
(2) �� A �������һ������ֱ���Ƶ� C ���ϣ�
(3) �� A �������ɣ��� B ���ϵ�(n-l)�������Ƶ�C���ϡ�
*/
void Hanoi(int n,char a,char b,char c) {
	//����A�ϵ�n���̰ᵽC������B����������
	if (n == 1)
		move(1,a,c); //�����Ϊ1��Բ�̴�A�Ƶ�c
	else
	{
		Hanoi(n-1,a,c,b);	//�� C �������ɣ��� A ���ϵ�(n-l)�������Ƶ� B ���ϣ�
		move(n,a,c);		//�� A �������һ������ֱ���Ƶ� C ���ϣ�
		Hanoi(n-1,b,a,c);	//�� A �������ɣ��� B ���ϵ�(n-l)�������Ƶ�C���ϡ�
	}
}

int main_digui() {
	Hanoi(4,'A','B','C');
	printf("һ���ƶ��� %d ��", m);
	return 0;
}