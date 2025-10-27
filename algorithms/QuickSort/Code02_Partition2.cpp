/**
 * @file Code02_Partition2.cpp
 * @brief 快速排序 - Partition方法2（双指针法）
 * @author Algorithm Learning Environment
 * @version 1.0
 *
 * 算法思想：
 * - 选择第一个元素作为基准
 * - 使用两个指针i和j，i指向小于等于基准的区域末尾
 * - j遍历数组，遇到小于等于基准的元素就与i+1交换
 */

#include "utility.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace algo;

/**
 * @brief Partition方法2 - 双指针法
 * @param R 待划分的数组
 * @param s 起始索引
 * @param t 结束索引
 * @return 基准元素最终位置
 */
int Partition2(vector<int> & R, int s, int t) {
    int i = s, j = s + 1;
    int base = R[s];

    // j遍历数组，维护i为小于等于base的区域末尾
    while (j <= t) {
        if (R[j] <= base) {
            i++;
            swap(R[i], R[j]);
        }
        j++;
    }

    // 将基准元素放到正确位置
    swap(R[s], R[i]);
    return i;
}

int main() {
    printAlgorithmTitle("快速排序-Partition2（双指针法）");

    // 测试数据
    vector<int> arr = {5, 3, 1, 9, 2, 8, 4, 7, 6};

    cout << "📊 原始数组: ";
    array_utils::print(arr, "", 20);

    int low = 0;
    int high = arr.size() - 1;

    // 性能测试
    AlgorithmTester tester("Partition2");
    int pivot_index = 0;

    tester.testPerformance([&]() {
        pivot_index = Partition2(arr, low, high);
    }, arr.size());

    cout << "\n📍 基准位置: " << pivot_index << endl;
    cout << "📍 基准值: " << arr[pivot_index] << endl;
    cout << "📊 Partition后数组: ";
    array_utils::print(arr, "", 20);

    // 验证Partition结果
    bool valid = true;
    for (int i = 0; i < pivot_index; i++) {
        if (arr[i] > arr[pivot_index]) {
            valid = false;
            break;
        }
    }
    for (size_t i = pivot_index + 1; i < arr.size(); i++) {
        if (arr[i] < arr[pivot_index]) {
            valid = false;
            break;
        }
    }

    cout << "\n🔍 Partition验证: " << (valid ? "✅ 正确" : "❌ 错误") << endl;

    cout << "\n📚 算法特性:" << endl;
    cout << "   • 方法: 双指针法" << endl;
    cout << "   • 时间复杂度: O(n)" << endl;
    cout << "   • 空间复杂度: O(1)" << endl;
    cout << "   • 特点: 代码简洁，易于理解" << endl;

    return 0;
}
