/*
复振幅类
*/

#ifndef CCOMPLEXMAT
#define CCOMPLEXMAT

#include <opencv2/core.hpp>

typedef int GS_type;
#define GS_CLPX 0
#define GS_REAL 1
#define GS_IMAG 2
#define GS_AMPL 3
#define GS_PHAS 4

// HoloLib 算法放置于gs命名空间内
namespace gs {

using namespace cv;

class CComplexMat
{

// 构造函数 Constructors
public:
    CComplexMat();
    CComplexMat(int _rows, int _cols);
    CComplexMat(Mat M, GS_type type = GS_CLPX);
    ~CComplexMat();

// 特性 Attributes
private:
    Mat m_ComplexMatCore;// 双通道复数矩阵 本类核心

// 属性 Property
private:
    Mat m_Re;           // 单通道矩阵 存放实部
    Mat m_Im;           // 单通道矩阵 存放虚部
    Mat m_Amplitude;    // 单通道矩阵 存放振幅
    Mat m_Phase;        // 单通道矩阵 存放相位
    int m_rows;         // 矩阵行数 
    int m_cols;         // 矩阵列数

public:
    int rows;           // 矩阵行数
    int cols;           // 矩阵列数

// 操作 Operations
// 对外接口
public:
    Mat getAmplitude();                 // 获取振幅
    Mat getPhase();                     // 获取相位
    Mat getRe();                        // 获取实部
    Mat getIm();                        // 获取虚部
    Mat getComplexM();                  // 获取复振幅矩阵
    int setRe(Mat R);                   // 设置实部
    int setIm(Mat I);                   // 设置虚部
    int setAmplitude(Mat A);            // 设置振幅
    int setPhase(Mat P);                // 设置相位
    int setComplexM(Mat M, GS_type type = GS_CLPX); // 设置
    int setComplexM_RC(Mat R, Mat I);   // 实部-虚部型
    int setComplexM_AP(Mat A, Mat P);   // 振幅-相位型
    int create(int _rows, int _cols);   // 创建
    // int CopyTo(CComplexMat& CM);        // 深复制

// 实现 Implementation 
// 内部转换
private:
    int splitRI();      // 分解m_ComplexM到m_ReM与m_ImM
    int mergeRI();      // 合成m_ReM与m_ImM到m_ComplexM
    int splitAP();      // 分解m_ComplexM到m_Amp与m_Phase
    int mergeAP();      // 合成m_Amp与m_Phase到m_ComplexM
    int preProcess();   // 对外接口调用时的内部预处理

// 矩阵三角函数运算
public:
    static Mat SinMat(Mat A);
    static Mat CosMat(Mat A);

// 类类型转换
public:
    operator _InputArray();
    operator _OutputArray();

// Overridables 重载
// 矩阵间运算
public:
    Mat mul(CComplexMat CM);        // 复振幅矩阵点乘
};

typedef CComplexMat CCM;            // 复振幅类别名
typedef CComplexMat CplxM;          // 复振幅类别名
typedef const CComplexMat& InputCCM;// 复振幅矩阵输入类型
typedef CComplexMat& OutputCCM;     // 复振幅矩阵输出类型

}

#endif // !CCOMPLEXMAT
