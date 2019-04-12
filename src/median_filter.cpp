/*!
* \brief        median filter
* \details      Apply median filter on an RGB image
* \author       Nazanin Tafreshi
* \date         2019 Apr 7
*/
#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

/**
* apply median filter on each channel of the RGB image.
* @param in_image a noisy RGB input image.
* @param out_image output image.
* @param filter_size size of the kernel.
* @param val channel index number.
* @return cleared output image for the channel index number.
*/
Mat medianFilter(Mat &in_image, Mat &out_image, int filter_size, int val) {

	int s = filter_size / 2;
	int median = 0;
	int n = filter_size * filter_size; //size of the neighbours to put it in an array

	for (int x = s; x < in_image.rows - s; x++) {
		for (int y = s; y < in_image.cols - s; y++) {
			int *kernel = new int[n];
			int c = 0;
			for (int fy = -s; fy < s + 1; fy++) {
				for (int fx = -s; fx < s + 1; fx++) {
					//create an array for each pixel's neighbours in the image
					kernel[c] = in_image.at<Vec3b>(x + fx, y + fy)[val];
					c += 1;
				}
			}
			//sort each array to find median value
			sort(kernel, kernel + n);

			// median value for array with odd number of elements
			median = kernel[(n / 2) + 1];

			delete[] kernel;

			//replace each pixel in the image with the median value of its neighbours
			out_image.at<Vec3b>(x, y)[val] = median;

		}
	}
	return out_image;
}

/**
* apply median filter.
* @param in_image a noisy RGB input image.
* @param size size of the kernel.
* @return cleared output image.
*/
Mat applyMedianFilter(Mat &in_image, int size) {
	Mat out_image = in_image;
	out_image = medianFilter(in_image, out_image, size, 0);
	out_image = medianFilter(in_image, out_image, size, 1);
	out_image = medianFilter(in_image, out_image, size, 2);
	return out_image;
}

int main()
{

	//in_image for median filter
	Mat in_image = imread("noisyImage.jpg", 1);

	imshow("in_image", in_image);

	Mat out_image = applyMedianFilter(in_image, 5);
	imwrite("median.jpg", out_image);
	imshow("out_image", out_image);

	waitKey(0);
}
