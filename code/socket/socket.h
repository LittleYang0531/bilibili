#ifndef SOCKET_H
#define SOCKET_H
class Server
{
	public:
		SOCKET ServerSocket;
		SOCKET ClientSocket;
		SOCKADDR_IN ServerAddress;
		SOCKADDR_IN ClientAddress;
		void SetEnvironment(std::string ip,int port);
		void Connect();
		void SendData(char data[],int Length);
		void RecvData(char data[],int Length);
		void Clear();
};
class Client
{
	public:
		SOCKET ServerSocket;
		SOCKET ClientSocket;
		SOCKADDR_IN ServerAddress;
		SOCKADDR_IN ClientAddress;
		void SetEnvironment(std::string ip,int port);
		void Connect();
		void SendData(char data[],int Length);
		void RecvData(char data[],int Length);
		void Clear();
};

bool GetLocalIp(char* ip);
int StringToInt(std::string a);
std::string IntToString(int a);
#endif
