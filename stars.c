#include<stdio.h>

void func1(int n);
void func2(int n);
void func3(int n);

int main() 
{

func3(6);

return 0;
}

void func1(int n) 
{
int i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < i+1; j++) {
			printf("*");
		}
		printf("\n");
	}
}

void func2(int n)
{
int i, j;
	for(i = 0; i < 2*n-1; i++) {
		if(i<n)
		{
			for(j = 0; j < i+1; j++) {
				printf("*");
			}
		}
		else {
			for(j = i; j < 2*n-1; j++) {
				printf("*");
			}
		}			
		printf("\n");
	}
} 

void func3(int n)
{
int stars = 1, i, j;

	for(i = 0; i < n; i++) {
		for(j = 0; j < n-i-1; j++) {
			printf(" ");
		}
		for(j = 0; j < stars; j++) {
			printf("*");
		}
	printf("\n");
	stars += 2;
	}
}


