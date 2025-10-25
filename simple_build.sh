#!/bin/bash

# 简单构建脚本 - 不依赖CMake
# 直接使用g++编译所有算法文件

set -e

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

print_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

# 创建输出目录
mkdir -p bin

# 编译选项
CXX_FLAGS="-std=c++17 -Wall -Wextra -O2"
INCLUDE_DIR="-I./include"

print_info "开始编译算法文件..."

# 编译algorithms目录下的文件
for file in algorithms/*/*.cpp; do
    if [ -f "$file" ]; then
        filename=$(basename "$file" .cpp)
        print_info "编译: $file -> bin/$filename"
        g++ $CXX_FLAGS $INCLUDE_DIR -o "bin/$filename" "$file"
    fi
done

# 编译QuickSort目录下的文件
for file in QuickSort/*.cpp; do
    if [ -f "$file" ]; then
        filename=$(basename "$file" .cpp)
        print_info "编译: $file -> bin/$filename"
        g++ $CXX_FLAGS $INCLUDE_DIR -o "bin/$filename" "$file"
    fi
done

print_success "编译完成！"
print_info "可执行文件位于 bin/ 目录"

echo ""
echo "🎯 可用算法:"
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
echo "   ./bin/Code01_Partition1"
