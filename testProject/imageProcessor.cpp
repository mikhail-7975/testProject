#include "ImageProcessor.h"
#include <math.h>
#include <vector>

#include <iostream>

int ImageProcessor::turnImage(const std::string & inputName, const std::string & outName)
{
	if(upload(inputName)) return -1;
	int angle = computeAngle();
	//turn(angle);
	//save(outName);
	//return 0;
	return angle;
}

int ImageProcessor::upload(const std::string & name)
{
	if(bitmap.load(name) == false) return 1;
	return 0;
}

int ImageProcessor::save(const std::string & name)
{
	bitmap.save(name);
	return 0;
}

size_t getIndexMax(std::vector<double> a) {
	double max = 0;
	size_t index = 0;

	size_t j = 0;
	for (auto i : a) {
		if (i > max) {
			max = i;
			index = j;
		}
		++j;
	}
	return index;
}

double getDelta(std::vector<double> a) {
	double max = 0;
	double min = *a.begin();
	for (auto i : a) {
		if (i > max) max = i;
		if (i < min) min = i;
	}
	return max - min;
}

int ImageProcessor::computeAngle()
{
	int angle = 0;
	std::vector<double> delta;
	while (angle < 90) {
		std::cout << "angle: " << angle << std::endl;
		std::vector<double> midBright;
		for (int y = 0; y <= bitmap.m_height; y++) {
			midBright.push_back(computeMidBright(y, angle));
		}
		delta.push_back(getDelta(midBright));
		angle++;
	}
	return getIndexMax(delta);
}

int ImageProcessor::turn(int angle)
{
	return 0;
}

size_t ImageProcessor::computeArrPos(size_t x, size_t y)
{
	return 3 * x + y * stride(bitmap.m_width);
}

size_t ImageProcessor::stride(size_t w)
{
	return ((3 * w - 1) / 4 + 1) * 4;
}

size_t chooseMin(size_t a, size_t b) {
	if (a < b) return a;
	else return b;
}

double ImageProcessor::computeMidBright(size_t y, size_t angle)
{
	double bright = 0; 
	for (size_t x = 0; x < chooseMin(bitmap.m_height, bitmap.m_width); ++x) {
		size_t pos = computeArrPos(x, (static_cast<size_t>(y + x * tan(angle)) % bitmap.m_height));
		bright += (bitmap.m_buffer[pos] + bitmap.m_buffer[pos + 1] + bitmap.m_buffer[pos + 2]);
	}
	//return bright / (3 * bitmap.m_width);
	return bright;
}
