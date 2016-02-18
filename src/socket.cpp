/*
 * socket.cpp
 *
 *  Created on: 31 июля 2015 г.
 *      Author: alexey
 */

#include "socket_tcp.h"

socket_tcp::socket_tcp():socketHandleFlag(false) {


}

socket_tcp::~socket_tcp() {

}



int socket_tcp::socket_open(const char* ip_host)
{
   int socketHandle;
   struct sockaddr_in remoteSocketInfo;
   struct hostent *hPtr;

   const char *remoteHost=ip_host;
   int portNumber = 33333;

   bzero(&remoteSocketInfo, sizeof(sockaddr_in));  //очищение памяти


//проверка хоста
   if((hPtr = gethostbyname(remoteHost)) == NULL)
   {
      cerr << "System DNS name resolution not configured properly." << endl;
      cerr << "Error number: " << ECONNREFUSED << endl;
      exit(EXIT_FAILURE);
   }

   // создание сокета

   if((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   {
      exit(EXIT_FAILURE);
   }

   // загрузка информации о системе в сокет

   memcpy((char *)&remoteSocketInfo.sin_addr, hPtr->h_addr, hPtr->h_length);
   remoteSocketInfo.sin_family = AF_INET;
   remoteSocketInfo.sin_port = htons((u_short)portNumber);      // номер порта

   if(connect(socketHandle, (struct sockaddr *)&remoteSocketInfo, sizeof(sockaddr_in)) < 0)
   {
      exit(EXIT_FAILURE);
   }

   	   socketHandleFlag=true;

   return socketHandle;

}

bool  socket_tcp::isOpen(){
	return socketHandleFlag;
}

void socket_tcp::socket_write(int socketHandle, string m_data)
{
	 char buf[512];
	 strcpy(buf,m_data.c_str());
	 send(socketHandle, buf, strlen(buf)+1, 0);
}
