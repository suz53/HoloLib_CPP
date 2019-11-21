#include "CGH.hpp"

using namespace cv;

int gs::iterFourier(InputArray _src, OutputArray _dst, int N_iter)
{
    Mat src0 = _src.getMat(), src = Mat_<double>(src0);
    normalize(src, src, 0, 1.0, NORM_MINMAX);
    Mat Random_Phase = Mat_<double>(src.rows, src.cols, 0.0);
    RNG Random_Phase_Generater(getTickCount());
    Random_Phase_Generater.fill(Random_Phase, RNG::UNIFORM, 0.0, 2 * CV_PI);
    CComplexMat data(src, GS_AMPL);
    data.setPhase(Random_Phase);
    for (int i = 0; i < N_iter; i++)
    {
        dft(data, data);
        data.setAmplitude(Mat_<double>(src.rows, src.cols, 1.0));
        idft(data, data);
        data.setAmplitude(src);
    }
    dft(data, data);
    Mat dst = _dst.getMat();
    dst = mod(data.getPhase(), 2 * CV_PI);
    dst.copyTo(_dst);
    return NORMAL;
}