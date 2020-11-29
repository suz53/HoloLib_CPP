// Demo_BinaryAmplitudeHologram.cpp --- 此文件包含 "main" 函数。
// 二元振幅全息图示例
//
#include <iostream>
#include "opencv2/core.hpp"
#include "CComplexMat.hpp"
#include "CGH.hpp";
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace gs;

static void help(const char** argv)
{
    printf("\n此程序演示了二元振幅全息图的生成以及重构.\n"
        "显示了重构的振幅和相位.\n"
        "程序路径:\n %s.\n", argv[0]);
}

int main(int argc, const char** argv)
{
    help(argv);

    if (argc != 3) // 启动时需要携带图片路径参数(项目属性-调试-命令参数-图片路径)
    {
        std::cout << " Usage: display_image ImageToLoadAndDisplay" << std::endl;
        return -1;
    }

    // 读入振幅和相位图像、设置图像分辨率、数据类型、数据范围
    Mat Amp = imread(argv[1], IMREAD_GRAYSCALE);
    Mat Pha = imread(argv[2], IMREAD_GRAYSCALE);
    Size dsize = Size(800, 800);
    resize(Amp, Amp, dsize);
    Amp = Mat_<double>(Amp);
    normalize(Amp, Amp, 0, 1, NORM_MINMAX);
    resize(Pha, Pha, dsize);
    Pha = Mat_<double>(Pha);
    normalize(Pha, Pha, 0, 1, NORM_MINMAX);

    // 生成二元振幅全息图
    Mat hologram = Mat(Amp.rows, Amp.cols, CV_64F);
    getBinaryHologram(Amp, Pha, hologram);

    // 重构二元振幅全息图，并且显示
    CComplexMat result(Amp.rows, Amp.cols);
    recDoubleHologram(hologram, result, 200);
    Mat recAmplitude = result.getAmplitude();
    Mat recPhase = result.getPhase();
    normalize(recAmplitude, recAmplitude, 0, 1, NORM_MINMAX);
    normalize(recPhase, recPhase, 0, 1, NORM_MINMAX);
    imshow("振幅", recAmplitude);
    imshow("相位", recPhase);
    waitKey(0);
    return 0;
}
