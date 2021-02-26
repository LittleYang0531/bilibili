#include"socket.h"
void Server::SetEnvironment(std::string ip,int port)
{
	WORD w_req=MAKEWORD(2,2);
	WSADATA wsadata;
	int err;
	err=WSAStartup(w_req,&wsadata);
	if (err!=0)
	{
		MessageBox(NULL,"³õÊ¼»¯Ì×½Ó×Ö¿âÊ§°Ü£¡","Wrong!",MB_OK);
		exit(1);
	}
	if (LOBYTE(wsadata.wVersion)!=2||HIBYTE(wsadata.wHighVersion)!=2) 
	{
		MessageBox(NULL,"Ì×½Ó×Ö¿â°æ±¾ºÅ²»·û£¡","Wrong!",MB_OK);
		this->Clear();
		exit(2);
	}
	this->ServerAddress.sin_family=AF_INET;
	this->ServerAddress.sin_addr.S_un.S_addr=inet_addr(ip.c_str());
	this->ServerAddress.sin_port=htons(port);
	this->ServerSocket=socket(AF_INET,SOCK_STREAM,0);
	if (bind(this->ServerSocket,(SOCKADDR*)&this->ServerAddress,sizeof(SOCKADDR))==SOCKET_ERROR){
		MessageBox(NULL,"Ì×½Ó×Ö°ó¶¨Ê§°Ü£¡","Wrong!",MB_OK);
		this->Clear();
		exit(3);
	}
	if (listen(this->ServerSocket,SOMAXCONN)<0)
	{
		MessageBox(NULL,"ÉèÖÃ¼àÌý×´Ì¬Ê§°Ü£¡","Wrong!",MB_OK);
		this->Clear();
		exit(4);
	}
}
void Server::Connect()
{
	int len=sizeof(SOCKADDR);
	this->ClientSocket=accept(this->ServerSocket,(SOCKADDR*)&this->ClientAddress,&len);
	if (this->ClientSocket==SOCKET_ERROR) {
		MessageBox(NULL,"Á¬½ÓÊ§°Ü£¡","Wrong!",MB_OK);
		this->Clear();
		exit(5);
	}
}
void Server::SendData(char data[],int length)
{
	int SendLen=send(ClientSocket,data,length,0);
	if(SendLen<0)
	{
		MessageBox(NULL,"·¢ËÍÊ§°Ü£¡","Wrong!",MB_OK);
		this->Clear();
		exit(6);
	}
}
void Server::RecvData(char data[],int length)
{
	int RecvLen=recv(ClientSocket,data,length,0);
	if (RecvLen<0)
	{
		MessageBox(NULL,"½ÓÊÜÊ§°Ü£¡","Wrong!",MB_OK);
		this->Clear();
		exit(7);
	}
}
void Server::Clear()
{
	closesocket(this->ServerSocket);
	closesocket(this->ClientSocket);
	WSACleanup();
}
void Client::SetEnvironment(std::string ip,int port)
{
	WORD w_req=MAKEWORD(2,2);
	WSADATA wsadata;
	int err;
	err=WSAStartup(w_req,&wsadata);
	if (err!=0) {
		MessageBox(NULL,"³õÊ¼»¯Ì×½Ó×Ö¿âÊ§°Ü£¡","Wrong!",MB_OK);
		this->Clear();
		exit(1);
	}
	if (LOBYTE(wsadata.wVersion)!=2||HIBYTE(wsadata.wHighVersion)!=2)
	{
		MessageBox(NULL,"Ì×½Ó×Ö¿â°æ±¾ºÅ²»·û£¡","Wrong!",MB_OK);
		this->Clear();
		exit(2);
	}
	this->ServerAddress.sin_family=AF_INET;
	this->ServerAddress.sin_addr.S_un.S_addr=inet_addr(ip.c_str());
	this->ServerAddress.sin_port=htons(port);
}
void Client::Connect()
{
	this->ServerSocket=socket(AF_INET,SOCK_STREAM,0);
	if (connect(this->ServerSocket,(SOCKADDR*)&this->ServerAddress,sizeof(SOCKADDR))==SOCKET_ERROR) 
	{
		MessageBox(NULL,"·þÎñÆ÷Á¬½ÓÊ§°Ü£¡","Wrong!",MB_OK);
		this->Clear();
		exit(5);
	}
}
void Client::SendData(char data[],int Length)
{
	int SendLen=send(ServerSocket,data,Length,0);
	if (SendLen<0)
	{
		MessageBox(NULL,"·¢ËÍÊ§°Ü£¡","Wrong!",MB_OK);
		this->Clear();
		exit(6);
	}
}
void Client::RecvData(char data[],int Length)
{
	int RecvLen=recv(ServerSocket,data,Length,0);
	if (RecvLen<0) 
	{
		MessageBox(NULL,"½ÓÊÜÊ§°Ü£¡","Wrong!",MB_OK);
		this->Clear();
		exit(7);
	}
}
void Client::Clear()
{
	closesocket(this->ServerSocket);
	closesocket(this->ClientSocket);
	WSACleanup();
}


bool GetLocalIp(char* ip)
{
    WSADATA wsaData;  
    int ret=WSAStartup(MAKEWORD(2,2),&wsaData);  
    if (ret!=0)  return false;  
    char hostname[256];  
    ret=gethostname(hostname,sizeof(hostname));  
    if (ret==SOCKET_ERROR) return false;  
    HOSTENT* host=gethostbyname(hostname);  
    if (host==NULL) return false;  
    strcpy(ip,inet_ntoa(*(in_addr*)*host->h_addr_list));  
    return true;
}  
int StringToInt(std::string a)
{
	int ans=0;
	for (int i=0;i<a.size();i++) ans*=10,ans+=a[i]-48;
	return ans;
}
std::string IntToString(int a)
{
	char ans[101]="",k=-1;
	while (a!=0)
	{
		ans[++k]=a%10+48;
		a/=10;
	}
	for (int i=0;i<(k+1)/2;i++) std::swap(ans[i],ans[k-i]);
	return (char*)(((std::string)ans).data()); 
}
