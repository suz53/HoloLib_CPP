#include "CGH.hpp"

using namespace cv;

int gs::propDOE(InputArray _src, OutputArray _dst, double width, double height, \
                 double z, double lambda)
{
    Mat w, h;
    Mat X, Y;
    Mat data = _src.getMat();
    int width_Pixel = data.cols;
    int height_Pixel = data.rows;
    data = mod(data, 2 * CV_PI);
    w = linspace(-width / 2, width / 2, width_Pixel);
    h = linspace(-height / 2, height / 2, height_Pixel);
    meshgrid(w, h, X, Y);
    Mat RR = (X.mul(X) + Y.mul(Y));
    Mat PPF = (CV_PI / (lambda * z)) * RR;
    Mat H = mod(data + PPF, 2 * 3.141593);
    CComplexMat U(H, GS_PHAS);
    idft(U, U);
    _dst.create(data.rows, data.cols, CV_64F);
    U.getAmplitude().copyTo(_dst);
    return NORMAL;
}
