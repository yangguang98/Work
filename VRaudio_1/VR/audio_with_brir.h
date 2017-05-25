#ifndef AUDIO_WITH_BRIR_H
#define AUDIO_WITH_BRIR_H
#include "conv.h"
#include "SamplePoint.h"
//fnΪԭʼ�����㣬N1Ϊfn�ĳ��ȣ�hrirL��hrirR�ֱ�Ϊ���ݿ�������Ҷ��Ĳ�����
//leftEar��rightEar�ֱ�Ϊ������Ҷ��ķ���ֵ
void audio_with_brir(double *fn,int len,double *hrirL,double *hrirR,
	double *leftEar, double *rightEar) {
	int N = 200;
	conv(fn, hrirL, len, N, leftEar);
	conv(fn, hrirR, len, N, rightEar);

}



#endif
