/*
复振幅类CComplexMat类的实现
*/

#include "CComplexMat.hpp"

using namespace cv;

gs::CComplexMat::CComplexMat()  { }
gs::CComplexMat::~CComplexMat() { }

gs::CComplexMat::CComplexMat(int _rows, int _cols)
{

    m_Re = Mat_<double>( _rows, _cols, 0.0 );
    m_Im = Mat_<double>( _rows, _cols, 0.0 );
    m_rows = _rows;
    m_cols = _cols;
    rows = m_rows;
    cols = m_cols;
    mergeRI();
}

gs::CComplexMat::CComplexMat(Mat M, CPLX_type type)
{
    if (M.channels() == 2 && type == GS_CLPX)
    {
        m_ComplexMatCore = M.clone();
    }
    else
    {
        switch (type)
        {
        case GS_REAL:
            m_Re = Mat_<double>(M.clone());
            m_Im = Mat_<double>(M.rows, M.cols, 0.0);
            mergeRI();
            break;
        case GS_IMAG:
            m_Re = Mat_<double>(M.rows, M.cols, 0.0);
            m_Im = Mat_<double>(M.clone());
            mergeRI();
            break;
        case GS_AMPL:
            m_Amplitude = Mat_<double>(M.clone());
            m_Phase     = Mat_<double>(M.rows, M.cols, 0.0);
            mergeAP();
            break;
        case GS_PHAS:
            m_Amplitude = Mat_<double>(M.rows, M.cols, 1.0);
            m_Phase     = Mat_<double>(M.clone());
            mergeAP();
            break;
        default:
            m_Re = Mat_<double>(M.clone());
            m_Im = Mat_<double>(M.rows, M.cols, 0.0);
            mergeRI();
            break;
        }
    }
    splitRI();
    splitAP();
    m_rows = M.rows;
    m_cols = M.cols;
    rows = m_rows;
    cols = m_cols; 
}

Mat gs::CComplexMat::getAmplitude()
{
    preProcess();
    return m_Amplitude;
}

Mat gs::CComplexMat::getPhase()
{
    preProcess();
    return m_Phase;
}

Mat gs::CComplexMat::getRe()
{
    preProcess();
    return m_Re;
}

Mat gs::CComplexMat::getIm()
{
    preProcess();
    return m_Im;
}

Mat gs::CComplexMat::getComplexM()
{
    preProcess();
    return m_ComplexMatCore;
}

int gs::CComplexMat::setRe(Mat R)
{
    preProcess();
    m_Re = R.clone();
    mergeRI();
    return NORMAL;
}

int gs::CComplexMat::setIm(Mat I)
{
    preProcess();
    m_Im = I.clone();
    mergeRI();
    return NORMAL;
}

int gs::CComplexMat::setAmplitude(Mat A)
{
    preProcess();
    m_Amplitude = A.clone();
    mergeAP();
    return NORMAL;
}

int gs::CComplexMat::setPhase(Mat P)
{
    preProcess();
    m_Phase = P.clone();
    mergeAP();
    return NORMAL;
}

int gs::CComplexMat::setComplexM(Mat M, CPLX_type type)
{
    preProcess();
    if (M.channels() == 2 && type == GS_REAL)
    {
        m_ComplexMatCore = M.clone();
    }
    else
    {
        switch (type)
        {
        case GS_REAL:
            m_Re = Mat_<double>(M.clone());
            m_Im = Mat_<double>(M.rows, M.cols, 0.0);
            mergeRI();
            break;
        case GS_IMAG:
            m_Re = Mat_<double>(M.rows, M.cols, 0.0);
            m_Im = Mat_<double>(M.clone());
            mergeRI();
            break;
        case GS_AMPL:
            m_Amplitude = Mat_<double>(M.clone());
            m_Phase = Mat_<double>(M.rows, M.cols, 0.0);
            mergeAP();
            break;
        case GS_PHAS:
            m_Amplitude = Mat_<double>(M.rows, M.cols, 1.0);
            m_Phase = Mat_<double>(M.clone());
            mergeAP();
            break;
        default:
            m_Re = Mat_<double>(M.clone());
            m_Im = Mat_<double>(M.rows, M.cols, 0.0);
            mergeRI();
            break;
        }
    }
    splitRI();
    splitAP();
    m_rows = M.rows;
    m_cols = M.cols;
    rows = m_rows;
    cols = m_cols;
    return NORMAL;
}

