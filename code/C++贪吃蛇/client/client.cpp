#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<io.h>
#include"socket.h"
#include"socket.cpp"
using namespace std;
int main()
{
	string ip;int port;
	cout<<"请输入服务器ip:";
	cin>>ip;
	cout<<"请输入服务器端口:";
	cin>>port;
	Client cli;char ip1[8192];
	cli.SetEnvironment(ip,port);
	cli.Connect();
	GetLocalIp(ip1);
	ofstream ywhout("config.tmp");int port1=rand()%10000+50000;
	ywhout<<2<<" "<<ip1<<" "<<port1<<endl;
	ywhout.close();
	cout<<"连接成功!"<<endl;
	cout<<"游戏将在3秒后开始(游戏进行时，请不要关闭此程序，谢谢！)"<<endl;
	Sleep(3000);
	Server ser1;
	ser1.SetEnvironment(ip1,port1);
	system("start main.exe");
	ser1.Connect();
	while(1)
	{
		char type[1024]="";char direction[1024],direction_now[1024];
		ser1.RecvData(type,1024);
		if (type[0]=='A')
		{
			ser1.RecvData(direction_now,1024);
			cli.SendData(direction_now,1024);
			cli.RecvData(direction,1024);
			ser1.SendData(direction,1024);
		}
		else if (type[0]=='B')
		{
			char xx[1024],yy[1024];
			cli.RecvData(xx,1024);
			cli.RecvData(yy,1024);
			ser1.SendData(xx,1024);
			ser1.SendData(yy,1024);
		}
	}
}
