/**
 * @file insertion_sort.cpp
 * @brief 插入排序算法实现
 * @author Algorithm Learning Environment
 * @version 1.0
 *
 * 时间复杂度: O(n²) - 最坏情况, O(n) - 最好情况
 * 空间复杂度: O(1)
 * 稳定性: 稳定
 */

#include "utility.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace algo;

/**
 * @brief 插入排序算法
 * @param arr 待排序数组
 */
void insertionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // 将大于key的元素向后移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // 插入key到正确位置
        arr[j + 1] = key;
    }
}

/**
 * @brief 插入排序算法（带详细步骤输出）
 * @param arr 待排序数组
 */
void insertionSortWithSteps(vector<int>& arr) {
    int n = arr.size();
    cout << "🔄 开始插入排序..." << endl;

    for (int i = 1; i < n; ++i) {
        cout << "\n第 " << i << " 轮插入:" << endl;
        int key = arr[i];
        int j = i - 1;

        cout << "  当前元素: " << key << " (位置 " << i << ")" << endl;
        cout << "  已排序部分: ";
        for (int k = 0; k < i; ++k) {
            cout << arr[k] << " ";
        }
        cout << endl;

        cout << "  寻找插入位置..." << endl;

        // 将大于key的元素向后移动
        while (j >= 0 && arr[j] > key) {
            cout << "    移动 " << arr[j] << " 到位置 " << (j + 1) << endl;
            arr[j + 1] = arr[j];
            j--;
        }

        // 插入key到正确位置
        arr[j + 1] = key;
        cout << "  插入 " << key << " 到位置 " << (j + 1) << endl;

        cout << "  第 " << i << " 轮结果: ";
        array_utils::print(arr, "", 20);
    }
}

/**
 * @brief 二分插入排序（优化版本）
 * @param arr 待排序数组
 */
void binaryInsertionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; ++i) {
        int key = arr[i];

        // 使用二分查找找到插入位置
        int left = 0, right = i - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] <= key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // 移动元素
        for (int j = i - 1; j >= left; --j) {
            arr[j + 1] = arr[j];
        }

        // 插入元素
        arr[left] = key;
    }
}

int main() {
    printAlgorithmTitle("插入排序");

    // 测试数据
    vector<int> test_data = {12, 11, 13, 5, 6, 7};

    cout << "📊 原始数据: ";
    array_utils::print(test_data, "", 20);

    // 基本插入排序测试
    {
        auto data_copy = array_utils::copy(test_data);
        AlgorithmTester tester("插入排序");
        tester.testPerformance([&]() {
            insertionSort(data_copy);
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
        insertionSortWithSteps(data_copy);
    }

    cout << "\n" << string(50, '=') << endl;

    // 不同数据类型的性能测试
    {
        cout << "💪 不同数据类型的性能测试:" << endl;
        vector<size_t> sizes = {100, 500, 1000};

        // 随机数据
        cout << "\n随机数据:" << endl;
        for (size_t size : sizes) {
            auto random_data = array_utils::generateRandom(size);

            Timer timer("插入排序-随机-" + to_string(size));
            insertionSort(random_data);
            long long time = timer.stop();

            cout << "   数据大小: " << size << ", 时间: " << time << " μs" << endl;
        }

        // 已排序数据
        cout << "\n已排序数据:" << endl;
        for (size_t size : sizes) {
            auto sorted_data = array_utils::generateSorted(size);

            Timer timer("插入排序-已排序-" + to_string(size));
            insertionSort(sorted_data);
            long long time = timer.stop();

            cout << "   数据大小: " << size << ", 时间: " << time << " μs" << endl;
        }

        // 逆序数据
        cout << "\n逆序数据:" << endl;
        for (size_t size : sizes) {
            auto reverse_data = array_utils::generateReverse(size);

            Timer timer("插入排序-逆序-" + to_string(size));
            insertionSort(reverse_data);
            long long time = timer.stop();

            cout << "   数据大小: " << size << ", 时间: " << time << " μs" << endl;
        }
    }

    cout << "\n" << string(50, '=') << endl;

    // 二分插入排序测试
    {
        cout << "🔍 二分插入排序测试:" << endl;
        auto data_copy = array_utils::copy(test_data);

        Timer timer("二分插入排序");
        binaryInsertionSort(data_copy);
        long long time = timer.stop();

        cout << "📊 排序结果: ";
        array_utils::print(data_copy, "", 20);

        bool is_correct = array_utils::isSorted(data_copy);
        cout << "🔍 排序验证: " << (is_correct ? "✅ 正确" : "❌ 错误") << endl;
        cout << "⏱️  执行时间: " << time << " μs" << endl;
    }

    cout << "\n" << string(50, '=') << endl;

    // 算法特性说明
    cout << "📚 算法特性:" << endl;
    cout << "   • 时间复杂度: O(n²) - 最坏情况, O(n) - 最好情况" << endl;
    cout << "   • 空间复杂度: O(1) - 原地排序" << endl;
    cout << "   • 稳定性: 稳定 - 相等元素的相对位置不变" << endl;
    cout << "   • 适用场景: 小规模数据，部分有序数据" << endl;
    cout << "   • 优势: 对已排序数据性能优秀，实现简单" << endl;
    cout << "   • 优化: 二分插入排序可以减少比较次数" << endl;
    cout << "   • 实际应用: 作为其他排序算法的子程序" << endl;

    return 0;
}
