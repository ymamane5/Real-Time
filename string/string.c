#include<stdio.h>

int strcompare(char* s1, char* s2);
char* strcopy(char* s1, char* s2);
char* strconcat(char* s1, char* s2);

int main()
{
char s1[16] = "abcd";
char s2[16] = "ahd34";

printf("%d\n", strcompare(s1, s2));
printf("%s\n", strcopy(s1, s2));
printf("%s\n", strconcat(s1, s2));

}

int strcompare(char* s1, char* s2)
{
	int i;

	for(i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
	{
		if(s1[i] == s2[i])
			continue;
		else
			return s1[i] - s2[i];
	}  
	return 0;

}

char* strcopy(char* s1, char* s2)
{
	int i;
	
	for(i = 0; s2[i] != '\0'; i++)
	{
		s1[i] = s2[i];
	}
	s1[i] = '\0';
	return s1;

}

char* strconcat(char* s1, char* s2)
{
	int i, index;

	for(index = 0; s1[index] != '\0'; index++);

	for(i = 0; s2[i] != '\0'; i++)
	{
		s1[index++] = s2[i];
	}
	s1[index] = '\0';

	return s1;

}


/*
cmp
copy 
cat
*/

