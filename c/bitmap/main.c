#include<stdio.h>
#include "bitmap.h"

int main()
{
	int size, input, bit;
	Bitmap* map;
	printf("Enter size of bits\n");
	do {
		scanf("%d", &size);
		map = createBitmap(size);
	} while (size < 0);
	
	do {
			printf("1. bitOn\n2. bitOff\n3. isBit\n4. print bits\n5. exit\n");
			scanf("%d", &input);

			switch (input)
			{
				case 1: {
					printf("Enter bit number to turn ON\n");
					scanf("%d", &bit);
					if (bitOn(map, bit) == 1)
						printf("operation successed\n");
					else
						printf("cannot turn on bit\n");
				}
					break;
				case 2: {
					printf("Enter bit number to turn OFF\n");
					scanf("%d", &bit);
					if (bitOff(map, bit) == 1)
						printf("operation successed\n");
					else
						printf("cannot turn off bit\n");
				}
					break;
				case 3: {
					printf("Enter bit number to see\n");
					scanf("%d", &bit);
					if (isBit(map, bit) == -1)
						printf("operation failed\n");
					else if (isBit(map, bit) == 0)
						printf("bit is OFF\n");
					else
						printf("bit is ON\n");										
				}
					break;
				case 4: printBitmap(map);
					break;
				default:
					break;
			}
		
	} 
	while (input > 0 && input < 5);

	destroyBitmap(map);
	return 0;
}