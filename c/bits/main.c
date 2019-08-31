#include<stdio.h>
#include<stdlib.h>
#include "bits.h"

int main()
{
	char x, y;
	int rotate, input, n, p, w, i, j, value, res;

	do {
		printf("Choose an action\n1. invert x\n2. rotate x\n3. set bits\n4. setbits (integer)\n5. exit\n");
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
			case 3:
				printf("Please enter char\n");
				scanf("\n%c", &x);
				printf("Enter second char\n");
				scanf("\n%c", &y);
				printf("Enter num of bits to replace:\n");
				scanf("\n%d", &n);
				printf("Enter start position:\n");
				scanf("\n%d", &p);
				printf("x = \n");
				char2bin(x);
				printf("y = \n");
				char2bin(y);
				if(setbits(&x, p, n, y) == 1){
					printf("final x = \n");
					char2bin(x);
				}
				else{
					printf("illegal parameters\n");
				}	
				break;
			case 4:
				printf("Please enter positive number\n");
				scanf("\n%d", &w);
				printf("Enter higher location\n");
				scanf("\n%d", &i);
				printf("Enter lower location:\n");
				scanf("\n%d", &j);
				printf("Enter bit value (0 or 1):\n");
				scanf("\n%d", &value);
				res = setbits2(w, i, j, value);
				if(res != 0)
				{
					printf("number = \n");
					int2bin(w);				
					printf("new number = \n");
					int2bin(res);
				}
				else{
					printf("illegal parameters\n");
				}	
				break;
			default:
				break;
		}
	}
	while (input < 5 && input > 0);

	return 0;
}
