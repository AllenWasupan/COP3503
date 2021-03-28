#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
using namespace std;
typedef unsigned int uint;
typedef unsigned char uchar;

uint Convertcharint(uchar _uchar) {
	return (uint)(_uchar - '\0');
}

uchar Convertintchar(uint _uint) {
	return (uchar)(_uint + '\0');
}

float scale(float num) {
	num += .5f;
	return num;
}

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

	struct Pixel {
		char blue, green, red;
		uint bint, gint, rint;
	};

private:
	Header header;
	Pixel pixel;
	vector<Pixel> pvec;

public:

	void Load(string filename) {

		ifstream file(filename, ios_base::binary);

		if (file.is_open()) {
			file.read(&header.idLength, sizeof(header.idLength));
			file.read(&header.colorMapType, sizeof(header.colorMapType));
			file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
			file.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
			file.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
			file.read((char*)&header.colorMapDepth, sizeof(header.colorMapDepth));

			file.read((char*)&header.xOrigin, sizeof(header.xOrigin));
			file.read((char*)&header.yOrigin, sizeof(header.yOrigin));
			file.read((char*)&header.width, sizeof(header.width));
			file.read((char*)&header.height, sizeof(header.height));
			file.read((char*)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
			file.read((char*)&header.imageDescriptor, sizeof(header.imageDescriptor));

			uint pcount = header.width * header.height;

			for (uint i = 0; i < pcount; i++) {
				Pixel pixel;
				file.read((char*)&pixel.blue, sizeof(pixel.blue));
				file.read((char*)&pixel.green, sizeof(pixel.green));
				file.read((char*)&pixel.red, sizeof(pixel.red));

				pixel.bint = Convertcharint(pixel.blue);
				pixel.gint = Convertcharint(pixel.green);
				pixel.rint = Convertcharint(pixel.red);

				pvec.push_back(pixel);
			}
		}
	}

	void write(string filename) {
		
		ofstream file(filename, ios::binary);

		if (file.is_open()) {
			file.write(&header.idLength, sizeof(header.idLength));
			file.write(&header.colorMapType, sizeof(header.colorMapType));
			file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
			file.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
			file.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
			file.write((char*)&header.colorMapDepth, sizeof(header.colorMapDepth));

			file.write((char*)&header.xOrigin, sizeof(header.xOrigin));
			file.write((char*)&header.yOrigin, sizeof(header.yOrigin));
			file.write((char*)&header.width, sizeof(header.width));
			file.write((char*)&header.height, sizeof(header.height));
			file.write((char*)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
			file.write((char*)&header.imageDescriptor, sizeof(header.imageDescriptor));


			for (uint i = 0; i < pvec.size(); i++) {

				Pixel pixel = pvec[i];
				file.write((char*)&pixel.blue, 1);
				file.write((char*)&pixel.green, 1);
				file.write((char*)&pixel.red, 1);
			}

			file.close();
		}
	}

	void setHeader(Img::Header& data)
	{
		header.idLength = data.idLength;
		header.colorMapType = data.colorMapType;
		header.dataTypeCode = data.dataTypeCode;
		header.colorMapOrigin = data.colorMapOrigin;
		header.colorMapDepth = data.colorMapDepth;
		header.xOrigin = data.xOrigin;
		header.yOrigin = data.yOrigin;
		header.width = data.width;
		header.height = data.height;
		header.bitsPerPixel = data.bitsPerPixel;
		header.imageDescriptor = data.imageDescriptor;

	}

	Header getHeader() {
		return header;
	}

	void setPixel() {

		for (uint i = 0; i < pvec.size(); i++) {
			pvec[i].rint = Convertcharint(pvec[i].red);
			pvec[i].gint = Convertcharint(pvec[i].green);
			pvec[i].bint = Convertcharint(pvec[i].blue);
		}
	}

	Pixel getPixel() {
		return pixel;
	}

	vector<Pixel> getPvec() {
		return pvec;
	}

	void setPvec(vector<Pixel>& vec) {

		for (uint i = 0; i < vec.size(); i++) {
			pvec.push_back(vec[i]);
		}
	}

};


Img Multiblend(Img &a, Img &b) {
	//C is the new image
	Img c;
	//Sets pattern one as the base
	Img::Header tempheader = a.getHeader();
	c.setHeader(tempheader);

	//Sets pixels for examination
	a.setPixel();
	b.setPixel();

	//gets the pixel vectors
	vector<Img::Pixel> avec = a.getPvec();
	vector<Img::Pixel> bvec = b.getPvec();

	//Preps new pixel vec
	vector<Img::Pixel> cvec;

	//Loops to set the new values
	for (uint i = 0; i < avec.size(); i++) {
		//Makes a new pixel
		Img::Pixel cpix;

		//Multiplies red from both images and sets it back down
		uint rint = (uint) (scale(avec[i].rint * bvec[i].rint / 255.0f));
		uchar  rchar = Convertintchar(rint);
		cpix.red = rchar;


		uint bint = (uint)(scale((avec[i].bint * bvec[i].bint) / 255.0f));
		uchar  bchar = Convertintchar(bint);
		cpix.blue = bchar;


		uint gint = (uint)(scale((avec[i].gint * bvec[i].gint) / 255.0f));
		uchar  gchar = Convertintchar(gint);
		cpix.green = gchar;
		

		cvec.push_back(cpix);
	}
	
	c.setPvec(cvec);
	
	return c;
}

uint pabs(int num) {
	if (num < 0) {
		num = 0;
	}
	else if (num > 255) {
		num = 255;
	}
	return (uint)num;
}

Img Subblend(Img& a, Img& b) {
	//C is the new image
	Img c;
	//Sets pattern one as the base
	Img::Header tempheader = a.getHeader();
	c.setHeader(tempheader);

	//Sets pixels for examination
	a.setPixel();
	b.setPixel();

	//gets the pixel vectors
	vector<Img::Pixel> avec = a.getPvec();
	vector<Img::Pixel> bvec = b.getPvec();

	//Preps new pixel vec
	vector<Img::Pixel> cvec;

	//Loops to set the new values
	for (uint i = 0; i < avec.size(); i++) {
		//Makes a new pixel
		Img::Pixel cpix;

		//Multiplies red from both images and sets it back down
		int rint = bvec[i].rint - avec[i].rint;
		uchar  rchar = Convertintchar(pabs(rint));
		cpix.red = rchar;


		int bint = bvec[i].bint - avec[i].bint;
		uchar  bchar = Convertintchar(pabs(bint));
		cpix.blue = bchar;


		int gint = bvec[i].gint - avec[i].gint;
		uchar  gchar = Convertintchar(pabs(gint));
		cpix.green = gchar;


		cvec.push_back(cpix);
	}

	c.setPvec(cvec);

	return c;
}

uint inverter(float mode, uint a, uint b) {

	//Mode is for either Screen blend or overlay blend
	//inv inverts both the uints, and blends
	float inv = 1.0f - (mode * ((1.0f - (((float)(a) / 255.0f))) * ((1.0f - ((float)(b) / 255.0f)))));
	//num resets the values so they can be used
	uint num = (uint) scale(inv * 255.0f);
	return num;
}

Img Screenblend(Img& a, Img& b) {
	//C is the new image
	Img c;
	//Sets pattern one as the base
	Img::Header tempheader = a.getHeader();
	c.setHeader(tempheader);

	//Sets pixels for examination
	a.setPixel();
	b.setPixel();

	//gets the pixel vectors
	vector<Img::Pixel> avec = a.getPvec();
	vector<Img::Pixel> bvec = b.getPvec();

	//Preps new pixel vec
	vector<Img::Pixel> cvec;

	//Loops to set the new values
	for (uint i = 0; i < avec.size(); i++) {
		//Makes a new pixel
		Img::Pixel cpix;

		//Multiplies red from both images and sets it back down

		uint rint = inverter(1.0, avec[i].rint,bvec[i].rint);
		uchar  rchar = Convertintchar(rint);
		cpix.red = rchar;


		uint bint = inverter(1.0, avec[i].bint, bvec[i].bint);
		uchar  bchar = Convertintchar(bint);
		cpix.blue = bchar;


		uint gint = inverter(1.0, avec[i].gint, bvec[i].gint);
		uchar  gchar = Convertintchar(gint);
		cpix.green = gchar;


		cvec.push_back(cpix);
	}

	c.setPvec(cvec);

	return c;
}

Img Overblend(Img& a, Img& b) {
	//C is the new image
	Img c;
	//Sets pattern one as the base
	Img::Header tempheader = a.getHeader();
	c.setHeader(tempheader);

	//Sets pixels for examination
	a.setPixel();
	b.setPixel();

	//gets the pixel vectors
	vector<Img::Pixel> avec = a.getPvec();
	vector<Img::Pixel> bvec = b.getPvec();

	//Preps new pixel vec
	vector<Img::Pixel> cvec;

	//Loops to set the new values
	for (uint i = 0; i < avec.size(); i++) {
		//Makes a new pixel
		Img::Pixel cpix;

		//Multiplies red from both images and sets it back down

		uint rint = inverter(1.0, avec[i].rint, bvec[i].rint);
		uchar  rchar = Convertintchar(rint);
		cpix.red = rchar;


		uint bint = inverter(1.0, avec[i].bint, bvec[i].bint);
		uchar  bchar = Convertintchar(bint);
		cpix.blue = bchar;


		uint gint = inverter(1.0, avec[i].gint, bvec[i].gint);
		uchar  gchar = Convertintchar(gint);
		cpix.green = gchar;


		cvec.push_back(cpix);
	}

	c.setPvec(cvec);

	return c;
}

Img addcolor(Img &a, int red, int blue, int green) {
	//C is the new image
	Img c;
	//Sets pattern one as the base
	Img::Header tempheader = a.getHeader();
	c.setHeader(tempheader);

	//Sets pixels for examination
	a.setPixel();

	//gets the pixel vectors
	vector<Img::Pixel> avec = a.getPvec();

	//Preps new pixel vec
	vector<Img::Pixel> cvec;

	//Loops to set the new values
	for (uint i = 0; i < avec.size(); i++) {
		//Makes a new pixel
		Img::Pixel cpix;

		//Multiplies red from both images and sets it back down
		int rint = avec[i].rint + red;
		uchar  rchar = Convertintchar(pabs(rint));
		cpix.red = rchar;


		int bint =  avec[i].bint + blue;
		uchar  bchar = Convertintchar(pabs(bint));
		cpix.blue = bchar;


		int gint = avec[i].gint + green;
		uchar  gchar = Convertintchar(pabs(gint));
		cpix.green = gchar;


		cvec.push_back(cpix);
	}

	c.setPvec(cvec);

	return c;
}

Img multcolor(Img& a, int red, int blue, int green) {
	//C is the new image
	Img c;
	//Sets pattern one as the base
	Img::Header tempheader = a.getHeader();
	c.setHeader(tempheader);

	//Sets pixels for examination
	a.setPixel();

	//gets the pixel vectors
	vector<Img::Pixel> avec = a.getPvec();

	//Preps new pixel vec
	vector<Img::Pixel> cvec;

	//Loops to set the new values
	for (uint i = 0; i < avec.size(); i++) {
		//Makes a new pixel
		Img::Pixel cpix;

		//Multiplies red from both images and sets it back down
		int rint = avec[i].rint * red;
		uchar  rchar = Convertintchar(pabs(rint));
		cpix.red = rchar;


		int bint = avec[i].bint * blue;
		uchar  bchar = Convertintchar(pabs(bint));
		cpix.blue = bchar;


		int gint = avec[i].gint * green;
		uchar  gchar = Convertintchar(pabs(gint));
		cpix.green = gchar;


		cvec.push_back(cpix);
	}

	c.setPvec(cvec);

	return c;
}

Img channelcolor(Img& a, int channel) {
	//C is the new image
	Img c;
	//Sets pattern one as the base
	Img::Header tempheader = a.getHeader();
	c.setHeader(tempheader);

	//Sets pixels for examination
	a.setPixel();

	//gets the pixel vectors
	vector<Img::Pixel> avec = a.getPvec();

	//Preps new pixel vec
	vector<Img::Pixel> cvec;

	//Loops to set the new values
	for (uint i = 0; i < avec.size(); i++) {
		//Makes a new pixel
		Img::Pixel cpix;
		uchar val;

		if (channel == 1) {
			val = avec[i].red;
		}
		if (channel == 2) {
			val = avec[i].blue;
		}
		if (channel == 3) {
			val = avec[i].green;
		}

		cpix.red = val;
		cpix.blue = val;
		cpix.green = val;


		cvec.push_back(cpix);
	}

	c.setPvec(cvec);

	return c;
}

Img reversechannel(Img& a, Img& b, Img& c) {
	//C is the new image
	Img d;
	//Sets pattern one as the base
	Img::Header tempheader = a.getHeader();
	d.setHeader(tempheader);

	//Sets pixels for examination
	a.setPixel();
	b.setPixel();
	c.setPixel();

	//gets the pixel vectors
	vector<Img::Pixel> avec = a.getPvec();
	vector<Img::Pixel> bvec = b.getPvec();
	vector<Img::Pixel> cvec = c.getPvec();

	//Preps new pixel vec
	vector<Img::Pixel> dvec;

	//Loops to set the new values
	for (uint i = 0; i < avec.size(); i++) {
		//Makes a new pixel
		Img::Pixel dpix;

		dpix.red = avec[i].red;

		dpix.blue = bvec[i].blue;

		dpix.green = cvec[i].green;

		dvec.push_back(dpix);
	}

	d.setPvec(dvec);

	return d;
}

Img flipper(Img& a) {
	//C is the new image
	Img c;
	//Sets pattern one as the base
	Img::Header tempheader = a.getHeader();
	c.setHeader(tempheader);

	//Sets pixels for examination
	a.setPixel();

	//gets the pixel vectors
	vector<Img::Pixel> avec = a.getPvec();

	//Preps new pixel vec
	vector<Img::Pixel> cvec;

	//Loops to set the new values
	for (uint i = 0; i < avec.size(); i++) {
		//Makes a new pixel
		Img::Pixel cpix;

		//Multiplies red from both images and sets it back down
		int rint = avec[i].rint;
		uchar  rchar = Convertintchar(pabs(rint));
		cpix.red = rchar;


		int bint = avec[i].bint;
		uchar  bchar = Convertintchar(pabs(bint));
		cpix.blue = bchar;


		int gint = avec[i].gint;
		uchar  gchar = Convertintchar(pabs(gint));
		cpix.green = gchar;


		cvec.push_back(cpix);
	}

	c.setPvec(cvec);

	return c;
}