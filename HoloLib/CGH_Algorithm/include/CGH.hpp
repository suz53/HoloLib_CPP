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

// 默认参数
const double DEF_lambda = 532e-9;
const int DEF_Niter = 30;
const int DEF_Width = 1280;
const int DEF_Height = 1024;

using namespace cv;

/** @brief 实现类似MATLAB中linspace函数功能
@param A 数列左端点
@param B 数列右端点
@param n 个数

@return 返回序列向量 */
Mat linspace(double A, double B, int n);

/** @brief 实现类似MATLAB中meshgrid函数功能
@param _xgv x方向向量
@param _ygv y方向向量
@param X x坐标
@param Y y坐标

@return 函数运行状态

Example:
_xgv = [1 2 3];
_ygv = [1 2 3 4 5];

X = [ 1, 2, 3;
      1, 2, 3;
      1, 2, 3;
      1, 2, 3;
      1, 2, 3; ]

Y = [ 1, 1, 1;
      2, 2, 2;
      3, 3, 3;
      4, 4, 4;
      5, 5, 5; ]
*/
int meshgrid(InputArray _xgv, InputArray _ygv, OutputArray _X, OutputArray _Y);

/** @overload
@brief 实现类似MATLAB中mod函数功能，对OpenCV中mod函数重载
@param M 被除数矩阵
@param n 除数

@return 返回结果矩阵 */
Mat mod(Mat M, double n);

/**
@brief 迭代傅里叶算法
@param _src 输入振幅矩阵
@param _dst 输出纯相位矩阵
@param N_iter 迭代次数，默认30次

@return 函数运行状态 */
int iterFourier(InputArray _src, OutputArray _dst, int N_iter = DEF_Niter);

/**
@brief 傅里叶重构算法
@param _src 输入纯相位矩阵
@param _dst 归一化振幅矩阵

@return 函数运行状态 */
int recFourier(InputArray _src, OutputArray _dst);

/** overload
@brief 傅里叶重构算法
@param _src 输入纯相位矩阵
@param _dst 归一化振幅矩阵
@param min 原图最小值，double类型，可通过minMaxLoc()获得
@param max 原图最大值，double类型，可通过minMaxLoc()获得

@return 函数运行状态 */
int recFourier(InputArray _src, OutputArray _dst, double min, double max);

/**
@brief D-FFT菲涅耳传播算法
@param _src 输入波阵面复振幅矩阵
@param _dst 输出波阵面复振幅矩阵
@param width  波阵面宽度，单位：米
@param height 波阵面高度，单位：米
@param z 传播距离
@param lambda 波长，默认波长532nm

@return 函数运行状态 */
int propDFFT(CComplexMat& _src, CComplexMat& _dst, double width, double height, \
              double z, double lambda = 532e-9);

/**
@brief 迭代菲涅尔算法
@param _src 输入振幅矩阵
@param _dst 输出纯相位矩阵
@param width  物平面宽度，单位：米
@param height 物平面高度，单位：米
@param z 传播距离
@param lambda 波长，默认波长532nm
@param N_iter 迭代次数，默认30次

@return 函数运行状态 */
int iterFresnel(InputArray _src, OutputArray _dst, double width, double height, \
                 double z, double lambda = DEF_lambda, int N_iter = DEF_Niter);

/**
@brief 迭代菲涅尔重构算法
@param _src 输入振幅矩阵
@param _dst 输出纯相位矩阵
@param width  物平面宽度，单位：米
@param height 物平面高度，单位：米
@param z 传播距离
@param lambda 波长，默认波长532nm

@return 函数运行状态 */
int recFresnel(InputArray _src, OutputArray _dst, double width, double height, \
                double z, double lambda = DEF_lambda);

/** overload
@brief 迭代菲涅尔重构算法
@param _src 输入振幅矩阵
@param _dst 输出纯相位矩阵
@param width  物平面宽度，单位：米
@param height 物平面高度， 单位：米
@param z 传播距离
@param min 原图最小值，double类型，可通过minMaxLoc()获得
@param max 原图最大值，double类型，可通过minMaxLoc()获得
@param lambda 波长，默认波长532nm

@return 函数运行状态 */
int recFresnel(InputArray _src, OutputArray _dst, double width, double height, \
                double z, double min, double max, double lambda = DEF_lambda);

/**
@brief 获取菲涅尔透镜相位
@param focus 焦距，单位：米
@param width  透镜高度， 单位：米
@param height 透镜高度， 单位：米
@param width_Pixel  宽度像素数
@param height_Pixel 高度像素数
@param lambda 波长，默认波长532nm

@return 透镜相位矩阵 */
Mat getLens(double focus, double width, double height, \
             int width_Pixel, int height_Pixel, double lambda = 532e-9);

