#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>   

#include "set_up.h"

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap1("C:/image/sample_video4.avi");

	if (!cap1.isOpened())
	{
		printf(" Can not open the vedio file \n");
	}

	while (1)
	{
		//read a frame from vedio
		cap1 >> COLOR_image;
		
		set_up(COLOR_image, 0.13, 0.2);

		float angle, x1, y1, x2, y2;


		 for (int i = 0; i < lines.size(); i++)
		{
			Vec4i Line = lines[i];
			Vec4i L_Line, R_Line;
			
			// check line left, right
			x1 = Line[0];	y1 = Line[1];	x2 = Line[2];	y2 = Line[3];
			angle = (y2 - y1) / (x2 - x1);
			angle *= 45;

			if ( angle < 90 && angle > 50 )			L_Line = Line;
			if ( -90 < angle && angle < -50 )		R_Line = Line;

			// draw line on image
			line(COLOR_image, Point(L_Line[0] + Horizontal * 0.13, L_Line[1] + vertical * 0.2), Point(L_Line[2] + Horizontal * 0.13, L_Line[3] + vertical * 0.2), Scalar(0, 0, 255), 2);
			line(COLOR_image, Point(R_Line[0] + Horizontal * 0.13, R_Line[1] + vertical * 0.2), Point(R_Line[2] + Horizontal * 0.13, R_Line[3] + vertical * 0.2), Scalar(0, 255, 0), 2);

			// Default
			// line(COLOR_image, Point(L_Line[0], L_Line[1]), Point(L_Line[2], L_Line[3]), Scalar(0, 0, 255), 2);
			// line(COLOR_image, Point(R_Line[0], R_Line[1]), Point(R_Line[2], R_Line[3]), Scalar(0, 255, 0), 2);
		}
		

		imshow("COLOR_image", COLOR_image);
		imshow("bila_Filter", bila_Filter);
		imshow("GRAY_edges", GRAY_edges);
		
		//30ms 정도 대기하도록 해야 동영상이 너무 빨리 재생되지 않음.
		if (waitKey(20) == 27) break; // ESC to end
	}
	return 0;
}