#include "CGH.hpp"

using namespace cv;

int gs::copyMakeBorder(InputArray _src, OutputArray _dst, int width_Pixel, int height_Pixel)
{
    Mat src = _src.getMat();
    Mat dst = Mat::zeros(height_Pixel, width_Pixel, CV_64FC1);
    int imageRows = src.rows;
    int imageCols = src.cols;
    int x = 0;
    int y = 0;
    for (int i = (height_Pixel / 2 - imageRows / 2); i < (height_Pixel / 2 + imageRows / 2); i++)
    {
        for (int j = (width_Pixel / 2 - imageCols / 2); j < (width_Pixel / 2 + imageCols / 2); j++)
        {
            dst.at<double>(i, j) = src.at<double>(x, y);
            y++;
        }
        x++;
        y = 0;
    }
    dst.copyTo(_dst);
    return NORMAL;
}