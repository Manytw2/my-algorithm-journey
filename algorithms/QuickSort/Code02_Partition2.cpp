#include "QuickSort_interface.h"

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

// 临时main函数，用于单独运行检验 Partition1()
int main() {
    vector<int> arr = {5, 3, 1, 9, 2, 8};
    int low = 0;
    int high = arr.size() - 1;
    int pivot_index = Partition2(arr, low, high);

    cout << "======Partition2 结果======" << endl;
    cout << "pivot_index = " << pivot_index << endl;
    print_array(arr);

    return 0;
}