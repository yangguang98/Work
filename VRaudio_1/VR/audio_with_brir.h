#ifndef AUDIO_WITH_BRIR_H
#define AUDIO_WITH_BRIR_H
#include "conv.h"
#include "SamplePoint.h"
//fn为原始语音点，N1为fn的长度，hrirL和hrirR分别为数据库左耳和右耳的采样点
//leftEar和rightEar分别为左耳和右耳的返回值
void audio_with_brir(double *fn,int len,double *hrirL,double *hrirR,
	double *leftEar, double *rightEar) {
	int N = 200;
	conv(fn, hrirL, len, N, leftEar);
	conv(fn, hrirR, len, N, rightEar);

}



#endif
