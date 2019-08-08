#include<stdio.h>
#include<string.h>

char* squeez(char* s1, char* s2);

int main()
{
	char s1[8] = "ABBCD", s2[8] = "QB";
	printf("%s\n", squeez(s1, s2));

	return 0;
}

char* squeez(char* s1, char* s2)
{
	int i, j, first_index, differ, finish = 0;
	char temp, toDelete;

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
			for (j = 0; j < differ; j++)
			{
				s1[first_index] = s1[first_index + differ];
				if (s1[first_index + differ] == '\0')
				{
					i = first_index;
					break;
				}

				first_index++;
			}
			s1[first_index] = '\0';
		}
	}
	return s1;
}
