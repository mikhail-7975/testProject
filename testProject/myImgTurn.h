#pragma once
#include "libbitmap.h"

class ImgTurn : public Bitmap {
public:
	int turn(double angle);
private: 
	int bufferLen;
	Bitmap bitmap;
	
	size_t computeArrPos(size_t x, size_t y);
	size_t stride(size_t width);

};