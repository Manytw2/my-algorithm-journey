#!/bin/bash

# C++算法练习环境 - 构建脚本
# 支持跨平台构建，自动发现和编译所有算法

set -e  # 遇到错误立即退出

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 打印带颜色的消息
print_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

# 检查依赖
check_dependencies() {
    print_info "检查构建依赖..."
    
    if ! command -v cmake &> /dev/null; then
        print_error "CMake 未安装，请先安装 CMake"
        exit 1
    fi
    
    if ! command -v make &> /dev/null && ! command -v ninja &> /dev/null; then
        print_error "未找到构建工具 (make 或 ninja)"
        exit 1
    fi
    
    print_success "依赖检查通过"
}

# 清理构建目录
clean_build() {
    print_info "清理构建目录..."
    if [ -d "build" ]; then
        rm -rf build
        print_success "构建目录已清理"
    fi
}

# 创建构建目录
create_build_dir() {
    print_info "创建构建目录..."
    mkdir -p build
    cd build
}

# 配置CMake
configure_cmake() {
    print_info "配置CMake..."
    
    # 检测构建类型
    BUILD_TYPE=${1:-Release}
    print_info "构建类型: $BUILD_TYPE"
    
    # 检测生成器
    if command -v ninja &> /dev/null; then
        GENERATOR="Ninja"
        print_info "使用 Ninja 生成器"
    else
        GENERATOR="Unix Makefiles"
        print_info "使用 Make 生成器"
    fi
    
    cmake -G "$GENERATOR" \
          -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
          -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
          ..
    
    print_success "CMake 配置完成"
}

# 构建项目
build_project() {
    print_info "开始构建项目..."
    
    # 获取CPU核心数
    if command -v nproc &> /dev/null; then
        CORES=$(nproc)
    elif command -v sysctl &> /dev/null; then
        CORES=$(sysctl -n hw.ncpu)
    else
        CORES=4
    fi
    
    print_info "使用 $CORES 个并行任务"
    
    if command -v ninja &> /dev/null; then
        ninja -j$CORES
    else
        make -j$CORES
    fi
    
    print_success "构建完成"
}

# 显示构建结果
show_results() {
    print_info "构建结果:"
    echo "=================="
    
    if [ -d "bin" ]; then
        echo "📁 可执行文件目录: $(pwd)/bin"
        echo ""
        echo "🎯 可用的算法:"
        
        # 列出所有可执行文件
        for file in bin/*; do
            if [ -f "$file" ] && [ -x "$file" ]; then
                filename=$(basename "$file")
                echo "   • $filename"
            fi
        done
        
        echo ""
        echo "💡 使用方法:"
        echo "   ./bin/<算法名称>"
        echo ""
        echo "📋 示例:"
        echo "   ./bin/bubble_sort"
        echo "   ./bin/quick_sort_enhanced"
        echo "   ./bin/binary_search"
    else
        print_warning "未找到可执行文件"
    fi
}

# 主函数
main() {
    echo "🎯 C++算法练习环境 - 构建脚本"
    echo "================================"
    
    # 解析命令行参数
    BUILD_TYPE="Release"
    CLEAN=false
    
    while [[ $# -gt 0 ]]; do
        case $1 in
            -d|--debug)
                BUILD_TYPE="Debug"
                shift
                ;;
            -c|--clean)
                CLEAN=true
                shift
                ;;
            -h|--help)
                echo "用法: $0 [选项]"
                echo "选项:"
                echo "  -d, --debug    构建Debug版本"
                echo "  -c, --clean    清理构建目录"
                echo "  -h, --help     显示帮助信息"
                exit 0
                ;;
            *)
                print_error "未知选项: $1"
                exit 1
                ;;
        esac
    done
    
    # 执行构建流程
    check_dependencies
    
    if [ "$CLEAN" = true ]; then
        clean_build
    fi
    
    create_build_dir
    configure_cmake $BUILD_TYPE
    build_project
    show_results
    
    print_success "构建完成！"
}

# 运行主函数
main "$@"
