#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib> 

using namespace cv;
using namespace std;


void labeling(Mat Dilate_binary, double Horizontal_x, double vertical_y, double Horizontal_size, double vertical_size)
{

	Mat img_labels, stats, centroids;
	int numOfLables = connectedComponentsWithStats(Dilate_binary, img_labels, stats, centroids, 4, CV_32S);

	int i = 0;

	//라벨링 된 이미지에 각각 직사각형으로 둘러싸기 
	for (int j = 1; j < numOfLables; j++) {
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);

		int x = centroids.at<double>(j, 0); //중심좌표
		int y = centroids.at<double>(j, 1);

		if (width * height > 500 && width * height < 5000)
		{
			rectangle(COLOR_image, Point(left + Horizontal * Horizontal_x, top + vertical * vertical_y), Point(left + width + Horizontal * Horizontal_x, top + height + +vertical * vertical_y),
				Scalar(0, 0, 255), 3);
			i++;
			putText(COLOR_image, to_string(i), Point(left + 20 + Horizontal * Horizontal_x, top + 20 + vertical * vertical_y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
		}

		/*
		if (width * height > 500 && width * height < 5000)
		{
		rectangle(COLOR_image, Point(left + Horizontal * Horizontal_x, top + vertical * vertical_y), Point(left + width + +Horizontal * Horizontal_x, top + height + +vertical * vertical_y),
		Scalar(0, 0, 255), 2);
		i++;
		putText(COLOR_image, to_string(i), Point(left + 20 + Horizontal * Horizontal_x, top + 20 + vertical * vertical_y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
		}
		*/
//		return COLOR_image;
	}
}