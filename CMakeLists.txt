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
    "QuickSort/*.cpp"
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
    
    message(STATUS "✅ 发现算法文件: ${SOURCE_FILE} -> ${FILE_NAME}")
endforeach()

# 创建算法目录（如果不存在）
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/algorithms/sorting)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/algorithms/searching)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/algorithms/graph)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/algorithms/dp)

# 创建示例算法文件（如果不存在）
set(EXAMPLE_ALGORITHMS
    "algorithms/sorting/bubble_sort.cpp"
    "algorithms/sorting/selection_sort.cpp"
    "algorithms/sorting/insertion_sort.cpp"
    "algorithms/searching/binary_search.cpp"
    "algorithms/searching/linear_search.cpp"
)

foreach(EXAMPLE_FILE ${EXAMPLE_ALGORITHMS})
    if(NOT EXISTS ${CMAKE_SOURCE_DIR}/${EXAMPLE_FILE})
        message(STATUS "📝 将创建示例文件: ${EXAMPLE_FILE}")
    endif()
endforeach()

# 打印构建信息
message(STATUS "")
message(STATUS "🎯 ====== 构建配置完成 ======")
message(STATUS "📁 项目名称: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "🔧 C++标准: C++${CMAKE_CXX_STANDARD}")
message(STATUS "📊 发现算法文件数量: ${CMAKE_CURRENT_LIST_LENGTH}")
message(STATUS "📂 可执行文件输出目录: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "📋 包含目录: ${CMAKE_SOURCE_DIR}/include")
message(STATUS "🎯 ================================")
message(STATUS "")

# 添加自定义目标
add_custom_target(list_algorithms
    COMMAND ${CMAKE_COMMAND} -E echo "📋 可用算法列表:"
    COMMAND ${CMAKE_COMMAND} -E echo "=================="
    COMMAND ${CMAKE_COMMAND} -E echo "QuickSort算法:"
    COMMAND ${CMAKE_COMMAND} -E echo "  - Code01_Partition1"
    COMMAND ${CMAKE_COMMAND} -E echo "  - Code02_Partition2" 
    COMMAND ${CMAKE_COMMAND} -E echo "  - Code03_QuickSort"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "其他算法:"
    COMMAND ${CMAKE_COMMAND} -E echo "  - 查看 algorithms/ 目录"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "💡 使用方法:"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build . --target <算法名称>"
    COMMAND ${CMAKE_COMMAND} -E echo "  ./bin/<算法名称>"
    VERBATIM
)

# 添加清理目标
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/lib
    COMMAND ${CMAKE_COMMAND} -E echo "🧹 清理完成"
    VERBATIM
)

# 安装规则
install(TARGETS ${ALGORITHM_SOURCES}
    RUNTIME DESTINATION bin
)

install(FILES include/utility.h
    DESTINATION include
)