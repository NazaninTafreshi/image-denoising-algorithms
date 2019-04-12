/*!
* \brief        gaussian filter 
* \details      gaussian filter on TaxiDriver.jpg
* \author       Nazanin Tafreshi 
* \date         2019 Apr 6 
*/
#include "pch.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>
#include <vector>

# define PI         3.1415926535897932384626 


using namespace cv;
using namespace std;

/*
** implementing gaussian kernel
*/
double** gaussianFilter(int height, int width, double sigma)
{
    double **kernel = new double*[height];
    double sum = 0.0;
    int h = height / 2;
    int w = width / 2;


    for (int i = -h; i < h+1; i++) {
        kernel[i+h] = new double[width];
        for (int j = -w; j < w+1; j++) {
            kernel[i+h][j+w] = exp(-(i*i + j * j) / (2 * sigma*sigma)) / (2 * PI* sigma *sigma);
                sum += kernel[i+h][j+w];
                    }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            kernel[i][j] /= sum;
            cout << kernel[i][j] << "\t";
        }
        cout << "\n";
    }

    return kernel;
}
/*
** apply gaussian kernel on an image 
*/
Mat gaussianFilter(Mat &in_image, double **filter, int xFilter,int yFilter) {

    int rows = in_image.rows;
    int cols = in_image.cols;
    double sum=0;

    Mat out_image = in_image;
    int h = yFilter / 2;
    int w = xFilter / 2;
    
    for (int i = h; i < rows - h; i++) {
        for (int j = w; j < cols - w; j++) {
            sum = 0;
            for (int y = -h; y < h+1; y++) {
                for (int x = -w; x < w+1; x++) {
                    sum += filter[y + 2][x + 2] * in_image.at<uchar>(i + y, j + x);
                }
            }
            out_image.at<uchar>(i, j) = sum;
        }
    }

    return out_image;
}


int main()
{
    double **filter = gaussianFilter(5, 5, 1.0);

    Mat in_image = imread("TaxiDriver.jpg", 0);
    imshow("in_image", in_image);
    Mat out_image;
    for (int i = 0; i < 5; i++) {
    out_image = gaussianFilter(in_image, filter, 5, 5);
    }
    imwrite("gaussian.jpg", out_image);
    imshow("out_image", out_image);

    waitKey(0);
}