/**
@brief 获取轴锥镜相位
@param focus 焦距，单位：米
@param Zg 焦深，单位：米
@param width  透镜高度， 单位：米
@param height 透镜高度， 单位：米
@param width_Pixel  宽度像素数
@param height_Pixel 高度像素数
@param lambda 波长，默认波长532nm
@param R 透镜半径，默认50mm

@return 轴锥镜相位矩阵 */
Mat getAxilens(double focus, double Zg, double width, \
                double height, int width_Pixel, int height_Pixel, double lambda = DEF_lambda, \
                double R = 50e-3);

/**
@brief 获取闪耀光栅相位
@param Rows 矩阵行数
@param Cols 矩阵列数
@param T 闪耀光栅周期，默认为4
@param direction 闪耀方向。GS_UP上; GS_DOWN下; GS_LEFT左; GS_RIGHT右; GS_LEFTUP左上; GS_LEFTDOWN左上; GS_RIGHTUP右上; GS_RIGHTDOWN右下


@return 闪耀光栅相位矩阵 */
Mat getBlaze(int Rows, int Cols, int T = 4, Blaze_dir direction = GS_UP);

/**
@brief 相位分阶函数
@param _src 输入连续相位矩阵
@param _dst 输出分阶后相位矩阵
@param N_step 分阶数

@return 函数运行状态 */
int stepPhase(InputArray _src, OutputArray _dst, int N_step = 4);

/**
@brief DOE元件传播，返回振幅图像
@param _src 输入纯相位矩阵
@param _dst 输出波阵面振幅矩阵
@param width  波阵面宽度，单位：米
@param height 波阵面高度，单位：米
@param width_Pixel  宽度像素数
@param height_Pixel 高度像素数
@param z 传播距离
@param lambda 波长，默认波长532nm

@return 函数运行状态 

@note 只在全息图叠加DOE元件后使用propDOE重构
@*/
int propDOE(InputArray _src, OutputArray _dst, double width, double height, \
             double z, double lambda = DEF_lambda);

/**
@brief 矩阵扩展
@param _src 输入矩阵
@param _dst 输出矩阵
@param nx 水平扩展倍数，默认4倍
@param ny 垂直扩展倍数，默认4倍
@param type 扩展方式，GS_PIXEL:单个像素扩展为宏像素；GS_OVERALL:矩阵整体重复拼接。默认GS_OVERALL方式

@return 函数运行状态

@*/
int expandMAT(InputArray _src, OutputArray _dst, int nx = 4, int ny = 4, \
               EX_style type = GS_OVERALL);

/**
@brief 将全息图重复拼接后裁剪到指定分辨率
@param _src 输入矩阵
@param _dst 输出矩阵
@param width_Pixel  宽度像素数，默认1280
@param height_Pixel 高度像素数，默认1024

@return 函数运行状态
@*/
int repImage(InputArray _src, OutputArray _dst, int width_Pixel = DEF_Width, int height_Pixel = DEF_Height);

/** overload
@brief 图像四周补零
@param _src 输入矩阵
@param _dst 输出矩阵
@param width_Pixel  宽度像素数，默认1280
@param height_Pixel 高度像素数，默认1024

@return 函数运行状态
*/
int copyMakeBorder(InputArray _src, OutputArray _dst, int width_Pixel = DEF_Width, int height_Pixel = DEF_Height);

/**
@brief 获取彩色全息图
@param _src 三通道目标振幅矩阵
@param _dst 三通道相位输出矩阵
@param lambda_red   红色光波长
@param lambda_green 绿色光波长
@param lambda_blue  蓝色光波长

@return 函数运行状态
*/
int ColoHologram(InputArray _src, OutputArray _dst, double lambda_red, double lambda_green, double lambda_blue);

/**
@brief 利用双相位法得到纯相位全息图
@param _src 输入两通道目标复振幅矩阵
#param _dst 输出纯相位矩阵
@param pixel_cell 棋盘格宏像素大小，默认1

@return 函数运行状态
@*/
int getDoublePhaseHologram(CComplexMat& _src, OutputArray _dst, int pixel_cell = 1);


/**
@brief 将相位弧度值范围转换到[0, 2*PI],等于0或pi负偶数倍的值映射为0，等于pi偶数倍的值映射为2*pi。
@param _src 输入相位矩阵

@return 输出相位矩阵
@*/
Mat wrapTo2pi(InputArray _src);

/**
@brief 实现邻近插值法
@param _src 输入矩阵
@param zoom_factor 缩放倍数
@*/
Mat  neighborInterpolation(InputArray _src, double zoom_factor);

}

#endif // !CGH
