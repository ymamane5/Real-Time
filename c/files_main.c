#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 60 
#define MAX_WORD 20

typedef struct
{
	char* str;
	int count;
}word_t;

typedef struct DA
{
	word_t** arr;
	int capacity;
	int index;
}DA;

void lastNLines(FILE* fp, int n);
void removeSpaces(FILE* fp);
void countletters(FILE* fp);
void countWords(FILE* fp);
void insert(DA* da, char* buff);
DA* createDA(int capacity);

int main()
{
	FILE* fp;
	fopen_s(&fp, "lastRows.txt", "r");

	if (fp == NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}
	/*
		lastNLines(fp, 2);
		removeSpaces(fp);
		countletters(fp);
		*/
	countWords(fp);

	fclose(fp);
	getch();

	return 0;
}

void countWords(FILE* fp)
{
	DA* da = createDA(3);
	char buff[MAX_WORD];

	fseek(fp, 0, SEEK_SET);

	while (fscanf(fp, "%s", buff) > 0)
	{
		insert(da, buff);
		//printf("%s\n", buff);
	}

}



void insert(DA* da, char* buff)
{

	da->arr[da->index] = (word_t*)malloc(sizeof(word_t));
	da->arr[da->index]->str = malloc(sizeof(char) * strlen(buff));
	
	strcpy((da->arr[da->index])->str, buff);
	printf("da[%d] = %s\n",da->index, (da->arr[da->index])->str);
	da->index++;
}

DA* createDA(int capacity)
{
	DA *da = malloc(sizeof(DA));
	if (da == NULL)
		return NULL;
	da->capacity = capacity;
	da->index = 0;
	da->arr = malloc(sizeof(word_t*) * capacity);
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
	char buff[MAX], ch;

	fseek(fp, 0, SEEK_SET);
	while (fgets(buff, MAX, fp) != NULL)
	{
		for (i = 0; buff[i] != 0; i++)
		{
			if (buff[i] < 123 && buff[i] > 64)
				arr[buff[i] - 65]++;
		}
	}

	printf("array:\n");
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

	while (1)
	{
		arr[i % n] = ftell(fp);
		i++;
		if (fgets(buf, MAX, fp) == NULL)
			break;
	}
	fseek(fp, 0, SEEK_SET);
	printf("array:\n%ld\n%ld\n", arr[0], arr[1]);

	printf("last lines:\n");
	for (i = 0; i < n; i++)
	{
		fseek(fp, arr[i], SEEK_SET);
		fgets(buf, MAX, fp);
		printf("%s", buf);
		/*printf("%ld\n", arr[i]);*/
	}

}
