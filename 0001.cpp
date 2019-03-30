#include<stdio.h>
#include<math.h>
#include<windows.h>
#define MAXLENGTH 1000
#define self 65536
#define referee 65537
#define online_coach_left 65538
//Sender 中用非角度的数字代码表示发送者

typedef struct{
	char ObjName[80];
	float Distance; 
	float Direction; 
	float DistChng;
	float DirChng;
	float BodyDir;
	float HeadDir;
} ObjInfo;


typedef struct{
	int time ;
	float Sender;//
	char message[80];
	ObjInfo ObjInfo[80];
	int ObjNum;
} information ;

typedef struct{
    char elem[MAXLENGTH];
    int top;
} Oseqstack;

void Initstack(Oseqstack *s){
    s->top = -1;
}

int IsEmpty(Oseqstack *s){
    if (s->top == -1) return 1;
    else return 0;
}

int IsFull(Oseqstack *s){
    if(s->top == 999 ) return 1;
    else return 0;
}

int Push(Oseqstack *s,char n){
    if(IsFull(s)) return 0;
    s->top++;
    s->elem[s->top] = n;
    return 1;
}

char Pop(Oseqstack *s){
    char n;
    if(IsEmpty(s)) return 0;
    n = s->elem[s->top];
    s->top--;
    return n;
}

int Getop(Oseqstack *s){
    if(IsEmpty(s)) return 0;
    return s->elem[s->top];
}

int check(char string[MAXLENGTH],char str[80],int *i){//在string中查找关键词str 并且修改i到尾部
	int j = 0;
	if( string[*i] == '\0' )
		return 0;
	while( str[j] != '\0' ){
		if( string[*i+j] != str[j] )
			return 0;
		j++;
	}
	*i += (j+1);
	return 1;
}

float achive(char string[MAXLENGTH],int *i){//转存char类型到float 并且修改i到尾部
	int j=0,flag=1;
	float dig=1,num=0;
	Oseqstack s;
	Initstack(&s);
	if(string[*i]=='-'){//如果是负数
		flag=-1;
		*i +=1;
	}
	if(string[*i]=='0'&&string[*i+1]=='.'){//小数
		*i += 2;
		dig /= 10;
		while( string[*i+j] >= '0' && string[*i+j] <='9'){
			Push(&s,string[*i+j]);
			j++;
		}
		while(!IsEmpty(&s)){
			num += ((int)Pop(&s)-48)*dig;
			dig /= 10;
		}
		*i += (j+1);
		return flag*num;
	}
	while( string[*i+j] >= '0' && string[*i+j] <='9'){
		Push(&s,string[*i+j]);
		j++;
	}
	while(!IsEmpty(&s)){
		num += ((int)Pop(&s)-48)*dig;
		dig*=10;
	}
	*i += (j+1);
	return flag*num;
}

float Sender(char string[MAXLENGTH],int *i){
	char s[80] = "self";
	char r[80] = "referee";
	char o[80] = "online_coach_left" ;
	if(check(string,s,i))
		return self;
	if(check(string,r,i))
		return referee;
	if(check(string,o,i))
		return online_coach_left;
	return achive(string,i);
}

void Getmessage(char string[MAXLENGTH],char str[80],int *i){
	int j = 0 ;
	Oseqstack s;
	Initstack(&s);
	Push(&s,0);
	Push(&s,1);
	while( Getop(&s) != 0 ){
		if(string[*i+1] == '('){
			Push(&s,1);
		}
		if(string[*i+1] == ')'){
			Pop(&s);
		}
		str[j] = string[*i];
		*i+=1;
		j++;
	}
	str[j]='\0';
	return;
}

void GetObjInfo(char string[MAXLENGTH],information &information,int *i){
	int j;
	char player[80] = "player";
	char goal[80] = "goal";
	char ball[80] = "ball";
	char flag[80] = "flag";
	information.ObjNum=0;
	while(string[*i-1]!=')'){
		//=====================================================================================================
		if(check(string,player,i)){//球员对象  具有Distance Direction DistChng  DirChng BodyDir HeadDir 共6个特征
			j=0;
			*i -= 8;
			while(string[*i-1] != ')' ){
				information.ObjInfo[information.ObjNum].ObjName[j] = string[*i];
				j++;
				*i+=1;
			}
			information.ObjInfo[information.ObjNum].ObjName[j]='\0';
			while(string[*i]<='0'||string[*i]>='9')
				*i+=1;
			information.ObjInfo[information.ObjNum].Distance = achive(string,i);
			information.ObjInfo[information.ObjNum].Direction = achive(string,i);
			information.ObjInfo[information.ObjNum].DistChng = achive(string,i);
			information.ObjInfo[information.ObjNum].DirChng = achive(string,i);
			information.ObjInfo[information.ObjNum].BodyDir = achive(string,i);
			information.ObjInfo[information.ObjNum].HeadDir = achive(string,i);
			information.ObjNum++;
			if(string[*i] == ')') //使指向此结构")"之后的位置的下一个结构的开头"("或全部结束则是")"   
				*i+=1;			  //作业中的示例并没有严格的数据格式 有的数字和")"之间有空格  有的没有
		}
		//========================================================================================================
		if(check(string,goal,i)){//目标对象 具有Distance Direction 共两个特征
			j=0;
			*i -= 6;
			while(string[*i-1] != ')' ){
				information.ObjInfo[information.ObjNum].ObjName[j] = string[*i];
				j++;
				*i+=1;
			}
			information.ObjInfo[information.ObjNum].ObjName[j]='\0';
			while(string[*i]<='0'||string[*i]>='9')
				*i+=1;
			information.ObjInfo[information.ObjNum].Distance = achive(string,i);
			information.ObjInfo[information.ObjNum].Direction = achive(string,i);
			information.ObjNum++;
			if(string[*i] == ')') *i+=1;
		}
		//========================================================================================================
		if(check(string,ball,i)){//球对象 具有Distance Direction DistChng DirChng 共四个特征
			j=0;
			*i -= 6;
			while(string[*i-1] != ')' ){
				information.ObjInfo[information.ObjNum].ObjName[j] = string[*i];
				j++;
				*i+=1;
			}
			information.ObjInfo[information.ObjNum].ObjName[j]='\0';
			while(string[*i]<='0'||string[*i]>='9')
				*i+=1;
			information.ObjInfo[information.ObjNum].Distance = achive(string,i);
			information.ObjInfo[information.ObjNum].Direction = achive(string,i);
			information.ObjInfo[information.ObjNum].DistChng = achive(string,i);
			information.ObjInfo[information.ObjNum].DirChng = achive(string,i);
			information.ObjNum++;
			if(string[*i] == ')') *i+=1;
		}
	    //============================================================================================================	
		if(check(string,flag,i)){//目标对象 具有Distance Direction 共两个特征
			j=0;
			*i -= 6;
			while(string[*i-1] != ')' ){
				information.ObjInfo[information.ObjNum].ObjName[j] = string[*i];
				j++;
				*i+=1;
			}
			information.ObjInfo[information.ObjNum].ObjName[j]='\0';
			while(string[*i]<='0'||string[*i]>='9')
				*i+=1;
			information.ObjInfo[information.ObjNum].Distance = achive(string,i);
			information.ObjInfo[information.ObjNum].Direction = achive(string,i);
			information.ObjNum++;
			if(string[*i] == ')') *i+=1;
		}
		//============================================================================================================	
	*i+=1;
	}
	information.ObjNum--;
	return;
}

