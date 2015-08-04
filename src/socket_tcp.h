/*
 * socket.h
 *
 *  Created on: 31 июля 2015 г.
 *      Author: alexey
 */

#ifndef SOCKET_TCP_H_
#define SOCKET_TCP_H_
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define MAXHOSTNAME 256

using namespace std;

class socket_tcp {
public:
	socket_tcp();
	~socket_tcp();
	int socket_open(const char* ip_host);
	void socket_write(int socketHandle, string m_data);

private:

};

#endif /* SOCKET_TCP_H_ */
