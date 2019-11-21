#include "CGH.hpp"

using namespace cv;

int gs::repImage(InputArray _src, OutputArray _dst, int width_Pixel, int height_Pixel)
{
    Mat src = _src.getMat();
    int M = (height_Pixel / src.rows) + 1;
    int N = (width_Pixel / src.cols) + 1;
    Mat tmp = repeat(src, M, N);
    Mat res = tmp(Rect(0, 0, width_Pixel, height_Pixel));
    _dst.create(res.rows, res.cols, CV_64F);
    res.copyTo(_dst);
    return NORMAL;
}