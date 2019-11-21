#include "CGH.hpp"

using namespace cv;

cv::Mat gs::getAxilens(double focus, double Zg, double width, \
    double height, int width_Pixel, int height_Pixel, double lambda, \
    double R)
{
    Mat w, h;
    Mat X, Y;
    w = linspace(-width / 2, width / 2, width_Pixel);
    h = linspace(-height / 2, height / 2, height_Pixel);
    meshgrid(w, h, X, Y);
    Mat distance_r = (X.mul(X) + Y.mul(Y));
    Mat phase_fenzi = (CV_PI / lambda) * (distance_r);
    Mat phase_fenmu = focus + (Zg / R * R) * (distance_r);
    Mat P;
    divide(-phase_fenzi, phase_fenmu, P);
    P = mod(P, 2 * CV_PI);
    return P;
}