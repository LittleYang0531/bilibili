//客户端 
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<io.h>
#include"socket.h"
#include"socket.cpp"
using namespace std;
int main()
{
	Client cli;//创建服务端类库 
	string ip_tmp;char ip[1024]="";//获取读入的ip 
	cin>>ip_tmp;
	for (int i=0;i<ip_tmp.size();i++) ip[i]=ip_tmp[i];
	cli.SetEnvironment(ip,11000);//设置服务端运行环境 
	cli.Connect();//连接服务器
	cli.SendData("Hello Server!There is Client!",1024);//向服务端发送信息
	char Recv_Data[1024]="";//从服务端接受的信息 
	cli.RecvData(Recv_Data,1024);//从服务端接收信息 
	cout<<Recv_Data<<endl;
	getch();
	return 0;
}
//注意：客户端接收信息和服务端发送信息要一致，否则会出现发送错误的情况！(当我没说)
