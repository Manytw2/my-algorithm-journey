/**
 * @file binary_search.cpp
 * @brief 二分查找算法实现
 * @author Algorithm Learning Environment
 * @version 1.0
 *
 * 时间复杂度: O(log n)
 * 空间复杂度: O(1) - 迭代版本, O(log n) - 递归版本
 * 前提条件: 数组必须已排序
 */

#include "utility.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace algo;

/**
 * @brief 二分查找算法（迭代版本）
 * @param arr 已排序数组
 * @param target 目标值
 * @return 目标值的索引，如果未找到返回-1
 */
int binarySearchIterative(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;  // 避免溢出

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;  // 未找到
}

/**
 * @brief 二分查找算法（递归版本）
 * @param arr 已排序数组
 * @param target 目标值
 * @param left 左边界
 * @param right 右边界
 * @return 目标值的索引，如果未找到返回-1
 */
int binarySearchRecursive(const vector<int>& arr, int target, int left, int right) {
    if (left > right) {
        return -1;  // 未找到
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursive(arr, target, mid + 1, right);
    } else {
        return binarySearchRecursive(arr, target, left, mid - 1);
    }
}

/**
 * @brief 二分查找算法（带详细步骤输出）
 * @param arr 已排序数组
 * @param target 目标值
 * @return 目标值的索引，如果未找到返回-1
 */
int binarySearchWithSteps(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int step = 1;

    cout << "🔍 开始二分查找，目标值: " << target << endl;
    cout << "📊 搜索数组: ";
    array_utils::print(arr, "", 20);

    while (left <= right) {
        int mid = left + (right - left) / 2;

        cout << "\n第 " << step << " 步:" << endl;
        cout << "  搜索范围: [" << left << ", " << right << "]" << endl;
        cout << "  中间位置: " << mid << ", 值: " << arr[mid] << endl;

        if (arr[mid] == target) {
            cout << "  ✅ 找到目标值 " << target << " 在位置 " << mid << endl;
            return mid;
        } else if (arr[mid] < target) {
            cout << "  " << arr[mid] << " < " << target << ", 搜索右半部分" << endl;
            left = mid + 1;
        } else {
            cout << "  " << arr[mid] << " > " << target << ", 搜索左半部分" << endl;
            right = mid - 1;
        }

        step++;
    }

    cout << "  ❌ 未找到目标值 " << target << endl;
    return -1;
}

/**
 * @brief 线性查找算法（用于对比）
 * @param arr 数组
 * @param target 目标值
 * @return 目标值的索引，如果未找到返回-1
 */
int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int main() {
    printAlgorithmTitle("二分查找");

    // 测试数据
    vector<int> sorted_data = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25};
    vector<int> targets = {7, 1, 25, 10, 13};

    cout << "📊 已排序数组: ";
    array_utils::print(sorted_data, "", 20);

    // 基本二分查找测试
    {
        cout << "\n🔍 基本二分查找测试:" << endl;
        for (int target : targets) {
            AlgorithmTester tester("二分查找-迭代");
            int result = -1;
            tester.testPerformance([&]() {
                result = binarySearchIterative(sorted_data, target);
            }, sorted_data.size());

            cout << "  查找 " << target << ": "
                 << (result != -1 ? "找到在位置 " + to_string(result) : "未找到") << endl;
        }
    }

    cout << "\n" << string(50, '=') << endl;

    // 详细步骤演示
    {
        cout << "🎬 详细步骤演示:" << endl;
        binarySearchWithSteps(sorted_data, 13);
    }

    cout << "\n" << string(50, '=') << endl;

    // 递归版本测试
    {
        cout << "🔄 递归版本测试:" << endl;
        for (int target : targets) {
            Timer timer("二分查找-递归");
            int result = binarySearchRecursive(sorted_data, target, 0, sorted_data.size() - 1);
            long long time = timer.stop();

            cout << "  查找 " << target << ": "
                 << (result != -1 ? "找到在位置 " + to_string(result) : "未找到")
                 << " (时间: " << time << " μs)" << endl;
        }
    }

    cout << "\n" << string(50, '=') << endl;

    // 性能对比测试
    {
        cout << "⚡ 性能对比测试 (二分查找 vs 线性查找):" << endl;
        vector<size_t> sizes = {1000, 10000, 100000, 1000000};

        for (size_t size : sizes) {
            auto sorted_data_large = array_utils::generateSorted(size);
            int target = sorted_data_large[size / 2];  // 查找中间元素

            // 二分查找
            Timer timer_binary("二分查找");
            int result_binary = binarySearchIterative(sorted_data_large, target);
            long long time_binary = timer_binary.stop();

            // 线性查找
            Timer timer_linear("线性查找");
            int result_linear = linearSearch(sorted_data_large, target);
            long long time_linear = timer_linear.stop();

            cout << "  数据大小: " << size << endl;
            cout << "    二分查找: " << time_binary << " μs" << endl;
            cout << "    线性查找: " << time_linear << " μs" << endl;
            cout << "    性能提升: " << (time_linear / max(time_binary, 1LL)) << "x" << endl;
        }
    }

    cout << "\n" << string(50, '=') << endl;

    // 算法特性说明
    cout << "📚 算法特性:" << endl;
    cout << "   • 时间复杂度: O(log n) - 每次搜索范围减半" << endl;
    cout << "   • 空间复杂度: O(1) - 迭代版本, O(log n) - 递归版本" << endl;
    cout << "   • 前提条件: 数组必须已排序" << endl;
    cout << "   • 适用场景: 大规模已排序数据的查找" << endl;
    cout << "   • 优势: 比线性查找快得多，特别是大数据集" << endl;
    cout << "   • 局限性: 需要排序，不适合频繁插入/删除的场景" << endl;

    return 0;
}
