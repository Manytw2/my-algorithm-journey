// 统一算法运行器 - 自动发现和运行所有算法
// 支持命令行参数和交互式选择

#include "common/algorithm_registry.h"
#include "common/algorithm_interface.h"
#include <iostream>
#include <string>
#include <vector>

// 快速排序算法注册
IMPLEMENT_ALGORITHM(QuickSortAlgorithm, "quicksort", "快速排序算法");

void QuickSortAlgorithm::run() {
    vector<int> arr = {5, 3, 1, 9, 2, 8, 4, 7, 6};
    cout << "排序前: ";
    print_array(arr);
    
    // 这里应该调用实际的快速排序实现
    // QuickSort(arr, 0, arr.size() - 1);
    
    cout << "排序后: ";
    print_array(arr);
}

// Partition1算法注册
IMPLEMENT_ALGORITHM(Partition1Algorithm, "partition1", "Partition1分割算法");

void Partition1Algorithm::run() {
    vector<int> arr = {5, 3, 1, 9, 2, 8};
    cout << "分割前: ";
    print_array(arr);
    
    // 这里应该调用实际的Partition1实现
    // int pivot = Partition1(arr, 0, arr.size() - 1);
    
    cout << "分割后: ";
    print_array(arr);
}

// Partition2算法注册
IMPLEMENT_ALGORITHM(Partition2Algorithm, "partition2", "Partition2分割算法");

void Partition2Algorithm::run() {
    vector<int> arr = {5, 3, 1, 9, 2, 8};
    cout << "分割前: ";
    print_array(arr);
    
    // 这里应该调用实际的Partition2实现
    // int pivot = Partition2(arr, 0, arr.size() - 1);
    
    cout << "分割后: ";
    print_array(arr);
}

// 显示帮助信息
void showHelp() {
    cout << "====== 算法运行器使用说明 ======" << endl;
    cout << "用法: algorithm_runner [选项] [算法名称]" << endl;
    cout << "选项:" << endl;
    cout << "  -h, --help     显示此帮助信息" << endl;
    cout << "  -l, --list     列出所有可用算法" << endl;
    cout << "  -a, --all      运行所有算法" << endl;
    cout << "  [算法名称]     运行指定算法" << endl;
    cout << endl;
    cout << "示例:" << endl;
    cout << "  algorithm_runner quicksort    # 运行快速排序" << endl;
    cout << "  algorithm_runner --list       # 列出所有算法" << endl;
    cout << "  algorithm_runner --all        # 运行所有算法" << endl;
}

// 交互式选择算法
void interactiveMode() {
    cout << "====== 交互式算法选择 ======" << endl;
    AlgorithmRegistry::listAlgorithms();
    
    cout << "\n请选择要运行的算法 (输入算法名称，或输入 'all' 运行所有算法): ";
    string choice;
    getline(cin, choice);
    
    if (choice == "all") {
        AlgorithmRegistry::runAllAlgorithms();
    } else {
        if (!AlgorithmRegistry::runAlgorithm(choice)) {
            cout << "错误: 未找到算法 '" << choice << "'" << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    cout << "====== C++算法学习项目 - 统一运行器 ======" << endl;
    
    // 处理命令行参数
    if (argc > 1) {
        string arg = argv[1];
        
        if (arg == "-h" || arg == "--help") {
            showHelp();
            return 0;
        }
        else if (arg == "-l" || arg == "--list") {
            AlgorithmRegistry::listAlgorithms();
            return 0;
        }
        else if (arg == "-a" || arg == "--all") {
            AlgorithmRegistry::runAllAlgorithms();
            return 0;
        }
        else {
            // 运行指定算法
            if (!AlgorithmRegistry::runAlgorithm(arg)) {
                cout << "错误: 未找到算法 '" << arg << "'" << endl;
                cout << "使用 --list 查看可用算法" << endl;
                return 1;
            }
            return 0;
        }
    }
    
    // 没有参数时进入交互模式
    interactiveMode();
    return 0;
}
