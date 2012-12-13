/*
 * TCPIP.cpp
 *
 *  Created on: 11-12-2012
 *      Author: arch
 */

#include <stdio.h>
#include <tchar.h>
#include "TCPIP.h"
#include <iostream>

TCPIP::TCPIP() {
	// TODO Auto-generated constructor stub

}

TCPIP::~TCPIP() {
	// TODO Auto-generated destructor stub
}

bool TCPIP::init(){
	WSADATA wsaData;
	WORD version;
	int error;
	version = MAKEWORD( 2, 0 );
	error = WSAStartup( version, &wsaData );
	if ( error != 0 )	{
		return false;
	}
	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 0 ){
		return false;
	}
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET){
		printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
		return false;
	}
	printf("initialized\n");
	return true;
}

bool TCPIP::connect_to_server(char* ip, int port){
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr(ip);	//"127.0.0.1"
	clientService.sin_port = htons(port);			//55555
	if (connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR){
		printf("Client: connect() - Failed to connect.\n");
		return false;
	}
	printf("connected to server\n");
	return true;
}

void TCPIP::send_speed(int left, int right){
	char sendbuf[200] = "$SPEED,";
	char buffer [10];
	itoa (left,buffer,10);
	strcat(sendbuf, buffer);
	strcat(sendbuf, ",");
	itoa (right,buffer,10);
	strcat(sendbuf, buffer);
	strcat(sendbuf, "\n");
	send(m_socket, sendbuf, strlen(sendbuf), 0);
}
