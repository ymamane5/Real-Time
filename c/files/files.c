#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "files.h"

void countWords(FILE* fp)
{
	DA* da = createDA(20);
	char buff[MAX_WORD];

	fseek(fp, 0, SEEK_SET);
	while (fscanf(fp, "%s", buff) > 0)
	{
		insert(da, buff);
	}
	printDA(da);
	destroyDA(da);
}

void destroyDA(DA* da)
{
	int i;

	for (i = da->index - 1; i >= 0; i--)
	{
		free(da->arr[i]->str);
		free(da->arr[i]);
	}
	free(da);
}

void insert(DA* da, char* buff)
{
	int i, addWord = 1;
	word_t** temp;

	for (i = 0; i < da->index; i++)
	{
		if (strcmp(buff, da->arr[i]->str) == 0)
		{
			da->arr[i]->count++;
			addWord = 0;
			break;
		}
	}

	if (addWord == 1)
	{
		if (da->index >= da->capacity)
		{
			printf("realloc\n");
			temp = realloc(da->arr, (da->capacity) + 3);
			if (temp != NULL)
			{
				da->arr = temp;
				(da->capacity) += 3;
			}
		}
		da->arr[da->index] = malloc(sizeof(word_t));
		da->arr[da->index]->str = malloc(sizeof(char) * strlen(buff));
		da->arr[da->index]->count = 1;

		strcpy((da->arr[da->index])->str, buff);
		da->index++;
	}
}

DA* createDA(int capacity)
{
	DA *da = malloc(sizeof(DA));
	if (da == NULL)
		return NULL;
	da->capacity = capacity;
	da->index = 0;
	da->arr = calloc(capacity, sizeof(word_t*));

	if (da->arr == NULL)
	{
		free(da);
		return NULL;
	}
	return da;
}

void countletters(FILE* fp)
{
	int arr[58] = { 0 }, i;
	char buff[MAX];

	fseek(fp, 0, SEEK_SET);
	while (fgets(buff, MAX, fp) != NULL)
	{
		for (i = 0; buff[i] != 0; i++)
		{
			if (buff[i] <= 'z' && buff[i] >= 'A')
				arr[buff[i] - 'A']++;
		}
	}

	printf("letters:\n");
	for (i = 0; i < 58; i++)
	{
		if (arr[i] > 0)
			printf("%c   %d\n", i + 65, arr[i]);
	}

}

void removeSpaces(FILE* fp)
{
	FILE* new_fp = fopen("noSpacesFile.txt", "w");
	char buff[MAX];
	int i;

	fseek(fp, 0, SEEK_SET);

	while (fgets(buff, MAX, fp) != NULL)
	{
		for (i = 0; buff[i] != 0; i++)
		{
			if (buff[i] != ' ')
				fprintf(new_fp, "%c", buff[i]);
		}
	}
	fclose(new_fp);

}

void lastNLines(FILE* fp, int n)
{
	int i = 0;
	long int* arr = (long int*)malloc(sizeof(int) * n);
	char buf[MAX];
	long int temp;

	fseek(fp, 0, SEEK_SET);

	while (1)
	{
		temp = ftell(fp);
		fgets(buf, MAX, fp);
		if (feof(fp))
			break;
		arr[i % n] = temp;
		i++;
	}


	for (i = 0; i < n; i++)
	{
		if (arr[i] < temp)
		{
			temp = arr[i];
		}
	}

	fseek(fp, temp, SEEK_SET);
	printf("last %d lines:\n", n);
	for (i = 0; i < n; i++)
	{
		fgets(buf, MAX, fp);
		printf("%s", buf);
	}

}

void printDA(DA* da)
{
	int i;

	for (i = 0; i < da->index; i++)
	{
		printf("%s   %d\n", da->arr[i]->str, da->arr[i]->count);
	}
}
