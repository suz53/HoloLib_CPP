// Demo_doublePhaseHologram.cpp --- 此文件包含 "main" 函数。
// 双相位全息图示例
//
#include <iostream>
#include "opencv2/opencv.hpp"
#include "CComplexMat.hpp"
#include "CGH.hpp"

using namespace cv;
using namespace gs;

static void help(const char** argv)
{
    printf("\n此程序演示了双相位全息图的生成以及重构.\n"
           "显示了生成的双相位全息图以及重构的振幅和相位.\n"
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
    Mat amplitude = imread(argv[1], IMREAD_GRAYSCALE);
    Mat phase = imread(argv[2], IMREAD_GRAYSCALE);
    Size dsize = Size(800, 800);
    phase = Mat_<double>(phase);
    amplitude = Mat_<double>(amplitude);
    //resize(amplitude, amplitude, dsize);
    //resize(phase, phase, dsize);
    normalize(phase, phase, 0.0, 1.0, NORM_MINMAX);
    normalize(amplitude, amplitude, 0.0, 1.0, NORM_MINMAX);

    // 生成双相位全息图
    Mat hologram;
    getDoublePhaseHologram(amplitude, phase, hologram, 1);

    // 显示双相位全息图
    normalize(hologram, hologram, 0, 1, NORM_MINMAX);
    imshow("双相位全息图", hologram);

    // 重构双相位全息图，并且显示
    CComplexMat result(800, 800);
    recDoubleHologram(hologram, result, 200);
    Mat recAmplitude = result.getAmplitude();
    Mat recPhase = result.getPhase();
    normalize(recAmplitude, recAmplitude, 0, 1, NORM_MINMAX);
    normalize(recPhase, recPhase, 0, 1, NORM_MINMAX);
    imshow("振幅", recAmplitude);
    imshow("相位", recPhase);
    waitKey(0);
}
