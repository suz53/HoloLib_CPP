#include "CGH.hpp"

using namespace cv;

int gs::recDoubleHologram(InputArray _src, CComplexMat& _dst, int apertureSize)
{
	Mat src = _src.getMat();
	CComplexMat Holo(src.rows, src.cols);
	/*normalize(src, src, 0.0, 1.0, NORM_MINMAX);*/
	Mat amplitude = Mat::ones(src.rows, src.cols, CV_64F);
	Holo.setComplexM_AP(amplitude, src);
	dft(Holo, Holo);
	Mat recAmplitude = Holo.getAmplitude();
	Mat recPhase = Holo.getPhase();
	normalize(recAmplitude, recAmplitude, 0, 1, NORM_MINMAX);
	normalize(recPhase, recPhase, 0, 1, NORM_MINMAX);
	int height_Pixel = src.rows;
	int width_Pixel = src.cols;
	Mat aperture = Mat::zeros(src.rows, src.cols, CV_64F);
	for (int i = (src.rows / 2 - apertureSize / 2); i < (src.rows / 2 + apertureSize / 2) - 1; i++)
	{
		for (int j = (src.rows / 2 - apertureSize / 2); j < (src.rows / 2 + apertureSize / 2)- 1; j++)
		{
			aperture.at<double>(i, j) = 1.0;
		}
	}
	Mat frequencyDomainAmplitude = Holo.getAmplitude().mul(aperture);
	Mat frequencyDomainPhase = Holo.getPhase().mul(aperture);
	_dst.setComplexM_AP(frequencyDomainAmplitude, frequencyDomainPhase);
	idft(_dst, _dst);
	return NORMAL;
}
