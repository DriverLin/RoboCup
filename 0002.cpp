#include<stdio.h>
#include<iostream>
#include<math.h>
#include<windows.h>
#define MAXLENGTH 1000
#define π 3.141592653589793
using namespace std;

class Point{
	public:
		float x,y;
		float r,theta;
		char name;
		int number;
		Point(){};
		void setPointXY( float a , float b , char str , int n ){
			x = a ;
			y = b ;
			name = str ;
			number = n ;
		}
		void setPointRT( float a , float b , char str , int n ){
			r = a ;
			theta = b ;
			name = str ;
			number = n ;
		}
};

typedef struct{
	Point P[11];
	Point G[3];
	Point C;
}Coordinates;

void initalPoint(Coordinates &Coordinates){
	Coordinates.P[1].setPointXY(0,0,'P',1);
	Coordinates.P[2].setPointXY(-52.5,-32,'P',2);
	Coordinates.P[3].setPointXY(52.5,32,'P',3);
	Coordinates.P[4].setPointXY(52.5,-32,'P',4);
	Coordinates.P[5].setPointXY(0,-32,'P',5);
	Coordinates.P[6].setPointXY(0,32,'P',6);
	Coordinates.P[7].setPointXY(-30,-7,'P',7);
	Coordinates.P[8].setPointXY(-30,7,'P',8);
	Coordinates.P[9].setPointXY(30,7,'P',9);
	Coordinates.P[10].setPointXY(30,-7,'P',10);

	Coordinates.G[1].setPointXY(-52.5,0,'G',1);
	Coordinates.G[2].setPointXY(52.5,0,'G',2);

	Coordinates.C.setPointXY(0,0,'C',0);
}

void ReadRT( Point &P, char string[MAXLENGTH] , int &i , Coordinates xy ){//传入的i 应当指向标识字母
	char flag = string[i];
	int num ;
	if( flag == 'C'){
		i += 2;
		num = 0 ;
	}
	else {
		i += 3;
		num = (int)string[i-2] - 48 ;
	}
	int j = 0;
	char number[80];
	while( string[i] <= '9' && string[i] >= '-'){
		number[j] = string[i];
		j ++ ;
		i ++ ;
	}
	number[j] = '\0' ;
	float r;
	sscanf_s( number , "%f", &r );
	i ++ ;
	j = 0;
	while( string[i] <= '9' && string[i] >= '-'){
		number[j] = string[i];
		j ++ ;
		i ++ ;
	}
	number[j] = '\0';
	float theta;
	sscanf_s( number , "%f", &theta );	
	P.setPointRT( r , theta , flag , num );
	
	if(flag == 'P' ){
		P.x = xy.P[num].x;
		P.y = xy.P[num].y;
	}
	if(flag == 'G' ){
		P.x = xy.G[num].x;
		P.y = xy.G[num].y;
	}
	if(flag == 'C' ){
		P.x = xy.C.x;
		P.y = xy.C.y;
	}
}

int main() {
	Coordinates xy;
	initalPoint(xy);
	float SelfTheta = 180 ;//自身角度
	char string[MAXLENGTH];
	int count = 0;
	
	while( string[count-1] != '\n'){
		string[count] = getchar() ;
		count++;
	}
	string[count-1] = '\0' ;
	
	int i = 1 ;
	Point  P1 , P2 ;
	ReadRT( P1 , string , i , xy );
	while(string[i-1]!='(') i++;
	ReadRT( P2 , string , i , xy );

	cout<<P1.r<<"\t"<<P1.theta<<"\t"<<P1.name<<P1.number<<"\t"<<P1.x<<"\t"<<P1.y<<"\t"<<endl;

	cout<<P2.r<<"\t"<<P2.theta<<"\t"<<P2.name<<P2.number<<"\t"<<P2.x<<"\t"<<P2.y<<"\t"<<endl;

	float r1 = 180 - ( SelfTheta - P1.theta ) ;
	float r2 = 180 - ( SelfTheta - P2.theta ) ;

	float x = P1.x + P1.r*(float)cos((r1/180)*π);
	float y = P1.y + P1.r*(float)sin((r1/180)*π);
	cout<< x << "\n" << y << endl;

	x = P2.x + P2.r*(float)cos((r2/180)*π);
	y = P2.y + P2.r*(float)sin((r2/180)*π);
	cout<< x << "\n" << y << endl;
	
	system("pause");
	return 0 ;
}