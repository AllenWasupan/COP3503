#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>

class Img {
public:
	struct Header
	{
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;
	};

	void LoadImg(string filename) {

		ifstream file(filename, ios_base::binary);

		if (file.is_open()) {
			file.read(&header.idLength, sizeof(header.idLength));
			file.read(&header.colorMapType, sizeof(header.colorMapType));
			file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
			file.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
			file.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
			file.read((char*)&header.colorMapDepth, sizeof(header.colorMapDepth));

			// Image Specs
			file.read((char*)&header.xOrigin, sizeof(header.xOrigin));
			file.read((char*)&header.yOrigin, sizeof(header.yOrigin));
			file.read((char*)&header.width, sizeof(header.width));
			file.read((char*)&header.height, sizeof(header.height));
			file.read((char*)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
			file.read((char*)&header.imageDescriptor, sizeof(header.imageDescriptor));

		}
	}
	void WriteImg(string filename) {

	}
private:
	Header header;

};