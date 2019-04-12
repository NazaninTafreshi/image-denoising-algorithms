/*!
* \brief        Adaptive median filter
* \details      Apply adaptive median filter on a RGB image
* \author       Nazanin Tafreshi
* \date         2019 Apr 8
*/


#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>



using namespace cv;
using namespace std;

/**
* apply adaptive median filter on each channel of the RGB image.
* @param in_image a noisy RGB input image.
* @param out_image output image.
* @param smax maximum size of the kernel.
* @param val channel index number.
* @return cleared output image for the channel index number.
*/
Mat adaptiveMedianFilter(Mat &in_image, Mat &out_image, int smax, int val) {

	int max, min, median = 0;
	int n;
	int sxy = 3;

	int *kernel;
	for (int x = smax / 2; x < in_image.rows - smax / 2; x++) {
		for (int y = smax / 2; y < in_image.cols - smax / 2; y++) {
			sxy = 3;

			while (sxy <= smax) {
				n = sxy * sxy;
				kernel = new int[n];
				int c = 0;
				for (int fx = -(sxy / 2); fx < (sxy / 2) + 1; fx++) {
					for (int fy = -(sxy / 2); fy < (sxy / 2) + 1; fy++) {
						kernel[c] = in_image.at<Vec3b>(fx + x, fy + y)[val];
						c++;
					}
				}

				sort(kernel, kernel + n);
				min = kernel[0];
				max = kernel[n - 1];
				median = kernel[(n / 2) + 1];
				delete[] kernel;
				int A = median - min;
				int B = median - max;

				if ((A > 0) && (B < 0)) {
					int C = out_image.at<Vec3b>(x, y)[val] - min;
					int D = out_image.at<Vec3b>(x, y)[val] - max;
					if ((C > 0) && (D < 0)) {
						out_image.at<Vec3b>(x, y)[val] = out_image.at<Vec3b>(x, y)[val];
						break;
					}
					else {
						out_image.at<Vec3b>(x, y)[val] = median;
						break;
					}
				}
				else {
					sxy += 2;
					if (sxy > smax) {
						out_image.at<Vec3b>(x, y)[val] = out_image.at<Vec3b>(x, y)[val];
					}
				}
			}
		}
	}
	return out_image;
}

/**
* apply adaptive median filter.
* @param in_image a noisy RGB input image.
* @param smax maximum size of the kernel.
* @return cleared output image.
*/
Mat applyAdaptiveMedianFilter(Mat &in_image, int smax) {
	Mat out_image = in_image;
	out_image = adaptiveMedianFilter(in_image, out_image, 9, 0);
	out_image = adaptiveMedianFilter(in_image, out_image, 9, 1);
	out_image = adaptiveMedianFilter(in_image, out_image, 9, 2);
	return out_image;
}

int main() {
	// noisy input image for adaptive median filter on a RGB image
	Mat in_image = imread("noisyImage.jpg", 1);
	imshow("in_image", in_image);

	TickMeter tm;
	tm.start();
	Mat out_image = applyAdaptiveMedianFilter(in_image, 9);
	tm.stop();
	double time_elapsed = tm.getTimeSec() / tm.getCounter();
	cout << "Time elapsed: " << time_elapsed << "s" << endl;

	imwrite("outImage.jpg", out_image);
	imshow("out_image", out_image);

	waitKey(0);

}
