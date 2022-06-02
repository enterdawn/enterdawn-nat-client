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
#include "tcpconn.h"
#include "../logs/log.h"
#include <string>
extern logs* logger;
tcpConn::tcpConn(std::string ip,int port) {
	this->ip = ip; this->port = port;
	logger->info("Connect to " + ip + ":" + std::to_string(port));
	//创建头文件
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建套接字
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(ip.c_str());//暴露到外网的服务IP
	sockAddr.sin_port = htons(port);
	while (1) {
		int re = connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
		if (re < 0) {
			logger->error("Connect failed!");
			logger->info("try reconn in 10s");
			Sleep(10000);
		}
		else {
			logger->error("Connection established!");
			break;
		}
	}

}
tcpConn::~tcpConn() {
	//关闭套接字
	closesocket(sock);
	logger->debug("dectroy socket");
	//终止使用 DLL
	WSACleanup();
}
std::string tcpConn::getdata() {
	int cLen;
	char cmsg[1024];
	while (cLen = recv(sock, cmsg, sizeof(cmsg), 0)) {
		cmsg[cLen] = '\0';
		logger->info(cmsg);
		conn->sendData(cmsg);
	}

}
int tcpConn::sendData(std::string data) {
	int result = send(sock, data.c_str(), data.length(), 0);
	return result;
}