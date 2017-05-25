#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "vrAudio.h"
#include<time.h>
using namespace std;

template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

void main() {
	clock_t start, finish;
	start = clock();
	ifstream in_l, in_r, in;
	ofstream out_l,out_r;
	string s;
	//输出的值
	double *leftEar = new double[30000], *rightEar = new double[30000];
	double *headSampleL = new double[250000], *headSampleR = new double[250000];
	int m = 0;
	//原始语音采样点
	double *soundInfo = new double[30000];

	int i = 0, j, k, l = 0;
	in_l.open("hrir_l.txt");
	in_r.open("hrir_r.txt");
	in.open("soundInfo1.txt");
	out_l.open("3DAudio_l.txt");
	out_r.open("3DAudio_r.txt");

	//读取原始采样点
	while (i<30000) {
		getline(in, s);
		*(soundInfo+(i++)) = stringToNum<double>(s);
	}
	in.close();

	//读取HRIR
	for (i = 0; i<25; i++) {
		for (j = 0; j<50; j++) {
			for (k = 0; k<200; k++) {
				getline(in_l, s);
				*(headSampleL+i*10000+j*200+k) = stringToNum<double>(s);
				getline(in_r, s);
				*(headSampleR + i * 10000 + j * 200 + k) = stringToNum<double>(s);
			}
		}
	}
	in_l.close();
	in_r.close();

	finish = clock();
	cout << "读取数据的时间为：" << (double)(finish - start) / CLOCKS_PER_SEC<<endl;

	while (1) {
		start = clock();
		vrAudio(-1,0,0, 0,0,0, 0,1,0, -1,0,0, 0,0,1,
			soundInfo, 30000, headSampleL,
			headSampleR, leftEar, rightEar);
	/*	for (i = 0; i < 10; i++) {
			cout << leftEar[i] << endl;
			cout << rightEar[i] << endl;
		}*/
		for (i = 0; i < 30000; i++) {
			out_l << leftEar[i] << endl;
			out_r << rightEar[i] << endl;
		}
		finish = clock();
		cout << "合成3D语音时间为：" << (double)(finish - start) / CLOCKS_PER_SEC<<endl;
		system("pause"); 
	}
}
