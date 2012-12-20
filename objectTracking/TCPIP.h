/*
 * TCPIP.h
 *
 *  Created on: 11-12-2012
 *      Author: arch
 */

#ifndef TCPIP_H_
#define TCPIP_H_

#include <Winsock.h>

class TCPIP {
	SOCKET m_socket;
public:
	TCPIP();
	virtual ~TCPIP();
	bool init();
	bool connect_to_server(char* ip, int port);
	void send_speed(int left, int right);
};

#endif /* TCPIP_H_ */
