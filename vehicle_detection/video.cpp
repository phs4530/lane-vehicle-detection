#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>   

#include "set_up.h"
#include "labeling.h"

using namespace cv;
using namespace std;

double Horizontal_x = 0.13;
double vertical_y = 0.3;


int main(int argc, char** argv)
{
	VideoCapture cap1("C:/image/sample_vedio1.mp4");

	if (!cap1.isOpened())
	{
		printf(" Can not open the vedio file \n");
	}

	while (1)
	{
		cap1 >> COLOR_image;
		set_up(COLOR_image, Horizontal_x, vertical_y, 0.54, 0.5);
		labeling(Dilate_binary, Horizontal_x, vertical_y, 0.54, 0.5);
		
		imshow("COLOR_image", COLOR_image);
		imshow("GRAY_image", GRAY_image);
		imshow("binary_imageInv", binary_imageInv);
		imshow("Dilate_binary", Dilate_binary);

		if (waitKey(20) == 27) break; // ESC to end
	}
	return 0;
}