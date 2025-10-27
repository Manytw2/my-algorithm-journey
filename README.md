# C++ 算法练习环境

一个用于学习和练习 C++ 算法的小项目。主要特点是每个算法文件都可以独立运行，并且提供了性能测量工具。

---

## 主要特性

- **单文件独立运行** - 每个算法文件都有自己的 main 函数，互不干扰
- **性能测量** - 微秒级计时器和内存监控
- **工具函数复用** - 统一的 utility.h 提供常用工具
- **一键运行** - VSCode 按 F5，或命令行 `./run.sh <算法名>`
- **CMake 自动化** - 自动发现和编译所有算法文件

---

## 项目结构

```
algorithm-c/
├── algorithms/          # 算法代码
│
├── include/
│   └── utility.h       # 工具库（计时、内存分析、数组操作等）
│
├── .vscode/            # VSCode 配置（F5 运行）
├── build/              # 编译输出
│
├── CMakeLists.txt      # CMake 配置
├── run.sh              # 运行脚本
└── README.md
```

---

## 快速开始

### 使用 VSCode（推荐）

1. 打开任意算法文件，比如 `algorithms/sorting/bubble_sort.cpp`
2. 按 **F5** 或 **Ctrl+Shift+B**
3. 自动编译运行

### 使用命令行

```bash
# 列出所有算法
./run.sh -l

# 运行指定算法
./run.sh bubble_sort
./run.sh Code01_Partition1

# 清理重建
./run.sh -c && ./run.sh -r
```

---

## 核心工具

### 1. 高精度计时器

```cpp
#include "utility.h"
using namespace algo;

Timer timer("我的算法");
myAlgorithm(data);
timer.stop();  // 输出执行时间（微秒）
```

### 2. 内存分析

```cpp
MemoryAnalyzer analyzer;
quickSort(arr, 0, n-1);
analyzer.analyzeMemoryUsage(arr.size(), "快速排序");
```

### 3. 数组工具

```cpp
// 生成随机数组
auto data = array_utils::generateRandom(1000);

// 打印数组
array_utils::print(data, "原始数据");

// 验证排序
bool ok = array_utils::isSorted(data);
```

### 4. 完整测试框架

```cpp
AlgorithmTester tester("快速排序");
tester.testPerformance([&]() {
    quickSort(arr, 0, arr.size() - 1);
}, arr.size());
```

---

## 写算法的模板

```cpp
#include "utility.h"
#include <vector>
using namespace std;
using namespace algo;

void myAlgorithm(vector<int>& arr) {
    // 你的算法实现
}

ALGORITHM_MAIN("我的算法")

    auto data = array_utils::generateRandom(100);
    cout << "原始数据: ";
    array_utils::print(data, "", 20);

    AlgorithmTester tester("我的算法");
    tester.testPerformance([&]() {
        myAlgorithm(data);
    }, data.size());

    cout << "排序结果: ";
    array_utils::print(data, "", 20);

ALGORITHM_END
```

---

## 输出示例

```
🎯 快速排序-Partition1（挖坑填数法） 算法演示
===================================================
📊 原始数组:
   大小: 9
   内容: 5 3 1 9 2 8 4 7 6

🚀 开始测试算法: Partition1
===================================================
⏱️  Partition1 执行时间:        0 μs (微秒)

🧠 内存分析:
   数据大小: 9 个元素 (36 B)
   算法类型: Partition1
   初始内存: 1.02 MB
   当前内存: 1.02 MB
   额外内存: 0 B
   理论额外空间: 12 B
   空间复杂度: O(1) - 原地排序
✅ 算法测试完成

📍 基准位置: 4
📍 基准值: 5
📊 Partition后数组:
   大小: 9
   内容: 4 3 1 2 5 8 9 7 6

🔍 Partition验证: ✅ 正确
```

---

## 设计思路

### 解决的问题

1. **多个 main 函数冲突** → CMake 为每个文件生成独立可执行文件
2. **工具函数难复用** → 统一的 utility.h
3. **性能测量不方便** → 微秒级计时器 + 内存监控
4. **编译运行麻烦** → VSCode F5 + run.sh 脚本

### 架构

```
用户操作 (VSCode F5 / ./run.sh)
    ↓
构建系统 (CMake 自动发现)
    ↓
工具库 (utility.h)
    ↓
算法实现 (独立 .cpp 文件)
```

---

## VSCode 快捷键

- **Ctrl+Shift+B** - 编译运行当前文件
- **F5** - 调试运行
- **F9** - 设置断点
- **F10** - 单步跳过
