// 通用算法接口头文件
// 包含常用的头文件和辅助函数

#ifndef ALGORITHM_INTERFACE_H
#define ALGORITHM_INTERFACE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;

// 辅助函数：打印数组
template<typename T>
void print_array(const vector<T>& arr, const string& title = "数组内容") {
    cout << "====== " << title << " ======" << endl;
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << " ";
    }
    cout << endl;
}

// 辅助函数：生成随机数组
vector<int> generate_random_array(int size, int min_val = 1, int max_val = 100) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min_val, max_val);
    
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// 辅助函数：测试算法性能
template<typename Func>
void measure_time(Func func, const string& algorithm_name) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << algorithm_name << " 执行时间: " << duration.count() << " 微秒" << endl;
}

// 辅助函数：验证排序结果
bool is_sorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i-1]) {
            return false;
        }
    }
    return true;
}

#endif
