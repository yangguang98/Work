#include <math.h>;

#define pi 3.1415926  //����PIֵ

//�������������Ĳ��
void MulCross(double fx, double fy, double fz, 
	            double lx, double ly, double lz,
	              double *x,double *y,double *z)
{
	*x = fy*lz - fz*ly;//������������ʽ
	*y = fz*lx - fx*lz;
	*z = fx*ly - fy*lx;
}

//��������ֱ�ߵļн��Ƿ����90��
bool IsAcute(double fx, double fy, double fz, double deltaX, double deltaY, double deltaZ)
{
	bool isAcute = false;

	//�����˵�ֵ�����������߼нǾ�С��90�ȣ�С�������߼нǾʹ���90��
	isAcute = (fx*deltaX + fy*deltaY + fz*deltaZ) > 0 ? true:false;
	return isAcute;
}

//����һ��ֱ�ߵ�һ��ƽ��ļн�  dΪ�Է����꣬mΪ�Լ����꣬fΪ�Լ�ǰ����������lΪ�Լ��󷽵�����
double CalculateAngle(double dx, double dy, double dz,
	double mx, double my, double mz,
	double fx, double fy, double fz,
	double lx, double ly, double lz)
{
	double angle;
	double norVectorXHor, norVectorYHor, norVectorZHor;//ˮƽ�淨����
	double fDistanceToHorPlane;   //�㵽ˮƽ��ľ���
	double deltaX = dx - mx, deltaY = dy - my, deltaZ = dz - mz;
	double distanceFM;         // ����ľ���


	//����ƽ��ķ�����
	MulCross(fx, fy, fz, lx, ly, lz, &norVectorXHor, &norVectorYHor, &norVectorZHor);

	//����㵽ƽ��ľ���
	fDistanceToHorPlane = abs(norVectorXHor*dx + norVectorYHor*dy +
		norVectorZHor*dz - norVectorXHor*mx - norVectorYHor*my - norVectorZHor*mz) /
		sqrt(norVectorXHor*norVectorXHor + norVectorYHor*norVectorYHor + norVectorZHor*norVectorZHor);

	//������֮��ľ���
	distanceFM = sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));

	//����elevation

	//1.ͨ������ֵȥ�������ֵ����������е���������Ҫע�⣬����ƽ������������·���
	double elevationTemp = asin(fDistanceToHorPlane / distanceFM);  //����ֵ

	//2.ͨ������ֵ����н�
	angle = elevationTemp*(180 / pi);
	return angle;
}

//dΪ�Է����꣬mΪ�Լ����꣬fΪ�Լ�ǰ����������lΪ�Լ��󷽵�������tΪ�Լ������Ϸ���x,yΪ���
//ͨ���������꣬�����˵����������Լ���λ�ã����������Ӧ������ת������·��ȣ�

 void location(double dx, double dy, double dz, 
	                   double mx, double my, double mz, 
					   double fx, double fy, double fz, 
					   double lx, double ly, double lz, 
					   double tx,double ty,double tz,
					   int *x, int *y)
{
	 double elevation;//����
	 double azimute;//��λ��
	 double deltaX=dx-mx, deltaY=dy-my, deltaZ=dz-mz;

	 bool isTop = dy > my;  //true��ʾ�Է����Լ������棬false��ʾ�Է����Լ�������
	 bool isFront = false; //true��ʾ�Է����Լ���ǰ����false��ʾ�Է����Լ��Ķ���
	 bool isRight = false; //true��ʾ�Է����Լ����ҷ���false��ʾ�Է����Լ�����

	 //����
	 elevation = CalculateAngle(dx,dy,dz,mx,my, mz,fx,fy,fz,lx,ly,lz);
	 isFront = IsAcute(fx, fy, fz, deltaX, deltaY, deltaZ);
	 
	 //ͨ��elevationȷ������ֱ���������ݿ��ж�Ӧ�ĵ�  *y

	 if (isTop)
	 {
		 //�Է����Լ�������
		 if (isFront)
		 {
			 //�Է����Լ���ǰ��
			 int num1 = int(elevation / 5.625);
			 (*y) = num1 + 8;
		 }
		 else{
			 //�Է����Լ��ĺ�
			 int num1 = int(elevation / 5.625);
			 (*y) = 42-num1;
		 }
	 }
	 else{
		 //�Է����Լ�������
		 if (elevation > 45)
		 {
			 //����45������
			 if (isFront)
			 {
				 //�Է����Լ���ǰ��
				 (*y) = 1;
			 }
			 else{
				 //�Է����Լ��ĺ�
				 (*y) = 50;
			 }
		 }
		 else{
			 //С��45��
			 if (isFront)
			 {
				 //�Է����Լ���ǰ��
				 (*y) = 8-int(elevation / 5.625);
			 }
			 else{
				 //�Է����Լ��ĺ�
				 int num1 = int(elevation / 5.625);
				 (*y) = num1 + 42;
			 }
		 }
	 }
	 

	 //3.����ˮƽ����н�

	 azimute = CalculateAngle(dx, dy, dz, mx, my, mz, fx, fy, fz, tx,ty,tz);
	 isRight = IsAcute(lx, ly, lz, deltaX, deltaY, deltaZ);
	 if (isRight)
	 {
		 (*x) = int(((90 - azimute) * 5) / 36);
	 }
	 else{
		 (*x) = int((90 + azimute) * 5) / 36;
	 }
}