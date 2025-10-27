/**
 * @file Code01_Partition1.cpp
 * @brief 快速排序 - Partition方法1（挖坑填数法）
 * @author Algorithm Learning Environment
 * @version 1.0
 *
 * 算法思想：
 * - 选择第一个元素作为基准
 * - 从两端向中间扫描，找到不符合条件的元素进行交换
 * - 使用"挖坑填数"的思想，避免多次交换
 */

#include "utility.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace algo;

/**
 * @brief Partition方法1 - 挖坑填数法
 * @param R 待划分的数组
 * @param s 起始索引
 * @param t 结束索引
 * @return 基准元素最终位置
 */
int Partition1(vector<int> & R, int s, int t) {
    int i = s, j = t;
    int base = R[s];

    while (i < j) {
        // 从右向左找小于基准的元素
        while (i < j && R[j] >= base) {
            j--;
        }
        if (i < j) {
            // j占了i的位置，i往后走，j原本位置变为base (坑)
            R[i] = R[j];
            i++;
        }

        // 从左向右找大于基准的元素
        while (i < j && R[i] <= base) {
            i++;
        }
        if (i < j) {
            // i占了j的位置，j往前走，i原本位置变为base (坑)
            R[j] = R[i];
            j--;
        }
    }

    // 基准归位 (填坑)
    R[i] = base;
    return i;
}

ALGORITHM_MAIN("快速排序-Partition1（挖坑填数法）")

    // 测试数据
    vector<int> arr = {5, 3, 1, 9, 2, 8, 4, 7, 6};

    cout << "📊 原始数组: ";
    array_utils::print(arr, "", 20);

    int low = 0;
    int high = arr.size() - 1;

    // 性能测试
    AlgorithmTester tester("Partition1");
    int pivot_index = 0;

    tester.testPerformance([&]() {
        pivot_index = Partition1(arr, low, high);
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
    cout << "   • 方法: 挖坑填数法" << endl;
    cout << "   • 时间复杂度: O(n)" << endl;
    cout << "   • 空间复杂度: O(1)" << endl;
    cout << "   • 特点: 减少交换次数，效率较高" << endl;

ALGORITHM_END
