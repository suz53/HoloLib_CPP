#include "CGH.hpp"

int gs::getBinaryHologram(InputArray src_amplitude, InputArray src_phase, OutputArray _dst)
{
    Mat amplitude = src_amplitude.getMat();
    getBinaryImage(amplitude, amplitude);
    Mat phase = src_phase.getMat();
    phase = phase * (2 * CV_PI);

    Mat cancelingWave = Mat::zeros(phase.rows, phase.cols, CV_64FC1);
    cancelingWave = Mat_<double>(cancelingWave);
    int k = 1;
    for (int i = 1; i < phase.rows; i++)
    {
        for (int j = 1; j < phase.cols; j++)
        {
            if (amplitude.at<double>(i, j) == 0)
            {
                if (k == 1)
                {
                    cancelingWave.at<double>(i, j) = CV_PI;
                    k = -1;
                    continue;
                }
                if (k == -1)
                {
                    k = 1;
                    continue;
                }

            }
        }
    }
    Mat dst = _dst.getMat();
    dst = phase.mul(amplitude) + cancelingWave;
    normalize(dst, dst, 0.0, 1.0, NORM_MINMAX);
    dst.copyTo(_dst);
    return NORMAL;
}
