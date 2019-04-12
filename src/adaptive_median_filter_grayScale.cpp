/*!
* \brief        Adaptive median filter
* \details      Apply adaptive median filter on a gray scale image
* \author       Nazanin Tafreshi
* \date         2019 Apr 8
*/


#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/**
* apply adaptive median filter on a gray scale image.
* @param in_image a noisy gray scale input image.
* @param smax maximum size of the kernel.
* @return cleared output image.
*/ 
Mat adaptiveMedianFilter(Mat &in_image, int smax) {

    Mat out_image = in_image;
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
                        kernel[c] = in_image.at<uchar>(fx + x, fy + y);
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
                    int C = out_image.at<uchar>(x, y) - min;
                    int D = out_image.at<uchar>(x, y) - max;
                    if ((C > 0) && (D < 0)) {
                        out_image.at<uchar>(x, y) = out_image.at<uchar>(x, y);
                        break;
                    }
                    else {
                        out_image.at<uchar>(x, y) = median;
                        break;
                    }
                }
                else {
                    sxy += 2;
                    if (sxy > smax) {
                        out_image.at<uchar>(x, y) = out_image.at<uchar>(x, y);
                    }
                }
            }
        }
    }

    return out_image;
}
int main()
{
    //in_image for adaptive median filter
    Mat in_image = imread("noisyImageGrayScale.jpg", 0);
    imshow("in_image", in_image);
    
    Mat out_image = adaptiveMedianFilter(in_image, 9);
    
    imwrite("outImage.jpg", out_image);
    imshow("out_image", out_image);
    waitKey(0);
}
