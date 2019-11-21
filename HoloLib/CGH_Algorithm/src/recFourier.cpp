#include "CGH.hpp"

using namespace cv;

int gs::recFourier(InputArray _src, OutputArray _dst)
{
    Mat src = _src.getMat();
    src = mod(src, 2 * CV_PI);
    _dst.create(src.rows, src.cols, CV_64FC1);
    Mat dst = _dst.getMat();
    CComplexMat H(src, GS_PHAS);
    idft(H, H);
    dst = H.getAmplitude();
    normalize(dst, dst, 0, 1, NORM_MINMAX);
    dst.copyTo(_dst);
    return NORMAL;
}