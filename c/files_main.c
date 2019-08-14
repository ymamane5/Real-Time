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
void printDA(DA* da);

int main()
{
	FILE* fp;
	fp = fopen("test_file.txt", "r");

	if (fp == NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}
	
	lastNLines(fp, 2);
	//removeSpaces(fp);
	//countletters(fp);
	//countWords(fp);

	fclose(fp);
	//getch();

	return 0;
}

void countWords(FILE* fp)
{
	DA* da = createDA(2);
	char buff[MAX_WORD];
	int i;

	fseek(fp, 0, SEEK_SET);

	while (fscanf(fp, "%s", buff) > 0)
	{
		insert(da, buff);
		//printf("%s\n", buff);
	}

	for(i = da->index; i >= 0; i--)
	{
//		free(da->arr[i]->str);
//		free(da->arr[i]);
	}
//	free(da->arr);
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
		da->arr[da->index]->count = 0;

		strcpy((da->arr[da->index])->str, buff);
		printf("%s\n", (da->arr[da->index])->str);
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
			if (buff[i] <= 'z' && buff[i] >= 'A')
				arr[buff[i] - 'A']++;
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
		if(arr[i] < temp)
		{
			temp = arr[i];
		}
	}

	fseek(fp, temp, SEEK_SET);
	printf("last lines:\n");
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
