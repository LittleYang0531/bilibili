#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<io.h>
#include"socket.h"
#include"socket.cpp"
using namespace std;
int main()
{
	Server ser;
	srand(time(NULL));
	char ip[8192];int port=rand()%10000+50000;
	GetLocalIp(ip);
	ser.SetEnvironment(ip,port);
	cout<<"局域网游戏已在ip"<<ip<<",端口"<<port<<"上运行！"<<endl; 
	ser.Connect();
	cout<<"已检测到ip为"<<inet_ntoa(ser.ClientAddress.sin_addr)<<"的玩家加入了游戏"<<endl;
	cout<<"游戏将在3秒后开始(游戏进行时，请不要关闭此程序，谢谢！)"<<endl;
	Sleep(3000);
	Server ser1;int port1=rand()%10000+50000;
	ofstream ywhout("config.tmp");
	ywhout<<1<<" "<<ip<<" "<<port1;
	ywhout.close();
	ser1.SetEnvironment(ip,port1);
	system("start main.exe");
	ser1.Connect();
	while(1)
	{
		char type[1024]="";char direction[1024],direction_now[1024];
		ser1.RecvData(type,1024);
		if (type[0]=='A')
		{
			ser1.RecvData(direction_now,1024);
			ser.RecvData(direction,1024);
			ser1.SendData(direction,1024);
			ser.SendData(direction_now,1024);
		}
		else if (type[0]=='B')
		{
			int xx=rand()%35+1;
			int yy=rand()%35+1;
			string x_tmp=IntToString(xx),y_tmp=IntToString(yy);
			char x[8192]="",y[8192]="";
			for (int i=0;i<x_tmp.size();i++) x[i]=x_tmp[i];
			for (int i=0;i<y_tmp.size();i++) y[i]=y_tmp[i];
			
			ser1.SendData(x,1024);
			ser1.SendData(y,1024);
			ser.SendData(x,1024);
			ser.SendData(y,1024);
		}
	}
}
