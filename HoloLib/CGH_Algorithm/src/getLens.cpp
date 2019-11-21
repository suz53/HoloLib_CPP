#include "CGH.hpp"

using namespace cv;

Mat gs::getLens(double focus, double width, double height, \
    int width_Pixel, int height_Pixel, double lambda)
{
    double k = (2 * CV_PI) / lambda;
    Mat w, h;
    Mat X, Y;
    w = linspace(-width / 2, width / 2, width_Pixel);
    h = linspace(-height / 2, height / 2, height_Pixel);
    meshgrid(w, h, X, Y);
    Mat phi = - (k / 2.0 / focus) * (X.mul(X) + Y.mul(Y));;
    CComplexMat LP(phi, GS_PHAS);
    Mat P = mod(LP.getPhase(), 2 * CV_PI);
    return P;
}