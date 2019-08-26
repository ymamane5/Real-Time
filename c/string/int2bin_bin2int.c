#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* int2bin(int num, char* arr);
int bin2int(char* arr);
void reverseStr(char* str);
void swap(char* a, char* b);
int check_sequence(char* arr);

int main()
{
	char arr[32];
	int num, selection;

	printf("select operation:\n1. int2bin\n2. bin2int");
	scanf("%d", &selection);

	if (selection == 1)
	{

		printf("please enter number: \n");
		scanf("%d", &num);

		do {
			printf("binary sequence is: %s\n", int2bin(num, arr));
			printf("please enter number: \n");
			scanf("%d", &num);
		} while (num >= 0);
	}

	else if (selection == 2)
	{
		printf("please enter binary sequence: \n");
		scanf("%s", arr);
		if (check_sequence(arr) == 0)
		{
			do {
				printf("please enter valid sequnce\n");
				scanf("%s", arr);
			} while (check_sequence(arr) == 0);
		}

		do {
			printf("the number is: %d\n", bin2int(arr));
			printf("please enter binary sequence: \n");
			scanf("%s", arr);
			if (check_sequence(arr) == 0)
			{
				do {
					printf("please enter valid sequnce\n");
					scanf("%s", arr);
				} while (check_sequence(arr) == 0);
			}

		} while (arr[0] != '-');
	}


}

void swap(char* a, char* b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void reverseStr(char* str)
{
	int i, length = strlen(str);

	for (i = 0; i < length / 2; i++)
		swap(&str[i], &str[length - i - 1]);
}

char* int2bin(int num, char* arr)
{
	int i;

	num = abs(num);
	
	if (num == 0)
	{
		arr[0] = '0';
		arr[1] = '\0';
		return arr;
	}



	for (i = 0; num > 0; i++, num /= 2)
	{
		arr[i] = (num % 2 == 0) ? '0' : '1';
	}
	arr[i] = '\0';
	reverseStr(arr);
	return arr;
}

int bin2int(char* arr)
{
	int sum = 0, base = 1, i, length = strlen(arr);

	for (i = length - 1; i >= 0; i--)
	{
		if (arr[i] == '1')
		{
			sum += base;
		}
		base *= 2;
	}

	return sum;
}

int check_sequence(char* arr)
{
	int i = 0;

	if (arr[0] == '-')
		i++;

	for (; arr[i] != '\0'; i++)
	{
		if (arr[i] != '0' && arr[i] != '1')
			return 0;
	}
	return 1;
}
