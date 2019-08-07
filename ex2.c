#include<stdio.h>
#include<stdlib.h>

int* convert_to_array(int, int*);

int main()
{
printf("\nresult = %d\n",palindrom(32753));
}

int palindrom(int num)
{
int arr[11] = {0}, i = 0, lengh;
/*arr = (int*)malloc(11*sizeof(int));*/
/* convert to array */

convert_to_array(num, arr);
lengh = arr[10];

for(i=0; i<10; i++)
	{
	printf("%d ",arr[i]);
	}
/* check palindrom */
for(i=0; i<lengh/2; i++)
	{
	if(arr[i] != arr[lengh-1-i])
		return 0;
	}
return 1;
}

int* convert_to_array(int num, int* arr)
{
int lengh = 0, i = 0;

while(num > 0) 
{
	arr[i++] = num % 10;
	num /= 10;
	lengh++;
}
arr[10] = lengh;
return arr;
}
