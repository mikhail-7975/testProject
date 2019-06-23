#pragma once

#include "libbitmap.h"
#include <string>

class ImageProcessor
{
public:

	ImageProcessor() = default;
	~ImageProcessor() = default;

	int turnImage(const std::string &inputName, const std::string &outName);

private:
	int upload(const std::string & name);
	int save(const std::string &name);
	int computeAngle();
	int turn(int angle);

	size_t computeArrPos(size_t x, size_t y);
	size_t stride(size_t width);

	double computeMidBright(size_t y, size_t angle); //compute middle bright in one string of pixels

	Bitmap bitmap;
};

