// Demo_Quadratic-phaseFourierPhaseHologram.cpp --- 此文件包含 "main" 函数。
// 基于二次相位的优化傅里叶非迭代算法
// 重构相位保持均匀分布，抑制散斑噪声


#include <iostream>
#include "opencv2/core.hpp"
#include "CComplexMat.hpp"
#include "CGH.hpp";
#include "opencv2/highgui.hpp";

using namespace cv;
using namespace gs;

static void help(const char** argv)
{
    printf("\n此程序演示了基于二次相位的非迭代优化傅里叶相位全息图的生成以及重构.\n"
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

    // 设置二元振幅图像、二次相位，进行迭代优化得到优化的二次相位
    Mat BinaryAmplitude = Mat::ones(800, 800, CV_64FC1);
    BinaryAmplitude = Mat_<double>(BinaryAmplitude);
    copyMakeBorder(BinaryAmplitude, BinaryAmplitude, 1000, 1000);
    Mat initialHologram;
    optimizedIterFourier(BinaryAmplitude, initialHologram, 800, 800, 50, 1);
    Mat initialRecAmplitude;
    Mat initialRecPhase;
    recFourier(initialHologram, initialRecAmplitude, initialRecPhase);

    // 利用优化的二次相位与目标图像直接生成全息图以及重构
    // 读入振幅图像、设置图像分辨率、数据类型、数据范围
    Mat Amp = imread(argv[1], IMREAD_GRAYSCALE);
    Amp = Mat_<double>(Amp);
    normalize(Amp, Amp, 0, 1, NORM_MINMAX);
    Size ImageSize = Size(800, 800);
    resize(Amp, Amp, ImageSize);
    copyMakeBorder(Amp, Amp, 1000, 1000);
    Mat Hologram;
    nonIterFourier(Amp, initialRecPhase, Hologram);
    Mat recAmplitude;
    Mat recPhase;
    recFourier(Hologram, recAmplitude);
    normalize(recAmplitude, recAmplitude, 0, 1, NORM_MINMAX);
    Mat beita = Mat_<double>(Amp / recAmplitude);
    normalize(Amp.mul(beita), Amp, 0, 1, NORM_MINMAX);
    nonIterFourier(Amp, initialRecPhase, Hologram);
    recFourier(Hologram, recAmplitude, recPhase);
    imshow("振幅", recAmplitude);
    imshow("相位", recPhase);
    waitKey(0);
}