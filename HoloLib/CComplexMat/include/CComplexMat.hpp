/*/////////////////////////////////////////////////////////////////////////////
//  @file CComplexMat.hpp
//  @author rlxu
//  @brief 由于OpenCV的复数运算功能缺失，该 CComplexMat 复振幅类实现复振幅运算，C++实现傅里叶光学的基础。
//         该类实现了双通道Mat对象，以实数、虚数、振幅、相位方式构建矩阵。
//         复数矩阵的点乘操作。该类兼容_InputArray类型，可直接被DFT函数接受。
//
//  @note 采用qt代码注释风格，关键词说明如下
//      @brief 功能简要说明
//      @param 参数说明
//      @return 返回值说明
//      @note 注解
//
//*/

#ifndef CCOMPLEXMAT
#define CCOMPLEXMAT

#include "opencv2/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
// #inlcude "GS_ERR_INFO.hpp"

/** @brief 错误类型 */
#define NORMAL 1;   // 无错误正常结束


/** @brief 单通道矩阵构造复振幅矩阵时，指明矩阵代表的光场信息*/
typedef int CPLX_type;
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
    /** @overload
    @brief 复振幅矩阵类默认构造函数
    @note 不会开辟数据存放空间
    */
    CComplexMat();

    /** @overload
    @brief 指定行数和列数构造空复振幅矩阵
    @param _rows 矩阵行数
    @param _cols 矩阵列数
    */
    CComplexMat(int _rows, int _cols);

    /** @overload
    @brief 通过已知数据构建
    @param M 初始化使用的矩阵
    @param type 矩阵代表的光场信息，GS_CLPX双通道矩阵、GS_REAL实部、GS_IMAG虚部、GS_AMPL振幅、GS_PHAS相位
    */
    CComplexMat(Mat M, CPLX_type type = GS_AMPL);

    /** 析构函数*/
    ~CComplexMat();

public:
    void Create(Mat M, CPLX_type type = GS_AMPL);

// 特性 Attributes
private:
    Mat m_ComplexMatCore;// 双通道复数矩阵 本类核心

// 属性 Property
private:
    Mat m_Re;           // 单通道矩阵 存放实部
    Mat m_Im;           // 单通道矩阵 存放虚部
    Mat m_Amplitude;    // 单通道矩阵 存放振幅
    Mat m_Phase;        // 单通道矩阵 存放相位
    int m_rows = 0;     // 矩阵行数 
    int m_cols = 0;     // 矩阵列数

public:
    int rows = 0;       // 矩阵行数
    int cols = 0;       // 矩阵列数

// 操作 Operations
// 对外接口
public:
    Mat getAmplitude();        // 获取振幅
    Mat getPhase();            // 获取相位
    Mat getRe();               // 获取实部
    Mat getIm();               // 获取虚部
    Mat getComplexM();         // 获取复振幅矩阵
    int setRe(Mat R);          // 设置实部
    int setIm(Mat I);          // 设置虚部
    int setAmplitude(Mat A);   // 设置振幅
    int setPhase(Mat P);       // 设置相位

    /** 
    @brief 通过已知数据构建
    @param M 初始化使用的矩阵
    @param type 矩阵代表的光场信息，GS_CLPX双通道矩阵、GS_REAL实部、GS_IMAG虚部、GS_AMPL振幅、GS_PHAS相位
    */
    int setComplexM(Mat M, CPLX_type type = GS_CLPX); // 设置
    int setComplexM_RC(Mat R, Mat I);   // 实部-虚部型
    int setComplexM_AP(Mat A, Mat P);   // 振幅-相位型
    int create(int _rows, int _cols);   // 指定行数和列数构造空复振幅矩阵
    // int CopyTo(CComplexMat& CM);     // 深复制

// 将零频分量移动到数组中心
public:
    int fftshift();


// 实现 Implementation 
// 内部转换
private:
    int splitRI();      // 分解m_ComplexMatCore到m_Re与m_Im
    int mergeRI();      // 合成m_Re与m_IM到m_ComplexMatCore
    int splitAP();      // 分解m_ComplexMatCore到m_Amplitude与m_Phase
    int mergeAP();      // 合成m_Amplitude与m_Phase到m_ComplexMatCore
    int preProcess();   // 对外接口调用时的内部预处理

// 矩阵三角函数运算
public:
    static Mat SinMat(Mat A);
    static Mat CosMat(Mat A);


// 类类型转换
public:
    operator _InputArray();     // 将 m_ComplexMatCore 转换为_InputArray
    operator _OutputArray();    // 将 m_ComplexMatCore 转换为_OutputArray

// Overridables 重载
// 矩阵间运算
public:
    Mat mul(CComplexMat CM);    // 复振幅矩阵点乘
};

typedef CComplexMat CCM;            // 复振幅类别名
typedef CComplexMat CplxM;          // 复振幅类别名
typedef const CComplexMat& InputCCM;// 复振幅矩阵输入类型
typedef CComplexMat& OutputCCM;     // 复振幅矩阵输出类型

}

#endif // !CCOMPLEXMAT
