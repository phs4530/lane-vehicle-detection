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
	//동영상 파일로부터 부터 데이터 읽어오기 위해 준비
	VideoCapture cap1("C:/image/sample_video.avi");

	if (!cap1.isOpened())
	{
		printf("동영상 파일을 열수 없습니다. \n");
	}

	//동영상 플레이시 크기를 지정
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
		//웹캡으로부터 한 프레임을 읽어옴
		cap1 >> COLOR_image;
		ROI_image = COLOR_image(Rect(Horizontal * 0.1, vertical*0.4, Horizontal * 0.9, vertical*0.6));

		
		cvtColor(ROI_image, GRAY_image, CV_RGB2GRAY);
		bilateralFilter(GRAY_image, bila_Filter, 5, 250, 10);
			

		Canny(GRAY_image, GRAY_edges, 70, 210);

		float angle, x1, y1, x2, y2;

		vector<Vec4i> lines;

		HoughLinesP(GRAY_edges, lines, 1, CV_PI / 180, 30, 10, 20);


		//검출한 직선을 영상에 그려줍니다.
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

		//30ms 정도 대기하도록 해야 동영상이 너무 빨리 재생되지 않음.
		if (waitKey(20) == 27) break; //ESC키 누르면 종료
	}
}