#ifndef BITMAP
#define BITMAP

typedef struct
{
	int m_size;
	unsigned char* m_arr;
}Bitmap;

Bitmap* createBitmap(int size);
void destroyBitmap(Bitmap* map);
int bitOn(Bitmap* map, int location);
int bitOff(Bitmap* map, int location);
int isBit(Bitmap* map, int location);
void printBitmap(Bitmap* map);
#endif