#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>   

#include "set_up.h"

using namespace cv;
using namespace std;

Mat COLOR_image;
Mat ROI_image;
Mat GRAY_image;
Mat binary_image;
Mat img_binary;

int main(int argc, char** argv)
{
	String imageName("C:/image/vehicle1.jpg"); // by default

	if (argc > 1)
	{
		imageName = argv[1];
	}

	COLOR_image = imread(imageName, IMREAD_COLOR);
	cvtColor(COLOR_image, GRAY_image, CV_RGB2GRAY);
	threshold(GRAY_image, binary_image, 30, 255, CV_THRESH_BINARY);

	

	imshow("COLOR_image", COLOR_image);
	imshow("GRAY_image", GRAY_image);
	imshow("binary_image", binary_image);
	imshow("img_labels", img_labels);

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}