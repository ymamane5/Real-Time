#include<stdio.h>
#include<string.h>

#define SIZE 16

char* squeez(char* s1, char* s2);
int location(char* s1, char* s2);

int main()
{
	char s1[SIZE] = "ABBCDQRRQQQCTT", s2[SIZE] = "QR";
	
	printf("s1 = %s\ns2 = %s\n", s1, s2);
	printf("location: %d\n", location(s1, s2));
	printf("squeezed: %s\n", squeez(s1, s2));

	return 0;
}

int location(char* s1, char* s2)
{
	int i, j;

	if (strlen(s1) == 0 || strlen(s2) == 0)
		return -1;

	for (i = 0; i <= strlen(s1); i++)
	{
		j = 1;
		if (s1[i] == s2[0])
		{
			while (s1[i + j] == s2[j] && s1[i + j] != '\0')
				j++;
			if (s2[j] == '\0')
				return i;
		}
	}
	return -1;
}

char* squeez(char* s1, char* s2)
{
	int i, j, first_index, differ, finish = 0;
	char temp, toDelete;

	if(s1 == null || s2 == null)
		return null;
	
	toDelete = s2[0];
	for (i = 1; i < strlen(s2); i++)
	{
		for (j = 0; j < strlen(s1); j++)
		{
			if (s1[j] == s2[i])
				s1[j] = toDelete;
		}
	}
	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i++] == toDelete)
		{
			first_index = i - 1;
			while (s1[i] == toDelete)
				i++;

			differ = i - first_index;
			for (j = 0; s1[first_index + differ] != '\0'; j++)
			{
				s1[first_index++] = s1[first_index + differ];
			}
			s1[first_index] = '\0';
		}
	}
	return s1;
}
