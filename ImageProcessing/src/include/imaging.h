#pragma once
// Open CV
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

namespace Imaging {

	Mat read(char const* path);
	Mat convertTogray(Mat img);
	Mat convertToRGB(Mat img);
	Mat resize(Mat img, int target = 500);
	void show(Mat img, string windowName);
	Mat blur(Mat img, Size size = Size(3, 3));
	Mat canny(Mat img);
}