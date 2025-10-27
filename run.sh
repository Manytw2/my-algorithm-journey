#!/bin/bash
# =============================================================================
# 算法练习环境 - 一键编译运行脚本
# =============================================================================
# 用法：
#   ./run.sh                      - 列出所有可用的算法
#   ./run.sh <algorithm_name>     - 编译并运行指定算法
#   ./run.sh bubble_sort          - 运行冒泡排序
#   ./run.sh -l                   - 列出所有算法
#   ./run.sh -c                   - 清理所有编译产物
#   ./run.sh -h                   - 显示帮助信息
# =============================================================================

set -e  # 遇到错误立即退出

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# 项目根目录
PROJECT_ROOT="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build"
BIN_DIR="${BUILD_DIR}/bin"

# 显示帮助信息
show_help() {
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${CYAN}🚀 算法练习环境 - 一键运行脚本${NC}"
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""
    echo "用法："
    echo "  ./run.sh                    - 列出所有可用的算法"
    echo "  ./run.sh <algorithm_name>   - 编译并运行指定算法"
    echo "  ./run.sh -l, --list         - 列出所有算法"
    echo "  ./run.sh -c, --clean        - 清理所有编译产物"
    echo "  ./run.sh -r, --rebuild      - 重新构建整个项目"
    echo "  ./run.sh -h, --help         - 显示此帮助信息"
    echo ""
    echo "示例："
    echo "  ./run.sh bubble_sort        - 运行冒泡排序"
    echo "  ./run.sh Code01_Partition1  - 运行快速排序Partition1"
    echo "  ./run.sh quick_sort_enhanced - 运行优化版快速排序"
    echo ""
}

# 列出所有可用的算法
list_algorithms() {
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${CYAN}📋 可用的算法列表${NC}"
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""

    # 查找所有的.cpp文件
    local count=0
    while IFS= read -r file; do
        local filename=$(basename "$file" .cpp)
        local dir=$(dirname "$file" | sed "s|${PROJECT_ROOT}/algorithms/||")
        count=$((count + 1))
        printf "  ${GREEN}%2d.${NC} %-30s ${BLUE}(%s)${NC}\n" "$count" "$filename" "$dir"
    done < <(find "${PROJECT_ROOT}/algorithms" -name "*.cpp" -type f | sort)

    echo ""
    echo -e "${YELLOW}提示：使用 './run.sh <algorithm_name>' 运行指定算法${NC}"
    echo ""
}

# 清理编译产物
clean_build() {
    echo -e "${YELLOW}🧹 清理编译产物...${NC}"
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        echo -e "${GREEN}✅ 清理完成${NC}"
    else
        echo -e "${YELLOW}⚠️  build 目录不存在，无需清理${NC}"
    fi
}

# 重新构建项目
rebuild_project() {
    echo -e "${CYAN}🔨 重新构建项目...${NC}"
    clean_build
    build_project
}

# 构建项目
build_project() {
    echo -e "${CYAN}🔨 构建项目...${NC}"

    # 创建build目录
    if [ ! -d "$BUILD_DIR" ]; then
        mkdir -p "$BUILD_DIR"
    fi

    cd "$BUILD_DIR"

    # 运行CMake
    echo -e "${BLUE}▶ 运行 CMake...${NC}"
    cmake .. -DCMAKE_BUILD_TYPE=Release

    # 编译
    echo -e "${BLUE}▶ 编译项目...${NC}"
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

    cd "$PROJECT_ROOT"
    echo -e "${GREEN}✅ 构建完成${NC}"
}

# 编译并运行指定算法
run_algorithm() {
    local algorithm_name="$1"

    # 检查算法文件是否存在
    local source_files=$(find "${PROJECT_ROOT}/algorithms" -name "${algorithm_name}.cpp" -type f)

    if [ -z "$source_files" ]; then
        echo -e "${RED}❌ 错误: 找不到算法 '${algorithm_name}'${NC}"
        echo -e "${YELLOW}💡 提示: 使用 './run.sh -l' 查看所有可用的算法${NC}"
        exit 1
    fi

    # 确保项目已构建
    if [ ! -d "$BUILD_DIR" ]; then
        echo -e "${YELLOW}⚠️  项目尚未构建，开始构建...${NC}"
        build_project
    fi

    # 检查可执行文件是否存在
    local executable="${BIN_DIR}/${algorithm_name}"

    if [ ! -f "$executable" ]; then
        echo -e "${YELLOW}⚠️  可执行文件不存在，重新构建...${NC}"
        build_project
    fi

    # 运行算法
    echo ""
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${GREEN}🚀 运行算法: ${algorithm_name}${NC}"
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""

    "$executable"

    local exit_code=$?
    echo ""
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    if [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}✅ 算法执行成功 (退出码: $exit_code)${NC}"
    else
        echo -e "${RED}❌ 算法执行失败 (退出码: $exit_code)${NC}"
    fi
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""

    return $exit_code
}

# 主函数
main() {
    # 处理命令行参数
    case "${1:-}" in
        -h|--help)
            show_help
            ;;
        -l|--list)
            list_algorithms
            ;;
        -c|--clean)
            clean_build
            ;;
        -r|--rebuild)
            rebuild_project
            ;;
        "")
            list_algorithms
            ;;
        *)
            run_algorithm "$1"
            ;;
    esac
}

# 执行主函数
main "$@"
