// Demo_Quadratic-phaseFourierPhaseHologram.cpp --- ���ļ����� "main" ������
// ���ڶ�����λ���Ż�����Ҷ�ǵ����㷨
// �ع���λ���־��ȷֲ�������ɢ������


#include <iostream>
#include "opencv2/core.hpp"
#include "CComplexMat.hpp"
#include "CGH.hpp";
#include "opencv2/highgui.hpp";

using namespace cv;
using namespace gs;

static void help(const char** argv)
{
    printf("\n�˳�����ʾ�˻��ڶ�����λ�ķǵ����Ż�����Ҷ��λȫϢͼ�������Լ��ع�.\n"
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

    // ���ö�Ԫ���ͼ�񡢶�����λ�����е����Ż��õ��Ż��Ķ�����λ
    Mat BinaryAmplitude = Mat::ones(800, 800, CV_64FC1);
    BinaryAmplitude = Mat_<double>(BinaryAmplitude);
    copyMakeBorder(BinaryAmplitude, BinaryAmplitude, 1000, 1000);
    Mat initialHologram;
    optimizedIterFourier(BinaryAmplitude, initialHologram, 800, 800, 50, 1);
    Mat initialRecAmplitude;
    Mat initialRecPhase;
    recFourier(initialHologram, initialRecAmplitude, initialRecPhase);

    // �����Ż��Ķ�����λ��Ŀ��ͼ��ֱ������ȫϢͼ�Լ��ع�
    // �������ͼ������ͼ��ֱ��ʡ��������͡����ݷ�Χ
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
    imshow("���", recAmplitude);
    imshow("��λ", recPhase);
    waitKey(0);
}