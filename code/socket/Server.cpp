//����� 
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#include<io.h>
#include"socket.h"//����socket�� 
#include"socket.cpp"
using namespace std;
int main()
{
	Server ser;//������������ 
	char ip[1024]="";//ip��ַ 
	if (!GetLocalIp(ip))//�޷���ȡ������ip��ַ����� 
	{
		MessageBox(NULL,"Failed to get local ip!","Wrong",MB_OK);
		return 0;
	}
	cout<<ip<<endl;//��ʾip��ַ 
	ser.SetEnvironment(ip,11000);//���÷�������л���
	ser.Connect();//���ӿͻ���
	char data[1024]="Hello Client!There is Server!";//��Ҫ���͵���Ϣ 
	ser.SendData(data,1024);//��ͻ��˷�����Ϣ 
	char Recv_Data[1024]="";//�ӿͻ��˽��ܵ���Ϣ 
	ser.RecvData(Recv_Data,1024);//�ӿͻ������������Ϣ 
	cout<<Recv_Data<<endl;
	getch();
	return 0;
}
