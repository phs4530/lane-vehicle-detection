#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>

#include "set_up.h"

using namespace cv;
using namespace std;


int main( int argc, char** argv )
{
	String imageName("C:/image/sample_image.jpg"); // by default
	if (argc > 1)
	{
		imageName = argv[1];
	}

	COLOR_image = imread(imageName, IMREAD_COLOR); // Read the file
	set_up(COLOR_image, 0.13, 0.2);

	Canny(ROI_image, GRAY_edges, 50, 120);

	float angle, x1, y1, x2, y2;

	vector<Vec4i> lines;

	HoughLinesP(GRAY_edges, lines, 1, CV_PI / 180, 30, 100, 10);


	//////////
	/*
	for (int i = 0 ; i < lines.size(); i++)
	{
		Vec4i Line = lines[i];
		Vec4i L_Line, R_Line;

		// check line left, right
		x1 = Line[0];	y1 = Line[1];	x2 = Line[2];	y2 = Line[3];
		angle = (y2 - y1) / (x2 - x1);
		angle *= 45;

		if (angle < 90 && angle > 50)			L_Line = Line;
		if (-90 < angle && angle < -50)		R_Line = Line;


		// draw line on image
		line(COLOR_image, Point(L_Line[0] + Horizontal * 0.13, L_Line[1] + vertical * 0.2), Point(L_Line[2] + Horizontal * 0.13, L_Line[3] + vertical * 0.2), Scalar(0, 0, 255), 2);
		line(COLOR_image, Point(R_Line[0] + Horizontal * 0.13, R_Line[1] + vertical * 0.2), Point(R_Line[2] + Horizontal * 0.13, R_Line[3] + vertical * 0.2), Scalar(0, 255, 0), 2);
	}*/

	imshow("COLOR_image line", COLOR_image);
	imshow("GRAY_edges", GRAY_edges);

	waitKey(0); // Wait for a keystroke in the window

	return 0;
}
