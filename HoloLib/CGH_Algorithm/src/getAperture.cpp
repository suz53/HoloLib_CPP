#include "CGH.hpp"
using namespace cv;

Mat gs::getAperture(int _rows, int _cols, int apertureSize)
{
    Mat aperture = Mat::zeros(_rows, _cols, CV_64FC1);
    for (int i = (aperture.rows / 2 - apertureSize / 2); i < (aperture.rows / 2 + apertureSize / 2) - 1; i++)
    {
        for (int j = (aperture.rows / 2 - apertureSize / 2); j < (aperture.rows / 2 + apertureSize / 2) - 1; j++)
        {
            aperture.at<double>(i, j) = 1.0;
        }
    }
    return aperture;
}