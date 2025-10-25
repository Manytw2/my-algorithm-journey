#include "QuickSort_interface.h"

// Partition2函数实现 - 从Code02_Partition2.cpp复制
int Partition2(vector<int> & R, int s, int t) {
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

void QuickSort(vector<int> & R, int s, int t) {
    if (s < t) {
        int pivot = Partition2(R, s, t);  // 使用Partition2作为分割函数
        QuickSort(R, s, pivot - 1);       // 递归排序左半部分
        QuickSort(R, pivot + 1, t);       // 递归排序右半部分
    }
}

// 临时main函数，用于单独运行检验 QuickSort()
int main() {
    vector<int> arr = {5, 3, 1, 9, 2, 8, 4, 7, 6};
    
    cout << "======快速排序前======" << endl;
    print_array(arr);
    
    QuickSort(arr, 0, arr.size() - 1);
    
    cout << "======快速排序后======" << endl;
    print_array(arr);

    return 0;
}
