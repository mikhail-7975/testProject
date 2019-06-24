#include <iostream>
#include "imageProcessor.h"
#include "myImgTurn.h"

#include <opencv2/opencv.hpp>

double compute_skew(const char* filename)
{
	// Load in grayscale.
	cv::Mat img = cv::imread(filename, 0);

	// Binarize
	cv::threshold(img, img, 225, 255, cv::THRESH_BINARY);

	// Invert colors
	cv::bitwise_not(img, img);

	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 3));
	cv::erode(img, img, element);

	std::vector<cv::Point> points;
	cv::Mat_<uchar>::iterator it = img.begin<uchar>();
	cv::Mat_<uchar>::iterator end = img.end<uchar>();
	for (; it != end; ++it)
		if (*it)
			points.push_back(it.pos());

	cv::RotatedRect box = cv::minAreaRect(cv::Mat(points));

	double angle = box.angle;
	if (angle < -45.)
		angle += 90.;

	cv::Point2f vertices[4];
	box.points(vertices);
	for (int i = 0; i < 4; ++i)
		cv::line(img, vertices[i], vertices[(i + 1) % 4], cv::Scalar(255, 0, 0), 1, 16);

	std::cout << "File " << filename << ": " << angle << std::endl;

	return angle;
}

void deskew(const char* filename, double angle)
{
	cv::Mat img = cv::imread(filename, 0);

	cv::bitwise_not(img, img);

	std::vector<cv::Point> points;
	cv::Mat_<uchar>::iterator it = img.begin<uchar>();
	cv::Mat_<uchar>::iterator end = img.end<uchar>();
	for (; it != end; ++it)
		if (*it)
			points.push_back(it.pos());

	cv::RotatedRect box = cv::minAreaRect(cv::Mat(points));

	cv::Mat rot_mat = cv::getRotationMatrix2D(box.center, angle, 1);

	cv::Mat rotated;
	cv::warpAffine(img, rotated, rot_mat, img.size(), cv::INTER_CUBIC);

	cv::Size box_size = box.size;
	if (box.angle < -45.)
		std::swap(box_size.width, box_size.height);
	cv::Mat cropped;
	cv::getRectSubPix(rotated, box_size, box.center, cropped);

	//cv::imshow("Cropped", rotated);

	cv::bitwise_not(rotated, rotated);
	
	cv::imwrite("out.bmp", rotated);
}

int main() {
	
	deskew("text.bmp",compute_skew("text.bmp"));
}