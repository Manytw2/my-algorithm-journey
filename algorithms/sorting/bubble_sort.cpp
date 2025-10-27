/**
 * @file bubble_sort.cpp
 * @brief 冒泡排序算法实现
 * @author Algorithm Learning Environment
 * @version 1.0
 *
 * 时间复杂度: O(n²)
 * 空间复杂度: O(1)
 * 稳定性: 稳定
 */

#include "utility.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace algo;

/**
 * @brief 冒泡排序算法
 * @param arr 待排序数组
 */
void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;  // 优化：如果一轮中没有交换，说明已经有序

        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // 如果没有发生交换，数组已经有序
        if (!swapped) {
            break;
        }
    }
}

/**
 * @brief 冒泡排序算法（带详细步骤输出）
 * @param arr 待排序数组
 */
void bubbleSortWithSteps(vector<int>& arr) {
    int n = arr.size();
    cout << "🔄 开始冒泡排序..." << endl;

    for (int i = 0; i < n - 1; ++i) {
        cout << "\n第 " << (i + 1) << " 轮排序:" << endl;
        bool swapped = false;

        for (int j = 0; j < n - i - 1; ++j) {
            cout << "  比较 " << arr[j] << " 和 " << arr[j + 1];

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
                cout << " -> 交换" << endl;
            } else {
                cout << " -> 不交换" << endl;
            }
        }

        cout << "  第 " << (i + 1) << " 轮结果: ";
        array_utils::print(arr, "", 20);

        if (!swapped) {
            cout << "  ✅ 数组已有序，提前结束" << endl;
            break;
        }
    }
}

int main() {
    printAlgorithmTitle("冒泡排序");

    // 测试数据
    vector<int> test_data = {64, 34, 25, 12, 22, 11, 90, 5};

    cout << "📊 原始数据: ";
    array_utils::print(test_data, "", 20);

    // 基本冒泡排序测试
    {
        auto data_copy = array_utils::copy(test_data);
        AlgorithmTester tester("冒泡排序");
        tester.testPerformance([&]() {
            bubbleSort(data_copy);
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
        bubbleSortWithSteps(data_copy);
    }

    cout << "\n" << string(50, '=') << endl;

    // 性能测试
    {
        cout << "💪 性能测试:" << endl;
        vector<size_t> sizes = {100, 500, 1000, 2000};

        for (size_t size : sizes) {
            auto random_data = array_utils::generateRandom(size);

            Timer timer("冒泡排序-" + to_string(size));
            bubbleSort(random_data);
            long long time = timer.stop();

            cout << "   数据大小: " << size << ", 时间: " << time << " μs" << endl;
        }
    }

    cout << "\n" << string(50, '=') << endl;

    // 算法特性说明
    cout << "📚 算法特性:" << endl;
    cout << "   • 时间复杂度: O(n²) - 最坏和平均情况" << endl;
    cout << "   • 空间复杂度: O(1) - 原地排序" << endl;
    cout << "   • 稳定性: 稳定 - 相等元素的相对位置不变" << endl;
    cout << "   • 适用场景: 小规模数据，教学演示" << endl;
    cout << "   • 优化: 提前终止（如果一轮中没有交换）" << endl;

    return 0;
}
