#include<stdio.h>

void a();
void b();

int main()
{
	a(2);
}

void a(int val)
{
	int* xp;

	printf("im A\n");
	xp = &val;
	xp--;
	*xp = &b;
}

void b()
{
printf("im B\n");
}
