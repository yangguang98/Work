#ifndef CONV_H
#define CONV_H
using namespace std;
//x为需要卷积的语音点，y为数据库中的采样点
//N1为x的长度，N2为y的长度，z为返回的值
void conv(double *x, double *y, int lenX, int lenY, double *z) {
	int i, m;
	double temp = 0;
	for (i = 0; i < lenX + lenY - 1; i++) {
		for (m = 0; m < lenX; m++) {
			if ((i - m) >= 0 && (i - m) < lenY)
				temp += *(x+m)*(*(y+i-m));
		}
		z[i] = temp;
		//cout << z[i] << endl;
	}
}

#endif

