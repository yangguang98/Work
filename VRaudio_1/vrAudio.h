#ifndef VRAUDIO_H
#define VRAUDIO_H
#include "location.h"
#include "audio_with_brir.h"
#include "SamplePoint.h"

//d为说话人坐标，m为自己的坐标，f为自己前方向量，l为自己左方向量
//fn为需要处理的PCM，hrir为CIPIC数据库，leftEar和rightEar分别为左右耳返回值
void vrAudio(double dx, double dy, double dz, double mx, double my, double mz,
	double fx, double fy, double fz, double lx, double ly,double lz,double *fn,
	int len, SamplePoint *hrir_l,SamplePoint *hrir_r, double *leftEar,double *rightEar) {
	//x,y为水平转向和竖直幅度
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
