/*!
* \brief        Histogram Equalization
* \details      Apply Histogram Equalization on a gray scale image
* \author       Nazanin Tafreshi
*/

#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat histogramEqualization(Mat &image, int alpha) {
	Mat out_image = image;
	int n = image.rows * image.cols;
	int intensity[256];
	double probability[256];
	double cumulativeProbability[256];

	for (int i = 0; i < 256; i++) {
		intensity[i] = 0;
	}
	/*
	find the intensity of all pixels in the image
	*/
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			intensity[image.at<uchar>(i, j)]++;
		}
	}
	for (int i = 0; i < 256; i++) {
		probability[i] = double(intensity[i]) / n;
	}

	cumulativeProbability[0] = probability[0];

	for (int i = 1; i < 256; i++) {
		cumulativeProbability[i] = probability[i] + cumulativeProbability[i - 1];
	}

	for (int i = 0; i < 256; i++) {
		cumulativeProbability[i] = int(cumulativeProbability[i] * alpha);
	}

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			out_image.at<uchar>(i, j) = cumulativeProbability[image.at<uchar>(i, j)];
		}
	}
	return image;
}

int main()
{

	Mat in_image = imread("lena.jpg", 0);
	imshow("in_image", in_image);

	Mat out_image = histogramEqualization(in_image, 255);

	imwrite("outImage.jpg", out_image);
	imshow("out_image", out_image);

	waitKey(0);
}