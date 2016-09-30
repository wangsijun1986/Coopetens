
//客户端
//--------------------------------------------------------------------------------------------
#pragma once
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#include "targetver.h"
#include <tchar.h>


#include <fstream>
#include <iostream>

#include <ole2.h>
#include <conio.h>

using namespace std;

#include "string.h"


#pragma comment(lib,"WS2_32.lib")

void SendMessage(void);
int _tmain(int argc, _TCHAR* argv[])
{
    SendMessage();
	char q;
	 cin>>q;
	return 0;
}

void SendMessage(void)
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
	 memset(&addrSrv,0,sizeof(addrSrv));
	 addrSrv.sin_addr.S_un.S_addr=inet_addr("192.168.1.232");//要访问的IP地址
	 addrSrv.sin_family=AF_INET;
	 addrSrv.sin_port=htons(6000);                 //端口6000
     //绑定函数(指定本地IP地址所使用的端口号时候使用)
	 //(把sockSrv变量与addrSrv变量绑定在一起)
	 bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
	 if(connect(sockSrv, (sockaddr*)&addrSrv,sizeof( addrSrv ) ) != SOCKET_ERROR )
	 {
		 int i=0;
		 char strch[]={ "Client send OK!(from   Client) "};
		 while(true)
		 {
			 //strch[strlen(strch)]=i;
			 if(send(sockSrv,strch,strlen(strch),0)==SOCKET_ERROR)
			 {
				printf("WSAGetLastError:   %d\n ",WSAGetLastError());
			 }
			 else
			 {
                printf(strch);printf("\n");
			 }
			 Sleep(300);
		 }
	 }
	 else
	 {
		printf("没连上!\n");
	 }

	 //关闭Socket变量sockSrv
	 closesocket(sockSrv);
	 //清除Socket
	 WSACleanup();
	 printf("已退出SendMessage函数!\n");
}
