#include <iostream>
#include "imageProcessor.h"
#include "myImgTurn.h"


int main() {
	/*mageProcessor imgPr;
	int f = imgPr.turnImage("text.bmp", "out.bmp"); 
	std::cout << "angle == " << f << std::endl;
	system("pause");
	return 0; */

	ImgTurn A;
	A.load("kitty-24.bmp");
	A.turn(10 * 3.14 / 180);
	system("pause");
}