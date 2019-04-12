/*!
* \brief        salt & pepper noise 
* \details      adding salt & pepper noise on a RGB image
* \author       Nazanin Tafreshi 
* \date         2019 Apr 6 
*/
#include "pch.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>




using namespace cv;
using namespace std;


Mat salt_pepperNoise(Mat &in_image, int salt_noise, int pepper_noise) {
    Mat noisyImage = in_image;

    for (int i = 0; i < in_image.rows; i++) {
        for (int j = 0; j < in_image.cols; j++) {

            int r = rand() % 256;
            if (r == salt_noise) {
                noisyImage.at<Vec3b>(i, j)[0] = 255;
                noisyImage.at<Vec3b>(i, j)[1] = 255;
                noisyImage.at<Vec3b>(i, j)[2] = 255;
            }
            else if (r == pepper_noise) {
                noisyImage.at<Vec3b>(i, j)[0] = 0;
                noisyImage.at<Vec3b>(i, j)[1] = 0;
                noisyImage.at<Vec3b>(i, j)[2] = 0;
            }

        }
    }
    return noisyImage;
}


int main()
{
    Mat in_image = imread("blurred.bmp");
    imshow("in_image", in_image);
    Mat out_image = salt_pepperNoise(in_image, 5, 10);
    imwrite("outImage.jpg", out_image);
    imshow("out_image", out_image);

    waitKey(0);
}
