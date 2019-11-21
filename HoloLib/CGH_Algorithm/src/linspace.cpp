#include "CGH.hpp"

using namespace cv;

cv::Mat gs::linspace(double A, double B, int n)
{
    Mat res(1, n, CV_64F);
    double step = (B - A) / (n - 1.0);
    for (int i = 0; i < n; i++)
        res.at<double>(0, i) = A + i * step;
    return res;
}