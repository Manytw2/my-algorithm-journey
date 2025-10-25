/**
 * @file quick_sort_enhanced.cpp
 * @brief 增强版快速排序算法实现
 * @author Algorithm Learning Environment
 * @version 1.0
 * 
 * 基于原有QuickSort文件夹的算法，使用新的工具库进行增强
 * 时间复杂度: O(n log n) - 平均情况, O(n²) - 最坏情况
 * 空间复杂度: O(log n) - 平均情况, O(n) - 最坏情况
 */

#include "utility.h"
#include <vector>
#include <iostream>
#include <random>

using namespace std;
using namespace algo;

/**
 * @brief Partition1算法 - 挖坑填数法
 * @param arr 数组
 * @param s 起始位置
 * @param t 结束位置
 * @return 基准元素的位置
 */
int Partition1(vector<int>& arr, int s, int t) {
    int i = s, j = t;
    int base = arr[s];  // 选择第一个元素作为基准
    
    while (i < j) {
        // 从右向左找小于基准的元素
        while (i < j && arr[j] >= base) {
            j--;
        }
        if (i < j) {
            arr[i] = arr[j];  // 挖坑填数
            i++;
        }
        
        // 从左向右找大于基准的元素
        while (i < j && arr[i] <= base) {
            i++;
        }
        if (i < j) {
            arr[j] = arr[i];  // 挖坑填数
            j--;
        }
    }
    
    // 基准归位
    arr[i] = base;
    return i;
}

/**
 * @brief Partition2算法 - 双指针法
 * @param arr 数组
 * @param s 起始位置
 * @param t 结束位置
 * @return 基准元素的位置
 */
int Partition2(vector<int>& arr, int s, int t) {
    int pivot = arr[t];  // 选择最后一个元素作为基准
    int i = s - 1;       // 小于基准的元素的索引
    
    for (int j = s; j < t; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[t]);
    return i + 1;
}

/**
 * @brief 快速排序算法
 * @param arr 待排序数组
 * @param s 起始位置
 * @param t 结束位置
 */
void QuickSort(vector<int>& arr, int s, int t) {
    if (s < t) {
        int pivot_index = Partition1(arr, s, t);
        QuickSort(arr, s, pivot_index - 1);
        QuickSort(arr, pivot_index + 1, t);
    }
}

/**
 * @brief 快速排序算法（带详细步骤输出）
 * @param arr 待排序数组
 * @param s 起始位置
 * @param t 结束位置
 * @param depth 递归深度
 */
void QuickSortWithSteps(vector<int>& arr, int s, int t, int depth = 0) {
    if (s < t) {
        string indent(depth * 2, ' ');
        cout << indent << "🔍 排序范围 [" << s << ", " << t << "]" << endl;
        
        int pivot_index = Partition1(arr, s, t);
        cout << indent << "  基准位置: " << pivot_index << ", 基准值: " << arr[pivot_index] << endl;
        cout << indent << "  分割后: ";
        for (int i = s; i <= t; i++) {
            if (i == pivot_index) cout << "[" << arr[i] << "] ";
            else cout << arr[i] << " ";
        }
        cout << endl;
        
        QuickSortWithSteps(arr, s, pivot_index - 1, depth + 1);
        QuickSortWithSteps(arr, pivot_index + 1, t, depth + 1);
    }
}

/**
 * @brief 三路快速排序（处理重复元素）
 * @param arr 待排序数组
 * @param s 起始位置
 * @param t 结束位置
 */
void QuickSort3Way(vector<int>& arr, int s, int t) {
    if (s >= t) return;
    
    int pivot = arr[s];
    int lt = s;      // arr[s+1..lt] < pivot
    int gt = t;      // arr[gt..t] > pivot
    int i = s + 1;   // arr[lt+1..i-1] == pivot
    
    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[lt++], arr[i++]);
        } else if (arr[i] > pivot) {
            swap(arr[i], arr[gt--]);
        } else {
            i++;
        }
    }
    
    QuickSort3Way(arr, s, lt - 1);
    QuickSort3Way(arr, gt + 1, t);
}

/**
 * @brief 随机化快速排序
 * @param arr 待排序数组
 * @param s 起始位置
 * @param t 结束位置
 */
void RandomizedQuickSort(vector<int>& arr, int s, int t) {
    if (s < t) {
        // 随机选择基准
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(s, t);
        int random_index = dis(gen);
        swap(arr[s], arr[random_index]);
        
        int pivot_index = Partition1(arr, s, t);
        RandomizedQuickSort(arr, s, pivot_index - 1);
        RandomizedQuickSort(arr, pivot_index + 1, t);
    }
}

