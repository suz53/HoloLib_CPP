#include "CGH.hpp"

using namespace cv;

int gs::expandMAT(InputArray _src, OutputArray _dst, int nx, int ny, EX_style type)
{
    Mat src = _src.getMat();
    Mat res;
    Mat tmp, val;
    switch (type)
    {
    case GS_OVERALL:
        res = repeat(src, ny, nx);
        break;
    case GS_PIXEL:
        res.create(src.rows * ny, src.cols * nx, src.type());
        tmp.create(src.rows * ny, src.cols, src.type());
        
        for (int r = 0; r < src.rows; r++)
        {
            val = repeat(src(Rect(0, r, src.cols, 1)), ny, 1);
            val.copyTo(tmp(Rect(0, r * ny, src.cols, ny)));
        }
        for (int c = 0; c < src.cols; c++)
        {
            val = repeat(tmp(Rect(c, 0, 1, tmp.rows)), 1, nx);
            val.copyTo(res(Rect(c*nx, 0, nx, tmp.rows)));
        }
        break;
    default:
        res = repeat(src, ny, nx);
        break;
    }
    res.copyTo(_dst);
    return NORMAL;
}