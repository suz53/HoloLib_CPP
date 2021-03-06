﻿#include "CGH.hpp"

using namespace cv;

int gs::recFresnel(InputArray _src, OutputArray _dst, double width, double height, \
                    double z, double lambda)
{
    Mat src = _src.getMat();
    src = mod(src, 2 * CV_PI);
    _dst.create(src.rows, src.cols, CV_64F);
    Mat dst = _dst.getMat();
    CComplexMat H(src, GS_PHAS);
    propDFFT(H, H, width, height, lambda, -z);
    dst = H.getAmplitude();
    normalize(dst, dst, 0, 1.0, NORM_MINMAX);
    dst.copyTo(_dst);
    return NORMAL;
}

int gs::recFresnel(InputArray _src, OutputArray _dst, double width, double height, \
                    double z, double min, double max, double lambda)
{
    Mat src = _src.getMat();
    src = mod(src, 2 * CV_PI);
    _dst.create(src.rows, src.cols, CV_64F);
    Mat dst = _dst.getMat();
    CComplexMat H(src, GS_PHAS);
    propDFFT(H, H, width, height, lambda, -z);
    dst = H.getAmplitude();
    double norm_min = min / 255.0;
    double norm_max = max / 255.0;
    normalize(dst, dst, norm_min, norm_max, NORM_MINMAX);
    dst.copyTo(_dst);
    return NORMAL;
}
