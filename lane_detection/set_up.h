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
Mat bila_Filter;
Mat GRAY_edges;

int Horizontal = 640, vertical = 480;
vector<Vec4i> lines;

void set_up(Mat COLOR_image, double Horizontal_size, double vertical_size) {

	ROI_image = COLOR_image(Rect(Horizontal*Horizontal_size, vertical*vertical_size, Horizontal*(0.87 - Horizontal_size), vertical*(1 - vertical_size)));
	cvtColor(ROI_image, GRAY_image, CV_RGB2GRAY);
	bilateralFilter(GRAY_image, bila_Filter, 5, 500, 10);

	Canny(bila_Filter, GRAY_edges, (COLOR_image.rows + COLOR_image.cols) / 16, (COLOR_image.rows + COLOR_image.cols) / 8);



	// detecting line (,,,,,minLength, maxGap)
	HoughLinesP(GRAY_edges, lines, 1, CV_PI / 180, 30, 100, 10);
}

void check_direction(int i)
{


}


void draw_image()
{


}