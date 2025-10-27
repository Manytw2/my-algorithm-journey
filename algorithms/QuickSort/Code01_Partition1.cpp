#include "utility.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace algo;
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

int main() {
    printAlgorithmTitle("快速排序-Partition1（挖坑填数法）");

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

    return 0;
}

/*
 * 📝 算法总结 - 挖坑填数法
 *
 * 这个算法的核心思想就像是在地上挖坑填坑一样 (◕‿◕)
 * 想象一下，你要把一堆数字按大小分开，基准值就是这个"坑"
 *
 * 🎯 算法思路：
 * 1. 先把基准值 R[s] 挖出来当坑 (base)
 * 2. 从右边 j 开始，找到比基准小的数字，填到左边的坑里
 *    填完后，原来 j 的位置变成了新的坑 (◔_◔)
 * 3. 从左边 i 开始，找到比基准大的数字，填到右边的坑里
 *    填完后，原来 i 的位置又变成了新的坑
 * 4. 重复步骤 2 和 3，直到 i 和 j 相遇
 * 5. 最后把基准值填回最后的坑里 (ノ◕ω◕)ノ
 *
 * 这样就完成了分组：基准左边都是小的，右边都是大的！
 *
 * ⏱️ 时间复杂度：O(n) - 只需要遍历一次数组
 * 💾 空间复杂度：O(1) - 只用了几个变量，原地排序
 *
 * 🌟 优点：
 * - 减少了数字交换的次数，更高效 (ﾉ◕ヮ◕)ﾉ
 * - 逻辑清晰，理解起来也不难
 *
 * 这就是快速排序中最常用的划分方法之一！(=‿=)
 */
