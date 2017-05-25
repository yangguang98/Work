#ifndef VRAUDIO_H
#define VRAUDIO_H
#include "location.h"
#include "audio_with_brir.h"
#include "SamplePoint.h"

//dΪ˵�������꣬mΪ�Լ������꣬fΪ�Լ�ǰ��������lΪ�Լ�������
//fnΪ��Ҫ�����PCM��hrirΪCIPIC���ݿ⣬leftEar��rightEar�ֱ�Ϊ���Ҷ�����ֵ
void vrAudio(double dx, double dy, double dz, double mx, double my, double mz,
	double fx, double fy, double fz, double lx, double ly,double lz,double *fn,
	int len, SamplePoint *hrir_l,SamplePoint *hrir_r, double *leftEar,double *rightEar) {
	//x,yΪˮƽת�����ֱ����
	int *x, *y,i=0;
	double *hrirL, *hrirR;
	location(dx, dy, dz, mx, my, mz, fx, fy, fz, lx, ly, lz, x, y);
	//double *hrirL = hrir + ((*x - 1) * 10000 + (*y - 1) * 200 + 1);
	for (i = 0; i < 200; i++) {
		*(hrirL + i) = (hrir_l + ((*x - 1) * 50 + (*y - 1)  + 1))->getData(i);
		*(hrirR + i) = (hrir_r + ((*x - 1) * 50 + (*y - 1)  + 1))->getData(i);
	}
	
	audio_with_brir(fn, len, hrirL, hrirR, leftEar, rightEar);
}

#endif
