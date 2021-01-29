// Demo_MixPhaseHologram.cpp --- ���ļ����� "main" ������
// ���ڻ����λ�ķǵ�������Ҷ��λȫϢͼ
// ʹ�ö�����λֱ��������λȫϢͼ�ᵼ�����ص�����ЧӦ
// ʹ�������λֱ��������λȫϢͼ�ᵼ�����ص�ɢ������

#include <iostream>
#include "opencv2/core.hpp"
#include "CComplexMat.hpp"
#include "CGH.hpp";
#include "opencv2/highgui.hpp";

using namespace cv;
using namespace gs;

static void help(const char** argv)
{
    printf("\n�˳�����ʾ�˻��ڻ����λ�ķǵ�������Ҷ��λȫϢͼ�������Լ��ع�.\n"
        "��ʾ���ع����������λ.\n"
        "����·��:\n %s.\n", argv[0]);
}

int main(int argc, const char** argv)
{
    help(argv);

    if (argc != 2) // ����ʱ��ҪЯ��ͼƬ·������(��Ŀ����-����-�������-ͼƬ·��)
    {
        std::cout << " Usage: display_image ImageToLoadAndDisplay" << std::endl;
        return -1;
    }

    // �������ͼ������ͼ��ֱ��ʡ��������͡����ݷ�Χ
    Mat Amp = imread(argv[1], IMREAD_GRAYSCALE);
    Amp = Mat_<double>(Amp);
    normalize(Amp, Amp, 0, 1, NORM_MINMAX);
    Size ImageSize = Size(800, 800);
    resize(Amp, Amp, ImageSize);
    copyMakeBorder(Amp, Amp, 1000, 1000);
    // ����ȫϢͼ�Լ��ع�
    Mat Hologram;
    nonIterFourier(Amp, Hologram, 800, 800, 0.35);
    Mat recAmplitude;
    Mat recPhase;
    recFourier(Hologram, recAmplitude, recPhase);
    imshow("���", recAmplitude);
    imshow("��λ", recPhase);
    waitKey(0);
}