#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib> 

using namespace cv;
using namespace std;

Mat COLOR_image;
Mat ROI_image;
Mat GRAY_image;
Mat binary_imageInv;
Mat binary_image;
Mat Dilate_binary;


 // int Horizontal = 640, vertical = 480;
int Horizontal = 1280, vertical = 720;


void set_up(Mat COLOR_image, double Horizontal_x, double vertical_y, double Horizontal_size, double vertical_size)
{
	ROI_image = COLOR_image(Rect(Horizontal*Horizontal_x, vertical*vertical_y, Horizontal*Horizontal_size, vertical*vertical_size));
	
	cvtColor(ROI_image, GRAY_image, CV_RGB2GRAY);

	threshold(GRAY_image, binary_image, 50, 255, CV_THRESH_BINARY);

	threshold(binary_image, binary_imageInv, 128, 255, cv::THRESH_BINARY_INV);

	dilate(binary_imageInv, Dilate_binary, cv::Mat(), Point(1,3), 2);
}