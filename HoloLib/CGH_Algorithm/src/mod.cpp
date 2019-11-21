#include "CGH.hpp"

using namespace cv;

Mat gs::mod(Mat M, double n)
{
    double res;
    Mat R(M.rows, M.cols, CV_64FC1);
    for (int r = 0; r < M.rows; r++)
        for (int c = 0; c < M.cols; c++)
        {
            res = fmod(M.at<double>(r, c), n);
            R.at<double>(r, c) = (res >= 0) ? res : (res + n);
        }
    return R;
}