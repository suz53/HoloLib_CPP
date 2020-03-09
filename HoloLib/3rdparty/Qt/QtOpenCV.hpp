/*/////////////////////////////////////////////////////////////////////////////
//  @file QtOpenCV.hpp
//  @author rlxu
//  @brief 实现 Qt 与 OpenCV 数据交换操作
//
//  @note 采用Qt代码注释风格，关键词说明如下
//      @brief 功能简要说明
//      @param 参数说明
//      @return 返回值说明
//      @note 注解
//
//*/

#ifndef QtOpenCV
#define QtOpenCV

#include <opencv2/opencv.hpp>
#include <QImage>
#include <QDebug>

/**
@brief 将 cv::Mat 转换为 QImage 类
@param mat 输入 cv::Mat 矩阵

@return 转换后的 QImage
@*/
QImage Mat2QImage(const cv::Mat& mat);

/**
@brief 将全息图重复拼接后裁剪到指定分辨率
@param image 输入 QImage 矩阵

@return 转换后的 cv::Mat 矩阵
@*/
cv::Mat QImage2cvMat(const QImage& image);

#endif // !QtOpenCV
