#include<stdio.h>
#include<stdlib.h>
#include "bits.h"

int main()
{
	char x;
	int rotate, input;

	do {
		printf("Choose an action\n1. invert x\n2. rotate x\n");
		scanf("%d", &input);
		switch (input)
		{
			case 1: 
				printf("Please enter char\n");
				scanf("\n%c", &x);
				printf("x = ");
				char2bin(x);
				printf("x inverted = ");
				char2bin(*invertChar(x));
				break;

			case 2:
				printf("Please enter char\n");
				scanf("\n%c", &x);
				printf("Enter positions to rotate:\n");
				scanf("%d", &rotate);
				printf("x = ");
				char2bin(x);
				printf("x rotated = ");
				char2bin(*rotateN(x, rotate));
				break;
		}
	}
	while (input < 3 && input > 0);
	
	return 0;
}




