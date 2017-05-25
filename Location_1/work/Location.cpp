#include <math.h>;
#define pi 3.1415926  //定义PI值

//计算两个向量的叉乘
void MulCross(double fx, double fy, double fz, 
	            double lx, double ly, double lz,
	              double *x,double *y,double *z)
{
	*x = fy*lz - fz*ly;//计算三阶行列式
	*y = fz*lx - fx*lz;
	*z = fx*ly - fy*lx;
}

//计算两条直线的夹角是否大于90度
bool IsAcute(double rx, double ry, double rz, double deltaX, double deltaY, double deltaZ)
{
	bool isAcute = false;

	//计算点乘的值，大于零两者夹角就小于90度，小于零两者夹角就大于90度
	isAcute = (rx*deltaX + ry*deltaY + rz*deltaZ) > 0 ? true:false;
}

//计算一条直线到一个平面的夹角  d为对方坐标，m为自己坐标，f为自己前方的向量，l为自己左方的向量
float CalculateAngle(double fx, double fy, double fz,
	double rx, double ry, double rz,double dx, double dy, double dz,
	double mx, double my, double mz,
	bool isElevation)
{
	double angle;
	double norVectorXHor, norVectorYHor, norVectorZHor;//平面法向量
	double fDistanceToHorPlane;   //点到水平面的距离
	double distanceFM;         // 斜线
	double posX, posY, posZ;    //平面外一点

	//计算平面的法向量
	MulCross(fx, fy, fz, rx, ry, rz, &norVectorXHor, &norVectorYHor, &norVectorZHor);

	if (isElevation)
	{
		//平面外一点
		posX = mx + dx, posY = my + dy, posZ = mz + dz;

		//斜线
		distanceFM = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
	}
	else{

		posX = dx, posY = dy, posZ = dz;
		//斜线
		distanceFM = sqrt(pow((dx-mx), 2) + pow((dy-my), 2) + pow((dz-mz), 2));
		
	}

	//点到平面的距离
	fDistanceToHorPlane = abs(norVectorXHor*posX + norVectorYHor*posY +
		norVectorZHor*posZ - norVectorXHor*mx - norVectorYHor*my - norVectorZHor*mz) /
		sqrt(norVectorXHor*norVectorXHor + norVectorYHor*norVectorYHor + norVectorZHor*norVectorZHor);

	

	//计算elevation

	//1.通过正弦值去计算幅度值（计算过程中的正负问题要注意，即在平面的正方还是下方）
	double elevationTemp = asin(fDistanceToHorPlane / distanceFM);  //幅度值

	//2.通过幅度值计算夹角
	angle = elevationTemp*(180 / pi);
}

//d为对方坐标，m为自己坐标，f为自己前方的向量，l为自己左方的向量，t为自己的正上方，x,y为输出
//通过各个坐标，计算出说话人相对于自己的位置，并计算出相应的左右转向和上下幅度；

 void Location(double dx, double dy, double dz, 
	                   double mx, double my, double mz, 
					   double fx, double fy, double fz, 
					   double rx, double ry, double rz, 
					   double tx,double ty,double tz,
					   int *x, int *y)
{
	 double elevation;//仰角
	 double azimute;//方位角
	 double deltaX=dx-mx, deltaY=dy-my, deltaZ=dz-mz;

	 bool isTop = dy > my;  //true表示对方在自己的上面，false表示对方在自己的下面
	 bool isFront = false; //true表示对方在自己的前方，false表示对方在自己的都放
	 bool isRight = false; //true表示对方在自己的右方，false表示对方在自己的左方

	 //仰角
	 elevation = CalculateAngle(deltaX, deltaY, deltaZ, rx, ry, rz, fx, fy, fz, mx, my, mz,true);
	 isFront = IsAcute(fx, fy, fz, deltaX, deltaY, deltaZ);
	 
	 //通过elevation确定在竖直方向上数据库中对应的点  *y

	 if (isTop)
	 {
		 //对方在自己的上面
		 if (isFront)
		 {
			 //对方在自己的前方
			 int num1 = int(elevation / 5.625);
			 (*y) = num1 + 8;
		 }
		 else{
			 //对方在自己的后方
			 int num1 = int(elevation / 5.625);
			 (*y) = 42-num1;
		 }
	 }
	 else{
		 //对方在自己的下面
		 if (elevation > 45)
		 {
			 //按照45来处理
			 if (isFront)
			 {
				 //对方在自己的前方
				 (*y) = 1;
			 }
			 else{
				 //对方在自己的后方
				 (*y) = 50;
			 }
		 }
		 else{
			 //小于45度
			 if (isFront)
			 {
				 //对方在自己的前方
				 (*y) = 8-int(elevation / 5.625);
			 }
			 else{
				 //对方在自己的后方
				 int num1 = int(elevation / 5.625);
				 (*y) = num1 + 42;
			 }
		 }
	 }
	 

	 //3.计算水平方向夹角

	 azimute = CalculateAngle(tx, ty, tz, fx, fy, fz, dx, dy, dz, mx, my, mz,false);
	 isRight = IsAcute(rx, ry, rz, deltaX, deltaY, deltaZ);
	 if (isRight)
	 {
		 (*x) = int(((90 + azimute) * 5) / 36);
	 }
	 else{
		 (*x) = int(((90 - azimute) * 5) / 36);
	 }
}