#ifndef CGH
#define CGH

#include "opencv2/core.hpp"
#include "CComplexMat.hpp"

// 闪耀光栅方向标志
typedef int    Blaze_dir;
#define GS_UP        0
#define GS_DOWN      1
#define GS_LEFT      2
#define GS_RIGHT     3
#define GS_LEFTUP    4
#define GS_LEFTDOWN  5
#define GS_RIGHTUP   6
#define GS_RIGHTDOWN 7

// 矩阵扩展方式标志
typedef int EX_style;
#define GS_PIXEL   0
#define GS_OVERALL 1

// HoloLib 算法放置于gs命名空间内
namespace gs {

using namespace cv;

int linspace(OutputArray _dst, double A, double B, int n);

int meshgrid(InputArray xgv, InputArray ygv, OutputArray X, OutputArray Y);

Mat mod(Mat M, double n);

int iterFourier(InputArray _src, OutputArray _dst, int N_iter = 30);

int recFourier(InputArray _src, OutputArray _dst);

int iterFresnel(InputArray _src, OutputArray _dst, double width, double height, \
                 double z, double lambda = 532e-9, int N_iter = 30);

int propDFFT(CComplexMat& _src, CComplexMat& _dst, double width, double height, \
              double lambda, double z);

int recFresnel(InputArray _src, OutputArray _dst, double width, double height, \
                double z, double lambda = 532e-9);

int getLens(OutputArray _dst, double focus, double width, double height, \
             int width_Pixel, int height_Pixel, double lambda = 532e-9);

int getAxilens(OutputArray _dst, double focus, double Zg, double width, \
                double height, int width_Pixel, int height_Pixel, double lambda, \
                double R = 50e-3);

int getBlaze(OutputArray _dst, int Rows, int Cols, int T, Blaze_dir direction = GS_UP);

int stepPhase(InputArray _src, OutputArray _dst, int N_step = 4);

int expandMAT(InputArray _src, OutputArray _dst, int R_multiple = 4, \
               int C_multiple = 4, EX_style type = GS_PIXEL);

int repImage(InputArray _src, OutputArray _dst, int width_Pixel, int height_Pixel);
}

#endif // !CGH

