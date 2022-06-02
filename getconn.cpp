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
#include "getconn.h"
#include "tools/checkip.h"
#include <iostream>
#include "logs/log.h"

extern logs* logger;
getConn::getConn(std::string ip, int port, std::string token) {
	{
		this->ip = ip;
		if (!checkIP(ip)) {
			logger->error("IP check Error");
			exit(1);
		}
		this->port = port;
		if (port < 0 || port>65535) {
			logger->error("Port must >0&&<=65535");
			exit(1);
		}
		this->token = token;
		logger->info("Connect to "+ip+":"+std::to_string(port));
		//����ͷ�ļ�
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		//�����׽���
		sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
		sockAddr.sin_family = PF_INET;
		sockAddr.sin_addr.s_addr = inet_addr(ip.c_str());//������IP
		sockAddr.sin_port = htons(port);
		while (1) {
			int re = connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
			if (re < 0) {
				logger->error("Connect failed!");
				logger->info("try reconn in 10s");
				Sleep(10000);
			}
			else {
				send(sock, token.c_str(), strlen(token.c_str()), 0);
				//���շ��������ص�����
				char ok[] = "success";
				char szBuffer[255] = { 0 };
				recv(sock, szBuffer, 255, NULL);
				if (strcmp(szBuffer, ok) == 0) {
					logger->info("Connection established");
					break;
				}
				else {
					logger->info("Connect failed! Token error");
					logger->info("try reconn in 10s");
					Sleep(10000);
				}
			}
		}
		
		//����һ���̷߳���TCP������
		recv =new thread(&getConn::getData,this);
		
	}
}
getConn::~getConn() {
	//�ر��׽���
	closesocket(sock);
	logger->debug("dectroy socket");
	//��ֹʹ�� DLL
	WSACleanup();
}
std::string getConn::getData() {
	int cLen;
	char cmsg[1024] = {0};
	while (cLen = recv(sock, cmsg, sizeof(cmsg), 0)) {
		cmsg[cLen] = '\0';
		logger->info(cmsg);
		conn->sendData(cmsg);
	}
}

int getConn::sendData(std::string data) {
	int result = send(sock, data.c_str(), data.length(), 0);
	return result;
}
void getConn::sendHeart() {
	while (1) {
		Sleep(5000);
		int result = send(sock, "", 1, 0);
		//logger->debug("send heard");
		if (result < 0) {
			logger->info("Connection closed by server");
			break;
		}
	}
}