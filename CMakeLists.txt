# C++算法练习环境 - 现代化CMake配置
# 支持多文件独立运行、高精度性能测量、优雅的工具函数复用

cmake_minimum_required(VERSION 3.16)
project(AlgorithmLearning VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译选项
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /permissive-")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 自动发现算法文件
file(GLOB_RECURSE ALGORITHM_SOURCES 
    "algorithms/*.cpp"
)

# 过滤掉不需要的文件
list(FILTER ALGORITHM_SOURCES EXCLUDE REGEX ".*/output/.*")
list(FILTER ALGORITHM_SOURCES EXCLUDE REGEX ".*algorithm_runner.*")

# 为每个算法文件创建独立的可执行文件
foreach(SOURCE_FILE ${ALGORITHM_SOURCES})
    # 获取文件名（不含路径和扩展名）
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    
    # 跳过重复的文件名（如果存在）
    if(TARGET ${FILE_NAME})
        continue()
    endif()
    
    # 创建可执行文件
    add_executable(${FILE_NAME} ${SOURCE_FILE})
    
    # 设置输出目录
    set_target_properties(${FILE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
    
    # 添加编译定义
    target_compile_definitions(${FILE_NAME} PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
    )
    
endforeach()

# 创建算法目录（如果不存在）
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/algorithms/sorting)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/algorithms/searching)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/algorithms/graph)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/algorithms/dp)

# 添加清理目标
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/lib
    VERBATIM
)

# 安装规则 - 收集所有可执行目标
set(ALL_EXECUTABLES "")
foreach(SOURCE_FILE ${ALGORITHM_SOURCES})
    get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
    if(TARGET ${FILE_NAME})
        list(APPEND ALL_EXECUTABLES ${FILE_NAME})
    endif()
endforeach()

if(ALL_EXECUTABLES)
    install(TARGETS ${ALL_EXECUTABLES}
        RUNTIME DESTINATION bin
    )
endif()

install(FILES include/utility.h
    DESTINATION include
)