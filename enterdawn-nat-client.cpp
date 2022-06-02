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

#include "enterdawn-nat-client.h"


using namespace std;
class getConn;
class tcpConn;
logs* logger = new logs(1);

int main()
{
	std::map<std::string, std::map<std::string, std::string>> conf;
	confReader(conf);
	if (conf["main"].empty()) {
		logger->error("no main info");
		exit(1);
	}
	while (1) {
		getConn* conn = new getConn(conf["main"]["ip"], std::stoi(conf["main"]["port"]), conf["main"]["token"]);
		logger->info("loading conf");

		for (auto &i : conf) {
			if (i.first == "main") continue;
			logger->info("Create server " + i.first + ", " + i.second["local_ip"] + ":" + i.second["local_port"]
				+ " remote port " + i.second["remote_port"] + " by " + i.second["type"]);
			if (!checkIP(i.second["local_ip"])) {
				logger->error("IP check Error");
				exit(1);
			}
			if (stoi(i.second["local_port"]) < 0 || stoi(i.second["local_port"]) >65535) {
				logger->error("Port must >0&&<=65535");
				exit(1);
			}
			if (stoi(i.second["remote_port"]) < 0 || stoi(i.second["remote_port"]) > 65535) {
				logger->error("Port must >0&&<=65535");
				exit(1);
			}
			tcpConn* tcp = new tcpConn(i.second["local_ip"], stoi(i.second["local_port"]));
			tcp->conn = conn;
			conn->sendData("enterdawn-nat:"+i.first+":"+ i.second["remote_port"]);
			//std::thread route(&getConn::getData, tcp);
			conn->conn = tcp;
			conn->getData();
			//system("pause");
			/*
			type:tcp
			local_ip:127.0.0.1
			local_port:25565
			remote_port:6022
			*/
			

		}

		//阻塞当前线程
		conn->recv->join();
		//服务器断开连接，销毁所有对象，10s后尝试重连
		logger->info("try reconn in 10s");
		delete conn;
		Sleep(10000);
	}
	
	
	return 0;
}
