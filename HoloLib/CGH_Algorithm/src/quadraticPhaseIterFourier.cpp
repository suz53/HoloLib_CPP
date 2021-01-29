#include "CGH.hpp"
#include "CComplexMat.hpp"

using namespace cv;
using namespace gs;

int gs::quadraticPhaseIterFourier(InputArray _src, OutputArray _dst, int imageRows, int imageCols, int N_iter)
{
    Mat src = _src.getMat();
    src = Mat_<double>(src);
    Mat w, h;
    Mat X, Y;
    w = linspace(-src.cols / 2, src.cols / 2, src.cols);
    h = linspace(-src.rows / 2, src.rows / 2, src.rows);
    meshgrid(w, h, X, Y);
    double a = (double)CV_PI / (double)imageCols;
    double b = (double)CV_PI / (double)imageRows;
    Mat Quadratic_Phase = Mat_<double>(a * (X.mul(X)) + b * (Y.mul(Y)));
    Quadratic_Phase = mod(Quadratic_Phase, 2 * CV_PI);
    CComplexMat data(src, GS_AMPL);
    data.setPhase(Quadratic_Phase);
    Mat Ak = Mat_<double>(src.rows, src.cols, 0.0);
    Mat Ak_ = Mat_<double>(src.rows, src.cols, 0.0);
    double beita = 10e-8;
    for (int i = 0; i < N_iter; i++)
    {
        Ak = data.getAmplitude();
        Ak = Mat_<double>(abs(Ak));
        dft(data, data);
        data.setAmplitude(Mat_<double>(src.rows, src.cols, 1.0));
        idft(data, data);
        Ak_ = data.getAmplitude();
        Ak_ = Mat_<double>(abs(Ak_));
        normalize(Ak_, Ak_, 0, 1, NORM_MINMAX);
        Mat tmp = Mat_<double>(src / (Ak_ + 10e-10));
        pow(tmp, beita, tmp);
        beita = sqrt(beita);
        tmp = tmp.mul(src);
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




