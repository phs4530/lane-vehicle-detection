#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>   


using namespace cv;
using namespace std;


int main( int argc, char** argv )
{	
	String imageName("C:/image/sample_image.jpg"); // by default
	if (argc > 1)
	{
		imageName = argv[1];
	}
	
	Mat COLOR_image;
	Mat GRAY_image;
	
	
	COLOR_image = imread(imageName, IMREAD_COLOR); // Read the file 
	GRAY_image = imread(imageName, IMREAD_GRAYSCALE);
	

	if (COLOR_image.empty() && GRAY_image.empty())                  // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	Mat COLOR_resize_image;
	Mat resize_image;
	Mat ROI_image;
	
	int Horizontal = 480, vertical = 480;
	
	resize(COLOR_image, COLOR_resize_image, Size(Horizontal, vertical));
	resize(GRAY_image, resize_image, Size(Horizontal, vertical));
	ROI_image = resize_image(Rect(0, vertical*0.4, Horizontal, vertical*0.6));


	Mat COLOR_edges;
	Mat GRAY_edges;
	Mat GRAY_edges2;


	//Canny(COLOR_image, COLOR_edges, 50, 100);
	Canny(ROI_image, GRAY_edges, 50, 120);
	//Canny(GRAY_image, GRAY_edges2, 50, 210);

	float angle, x1, y1, x2, y2;
	//float fx1, fy1, fx2, fy2;

	vector<Vec4i> lines;
	//vector<Vec4i> Filter_lines;
	HoughLinesP(GRAY_edges, lines, 1, CV_PI / 180, 30, 10, 20);

	
	//검출한 직선을 영상에 그려줍니다.
	for (int i = 0 ; i < lines.size(); i++)
	{
		Vec4i Line = lines[i];
		// Vec4i fitLines;

		x1 = Line[0];	y1 = Line[1];	x2 = Line[2];	y2 = Line[3];
		angle = (y2 - y1) / (x2 - x1);
		angle = abs(angle);
		angle *= 45;

		if (angle < 60)
		{
			lines[i] = NULL;
		}

		Line = lines[i];
		line(COLOR_resize_image, Point(Line[0], Line[1]+ vertical * 0.4), Point(Line[2], Line[3]+ vertical * 0.4),
			Scalar(0, 0, 255), 2);

		
		//fitLine(lines, fitLines,
		//	CV_DIST_L2, // 거리 유형
		//	0,   // L2 거리를 사용하지 않음
		//	0.01, 0.01); // 정확도
		//fx1 = fitLines[0];	fy1 = fitLines[1];	fx2 = fitLines[2];	fy2 = fitLines[3];
		//line(COLOR_resize_image, Point(fitLines[0], fitLines[1] + vertical * 0.4), Point(fitLines[2], fitLines[3] + vertical * 0.6),
		//	Scalar(0, 0, 255), 5, 10);
		

	}

	imshow("COLOR_resize_image", COLOR_resize_image);
	//imshow("COLOR_edges", COLOR_edges);
	imshow("GRAY_edges", GRAY_edges);
	//imshow("GRAY_edges2", GRAY_edges2);
	imshow("resize_image", resize_image);
	///imshow("ROI_image", ROI_image);

	waitKey(0); // Wait for a keystroke in the window
	
	return 0;
}

