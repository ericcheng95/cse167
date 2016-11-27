#pragma once
#include <cstdio>
using namespace std;

class Image
{
public:
	int width;
	int height;
	unsigned char* bgr;
	Image(char* filename)
	{
		FILE* f = fopen(filename, "rb");
		unsigned char info[54];
		fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
		width = *(int*)&info[18];
		height = *(int*)&info[22];
		int size = 3 * width * height;
		bgr = new unsigned char[size]; // allocate 3 bytes per pixel
		fread(bgr, sizeof(unsigned char), size, f); // read the rest of the data at once
		fclose(f);
	}
};
