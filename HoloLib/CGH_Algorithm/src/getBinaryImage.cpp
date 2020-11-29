#include "CGH.hpp"
using namespace gs;


int gs::getBinaryImage(InputArray _src, OutputArray _dst)
{
    Mat src = _src.getMat();
    double positive = 1.0;
    double negative = 0.0;
    src = src * 255;
    Mat dst = Mat(src.rows, src.cols, CV_64FC1);
    double error;
    double value;
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            if (src.at<double>(i, j) > 128)
            {
                dst.at<double>(i, j) = positive;
                error = src.at<double>(i, j) - 255;
            }
            else
            {
                dst.at<double>(i, j) = negative;
                error = src.at<double>(i, j);
            }
            if (j < (src.cols - 1))
            {
                value = src.at<double>(i, j + 1) + error * (7.0 / 16.0);
                src.at<double>(i, j + 1) = value;
            }
            if (i < (src.rows - 1))
            {
                value = src.at<double>(i + 1, j) + error * (5.0 / 16.0);
                src.at<double>(i + 1, j) = value;
                if (j < (src.cols - 1))
                {
                    value = src.at<double>(i + 1, j + 1) + error * (1.0 / 16.0);
                    src.at<double>(i + 1, j + 1) = value;
                }
                if (j > 0)
                {
                    value = src.at<double>(i + 1, j - 1) + error * (3.0 / 16.0);
                    src.at<double>(i + 1, j - 1) = value;
                }
            }

        }
    }
    dst.copyTo(_dst);
    return NORMAL;
}
