#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int* convert_to_array(int, int*);
int palindrom(int num);
int is_ascending(int num);
int* num_divisors(int num, int* divisors_count);


int main()
{
	int num;

	do {
		printf("please enter number\n");
		scanf("%d", &num);
		printf("\palindrom check = %d\nis_ascending = %d\n", palindrom(num), is_ascending(num));
	} while (num != -1);

}

int palindrom(int num)
{
	int arr[11] = { 0 }, i = 0, length;

	convert_to_array(num, arr);
	length = arr[10];

	/* check palindrom */
	for (i = 0; i < length / 2; i++)
	{
		if (arr[i] != arr[length - 1 - i])
			return 0;
	}
	return 1;
}

int* convert_to_array(int num, int* arr)
{
	int lengh = 0, i = 0;

	while (num > 0)
	{
		arr[i++] = num % 10;
		num /= 10;
		lengh++;
	}
	arr[10] = lengh;
	return arr;
}

int is_ascending(int num)
{
	int prev;
	
	do {
		prev = num % 10;
		num /= 10;
		if ((num % 10) > prev)
			return 0;
	} while (num > 0);

	return 1;

}

int* num_divisors(int num, int* divisors_count)
{
	int i, j = 0, num_sqrt = (int)sqrt((double)num);
	int* arr = malloc(num_sqrt * sizeof(int));

	for (i = 2; i < num_sqrt; i++)
	{
		if (num % i == 0)
		{
			arr[j++] = i;
			arr[j++] = num / i;
		}
	}
	if (sqrt((double)num) - (int)sqrt((double)num) == 0)
		arr[j++] = sqrt((double)num);

	*divisors_count = j;
	return arr;
}
