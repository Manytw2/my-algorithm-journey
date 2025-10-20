#include "QuickSort_interface.h"

int Partition1(vector<int> & R, int s, int t) {
    int i = s, j = t;
    int base = R[s];
    
    while (i < j) {
      while (i < j && R[j] >= R[base]) {
        j--;
      }
      if (i < j) {
        // j占了i的位置，i往后走，j原本位置变为base (坑)
        R[i] = R[j];     
        i++; 
      }
      while (i < j && R[i] <= R[base]) {
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

// 临时main函数，用于单独运行检验 Partition1()
int main() {
    vector<int> arr = {5, 3, 1, 9, 2, 8};
    int low = 0;
    int high = arr.size() - 1;
    int pivot_index = Partition1(arr, low, high);

    cout << "======Partition1 结果======" << endl;
    cout << "pivot_index = " << pivot_index << endl;
    print_array(arr);

    return 0;
}
