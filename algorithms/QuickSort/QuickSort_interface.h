// 头文件保护宏
#ifndef QUICK_SORT_INTERFACE_H
#define QUICK_SORT_INTERFACE_H

#include <vector>
#include <iostream>

using namespace std;

int Partition1(vector <int> & R, int s, int t);

int Partition2(vector<int> & R, int s, int t);

void QuickSort(vector<int> & R, int s, int t);

// 一个辅助函数用于打印数组，方便测试
inline int print_array(const vector<int> & arr) {
    cout << "======当前arr======" << endl;
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}

#endif