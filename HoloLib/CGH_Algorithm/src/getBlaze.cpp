#include "CGH.hpp"

using namespace cv;

Mat gs::getBlaze(int Rows, int Cols, int T, Blaze_dir direction)
{
    double x_axis = 0;
    double y_axis = 0;
    Mat P = Mat_<double>(Rows, Cols);
    switch (direction)
    {
    case GS_UP:
        x_axis = 1.0; y_axis = 0.0;
        break;
    case GS_DOWN:
        x_axis = -1.0; y_axis = 0;
        break;
    case GS_LEFT:
        x_axis = 0; y_axis = 1.0;
        break;
    case GS_RIGHT:
        x_axis = 0; y_axis = -1.0;
        break;
    case GS_LEFTUP:
        x_axis = 1.0; y_axis = 1.0;
        break;
    case GS_LEFTDOWN:
        x_axis = -1.0; y_axis = 1.0;
        break;
    case GS_RIGHTUP:
        x_axis = 1.0; y_axis = -1.0;
        break;
    case GS_RIGHTDOWN:
        x_axis = -1.0; y_axis = -1.0;
        break;
    default:
        x_axis = 0; y_axis = 0;
        break;
    }

    for (int r = 0; r < Rows; r++)
        for (int c = 0; c < Cols; c++)
        {
            P.at<double>(r, c) = fmod(x_axis * r + y_axis * c, T) * 2 * CV_PI / T;
        }
    P = mod(P, 2 * CV_PI);
    return P;
}