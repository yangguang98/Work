#ifndef VRAUDIO_H
#define VRAUDIO_H
#include "location.h"
#include "conv.h"
#include<iostream>
#include "audio_with_brir.h"
#include "SamplePoint.h"
#include<time.h>
using namespace std;

//dΪ˵�������꣬mΪ�Լ������꣬fΪ�Լ�ǰ��������lΪ�Լ�������
//fnΪ��Ҫ�����PCM��hrirΪCIPIC���ݿ⣬leftEar��rightEar�ֱ�Ϊ���Ҷ�����ֵ
void vrAudio(double dx, double dy, double dz, double mx, double my, double mz,
	double fx, double fy, double fz, double lx, double ly,
	double tx,double ty,double tz,double lz,double *fn,
	int len, double *hrir_l,double *hrir_r, double *leftEar,double *rightEar) {
	//x,yΪˮƽת�����ֱ����
	int *x=new int, *y=new int,i=0;
	double hrirL[200], hrirR[200];
	location(dx, dy, dz, mx, my, mz, fx, fy, fz, lx, ly, lz,tx,ty,tz, x, y);
	//double *hrirL = hrir + ((*x - 1) * 10000 + (*y - 1) * 200 + 1);
	for (i = 0; i < 200; i++) {
		hrirL[i] = hrir_l[(*x) * 10000 + (*y) * 200 + i];
		hrirR[i] = hrir_r[(*x) * 10000 + (*y) * 200 + i];
		/*hrirL[i] = hrir_l[i];
		hrirR[i] = hrir_r[i];*/
	}
	clock_t start, finish;
	start = clock();
	conv(fn, hrirL, len, 200, leftEar);
	conv(fn, hrirR, len, 200, rightEar);
	finish = clock();
	cout << "���ʱ��Ϊ��" << (double)(finish - start) / CLOCKS_PER_SEC<<endl;
}

#endif
