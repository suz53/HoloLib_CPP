#include "CGH.hpp"
#include "CComplexMat.hpp"

using namespace cv;
using namespace gs;

int gs::optimizedIterFourier(InputArray _src, OutputArray _dst, int imageRows, int imageCols, int N_iter)
{
    Mat src = _src.getMat();
    src = Mat_<double>(src);
    normalize(src, src, 0, 1.0, NORM_MINMAX);
    Mat Random_Phase = Mat_<double>(src.rows, src.cols, 0.0);
    RNG Random_Phase_Generater(getTickCount());
    Random_Phase_Generater.fill(Random_Phase, RNG::UNIFORM, 0.0, 2 * CV_PI);
    CComplexMat data(src, GS_AMPL);
    data.setPhase(Random_Phase);
    Mat Ak = Mat_<double>(src.rows, src.cols, 0.0);
    Mat Ak_ = Mat_<double>(src.rows, src.cols, 0.0);
    double beita = 10e-8;
    for (int i = 0; i < N_iter; i++)
    {
        Ak = data.getAmplitude();
        Ak = Mat_<double>(abs(Ak));
        dft(data, data);
        double holoAmplitude = (double)(sum(src.mul(src)))[0];
        double Aholo = sqrt(holoAmplitude / (src.rows * src.cols));
        data.setAmplitude(Mat_<double>(src.rows, src.cols, Aholo));
        idft(data, data);
        Ak_ = data.getAmplitude();
        Ak_ = Mat_<double>(abs(Ak_));
        normalize(Ak_, Ak_, 0, 1, NORM_MINMAX);
        Mat tmp = Mat_<double>(src / (Ak_ + 10e-10));
        pow(tmp, beita, tmp);
        beita = sqrt(beita);
        tmp = tmp.mul(Ak);
        Mat Acon = Mat_<double>(Ak_);

        for (int i = (src.rows / 2 - imageRows / 2); i < (src.rows / 2 + imageRows / 2); i++)
        {
            for (int j = (src.cols / 2 - imageCols / 2); j < (src.cols / 2 + imageCols / 2); j++)
            {
                Acon.at<double>(i, j) = tmp.at<double>(i, j);
            }
        }

        data.setAmplitude(Acon);
    }
    dft(data, data);
    Mat dst = _dst.getMat();
    dst = mod(data.getPhase(), 2 * CV_PI);
    dst.copyTo(_dst);
    return NORMAL;
}