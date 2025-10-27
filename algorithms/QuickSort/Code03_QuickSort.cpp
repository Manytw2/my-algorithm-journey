/**
 * @file Code03_QuickSort.cpp
 * @brief 快速排序完整实现
 * @author Algorithm Learning Environment
 * @version 1.0
 *
 * 时间复杂度: O(n log n) - 平均情况，O(n²) - 最坏情况
 * 空间复杂度: O(log n) - 递归栈空间
 * 稳定性: 不稳定
 *
 * 算法思想：
 * - 分治法：选择基准元素，将数组分为两部分
 * - 递归处理左右两部分
 */

#include "utility.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace algo;

/**
 * @brief Partition函数 - 双指针法
 */
int Partition(vector<int> & R, int s, int t) {
    int i = s, j = s + 1;
    int base = R[s];

    while (j <= t) {
        if (R[j] <= base) {
            i++;
            swap(R[i], R[j]);
        }
        j++;
    }

    swap(R[s], R[i]);
    return i;
}

/**
 * @brief 快速排序主函数
 * @param R 待排序数组
 * @param s 起始索引
 * @param t 结束索引
 */
void QuickSort(vector<int> & R, int s, int t) {
    if (s < t) {
        int pivot = Partition(R, s, t);  // 分割
        QuickSort(R, s, pivot - 1);       // 递归排序左半部分
        QuickSort(R, pivot + 1, t);       // 递归排序右半部分
    }
}

int main() {
    printAlgorithmTitle("快速排序");

    // 测试数据
    vector<int> test_data = {5, 3, 1, 9, 2, 8, 4, 7, 6, 10};

    cout << "📊 原始数组: ";
    array_utils::print(test_data, "", 20);

    // 性能测试
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

    // 不同规模性能测试
    {
        cout << "💪 性能测试（不同数据规模）:" << endl;
        vector<size_t> sizes = {100, 500, 1000, 5000, 10000};

        for (size_t size : sizes) {
            auto random_data = array_utils::generateRandom(size, 1, 10000);

            Timer timer("快速排序-" + to_string(size) + "个元素");
            QuickSort(random_data, 0, random_data.size() - 1);
            timer.stop();

            // 验证结果
            bool valid = array_utils::isSorted(random_data);
            cout << "   验证: " << (valid ? "✅" : "❌") << endl;
        }
    }

    cout << "\n" << string(50, '=') << endl;

    // 不同数据分布测试
    {
        cout << "📈 不同数据分布测试:" << endl;
        size_t test_size = 1000;

        // 1. 随机数据
        {
            auto data = array_utils::generateRandom(test_size);
            Timer timer("随机数据");
            QuickSort(data, 0, data.size() - 1);
            timer.stop();
        }

        // 2. 已排序数据（最坏情况）
        {
            auto data = array_utils::generateSorted(test_size);
            Timer timer("已排序数据（最坏情况）");
            QuickSort(data, 0, data.size() - 1);
            timer.stop();
        }

        // 3. 逆序数据
        {
            auto data = array_utils::generateReverse(test_size);
            Timer timer("逆序数据");
            QuickSort(data, 0, data.size() - 1);
            timer.stop();
        }
    }

    cout << "\n" << string(50, '=') << endl;

    // 算法特性说明
    cout << "📚 算法特性:" << endl;
    cout << "   • 时间复杂度:" << endl;
    cout << "     - 最好情况: O(n log n) - 每次都平分" << endl;
    cout << "     - 平均情况: O(n log n)" << endl;
    cout << "     - 最坏情况: O(n²) - 已排序数组" << endl;
    cout << "   • 空间复杂度: O(log n) - 递归栈" << endl;
    cout << "   • 稳定性: 不稳定" << endl;
    cout << "   • 适用场景: 大规模数据排序" << endl;
    cout << "   • 优化方向:" << endl;
    cout << "     - 随机选择基准（避免最坏情况）" << endl;
    cout << "     - 三数取中法" << endl;
    cout << "     - 小数组使用插入排序" << endl;

    return 0;
}
