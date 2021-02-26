//服务端 
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<io.h>
#include"socket.h"//引入socket库 
#include"socket.cpp"
using namespace std;
int main()
{
	Server ser;//创立服务端类库 
	char ip[1024]="";//ip地址 
	if (!GetLocalIp(ip))//无法获取到本地ip地址的情况 
	{
		MessageBox(NULL,"Failed to get local ip!","Wrong",MB_OK);
		return 0;
	}
	cout<<ip<<endl;//显示ip地址 
	ser.SetEnvironment(ip,11000);//设置服务端运行环境
	ser.Connect();//连接客户端
	char data[1024]="Hello Client!There is Server!";//将要发送的信息 
	ser.SendData(data,1024);//向客户端发送信息 
	char Recv_Data[1024]="";//从客户端接受的信息 
	ser.RecvData(Recv_Data,1024);//从客户端那里接收信息 
	cout<<Recv_Data<<endl;
	getch();
	return 0;
}
