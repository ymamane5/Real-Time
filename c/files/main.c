#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "files.h"

int main()
{
	FILE* fp;
	fp = fopen("test_file.txt", "r");
	int input, n, finish = 0;

	if (fp == NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}

	do {
		printf("choose action:\n1. last N lines\n2. remove spaces\n3. count letters\n4. count words\n5. exit");
		scanf("%d", &input);
		switch (input)
		{
		case 1: 
			printf("Enter number of last lines:\n");
			scanf("%d", &n);
			lastNLines(fp, n);
			break;
		case 2:
			removeSpaces(fp);
			printf("done. output file is noSpacesFile.txt\n");
			break;
		case 3:
			countletters(fp);
			break;
		case 4:
			countWords(fp);
			break;
		default:finish = 1;
			break;
		}
	} while (input < 5);
	
	fclose(fp);
	return 0;
}