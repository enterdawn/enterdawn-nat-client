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
#ifndef currenttime
#define currenttime
#include <string>
#include <ctime>
std::string getTime() {
	time_t timep;
	tm* p;
	time(&timep);
	p = localtime(&timep);
	return "[" + std::to_string(1900 + p->tm_year) + "." + std::to_string(1 + p->tm_mon) + "." + std::to_string(p->tm_mday) + " "
		+ std::to_string(p->tm_hour) + ":" + std::to_string(p->tm_min) + ":" + std::to_string(p->tm_sec) + "]";
}
#endif
