/**
 * @file selection_sort.cpp
 * @brief 选择排序算法实现
 * @author Algorithm Learning Environment
 * @version 1.0
 *
 * 时间复杂度: O(n²)
 * 空间复杂度: O(1)
 * 稳定性: 不稳定
 */

#include "utility.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace algo;

/**
 * @brief 选择排序算法
 * @param arr 待排序数组
 */
void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        int min_index = i;

        // 找到未排序部分的最小元素
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        // 将最小元素与当前位置交换
        if (min_index != i) {
            swap(arr[i], arr[min_index]);
        }
    }
}

/**
 * @brief 选择排序算法（带详细步骤输出）
 * @param arr 待排序数组
 */
void selectionSortWithSteps(vector<int>& arr) {
    int n = arr.size();
    cout << "🔄 开始选择排序..." << endl;

    for (int i = 0; i < n - 1; ++i) {
        cout << "\n第 " << (i + 1) << " 轮选择:" << endl;
        int min_index = i;

        cout << "  在位置 " << i << " 到 " << (n - 1) << " 中寻找最小元素..." << endl;

        // 找到最小元素
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
                cout << "    找到更小的元素 " << arr[j] << " 在位置 " << j << endl;
            }
        }

        cout << "  最小元素: " << arr[min_index] << " 在位置 " << min_index << endl;

        // 交换元素
        if (min_index != i) {
            cout << "  交换 " << arr[i] << " 和 " << arr[min_index] << endl;
            swap(arr[i], arr[min_index]);
        } else {
            cout << "  元素已在正确位置，无需交换" << endl;
        }

        cout << "  第 " << (i + 1) << " 轮结果: ";
        array_utils::print(arr, "", 20);
    }
}

int main() {
    printAlgorithmTitle("选择排序");

    // 测试数据
    vector<int> test_data = {64, 25, 12, 22, 11, 90, 5, 34};

    cout << "📊 原始数据: ";
    array_utils::print(test_data, "", 20);

    // 基本选择排序测试
    {
        auto data_copy = array_utils::copy(test_data);
        AlgorithmTester tester("选择排序");
        tester.testPerformance([&]() {
            selectionSort(data_copy);
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
        selectionSortWithSteps(data_copy);
    }

    cout << "\n" << string(50, '=') << endl;

    // 性能测试
    {
        cout << "💪 性能测试:" << endl;
        vector<size_t> sizes = {100, 500, 1000, 2000};

        for (size_t size : sizes) {
            auto random_data = array_utils::generateRandom(size);

            Timer timer("选择排序-" + to_string(size));
            selectionSort(random_data);
            long long time = timer.stop();

            cout << "   数据大小: " << size << ", 时间: " << time << " μs" << endl;
        }
    }

    cout << "\n" << string(50, '=') << endl;

    // 算法特性说明
    cout << "📚 算法特性:" << endl;
    cout << "   • 时间复杂度: O(n²) - 所有情况都是O(n²)" << endl;
    cout << "   • 空间复杂度: O(1) - 原地排序" << endl;
    cout << "   • 稳定性: 不稳定 - 相等元素可能改变相对位置" << endl;
    cout << "   • 交换次数: 最多n-1次（比冒泡排序少）" << endl;
    cout << "   • 比较次数: 总是n(n-1)/2次" << endl;
    cout << "   • 适用场景: 交换成本高的情况" << endl;

    return 0;
}
