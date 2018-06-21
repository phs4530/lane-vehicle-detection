#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>   


using namespace cv;
using namespace std;

int Horizontal = 480, vertical = 480;

int main(int argc, char** argv)
{
	//������ ���Ϸκ��� ���� ������ �о���� ���� �غ�
	VideoCapture cap1("C:/image/sample_video.avi");

	if (!cap1.isOpened())
	{
		printf("������ ������ ���� �����ϴ�. \n");
	}

	//������ �÷��̽� ũ�⸦ ����
	cap1.set(CAP_PROP_FRAME_WIDTH, Horizontal);
	cap1.set(CAP_PROP_FRAME_HEIGHT, vertical);

	Mat COLOR_edges;
	Mat COLOR_image;
	Mat GRAY_image;
	Mat ROI_image;
	Mat GRAY_edges;
	Mat bila_Filter;

	namedWindow("video", 1);

	for (;;)
	{
		//��ĸ���κ��� �� �������� �о��
		cap1 >> COLOR_image;
		ROI_image = COLOR_image(Rect(Horizontal * 0.1, vertical*0.4, Horizontal * 0.9, vertical*0.6));

		
		cvtColor(ROI_image, GRAY_image, CV_RGB2GRAY);
		bilateralFilter(GRAY_image, bila_Filter, 5, 250, 10);
			

		Canny(GRAY_image, GRAY_edges, 70, 210);

		float angle, x1, y1, x2, y2;

		vector<Vec4i> lines;

		HoughLinesP(GRAY_edges, lines, 1, CV_PI / 180, 30, 10, 20);


		//������ ������ ���� �׷��ݴϴ�.
		for (int i = 0; i < lines.size(); i++)
		{
			Vec4i Line = lines[i];

			x1 = Line[0];	y1 = Line[1];	x2 = Line[2];	y2 = Line[3];
			angle = (y2 - y1) / (x2 - x1);
			angle = abs(angle);
			angle *= 45;

			if (angle < 60)
			{
				lines[i] = NULL;
			}

			Line = lines[i];

			line(COLOR_image, Point(Line[0] + Horizontal * 0.1, Line[1]+ vertical * 0.4), Point(Line[2] + Horizontal * 0.1, Line[3] + vertical * 0.4),
				Scalar(0, 0, 255), 1);

		}

		imshow("video", COLOR_image);

		//30ms ���� ����ϵ��� �ؾ� �������� �ʹ� ���� ������� ����.
		if (waitKey(20) == 27) break; //ESCŰ ������ ����
	}
}