#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int isNumber(char* str);
int isString(char* str);

int main(int argc, char* argv[])
{
	if(isNumber(argv[1]) == 1 && isString(argv[2]) == 1)
	{
		printf("%s %s\n", argv[1], argv[2]);
	}
	else if(isNumber(argv[2]) == 1 && isString(argv[1]) == 1)
	{
		printf("%s %s\n", argv[1], argv[2]);
	}
	else{
		printf("Eror\n");
	}

	return 0;
}

int isString(char* str)
{
	int i;

	if(strlen(str) == 0)
		return 0;

	for(i = 0; i < strlen(str); i++)
	{
		if(isalpha(str[i]) == 0)
			return 0;
	}

	return 1;
}

int isNumber(char* str)
{
	int i;

	if(strlen(str) == 0)
		return 0;

	for(i = 0; i < strlen(str); i++)
	{
		if(isdigit(str[i]) == 0)
			return 0;
	}

	return 1;
}