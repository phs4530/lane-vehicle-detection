#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>   


using namespace cv;
using namespace std;

int Horizontal = 640, vertical = 480;
int sv_Hor = 0.26;

int main(int argc, char** argv)
{
	//������ ���Ϸκ��� ���� ������ �о���� ���� �غ�
	VideoCapture cap1("C:/image/sample_video.avi");

	if (!cap1.isOpened())
	{
		printf("������ ������ ���� �����ϴ�. \n");
	}

	//������ �÷��̽� ũ�⸦ ����
	// cap1.set(CAP_PROP_FRAME_WIDTH, Horizontal);
	// cap1.set(CAP_PROP_FRAME_HEIGHT, vertical);

	Mat COLOR_edges;
	Mat COLOR_image;
	Mat GRAY_image;
	Mat ROI_image;
	Mat GRAY_edges;
	Mat bila_Filter;

	//CvRNG rng = cvRNG(-1);
	//int count = cvRandInt(&rng) % 100 + 1;
	//CvPoint pt1, pt2;
	//CvPoint* points = new CvPoint[count];
	//CvMat pointMat = cvMat(1, count, CV_32SC2, points);




	for (;;)
	{
		//ķ���κ��� �� �������� �о��
		cap1 >> COLOR_image;
		ROI_image = COLOR_image(Rect(Horizontal*0.13, vertical*0.3, Horizontal*0.74, vertical*0.7));
		
		
		cvtColor(ROI_image, GRAY_image, CV_RGB2GRAY);
		bilateralFilter(GRAY_image, bila_Filter, 5, 250, 10);
			
		//detect edges;   
		Canny(bila_Filter, GRAY_edges, 50, 120);
		
		// ���� �ݺ������� ���� ���� �ִ� ���� ��ǥ�� cv::Points�� std::vector�� ����
		/*
		vector<Point> points;
		// ��� �� ��ġ�� ��� ��ȯ ȭ�� ��ȸ
		for (int y = 0; y < GRAY_edges.rows; y++) { // y��
			uchar* rowPtr = GRAY_edges.ptr<uchar>(y);
			for (int x = 0; x < GRAY_edges.cols; x++) { // x��
													 // �ܰ����� �ִٸ�
				if (rowPtr[x]) {
					points.push_back(cv::Point(x, y));


				}
			}
		}
		
		// cv::fitLine�� ȣ���� ���� ������ ���� ã��
		cv::Vec4f line2;
		cv::fitLine(cv::Mat(points), line2,
			CV_DIST_L2, // �Ÿ� ����
			0,   // L2 �Ÿ��� ������� ����
			0.01, 0.01); // ��Ȯ��
						 // ���� ���� ����(cv::Vec4f�� ù �ΰ� ��), 
						 // ���� ���� �� ���� ��ǥ(cv::Vec4f�� ������ �� ��) ������ �� �������� �Ķ���͸� ����
						 // ������ �� �Ķ���ʹ� �� �Ķ���Ϳ� ���� �䱸 ��Ȯ���� ����
						 // �Լ����� �䱸 �ϴ� std::vector ���� ���Ե� �Է� ���� cv::Mat�� ����

		*/

		float angle, x1, y1, x2, y2;
		vector<Vec4i> lines;

		// vector<Vec4i> fitlines;
		// fitLine(lines, fitlines, CV_DIST_L2, 0, 0.01, 0.01);
		
		// detecting line
		HoughLinesP(GRAY_edges, lines, 1, CV_PI / 180, 30, 100, 30);


		//������ ������ ���� �׷��ݴϴ�.
		for (int i = 0; i < lines.size(); i++)
		{
			Vec4i Line = lines[i];
			Vec4i L_Line, R_Line;


			x1 = Line[0];	y1 = Line[1];	x2 = Line[2];	y2 = Line[3];
			angle = (y2 - y1) / (x2 - x1);
			//angle = abs(angle);
			angle *= 45;

			//if (-50 < angle && angle < 50)		lines[i] = NULL;
			if ( angle < 90 && angle > 50 )			L_Line = Line;
			if ( -90 < angle && angle < -50 )		R_Line = Line;

			//vector <Point> points;
			//points = L_Line;

			//fitLine(L_Line, L_Line, CV_DIST_L2, 0, 0.01, 0.01);
			//fitLine(R_Line, R_Line, CV_DIST_L2, 0, 0.01, 0.01);



			line(COLOR_image, Point(L_Line[0] + Horizontal * 0.13, L_Line[1] + vertical * 0.3), Point(L_Line[2] + Horizontal * 0.13, L_Line[3] + vertical * 0.3), Scalar(0, 0, 255), 2);
			line(COLOR_image, Point(R_Line[0] + Horizontal * 0.13, R_Line[1] + vertical * 0.3), Point(R_Line[2] + Horizontal * 0.13, R_Line[3] + vertical * 0.3), Scalar(0, 255, 0), 2);

			// line(COLOR_image, Point(L_Line[0], L_Line[1]), Point(L_Line[2], L_Line[3]), Scalar(0, 0, 255), 2);
			// line(COLOR_image, Point(R_Line[0], R_Line[1]), Point(R_Line[2], R_Line[3]), Scalar(0, 255, 0), 2);
			
		}

		imshow("COLOR_image", COLOR_image);
		imshow("GRAY_edges", GRAY_edges);

		//30ms ���� ����ϵ��� �ؾ� �������� �ʹ� ���� ������� ����.
		if (waitKey(20) == 27) break; //ESCŰ ������ ����
	}
}