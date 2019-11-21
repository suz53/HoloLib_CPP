#include "CGH.hpp"

using namespace cv;

int gs::propDFFT(CComplexMat& _src, CComplexMat& _dst, double width, double height, \
                  double z, double lambda)
{
    double k = (2 * CV_PI) / lambda;
    int height_Pixel = _src.getComplexM().rows;
    int width_Pixel = _src.getComplexM().cols;
    Mat kethi, nenta;
    kethi = linspace(-1. / 2. / width, 1. / 2. / width, width_Pixel);
    kethi = kethi * width_Pixel;
    nenta = linspace(-1. / 2. / height, 1. / 2. / height, height_Pixel);
    nenta = nenta * height_Pixel;
    meshgrid(kethi, nenta, kethi, nenta);
    Mat phi = k * z * (1.0 - lambda * lambda * (kethi.mul(kethi) + nenta.mul(nenta)) / 2.0);
    CComplexMat H(phi, GS_PHAS);
    CComplexMat F(phi.rows, phi.cols);
    dft(_src, F);
    Mat Fuf = F.mul(H);
    idft(Fuf, _dst);
    return NORMAL;
}