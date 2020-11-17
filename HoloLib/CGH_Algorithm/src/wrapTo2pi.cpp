#include "CGH.hpp";

using namespace cv;

Mat gs::wrapTo2pi(InputArray _src)
{
    Mat src = _src.getMat();
    Mat binarizationSrc;
    threshold(src, binarizationSrc, 0.0, 1.0, THRESH_BINARY);
    src = mod(src, 2 * CV_PI);

    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            if (binarizationSrc.at<double>(i, j) && src.at<double>(i, j) == 0)
                src.at<double>(i, j) = 2 * CV_PI;
        }
    }
    return src;
}