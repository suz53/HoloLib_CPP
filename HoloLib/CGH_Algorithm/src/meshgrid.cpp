#include "CGH.hpp"

using namespace cv;

int gs::meshgrid(InputArray _xgv, InputArray _ygv, OutputArray _X, OutputArray _Y)
{
    Mat xgv = _xgv.getMat();
    Mat ygv = _ygv.getMat();
    _X.create(xgv.rows, ygv.cols, xgv.type());
    _Y.create(xgv.rows, ygv.cols, ygv.type());
    Mat X = _X.getMat();
    Mat Y = _Y.getMat();
    repeat(xgv.reshape(1, 1), (int)ygv.total(), 1, X);
    repeat(ygv.reshape(1, 1).t(), 1, (int)xgv.total(), Y);
    X.copyTo(_X);
    Y.copyTo(_Y);
    return NORMAL;
}