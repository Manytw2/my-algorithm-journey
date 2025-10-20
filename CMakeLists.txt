# C++算法学习项目 - 智能CMake配置文件
# 自动发现和编译所有算法文件，无需手动维护

cmake_minimum_required(VERSION 3.10)
project(AlgorithmLearning)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR})

# 自动发现算法文件
file(GLOB_RECURSE ALGORITHM_SOURCES 
    "快速排序/*.cpp"
    "排序算法/*.cpp" 
    "查找算法/*.cpp"
    "图算法/*.cpp"
    "动态规划/*.cpp"
    "其他算法/*.cpp"
)

# 过滤掉不需要的文件
list(FILTER ALGORITHM_SOURCES EXCLUDE REGEX ".*/output/.*")
list(FILTER ALGORITHM_SOURCES EXCLUDE REGEX ".*algorithm_runner.*")

# 为每个算法文件创建独立的可执行文件
foreach(SOURCE_FILE ${ALGORITHM_SOURCES})
    # 获取文件名（不含路径和扩展名）
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    
    # 创建可执行文件
    add_executable(${FILE_NAME} ${SOURCE_FILE})
    
    # 设置输出目录
    set_target_properties(${FILE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
    
    message(STATUS "发现算法文件: ${SOURCE_FILE} -> ${FILE_NAME}")
endforeach()

# 创建统一的算法运行器
add_executable(algorithm_runner 
    algorithm_runner.cpp
    common/algorithm_registry.h
    common/algorithm_interface.h
)

# 设置编译选项
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

# 打印构建信息
message(STATUS "====== 构建配置完成 ======")
message(STATUS "发现算法文件数量: ${CMAKE_CURRENT_LIST_LENGTH}")
message(STATUS "可执行文件输出目录: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "统一运行器: algorithm_runner.exe")
