#include<stdio.h>

int Fibo(int n)
{
	if (n == 1)
		return 0;
	else if (n == 2)
		return 1;
	else
		return Fibo(n - 1) + Fibo(n - 2);
	/*n번째 수열의 값 = n-1번째 수열 + n-2번째 수열*/
}

int main()
{
	int i;
	for (i = 1; i < 15; i++)	
		printf("%d ", Fibo(i));
	

	return 0;
}