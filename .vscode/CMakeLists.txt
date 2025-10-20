# 设定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 给你的项目起个名字
project(My-Algorithm-Journey)

# 核心设置：统一输出目录
# 设置所有可执行文件的存放路径到 build/bin/
# CMAKE_BINARY_DIR 默认就是你的 build 文件夹
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)