cmake_minimum_required(VERSION 3.10)
project(TheLastBolt)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(json)

# 查找源文件
file(GLOB SOURCES "src/*.cpp" "main.cpp")

# 创建可执行文件
add_executable(TheLastBolt ${SOURCES})

# 添加 include 路径
target_include_directories(TheLastBolt PRIVATE
  ${json_SOURCE_DIR}/single_include
  ${CMAKE_SOURCE_DIR}/include
)
