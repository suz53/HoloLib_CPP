// Demo_OptimizedRandomPhaseHologram.cpp --- 此文件包含 "main" 函数。
// 基于优化随机相位的非迭代傅里叶相位全息图

#include <iostream>
#include "opencv2/core.hpp"
#include "CComplexMat.hpp"
#include "CGH.hpp";
#include "opencv2/highgui.hpp";

using namespace cv;
using namespace gs;

static void help(const char** argv)
{
    printf("\n此程序演示了基于优化随机相位的非迭代傅里叶相位全息图的生成以及重构.\n"
        "显示了重构的振幅和相位.\n"
        "程序路径:\n %s.\n", argv[0]);
}

int main(int argc, const char** argv)
{
    help(argv);

    if (argc != 2) // 启动时需要携带图片路径参数(项目属性-调试-命令参数-图片路径)
    {
        std::cout << " Usage: display_image ImageToLoadAndDisplay" << std::endl;
        return -1;
    }

    // 读入振幅图像、设置图像分辨率、数据类型、数据范围
    Mat Amp = imread(argv[1], IMREAD_GRAYSCALE);
    Amp = Mat_<double>(Amp);
    normalize(Amp, Amp, 0, 1, NORM_MINMAX);
    Size ImageSize = Size(800, 800);
    resize(Amp, Amp, ImageSize);
    copyMakeBorder(Amp, Amp, 1000, 1000);

    // 设置二值图像，与随机相位进行迭代，得到优化的随机相位
    Mat BinaryAmplitude = Mat::ones(800, 800, CV_64FC1);
    BinaryAmplitude = Mat_<double>(BinaryAmplitude);
    copyMakeBorder(BinaryAmplitude, BinaryAmplitude, 1000, 1000);
    Mat initialHologram;
    iterFourier(BinaryAmplitude, initialHologram, 30);
    Mat initialRecAmplitude;
    Mat initialRecPhase;
    recFourier(initialHologram, initialRecAmplitude, initialRecPhase);

    //利用优化的随机相位与目标图像直接生成全息图以及重构
    Mat Hologram;
    nonIterFourier(Amp, initialRecPhase, Hologram);
    Mat recAmplitude;
    recFourier(Hologram, recAmplitude);
    imshow("振幅", recAmplitude);
    waitKey(0);
}