#ifndef SAMPLEPOINT_H
#define SAMPLEPOINT_H

class SamplePoint{
private:
	double spData[200];
public:
	void setData(double data,int i){
		spData[i] = data;
	}
	
	//获取数据
	double getData(int i){
		return spData[i];
	}
	SamplePoint *nextData;
};

SamplePoint *getSample(SamplePoint head,int m){
	SamplePoint *p = new SamplePoint;
	*p = head;
	int i = 0;
	while(i++<m){
		p = p->nextData;
	}
	return p;
}

#endif