ALGORITHM_MAIN("增强版快速排序")

    // 测试数据
    vector<int> test_data = {64, 34, 25, 12, 22, 11, 90, 5, 77, 30};
    
    cout << "📊 原始数据: ";
    array_utils::print(test_data, "", 20);
    
    // 基本快速排序测试
    {
        auto data_copy = array_utils::copy(test_data);
        AlgorithmTester tester("快速排序");
        tester.testPerformance([&]() {
            QuickSort(data_copy, 0, data_copy.size() - 1);
        }, test_data.size());
        
        cout << "📊 排序结果: ";
        array_utils::print(data_copy, "", 20);
        
        // 验证排序结果
        bool is_correct = array_utils::isSorted(data_copy);
        cout << "🔍 排序验证: " << (is_correct ? "✅ 正确" : "❌ 错误") << endl;
    }
    
    cout << "\n" << string(50, '=') << endl;
    
    // 详细步骤演示
    {
        auto data_copy = array_utils::copy(test_data);
        cout << "🎬 详细步骤演示:" << endl;
        QuickSortWithSteps(data_copy, 0, data_copy.size() - 1);
        cout << "📊 最终结果: ";
        array_utils::print(data_copy, "", 20);
    }
    
    cout << "\n" << string(50, '=') << endl;
    
    // 不同分割算法对比
    {
        cout << "⚡ 不同分割算法对比:" << endl;
        vector<string> partition_names = {"Partition1", "Partition2"};
        vector<function<void(vector<int>&, int, int)>> partition_funcs = {
            [](vector<int>& arr, int s, int t) { QuickSort(arr, s, t); },
            [](vector<int>& arr, int s, int t) {
                if (s < t) {
                    int pivot_index = Partition2(arr, s, t);
                    QuickSort(arr, s, pivot_index - 1);
                    QuickSort(arr, pivot_index + 1, t);
                }
            }
        };
        
        AlgorithmTester tester("分割算法对比");
        tester.compareAlgorithms(partition_names, 
            [&]() {
                auto data_copy = array_utils::copy(test_data);
                QuickSort(data_copy, 0, data_copy.size() - 1);
            },
            [&]() {
                auto data_copy = array_utils::copy(test_data);
                if (data_copy.size() > 0) {
                    int pivot_index = Partition2(data_copy, 0, data_copy.size() - 1);
                    QuickSort(data_copy, 0, pivot_index - 1);
                    QuickSort(data_copy, pivot_index + 1, data_copy.size() - 1);
                }
            }
        );
    }
    
    cout << "\n" << string(50, '=') << endl;
    
    // 三路快速排序测试
    {
        cout << "🔄 三路快速排序测试 (处理重复元素):" << endl;
        vector<int> duplicate_data = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
        
        cout << "📊 原始数据 (含重复): ";
        array_utils::print(duplicate_data, "", 20);
        
        Timer timer("三路快速排序");
        QuickSort3Way(duplicate_data, 0, duplicate_data.size() - 1);
        long long time = timer.stop();
        
        cout << "📊 排序结果: ";
        array_utils::print(duplicate_data, "", 20);
        
        bool is_correct = array_utils::isSorted(duplicate_data);
        cout << "🔍 排序验证: " << (is_correct ? "✅ 正确" : "❌ 错误") << endl;
    }
    
    cout << "\n" << string(50, '=') << endl;
    
    // 性能测试
    {
        cout << "💪 性能测试:" << endl;
        vector<size_t> sizes = {1000, 5000, 10000, 20000};
        
        for (size_t size : sizes) {
            auto random_data = array_utils::generateRandom(size);
            
            Timer timer("快速排序-" + to_string(size));
            QuickSort(random_data, 0, random_data.size() - 1);
            long long time = timer.stop();
            
            cout << "   数据大小: " << size << ", 时间: " << time << " μs" << endl;
        }
    }
    
    cout << "\n" << string(50, '=') << endl;
    
    // 算法特性说明
    cout << "📚 算法特性:" << endl;
    cout << "   • 时间复杂度: O(n log n) - 平均情况, O(n²) - 最坏情况" << endl;
    cout << "   • 空间复杂度: O(log n) - 平均情况, O(n) - 最坏情况" << endl;
    cout << "   • 稳定性: 不稳定 - 相等元素可能改变相对位置" << endl;
    cout << "   • 适用场景: 大规模数据排序，实际应用中最常用" << endl;
    cout << "   • 优势: 平均性能优秀，原地排序" << endl;
    cout << "   • 优化: 随机化选择基准，三路分割处理重复元素" << endl;
    cout << "   • 分割方法: Partition1(挖坑填数), Partition2(双指针)" << endl;

ALGORITHM_END
