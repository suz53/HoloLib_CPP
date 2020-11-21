#include "CGh.hpp"

using namespace cv;

int gs::getDoublePhaseHologram(InputArray src_amplitude, InputArray src_phase, OutputArray _dst, int pixel_cell)
{
	Mat amplitude = src_amplitude.getMat();
	//normalize(amplitude, amplitude, 0.0, 1.0, NORM_MINMAX);

	Mat phase = src_phase.getMat();
	//normalize(phase, phase, 0.0, 1.0, NORM_MINMAX);
	phase = (phase * 2 + (-1)) * CV_PI;
	phase = wrapTo2pi(phase);
	/*normalize(phase, phase, 0.0, 1.0, NORM_MINMAX);*/

	double num[2][2] = { {1, 0}, {0, 1} };
	Mat Easy_CheckBoard(2, 2, CV_64F, num);
	int M = phase.rows / (2 * pixel_cell);
	int N = phase.cols / (2 * pixel_cell);
	Mat bw_CheckBoard = repeat(Easy_CheckBoard, M, N);
	bw_CheckBoard = neighborInterpolation(bw_CheckBoard, pixel_cell);
	Mat wh_CheckBoard = (bw_CheckBoard + (-1)) * (-1);

	Mat bw_phase = Mat_<double>(phase.rows, phase.cols, 0.0);
	Mat wh_phase = Mat_<double>(phase.rows, phase.cols, 0.0);
	for (int i = 0; i < phase.rows; i++)
	{
		for (int j = 0; j < phase.cols; j++)
		{
			bw_phase.at<double>(i, j) = phase.at<double>(i, j) + acos(amplitude.at<double>(i, j));
			wh_phase.at<double>(i, j) = phase.at<double>(i, j) - acos(amplitude.at<double>(i, j));
		}
	}
	bw_phase = mod(bw_phase, 2 * CV_PI);
	wh_phase = mod(wh_phase, 2 * CV_PI);

	Mat dst = _dst.getMat();
	dst = (bw_CheckBoard.mul(bw_phase)) + (wh_CheckBoard.mul(wh_phase));
	dst.copyTo(_dst);
	normalize(dst, dst, 0.0, 1.0, NORM_MINMAX);
	return NORMAL;
}
