#include "CGH.hpp"

using namespace cv;

Mat gs::neighborInterpolation(InputArray _src, double zoom_factor)
{
    Mat src = _src.getMat();
    Mat dst = Mat::zeros(int(src.rows * zoom_factor), int(src.cols * zoom_factor), CV_64F);

    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            dst.at<double>(i, j) = src.at<double>(int(i / zoom_factor), int(j / zoom_factor));
        }
    }
    return dst;
}
