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

int gs::nonIterFourier(InputArray _src, OutputArray _dst, int imageRows, int imageCols, double mix_Factor)
{
    Mat src = _src.getMat();
    src = Mat_<double>(src);
    Mat w, h;
    Mat X, Y;
    w = linspace(-src.cols / 2, src.cols / 2, src.cols);
    h = linspace(-src.rows / 2, src.rows / 2, src.rows);
    meshgrid(w, h, X, Y);
    double a = (double)CV_PI / (double)imageCols;
    double b = (double)CV_PI / (double)imageRows;
    Mat Quadratic_Phase = Mat_<double>(a * (X.mul(X)) + b * (Y.mul(Y)));
    Quadratic_Phase = mod(Quadratic_Phase, 2 * CV_PI);
    Mat Random_Phase = Mat_<double>(src.rows, src.cols, 0.0);
    RNG Random_Phase_Generater(getTickCount());
    Random_Phase_Generater.fill(Random_Phase, RNG::UNIFORM, 0.0, 2 * CV_PI);
    Mat MixPhase = Quadratic_Phase + Random_Phase.mul(mix_Factor);
    MixPhase = mod(MixPhase, 2 * CV_PI);
    CComplexMat data(src, GS_AMPL);
    data.setPhase(MixPhase);
    dft(data, data);
    Mat dst = _dst.getMat();
    dst = mod(data.getPhase(), 2 * CV_PI);
    dst.copyTo(_dst);
    return NORMAL;
}