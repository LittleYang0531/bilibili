//�ͻ��� 
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<io.h>
#include"socket.h"
#include"socket.cpp"
using namespace std;
int main()
{
	Client cli;//������������ 
	string ip_tmp;char ip[1024]="";//��ȡ�����ip 
	cin>>ip_tmp;
	for (int i=0;i<ip_tmp.size();i++) ip[i]=ip_tmp[i];
	cli.SetEnvironment(ip,11000);//���÷�������л��� 
	cli.Connect();//���ӷ�����
	cli.SendData("Hello Server!There is Client!",1024);//�����˷�����Ϣ
	char Recv_Data[1024]="";//�ӷ���˽��ܵ���Ϣ 
	cli.RecvData(Recv_Data,1024);//�ӷ���˽�����Ϣ 
	cout<<Recv_Data<<endl;
	getch();
	return 0;
}
//ע�⣺�ͻ��˽�����Ϣ�ͷ���˷�����ϢҪһ�£��������ַ��ʹ���������(����û˵)
