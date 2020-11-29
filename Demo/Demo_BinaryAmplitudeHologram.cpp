// Demo_BinaryAmplitudeHologram.cpp --- ���ļ����� "main" ������
// ��Ԫ���ȫϢͼʾ��
//
#include <iostream>
#include "opencv2/core.hpp"
#include "CComplexMat.hpp"
#include "CGH.hpp";
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace gs;

static void help(const char** argv)
{
    printf("\n�˳�����ʾ�˶�Ԫ���ȫϢͼ�������Լ��ع�.\n"
        "��ʾ���ع����������λ.\n"
        "����·��:\n %s.\n", argv[0]);
}

int main(int argc, const char** argv)
{
    help(argv);

    if (argc != 3) // ����ʱ��ҪЯ��ͼƬ·������(��Ŀ����-����-�������-ͼƬ·��)
    {
        std::cout << " Usage: display_image ImageToLoadAndDisplay" << std::endl;
        return -1;
    }

    // �����������λͼ������ͼ��ֱ��ʡ��������͡����ݷ�Χ
    Mat Amp = imread(argv[1], IMREAD_GRAYSCALE);
    Mat Pha = imread(argv[2], IMREAD_GRAYSCALE);
    Size dsize = Size(800, 800);
    resize(Amp, Amp, dsize);
    Amp = Mat_<double>(Amp);
    normalize(Amp, Amp, 0, 1, NORM_MINMAX);
    resize(Pha, Pha, dsize);
    Pha = Mat_<double>(Pha);
    normalize(Pha, Pha, 0, 1, NORM_MINMAX);

    // ���ɶ�Ԫ���ȫϢͼ
    Mat hologram = Mat(Amp.rows, Amp.cols, CV_64F);
    getBinaryHologram(Amp, Pha, hologram);

    // �ع���Ԫ���ȫϢͼ��������ʾ
    CComplexMat result(Amp.rows, Amp.cols);
    recDoubleHologram(hologram, result, 200);
    Mat recAmplitude = result.getAmplitude();
    Mat recPhase = result.getPhase();
    normalize(recAmplitude, recAmplitude, 0, 1, NORM_MINMAX);
    normalize(recPhase, recPhase, 0, 1, NORM_MINMAX);
    imshow("���", recAmplitude);
    imshow("��λ", recPhase);
    waitKey(0);
    return 0;
}
