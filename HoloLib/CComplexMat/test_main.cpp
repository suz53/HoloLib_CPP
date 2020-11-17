//// test_CComplexMat.cpp : 此文件包含 "main" 函数。
//// CComplexMat 复振幅类运行测试
//
//#include <iostream>
//#include "opencv2/core.hpp"
//#include "opencv2/highgui.hpp"
//#include "CComplexMat.hpp"
//
//using namespace cv;
//using namespace gs;
//
//int main(int argc, char** argv) // 启动时需要携带图片路径参数(项目属性-调试-命令参数-图片路径)
//{
//    if (argc != 2)
//    {
//        std::cout << " Usage: display_image ImageToLoadAndDisplay" << std::endl;
//        return -1;
//    }
//
//    Mat IMG = imread(argv[1], IMREAD_GRAYSCALE);
//    std::cout << "Image Height: " << IMG.rows << std::endl;
//    std::cout << "Image Width : " << IMG.cols << std::endl;
//    imshow("原图", IMG);
//    CplxM T(IMG, GS_AMPL);
//    dft(T, T);
//    idft(T, T);
//    Mat A = T.getAmplitude();
//    normalize(A, A, 0, 1, NORM_MINMAX);
//    imshow("重构", A);
//    waitKey(0);
//    return 0;
//}
//
