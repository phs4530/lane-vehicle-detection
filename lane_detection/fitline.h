#pragma once

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>   

using namespace cv;
using namespace std;


// ���� ù ��°�� ���� ������ ���̴� �� ������ �����ϱ� ���� ������ ���� ����
// ���� ���� �Ͼ� ���� �׸� �� �� ���� �����ϱ� ���� ����ϴ� �ܰ����� ĳ�� �������� �Բ� ����
int n = 0; // 0��° �� ����
Mat oneline(ROI_image.size(), CV_8U, cv::Scalar(0)); // ���� ����
for (int n = 0; n < 3; n++)
{
	line(oneline, // �Ͼ� ��
		Point(lines[n][0], lines[n][1]),
		Point(lines[n][2], lines[n][3]),
		Scalar(255),
		5); //Ư�� �β� 5�� ���� ���� �׸�
}
bitwise_and(GRAY_edges, oneline, oneline);
// �ܰ����� �Ͼ� �� ���� AND
// ����� ������ ���� ���õ� ���� ����

// ���� ����� �Ͼ� ���� ������Ŵ
Mat onelineInv;
threshold(oneline, onelineInv, 128, 255, cv::THRESH_BINARY_INV);
namedWindow("One line");
imshow("One line", onelineInv);

// ���� �ݺ������� ���� ���� �ִ� ���� ��ǥ�� cv::Points�� std::vector�� ����
vector<Point> points;

// ��� �� ��ġ�� ��� ��ȯ ȭ�� ��ȸ
for (int y = 0; y < oneline.rows; y++) { // y��
	uchar* rowPtr = oneline.ptr<uchar>(y);
	for (int x = 0; x < oneline.cols; x++) { // x��
											 // �ܰ����� �ִٸ�
		if (rowPtr[x]) {
			points.push_back(Point(x, y));
		}
	}
}

cv::Vec4f fitline;
cv::fitLine(Mat(points), fitline,
	CV_DIST_L2, // �Ÿ� ����
	0,   // L2 �Ÿ��� ������� ����
	0.01, 0.01); // ��Ȯ��
				 // ���� ���� ����(cv::Vec4f�� ù �ΰ� ��), 
				 // ���� ���� �� ���� ��ǥ(cv::Vec4f�� ������ �� ��) ������ �� �������� �Ķ���͸� ����
				 // ������ �� �Ķ���ʹ� �� �Ķ���Ϳ� ���� �䱸 ��Ȯ���� ����
				 // �Լ����� �䱸 �ϴ� std::vector ���� ���Ե� �Է� ���� cv::Mat�� ����

				 // �� �������� �Ϻ� �Ӽ���꿡 ���
				 // �ùٸ� ���� ����ϴ��� Ȯ���ϱ� ���� ���� ���� ���� �׸�
				 // 200ȭ�� ���̿� 3ȭ�� �β��� ���� ������ ���� ���׸�Ʈ�� �׸�
int fx0 = fitline[2]; // ���� ���� �� ��
int fy0 = fitline[3];
int fx1 = fx0 - 200 * fitline[0]; // 200 ���̸� ���� ���� �߰�
int fy1 = fy0 - 200 * fitline[1]; // ���� ���� ���
								  //COLOR_image = imread("road.jpg", 0);


line(COLOR_image, Point(fx0 + Horizontal * 0.13, fy0 + vertical * 0.2), cv::Point(fx1 + Horizontal * 0.13, fy1 + vertical * 0.2), cv::Scalar(0), 3);