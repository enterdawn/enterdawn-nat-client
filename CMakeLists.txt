# CMakeList.txt: enterdawn-nat-client 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("enterdawn-nat-client")

# 将源代码添加到此项目的可执行文件。
add_executable (enterdawn-nat-client "enterdawn-nat-client.cpp" "enterdawn-nat-client.h" "tcp/tcpconn.h" "getconn.cpp" "getconn.h" "tools/checkip.h" "logs/log.cpp" "logs/log.h" "tools/currenttime.h" "tools/confreader.h" "tcp/tcpconn.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET enterdawn-nat-client PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
