// Created by enterdawn on 2022/6/1. admin@mail.enterdawn.top
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef getconn
#define getconn
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include "tcp/tcpconn.h"
#include <string>
#include <thread>
using std::thread;
#pragma comment(lib, "ws2_32.lib") 
class getConn;
class tcpConn;
class getConn {
public:
	tcpConn* conn;
public:
	getConn(std::string ip,int port,std::string token);
	int sendData(std::string data);
	std::string getData();
	thread *recv;
	~getConn();
	
private:
	std::string ip;
	void sendHeart();
	int port;
	std::string token;
	WSADATA wsaData;
	SOCKET sock;
	sockaddr_in sockAddr;

}; 

#endif