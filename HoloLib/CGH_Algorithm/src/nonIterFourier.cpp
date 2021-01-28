#include "CGH.hpp"

using namespace cv;

int gs::nonIterFourier(InputArray _srcAmplitude, InputArray _srcPhase, OutputArray _dst)
{
    Mat srcAmplitude = _srcAmplitude.getMat();
    srcAmplitude = Mat_<double>(srcAmplitude);
    normalize(srcAmplitude, srcAmplitude, 0, 1.0, NORM_MINMAX);
    Mat srcPhase = _srcPhase.getMat();
    srcPhase = Mat_<double>(srcPhase);
    normalize(srcPhase, srcPhase, 0, 1.0, NORM_MINMAX);
    srcPhase = srcPhase * 2 * CV_PI;
    CComplexMat data(srcAmplitude, GS_AMPL);
    data.setPhase(srcPhase);
    dft(data, data);
    Mat dst = _dst.getMat();
    dst = mod(data.getPhase(), 2 * CV_PI);
    dst.copyTo(_dst);
    return NORMAL;
}