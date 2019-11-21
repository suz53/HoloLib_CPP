#include "CGH.hpp"
#include "vector"

using namespace cv;

int gs::stepPhase(InputArray _src, OutputArray _dst, int N_step)
{
    Mat src0 = _src.getMat(), src = Mat_<double>(src0);
    Mat dst = _dst.getMat();
    src = mod(src, 2 * CV_PI);
    std::vector<double> table;
    double step = (2 * CV_PI) / N_step;
    for (int i = 0; i <= N_step; i++)
        table.push_back(i * step);
    for (int r = 0; r < src.rows; r++)
    {
        for (int c = 0; c < src.cols; c++)
        {
            for (int i = 0; i < N_step; i++)
            {
                if (table[i] <= src.at<double>(r, c) && src.at<double>(r, c) <= table[i + 1])
                {
                    dst.at<double>(r, c) = (table[i] + table[i + 1]) / 2.0;
                }
            }
        }
    }  
    dst.copyTo(_dst);
    return NORMAL;
}