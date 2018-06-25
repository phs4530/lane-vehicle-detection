#pragma once

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>   

using namespace cv;
using namespace std;


// 선의 첫 번째에 속한 것으로 보이는 점 집합을 추출하기 위해 다음과 같이 진행
// 검은 영상에 하얀 선을 그린 후 그 선을 감지하기 위해 사용하는 외곽선의 캐니 영상으로 함께 교차
int n = 0; // 0번째 선 선택
Mat oneline(ROI_image.size(), CV_8U, cv::Scalar(0)); // 검은 영상
for (int n = 0; n < 3; n++)
{
	line(oneline, // 하얀 선
		Point(lines[n][0], lines[n][1]),
		Point(lines[n][2], lines[n][3]),
		Scalar(255),
		5); //특정 두께 5를 갖는 선을 그림
}
bitwise_and(GRAY_edges, oneline, oneline);
// 외곽선과 하얀 선 간의 AND
// 결과는 지정한 선과 관련된 점만 포함

// 검은 영상과 하얀 선을 반전시킴
Mat onelineInv;
threshold(oneline, onelineInv, 128, 255, cv::THRESH_BINARY_INV);
namedWindow("One line");
imshow("One line", onelineInv);

// 이중 반복문으로 집합 내에 있는 점의 좌표를 cv::Points의 std::vector에 삽입
vector<Point> points;

// 모든 점 위치를 얻기 위환 화소 조회
for (int y = 0; y < oneline.rows; y++) { // y행
	uchar* rowPtr = oneline.ptr<uchar>(y);
	for (int x = 0; x < oneline.cols; x++) { // x열
											 // 외곽선에 있다면
		if (rowPtr[x]) {
			points.push_back(Point(x, y));
		}
	}
}

cv::Vec4f fitline;
cv::fitLine(Mat(points), fitline,
	CV_DIST_L2, // 거리 유형
	0,   // L2 거리를 사용하지 않음
	0.01, 0.01); // 정확도
				 // 단위 방향 벡터(cv::Vec4f의 첫 두개 값), 
				 // 선에 놓인 한 점의 좌표(cv::Vec4f의 마지막 두 값) 형태인 선 방정식의 파라미터를 제공
				 // 마지막 두 파라미터는 선 파라미터에 대한 요구 정확도를 지정
				 // 함수에서 요구 하는 std::vector 내에 포함된 입력 점은 cv::Mat로 전달

				 // 선 방정식은 일부 속성계산에 사용
				 // 올바른 선을 계산하는지 확인하기 위해 영상에 예상 선을 그림
				 // 200화소 길이와 3화소 두께를 갖는 임의의 검은 세그먼트를 그림
int fx0 = fitline[2]; // 선에 놓은 한 점
int fy0 = fitline[3];
int fx1 = fx0 - 200 * fitline[0]; // 200 길이를 갖는 벡터 추가
int fy1 = fy0 - 200 * fitline[1]; // 단위 벡터 사용
								  //COLOR_image = imread("road.jpg", 0);


line(COLOR_image, Point(fx0 + Horizontal * 0.13, fy0 + vertical * 0.2), cv::Point(fx1 + Horizontal * 0.13, fy1 + vertical * 0.2), cv::Scalar(0), 3);