void PrintMessage(information &information){
	int i = 0;
	printf("在%d周期hear从",information.time);
	if(information.Sender == self) 
		printf("self");
	else if(information.Sender == referee) 
		printf("referee");
	else if(information.Sender == online_coach_left) 
		printf("online_coach_left");
	else 
		printf("%f",information.Sender);
	printf("方向听到了");
	while(information.message[i]!='\0'){
		putchar(information.message[i]);
		i++;
	}
	printf("\n");
	printf("在%d周期see ",information.time);
	int j ;
	for( i = 0 ; i <= information.ObjNum ; i++ ){
		if(i!=0) printf("             ");
		if(information.ObjInfo[i].ObjName[1] == 'p'){
			j = 0;
			while(information.ObjInfo[i].ObjName[j] != '\0'){
				putchar(information.ObjInfo[i].ObjName[j]);
				j++;
			}
			printf("距离我");
			printf("Distance是%.2f，",information.ObjInfo[i].Distance);
			printf("Direction是%.2f，",information.ObjInfo[i].Direction);		
			printf("DistChng是%.2f，",information.ObjInfo[i].DistChng);
			printf("DirChng是%.2f，",information.ObjInfo[i].DirChng);
			printf("BodyDir是%.2f，",information.ObjInfo[i].BodyDir);
			printf("HeadDir是%.2f。\n",information.ObjInfo[i].HeadDir);
		}
		if(information.ObjInfo[i].ObjName[1] == 'g'){
			j = 0;
			while(information.ObjInfo[i].ObjName[j] != '\0'){
				putchar(information.ObjInfo[i].ObjName[j]);
				j++;
			}
			printf("距离我");
			printf("Distance是%.2f，",information.ObjInfo[i].Distance);
			printf("Direction是%.2f。\n",information.ObjInfo[i].Direction);	
		}
		if(information.ObjInfo[i].ObjName[1] == 'b'){
			j = 0;
			while(information.ObjInfo[i].ObjName[j] != '\0'){
				putchar(information.ObjInfo[i].ObjName[j]);
				j++;
			}
			printf("距离我");
			printf("Distance是%.2f，",information.ObjInfo[i].Distance);
			printf("Direction是%.2f，",information.ObjInfo[i].Direction);		
			printf("DistChng是%.2f，",information.ObjInfo[i].DistChng);
			printf("DirChng是%.2f。\n",information.ObjInfo[i].DirChng);	
		}
		if(information.ObjInfo[i].ObjName[1] == 'f'){
			j = 0;
			while(information.ObjInfo[i].ObjName[j] != '\0'){
				putchar(information.ObjInfo[i].ObjName[j]);
				j++;
			}
			printf("距离我");
			printf("Distance是%.2f，",information.ObjInfo[i].Distance);
			printf("Direction是%.2f。\n",information.ObjInfo[i].Direction);	
		}
	}
}

int main()
{
	char string[MAXLENGTH] ;//存放读取字符串
	char hear[80] = "hear";
	char see[80] = "see";
	int i = 0 , j = 0;
	information information;
	head:
	system("cls");
	while( string[i-1] != '\n' ){
		string[i] = getchar();
		i++;
	}//读取输入流到string 也可以改用其他方式输入
	string[i-1]='\0';
	i = 0;
	if(string[i]!='('){
		printf("输入格式错误！");
		system("pause");
		goto head;
	}
	while( string[i-1] != '\0' ){
		if(check(string,hear,&i)){
			information.time = (int)achive(string,&i);
			information.Sender = Sender(string,&i);
			if(string[i-1]!=')')
				Getmessage(string,information.message,&i);
			else//考虑此周期是没有接受到消息
				information.message[0]='\0';
		}
		if(check(string,see,&i)){
			information.time = (int)achive(string,&i);
			if(string[i-1]!=')')//同样考虑没有接受信息
				GetObjInfo(string,information,&i);
			else
				information.ObjNum = 0 ;
		}
		i++;
	}
	system("cls");
	PrintMessage(information);
	getchar();
	return 0;
}
