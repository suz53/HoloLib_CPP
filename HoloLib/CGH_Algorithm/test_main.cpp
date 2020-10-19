#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "CGH.hpp"

using namespace cv;
using namespace gs;

int main(int argc, char** argv) // 启动时需要携带图片路径参数(项目属性-调试-命令参数-图片路径)
{
    if (argc != 2)
    {
        std::cout << " Usage: display_image ImageToLoadAndDisplay" << std::endl;
        return -1;
    }

    Mat IMG = imread(argv[1], IMREAD_GRAYSCALE);
    int width_Pixel = IMG.cols;
    int height_Pixel = IMG.rows;
    double width = width_Pixel * 12e-6;
    double height = height_Pixel * 12e-6;
    double z = 0.3;
    double f = 0.3;
    double Zg = 0.05;
    double lambda = 532e-9;

    Mat A, B, P, H, L, LP, ALP, BGP, HL, HB;

    LP = getLens(f, width, height, width_Pixel, height_Pixel, lambda);
    ALP = getAxilens(f, Zg, width, height, width_Pixel, height_Pixel, lambda);
    BGP = getBlaze(height_Pixel, width_Pixel, 4, GS_RIGHTDOWN);
    normalize(LP, A, 0.0, 1.0, NORM_MINMAX);
    imshow("菲涅尔透镜", A);
    normalize(ALP, A, 0.0, 1.0, NORM_MINMAX);
    imshow("轴锥镜透镜", A);
    normalize(BGP, A, 0.0, 1.0, NORM_MINMAX);
    imshow("闪耀光栅", A);

    iterFourier(IMG, H, 10);
    normalize(H, P, 0.0, 1.0, NORM_MINMAX);
    imshow("傅里叶全息图", P);

    recFourier(H, A);
    normalize(A, A, 0.0, 1.0, NORM_MINMAX);
    imshow("傅里叶全息图重构", A);

    iterFresnel(IMG, L, width, height, z, lambda, 10);
    normalize(L, P, 0.0, 1.0, NORM_MINMAX);
    imshow("菲涅尔全息图", P);

    recFresnel(L, A, width, height, z, lambda);
    normalize(A, A, 0.0, 1.0, NORM_MINMAX);
    imshow("菲涅尔全息图重构", A);

    HL = mod(LP + H, 2 * CV_PI);
    propDOE(HL, A, width, height, z, lambda);
    normalize(A, A, 0.0, 1.0, NORM_MINMAX);
    imshow("傅里叶全息图叠加透镜重构", A);

    HB = mod(H + BGP, 2 * CV_PI);
    recFourier(HB, A);
    normalize(A, A, 0.0, 1.0, NORM_MINMAX);
    imshow("傅里叶全息叠加闪耀光栅图重构", A);

    waitKey(0);
    std::cout << "Hello World!\n";
}
