//C语言编写Socket监听处理程序一例
//服务器端
//--------------------------------------------------------------------------------------------
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <fstream>
#include <iostream>
#include <ole2.h>
#include <conio.h>

#pragma comment(lib,"WS2_32.lib")

#define   MAX_PENDING_CONNECTS   4

//声明函数
void tt(void);
DWORD WINAPI HandleSocket(LPVOID lpParam);

//程序入口点
int _tmain(int argc, _TCHAR* argv[])
{
	 tt();
	 //stop screen method 1
	 char q;
	 cin>>q;
	 //stop screen method 2
	 //getchar();
	return 0;
}

//#include <winsock2.h>  //放在最顶端的.h中开头处
//#include <stdio.h>
//#include <stdlib.h>
//#pragma comment(lib,"WS2_32.lib")
void tt(void)
{
     WORD wVersionRequested;
	 WSADATA wsaData;
	 int err;

	 //版本请求
	 wVersionRequested = MAKEWORD( 1, 1 );
	 //初始化WinSock(WSAStartup函数)
	 err = WSAStartup( wVersionRequested, &wsaData);
	 if ( err != 0 )
	 {  //初始化出错了退出函数
		return;
	 }
	 //初始化成功！但版本不一致! 退出函数
	 if ( LOBYTE( wsaData.wVersion ) != 1 ||
			HIBYTE( wsaData.wVersion ) != 1 ) {
		  WSACleanup( ); //清除Socket
		  return;        //退出函数
	 }
     //生成一个socket(sockSrv变量)
	 //SOCK_STREAM  用于TCP协议
	 //SOCK_DGRAM   用于UDP协议
	 SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,0);  //使用TCP协议
	 //设置一个地址Socket(addrSrv变量)
	 SOCKADDR_IN addrSrv;
	 addrSrv.sin_addr.S_un.S_addr=inet_addr("192.168.1.232"); //本机IP地址
	 addrSrv.sin_family=AF_INET;
	 addrSrv.sin_port=htons(6000);                 //端口6000
     //绑定函数(指定本地IP地址所使用的端口号时候使用)
	 //(把sockSrv变量与addrSrv变量绑定在一起)
	 bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

	 //监听端口开始
	 if(listen(sockSrv,MAX_PENDING_CONNECTS)!=0)
	 {
		printf("listen(sock)   failed:   %d\n ",::WSAGetLastError());
		return;//ExitProcess(STATUS_FAILED);
	 }
	 printf("开始监听...");

	 //接收来自客户端的请求连接
	 SOCKET sockClient;
	 SOCKADDR_IN addrClient;//定义一个客户端Socket地址
	 int len=sizeof(SOCKADDR);
	 char recvBuf[100];
	 int recv_len=-1;
	 //
	 sockaddr_in	 acc_sin;
	 int	 acc_sin_len;
	 acc_sin_len=sizeof(acc_sin);
	 //
	 while(true)
	 {
		 //接收Socket请求   来自客户端的Connect
		 sockClient=accept(sockSrv,(struct sockaddr*)&acc_sin, &acc_sin_len);
		 if(sockClient>=0)
	     {
			 //创建一个线程来处理socket请求threadHandle
			 DWORD id;
			 HANDLE  threadHandle = CreateThread(0, 0,(LPTHREAD_START_ROUTINE)HandleSocket,(LPVOID)sockClient, 0, &id);

			 ////接收数据并保存到recvBuf变量中
			 //recv_len=recv(sockClient,recvBuf,100,0);
			 ////recv_len=recvfrom(sockClient,recvBuf,100,0,(SOCKADDR*)&addrClient,&len);
			 //while(recv_len>=0)
			 //{
				// if (recv_len==0)
				// {
				//	 printf("本次接收的没有数据，是响应客户端连接信息！\n ");
				// }
				// else
				// {
				//	 //输出数据
				//	 recvBuf[recv_len]='\0'; //在末尾加入字符串结束符号 '\0 '
				//	 printf("%s\n",recvBuf);
				//	 printf("本次数据接收结束。\n ");
				// }
				// recv_len=recv(sockClient,recvBuf,100,0);//recvfrom(sockSrv,recvBuf,100,0,(SOCKADDR*)&addrClient,&len);
			 //}
		 }
		 else
		 { //没有客户端接入
			 printf("没有客户端接入2\n");
		 }
		 Sleep(200);
	 }
	 //关闭Socket变量sockSrv
	 closesocket(sockSrv);
	 //清除Socket
	 WSACleanup();
}


DWORD WINAPI HandleSocket(LPVOID lpParam)
{
	SOCKET sockClient=(SOCKET)lpParam;
   //接收数据并保存到recvBuf变量中
	char recvBuf[100];
	 int recv_len=-1;
	while(1)
	{
		 recv_len=recv(sockClient,recvBuf,100,0);
		 //recv_len=recvfrom(sockClient,recvBuf,100,0,(SOCKADDR*)&addrClient,&len);
		 if(recv_len>=0)
		 {
			 if (recv_len==0)
			 {
				 printf("本次接收的没有数据，是响应客户端连接信息！\n ");
			 }
			 else
			 {
				 //输出数据
				 recvBuf[recv_len]='\0'; //在末尾加入字符串结束符号 '\0 '
				 printf("%s\n",recvBuf);
				 printf("本次数据接收结束。\n ");
			 }
			 //recv_len=recv(sockClient,recvBuf,100,0);//recvfrom(sockSrv,recvBuf,100,0,(SOCKADDR*)&addrClient,&len);
		 }
	}
}
