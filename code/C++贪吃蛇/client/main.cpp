#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include"socket.h"
#include"socket.cpp"
using namespace std;
int VanGo[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
int Map[36][36];
int Map2[36][36];
bool in(int x,int y)
{
	return x>0&&x<=35&&y>0&&y<=35;
}
void coord(int x,int y)
{
	COORD pos;HANDLE hOut;
	pos.X=y;
	pos.Y=x;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut,pos);
}
void Change(int lastx,int lasty,int startx,int starty)
{
	coord(lastx,lasty*2);
	cout<<"  ";
	coord(startx,starty*2);
	cout<<"��";
}
int main()
{
	ofstream ywhout("log.txt");
	ifstream ywhin("config.tmp");
	string ip;int port,type;
	ywhin>>type>>ip>>port;
	ywhin.close();
	ywhout<<"�ļ����ܳɹ�!"<<endl;
	Client cli;
	cli.SetEnvironment(ip,port);
	ywhout<<"�ͻ������л�����ɹ�!"<<endl;
	cli.Connect();
	ywhout<<"���������ӳɹ�!"<<endl;
	srand(time(NULL));
	Sleep(1000);
	
	
	
	
	int headx=1,heady=3,tailx=1,taily=1,direction=2,length=3;
	int headx2=35,heady2=33,tailx2=35,taily2=35,direction2=4,length2=3;
	if (type==2)
	{
		swap(headx,headx2);
		swap(heady,heady2);
		swap(tailx,tailx2);
		swap(taily,taily2);
		swap(direction,direction2);
	}
	ywhout<<"������Ϣ���óɹ�!"<<endl;
	
	int goalx,goaly;bool ifgoal=0;
	coord(0,0);
	for (int i=0;i<37;i++) cout<<"��";
	for (int i=0;i<37;i++)
	{
		coord(i,0);
		cout<<"��";
		coord(i,72);
		cout<<"��";
	}
	coord(36,0);
	for (int i=0;i<37;i++) cout<<"��";
	if (type==1)
	{
		Map[1][1]=Map[1][2]=Map[1][3]=2;
		Map2[35][35]=Map2[35][34]=Map2[35][33]=4;
	}
	else
	{
		Map2[1][1]=Map2[1][2]=Map2[1][3]=2;
		Map[35][35]=Map[35][34]=Map[35][33]=4;
	}
	coord(1,2);
	for (int i=0;i<3;i++) cout<<"��";
	coord(35,66);
	for (int i=0;i<3;i++) cout<<"��";
	coord(38,2);
	ywhout<<"ͼ�δ�ӡ�ɹ�!"<<endl;
	while (1)
	{
		Map[headx][heady]=direction;
		Map2[headx2][heady2]=direction2;
		ywhout<<"��ͼͷ���óɹ�!"<<endl;
		while (!ifgoal)
		{
			char x[1024]="",y[1024]="";int xx,yy;
			cli.SendData("B",1024);
			ywhout<<"�������ͷ��ͳɹ�!"<<endl;
			cli.RecvData(x,1024);
			cli.RecvData(y,1024);
			ywhout<<"�����������ܳɹ�!x:"<<x<<",y:"<<y<<endl;
			xx=StringToInt(x);yy=StringToInt(y);
			if (Map[xx][yy]==0&&Map2[xx][yy]==0)
			{
				ifgoal=1;
				goalx=xx;goaly=yy;
				coord(goalx,goaly*2);
				cout<<"��";
			}
		}
		ywhout<<"��������óɹ�!"<<endl;
		headx+=VanGo[direction-1][0];heady+=VanGo[direction-1][1];
		headx2+=VanGo[direction2-1][0];heady2+=VanGo[direction2-1][1];
		ywhout<<"��ͷ�ƶ��ɹ�!"<<endl;
		if (Map[headx][heady]!=0||!in(headx,heady))
		{
			Sleep(100);
			MessageBox(NULL,"You Lost!","Finished",MB_OK);
			ywhout<<"��Ϣ��ʾ�ɹ�!"<<endl;
			coord(39,0);
			return 0;
		}
		if (Map[headx2][heady2]!=0||!in(headx2,heady2))
		{
			Sleep(100);
			MessageBox(NULL,"You Win!","Finished",MB_OK);
			ywhout<<"��Ϣ��ʾ�ɹ�!"<<endl;
			coord(39,0);
			return 0;
		}
		if (headx==goalx&&heady==goaly)
		{
			coord(headx,heady*2);
			cout<<"��";
			coord(38,2);
			ywhout<<"��ͷ�ƶ��ɹ�!"<<endl;
			ifgoal=0;
		}
		else 
		{
			Change(tailx,taily,headx,heady);
			int beforex=tailx,beforey=taily;
			tailx+=VanGo[Map[beforex][beforey]-1][0];taily+=VanGo[Map[beforex][beforey]-1][1];
			Map[beforex][beforey]=0;
			ywhout<<"��ͷ����β�任�ɹ�!"<<endl;
		}
		if (headx2==goalx&&heady2==goaly)
		{
			coord(headx2,heady2*2);
			cout<<"��";
			coord(38,2);
			ifgoal=0; 
			ywhout<<"��ͷ�ƶ��ɹ�!"<<endl;
		}
		else
		{
			Change(tailx2,taily2,headx2,heady2);
			int beforex2=tailx2,beforey2=taily2;
			tailx2+=VanGo[Map2[beforex2][beforey2]-1][0];taily2+=VanGo[Map2[beforex2][beforey2]-1][1];
			ywhout<<"�Է���ͷ����β�任�ɹ�!��ǰtailx:"<<beforex2<<",taily"<<beforey2<<endl;
			Map2[beforex2][beforey2]=0;
		}
		if (kbhit())
		{
			char change=getch();
			switch(change)
			{
				case 'A':case 'a':direction=4;break;
				case 'S':case 's':direction=1;break;
				case 'D':case 'd':direction=2;break;
				case 'W':case 'w':direction=3;break;
			}
			ywhout<<"���̶�ȡ�ɹ�!"<<endl;
		}
		cli.SendData("A",1024);
		ywhout<<"�������ͷ��ͳɹ�!"<<endl;
		string tmp=IntToString(direction);
		char tmp1[8192]="";
		for (int i=0;i<tmp.size();i++) tmp1[i]=tmp[i];
		cli.SendData(tmp1,1024);
		ywhout<<"���߷����ͳɹ�!"<<endl;
		char direction_tmp[1024];
		cli.RecvData(direction_tmp,1024);
		ywhout<<"�Է�������ܳɹ�!"<<endl;
		direction2=StringToInt(direction_tmp);
		Sleep(100);
	}
}
