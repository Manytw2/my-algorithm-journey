#!/bin/bash

# C++算法练习环境 - 运行脚本
# 提供便捷的算法运行和测试功能

set -e

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
NC='\033[0m'

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

print_header() {
    echo -e "${PURPLE}🎯 $1${NC}"
}

# 检查构建目录
check_build() {
    if [ ! -d "build" ] && [ ! -d "bin" ]; then
        print_error "构建目录不存在，请先运行 ./build.sh 或 ./simple_build.sh"
        exit 1
    fi
    
    if [ ! -d "build/bin" ] && [ ! -d "bin" ]; then
        print_error "可执行文件目录不存在，请先构建项目"
        exit 1
    fi
}

# 列出所有可用算法
list_algorithms() {
    print_header "可用算法列表"
    echo "=================="
    
    local count=0
    # 检查build/bin目录
    if [ -d "build/bin" ]; then
        for file in build/bin/*; do
            if [ -f "$file" ] && [ -x "$file" ]; then
                filename=$(basename "$file")
                echo "   • $filename"
                ((count++))
            fi
        done
    fi
    
    # 检查bin目录
    if [ -d "bin" ]; then
        for file in bin/*; do
            if [ -f "$file" ] && [ -x "$file" ]; then
                filename=$(basename "$file")
                echo "   • $filename"
                ((count++))
            fi
        done
    fi
    
    echo ""
    echo "📊 总计: $count 个算法"
}

# 运行指定算法
run_algorithm() {
    local algorithm_name=$1
    local executable=""
    
    # 优先检查build/bin目录
    if [ -f "build/bin/$algorithm_name" ]; then
        executable="build/bin/$algorithm_name"
    elif [ -f "bin/$algorithm_name" ]; then
        executable="bin/$algorithm_name"
    else
        print_error "算法 '$algorithm_name' 不存在"
        print_info "使用 '$0 --list' 查看可用算法"
        exit 1
    fi
    
    print_header "运行算法: $algorithm_name"
    echo "=================="
    
    # 运行算法
    "$executable"
    
    print_success "算法执行完成"
}

# 运行所有算法
run_all_algorithms() {
    print_header "运行所有算法"
    echo "=================="
    
    local count=0
    for file in build/bin/*; do
        if [ -f "$file" ] && [ -x "$file" ]; then
            filename=$(basename "$file")
            echo ""
            print_info "运行算法: $filename"
            echo "----------------------------------------"
            "$file"
            ((count++))
        fi
    done
    
    echo ""
    print_success "所有算法执行完成 (共 $count 个)"
}

# 性能测试
performance_test() {
    print_header "性能测试"
    echo "=================="
    
    local algorithms=("bubble_sort" "selection_sort" "insertion_sort" "quick_sort_enhanced")
    local sizes=(1000 5000 10000)
    
    for algorithm in "${algorithms[@]}"; do
        if [ -f "build/bin/$algorithm" ]; then
            print_info "测试算法: $algorithm"
            echo "----------------------------------------"
            for size in "${sizes[@]}"; do
                echo "数据大小: $size"
                time build/bin/$algorithm > /dev/null 2>&1
            done
            echo ""
        fi
    done
}

# 交互式选择
interactive_mode() {
    print_header "交互式算法选择"
    echo "=================="
    
    list_algorithms
    echo ""
    echo "请选择要运行的算法:"
    echo "1. 输入算法名称运行单个算法"
    echo "2. 输入 'all' 运行所有算法"
    echo "3. 输入 'test' 进行性能测试"
    echo "4. 输入 'quit' 退出"
    echo ""
    
    while true; do
        read -p "请输入选择: " choice
        
        case $choice in
            "quit"|"exit"|"q")
                print_success "退出程序"
                exit 0
                ;;
            "all")
                run_all_algorithms
                break
                ;;
            "test")
                performance_test
                break
                ;;
            *)
                if [ -n "$choice" ]; then
                    run_algorithm "$choice"
                    break
                else
                    print_warning "请输入有效的选择"
                fi
                ;;
        esac
    done
}

# 显示帮助信息
show_help() {
    echo "🎯 C++算法练习环境 - 运行脚本"
    echo "================================"
    echo ""
    echo "用法: $0 [选项] [算法名称]"
    echo ""
    echo "选项:"
    echo "  -l, --list      列出所有可用算法"
    echo "  -a, --all       运行所有算法"
    echo "  -t, --test      进行性能测试"
    echo "  -i, --interactive  交互式模式"
    echo "  -h, --help      显示此帮助信息"
    echo ""
    echo "示例:"
    echo "  $0 bubble_sort           # 运行冒泡排序"
    echo "  $0 --list               # 列出所有算法"
    echo "  $0 --all                # 运行所有算法"
    echo "  $0 --test               # 性能测试"
    echo "  $0 --interactive        # 交互式选择"
    echo ""
    echo "QuickSort算法 (保持原有结构):"
    echo "  $0 Code01_Partition1    # 运行Partition1"
    echo "  $0 Code02_Partition2    # 运行Partition2"
    echo "  $0 Code03_QuickSort     # 运行快速排序"
}

# 主函数
main() {
    # 检查构建目录
    check_build
    
    # 解析命令行参数
    if [ $# -eq 0 ]; then
        interactive_mode
        return
    fi
    
    case $1 in
        -l|--list)
            list_algorithms
            ;;
        -a|--all)
            run_all_algorithms
            ;;
        -t|--test)
            performance_test
            ;;
        -i|--interactive)
            interactive_mode
            ;;
        -h|--help)
            show_help
            ;;
        *)
            run_algorithm "$1"
            ;;
    esac
}

# 运行主函数
main "$@"
