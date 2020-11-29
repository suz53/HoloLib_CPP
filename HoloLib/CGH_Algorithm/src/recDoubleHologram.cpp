#include "CGH.hpp"

using namespace cv;

int gs::recDoubleHologram(InputArray _src, CComplexMat& _dst, int apertureSize)
{
    Mat src = _src.getMat();
    src = src * (2 * CV_PI);
    CComplexMat Holo(src.rows, src.cols);
    Mat amplitude = Mat::ones(src.rows, src.cols, CV_64F);
    Holo.setComplexM_AP(amplitude, src);
    Holo.fftshift();
    dft(Holo, Holo);
    Holo.fftshift();
    Mat aperture = getAperture(src.rows, src.cols, apertureSize);
    Mat frequencyDomainAmplitude = Holo.getAmplitude().mul(aperture);
    Mat frequencyDomainPhase = Holo.getPhase().mul(aperture);
    _dst.setComplexM_AP(frequencyDomainAmplitude, frequencyDomainPhase);
    _dst.fftshift();
    idft(_dst, _dst);
    _dst.fftshift();
    return NORMAL;
}
