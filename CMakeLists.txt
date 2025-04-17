cmake_minimum_required(VERSION 3.10)
project(TheLastBolt)  # 项目名称需与目录一致

# 添加可执行文件，包含所有源文件（含 main.cpp 和 src 下的 .cpp）
file(GLOB SOURCES "src/*.cpp" "main.cpp")  # 自动匹配 src 目录下的 .cpp
add_executable(TheLastBolt ${SOURCES})

# 包含头文件目录
target_include_directories(TheLastBolt PRIVATE include)

# 设置 C++ 标准（可选，若代码需要）
set(CMAKE_CXX_STANDARD 17)