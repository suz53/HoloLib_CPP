// test_CComplexMat.cpp : 此文件包含 "main" 函数。
// CComplexMat 复振幅类运行测试

#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "CComplexMat.hpp"

using namespace cv;
using namespace gs;

int main()
{
    Mat IMG = imread("..//lena.bmp", IMREAD_GRAYSCALE);
    imshow("原图", IMG);
    CplxM T(IMG, GS_AMPL);
    dft(T, T);
    idft(T, T);
    Mat A = T.getAmplitude();
    normalize(A, A, 0, 1, NORM_MINMAX);
    imshow("重构", A);
    waitKey(0);
    return 0;
}

