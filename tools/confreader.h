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
#include <map>
#include <iostream>
#include <string>
#include <fstream>
extern logs* logger;
void eraseSpace(std::string& s) {
	if (s.empty()) return;
	int i = s.find(" ");
	while (i != s.npos) {
		s.erase(i, 1);
		i = s.find(" ", i);
	}
}
void confReader(std::map<std::string, std::map<std::string, std::string>> & conf) {
	std::ifstream infile("D:\\C#\\enterdawn-nat-client\\conf.txt", std::ios::in);
	if (!infile.is_open())
	{
		logger->error("conf open error");
		exit(1);
	}
	std::string buf;
	std::string now = "";
	while (std::getline(infile, buf))
	{
		eraseSpace(buf);
		if (buf.empty()) continue;
		int i = buf.find(":");
		if (i == buf.npos) {
			now = buf;
		}
		else {
			if (now == "") {
				logger->error("conf PE");
			}
			conf[now].insert({buf.substr(0,i),buf.substr(i+1) });
		}
		
	}
}