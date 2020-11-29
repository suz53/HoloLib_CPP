#include "CGH.hpp"

int gs::recBinaryHologram(InputArray _src, CComplexMat& _dst, int apertureSize)
{
    Mat phase = _src.getMat();
    CComplexMat Holo(phase.rows, phase.cols);
    phase = phase * (2 * CV_PI);
    Mat amplitude = Mat::ones(phase.rows, phase.cols, CV_64F);
    Holo.setComplexM_AP(amplitude, phase);
    Holo.fftshift();
    dft(Holo, Holo);
    Holo.fftshift();
    Mat aperture = getAperture(phase.rows, phase.cols, apertureSize);
    Mat frequencyDomainAmplitude = Holo.getAmplitude().mul(aperture);
    Mat frequencyDomainPhase = Holo.getPhase().mul(aperture);
    _dst.setComplexM_AP(frequencyDomainAmplitude, frequencyDomainPhase);
    _dst.fftshift();
    idft(_dst, _dst);
    _dst.fftshift();
    return NORMAL;
}
