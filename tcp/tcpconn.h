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
#ifndef tcpconn
#define tcpconn
#include <winsock2.h>
#include <iostream>
#include <string>
#include "../getconn.h"
#pragma comment(lib,"ws2_32.lib")
class getConn;
class tcpConn;
class tcpConn {
public:
	getConn* conn;
public:
	tcpConn(std::string ip, int port);
	int sendData(std::string data);
	std::string getdata();
	~tcpConn();
private:
	std::string ip;
	int port;
	WSADATA wsaData;
	SOCKET sock;
	sockaddr_in sockAddr;

};
#endif
