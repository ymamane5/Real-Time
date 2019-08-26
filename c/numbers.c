#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int* convert_to_array(int, int*);
int palindrom(int num);
int is_ascending(int num);
int* num_divisors(int num, int* arrSize);
int isPerfect(int num);
int reverse(int num);
int isPrime(int num);


int main()
{
	int num;

	do {
		printf("please enter number\n");
		scanf("%d", &num);
		printf("\palindrom check = %d\nis_ascending = %d\n", palindrom(num), is_ascending(num));
		printf("isPerfect = %d\n", isPerfect(num));
		printf("reverse = %d\n", reverse(num));
		printf("isPrime = %d\n", isPrime(num));

	} while (num != -1);

}

int reverse(int num)
{
	int res = 0;

	num = abs(num);
	while (num > 0)
	{
		res *= 10;
		res += num % 10;
		num /= 10;
	}
	return res;
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

int* num_divisors(int num, int* arrSize)
{
	int i, j = 1, num_sqrt = ceilf(sqrt((double)num)), sum = 0;
	int* arr = malloc(num_sqrt * sizeof(int));

	arr[0] = 1;
	for (i = 2; i < num_sqrt; i++)
	{
		if (num % i == 0)
		{
			arr[j++] = i;
			arr[j++] = num / i;
		}
	}
	if (floorf(sqrt(num)) == sqrt(num))
		arr[j++] = sqrt((double)num);

	*arrSize = j;
	
	return arr;

	
}

int isPrime(int num)
{
	int i, num_sqrt = ceilf(sqrt((double)num));
	
	for (i = 2; i < num_sqrt; i++)
	{
		if (num % i == 0)
		{
			return 0;
		}
	}

	return 1;
}

int isPerfect(int num)
{
	int sum = 0, i, size, num_sqrt = ceilf(sqrt((double)num));
	int* arr = malloc(sizeof(int) * num_sqrt);
	
	arr = num_divisors(num, &size);
	
	for (i = 0; i < size; i++)
	{
		/*printf("%d ", arr[i]);*/
		sum += arr[i];
	}
	if (sum == num)
		return 1;
	else
		return 0;
}