int gs::CComplexMat::setComplexM_RC(Mat R, Mat I)
{
    preProcess();
    m_Re = R.clone();
    m_Im = I.clone();
    mergeRI();
    return NORMAL;
}

int gs::CComplexMat::setComplexM_AP(Mat A, Mat P)
{
    preProcess();
    m_Amplitude = A.clone();
    m_Phase     = P.clone();
    mergeAP();
    return NORMAL;
}

int gs::CComplexMat::create(int _rows, int _cols)
{
    m_Re = Mat_<double>(_rows, _cols, 0.0);
    m_Im = Mat_<double>(_rows, _cols, 0.0);
    mergeRI();
    return NORMAL;
}

int gs::CComplexMat::splitRI()
{
    Mat channels[2];
    split(m_ComplexMatCore, channels);
    m_Re = channels[0];
    m_Im = channels[1];
    return NORMAL;
}

int gs::CComplexMat::mergeRI()
{
    Mat channels[2];
    channels[0] = m_Re;
    channels[1] = m_Im;
    merge(channels, 2, m_ComplexMatCore);
    return NORMAL;
}

int gs::CComplexMat::splitAP()
{
    splitRI();
    magnitude(m_Re, m_Im, m_Amplitude);
    phase(m_Re, m_Im, m_Phase);
    return NORMAL;
}

int gs::CComplexMat::mergeAP()
{
    Mat channels[2];
    channels[0] = m_Amplitude.mul(CosMat(m_Phase));
    channels[1] = m_Amplitude.mul(SinMat(m_Phase));
    merge(channels, 2, m_ComplexMatCore);
    return NORMAL;
}

int gs::CComplexMat::preProcess()
{
    splitRI();
    splitAP();
    m_rows = m_ComplexMatCore.rows;
    m_cols = m_ComplexMatCore.cols;
    rows = m_rows;
    cols = m_cols;
    return NORMAL;
}

Mat gs::CComplexMat::SinMat(Mat A)
{
    int _rows = A.rows;
    int _cols = A.cols;
    Mat out;
    out.create(_rows, _cols, A.type());
    for (int i = 0; i < _rows; i++)
    {
        double* ptra = (double*)(A.data + i * A.step);
        double* ptrout = (double*)(out.data + i * out.step);
        for (int j = 0; j < _cols; j++)
        {
            *ptrout = sin(*ptra);
            ptra++;
            ptrout++;
        }
    }
    return out;
}

Mat gs::CComplexMat::CosMat(Mat A)
{
    int _rows = A.rows;
    int _cols = A.cols;
    Mat out;
    out.create(_rows, _cols, A.type());
    for (int i = 0; i < _rows; i++)
    {
        double* ptra = (double*)(A.data + i * A.step);
        double* ptrout = (double*)(out.data + i * out.step);
        for (int j = 0; j < _cols; j++)
        {
            *ptrout = cos(*ptra);
            ptra++;
            ptrout++;
        }
    }
    return out;
}

gs::CComplexMat::operator _InputArray()
{
    return _InputArray(m_ComplexMatCore);
}

gs::CComplexMat::operator _OutputArray()
{
    return _OutputArray(m_ComplexMatCore);
}

Mat gs::CComplexMat::mul(CComplexMat CM)
{
    preProcess();
    CComplexMat res(m_rows, m_cols);
    Mat R = m_Re.mul(CM.getRe()) - m_Im.mul(CM.getIm());
    Mat I = m_Re.mul(CM.getIm()) + m_Im.mul(CM.getRe());
    res.setComplexM_RC(R, I);
    return res.getComplexM();
}
