# 🎯 C++ 算法练习环境

> 一个现代化的 C++ 算法学习环境，支持单文件独立运行、高精度性能测量、真实内存监控和优雅的工具函数复用

[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![CMake](https://img.shields.io/badge/CMake-3.16+-green.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Linux%20%7C%20Windows-lightgrey.svg)](README.md)

---

## ✨ 核心特性

### 🚀 **一键运行，极致体验**
- **单文件独立运行** - 每个算法文件都是独立的，可直接编译运行
- **VSCode F5 直接运行** - 打开文件按 F5，自动编译并执行
- **智能脚本工具** - `./run.sh <算法名>` 一键编译运行任何算法

### ⏱️ **高精度性能测量**
- **微秒级计时器** - 基于 `std::chrono::high_resolution_clock`
- **RAII 风格** - 自动计时，无需手动管理
- **多维度测试** - 支持不同数据规模和分布的性能测试

### 🧠 **真实内存监控**
- **跨平台内存追踪** - macOS (mach)、Linux (getrusage)、Windows (GetProcessMemoryInfo)
- **理论+实际对比** - 同时显示理论空间复杂度和实际内存使用
- **可视化展示** - 自动格式化内存大小（B/KB/MB）

### 🛠️ **统一工具库**
- **utility.h** - 统一的工具函数库，包含计时、内存分析、数组操作
- **函数复用** - 打印数组、生成随机数据、验证排序等常用工具
- **宏定义框架** - 简化 main 函数编写，减少重复代码

### 🏗️ **现代化构建系统**
- **CMake 自动发现** - 自动扫描并编译所有算法文件
- **增量编译** - 只编译修改的文件，提高编译速度
- **跨平台支持** - 支持 macOS、Linux、Windows

---

## 📁 项目结构

```
algorithm-c/
├── 📂 include/                    # 通用头文件
│   └── utility.h                  # 统一工具库（Timer、MemoryAnalyzer、数组工具等）
│
├── 📂 algorithms/                 # 算法实现目录
│   ├── 📂 sorting/               # 排序算法
│   │   ├── bubble_sort.cpp       # 冒泡排序（带详细步骤演示）
│   │   ├── selection_sort.cpp    # 选择排序
│   │   ├── insertion_sort.cpp    # 插入排序
│   │   └── quick_sort_enhanced.cpp # 优化版快速排序
│   │
│   ├── 📂 QuickSort/             # 快速排序专题（三种实现）
│   │   ├── Code01_Partition1.cpp # 挖坑填数法
│   │   ├── Code02_Partition2.cpp # 双指针法
│   │   └── Code03_QuickSort.cpp  # 完整快速排序
│   │
│   ├── 📂 searching/             # 查找算法
│   │   └── binary_search.cpp     # 二分查找
│   │
│   ├── 📂 dp/                    # 动态规划（待扩展）
│   └── 📂 graph/                 # 图算法（待扩展）
│
├── 📂 .vscode/                   # VSCode 配置
│   ├── tasks.json                # 任务配置（F5 一键运行）
│   ├── launch.json               # 调试配置
│   ├── settings.json             # 项目设置
│   └── c_cpp_properties.json     # C++ 智能感知配置
│
├── 📂 build/                     # CMake 构建目录
│   └── bin/                      # 可执行文件输出
│
├── 📄 CMakeLists.txt             # CMake 配置文件
├── 📄 run.sh                     # 一键运行脚本 ⭐
├── 📄 build.sh                   # 构建脚本
├── 📄 simple_build.sh           # 简单构建脚本
├── 📄 VSCODE_CMAKE_GUIDE.md      # VSCode 使用指南
└── 📄 README.md                  # 项目文档
```

---

## 🚀 快速开始

### 方式 1：使用 VSCode（最简单，推荐）

1. **打开项目**
   ```bash
   code algorithm-c/
   ```

2. **打开任意算法文件**
   - 例如：`algorithms/sorting/bubble_sort.cpp`

3. **按 F5 或 Ctrl+Shift+B**
   - 自动编译并运行当前文件
   - 无需任何额外配置！

4. **调试算法**
   - 在行号左侧点击设置断点
   - 按 F5 开始调试
   - 单步执行、查看变量值

### 方式 2：使用命令行脚本

#### 一键运行脚本（推荐）

```bash
# 列出所有可用算法
./run.sh -l

# 运行指定算法
./run.sh bubble_sort
./run.sh Code01_Partition1
./run.sh quick_sort_enhanced

# 清理构建产物
./run.sh -c

# 重新构建项目
./run.sh -r

# 查看帮助
./run.sh -h
```

#### 传统构建方式

```bash
# 1. 构建项目
mkdir -p build && cd build
cmake ..
make

# 2. 运行算法
./build/bin/bubble_sort
./build/bin/Code03_QuickSort
```

---

## 🎨 设计思路与架构

### 分层混合方案

本项目采用 **分层混合架构**，解决了 C++ 算法练习的几个核心痛点：

#### 痛点 1：多个 main 函数冲突
**传统问题**：多个 `.cpp` 文件不能同时有 `main` 函数

**解决方案**：
- CMake 自动为每个 `.cpp` 生成独立的可执行文件
- 每个算法文件都可以有自己的 `main` 函数
- 编译时完全隔离，互不影响

#### 痛点 2：工具函数难以复用
**传统问题**：打印数组、计时等函数需要在每个文件里重复定义

**解决方案**：
- 统一的 `utility.h` 头文件
- 包含 Timer、MemoryAnalyzer、数组工具等
- 直接 `#include "utility.h"` 即可使用

#### 痛点 3：性能测量不够精确
**传统问题**：使用 `time` 命令精度不够，且无法测量内存

**解决方案**：
- 微秒级高精度计时器（`std::chrono`）
- 真实内存监控（跨平台实现）
- 理论空间复杂度分析

#### 痛点 4：编译运行不够便捷
**传统问题**：每次都要手动编译、链接、运行

**解决方案**：
- VSCode 按 F5 一键运行
- `./run.sh <算法名>` 脚本自动化
- CMake 增量编译

---

## 🛠️ 核心工具使用

### 1. 高精度计时器

```cpp
#include "utility.h"
using namespace algo;

// 方式 1：RAII 风格（推荐）
{
    Timer timer("冒泡排序");
    bubbleSort(arr);
    // 自动输出执行时间
}

// 方式 2：手动控制
Timer timer("快速排序");
quickSort(arr, 0, n-1);
long long time_us = timer.stop();  // 返回微秒数
```

### 2. 内存分析器

```cpp
#include "utility.h"
using namespace algo;

MemoryAnalyzer analyzer;
quickSort(arr, 0, n-1);
analyzer.analyzeMemoryUsage(arr.size(), "快速排序");

// 输出示例：
// 🧠 内存分析:
//    数据大小: 1000 个元素 (3.91 KB)
//    算法类型: 快速排序
//    初始内存: 2.45 MB
//    当前内存: 2.46 MB
//    额外内存: 12.00 KB
//    理论额外空间: 84 B
//    空间复杂度: O(log n) 平均，O(n) 最坏 - 递归栈
```

### 3. 数组工具

```cpp
#include "utility.h"
using namespace algo;

// 生成随机数组
auto data = array_utils::generateRandom(1000, 1, 10000);

// 生成有序数组
auto sorted = array_utils::generateSorted(100);

// 生成逆序数组
auto reversed = array_utils::generateReverse(100);

// 打印数组
array_utils::print(data, "原始数据", 20);  // 最多显示20个元素

// 验证排序
bool is_sorted = array_utils::isSorted(data);

// 复制数组
auto data_copy = array_utils::copy(data);
```

### 4. 算法测试框架

```cpp
#include "utility.h"
using namespace algo;

// 完整的测试框架
AlgorithmTester tester("快速排序");
tester.testPerformance([&]() {
    quickSort(arr, 0, arr.size() - 1);
}, arr.size());

// 输出示例：
// 🚀 开始测试算法: 快速排序
// ==================================================
// ⏱️  快速排序 执行时间:     1234 μs (微秒)
// 🧠 内存分析: ...
// ✅ 算法测试完成
```

### 5. 宏定义框架

```cpp
#include "utility.h"
using namespace algo;

void myAlgorithm(vector<int>& arr) {
    // 算法实现
}

ALGORITHM_MAIN("我的算法名")

    // 测试代码
    auto data = array_utils::generateRandom(100);

    AlgorithmTester tester("我的算法");
    tester.testPerformance([&]() {
        myAlgorithm(data);
    }, data.size());

ALGORITHM_END
```

---

## 📊 已实现算法

### 🔢 排序算法

| 算法 | 文件 | 时间复杂度 | 空间复杂度 | 稳定性 | 特点 |
|------|------|-----------|-----------|--------|------|
| **冒泡排序** | `bubble_sort.cpp` | O(n²) | O(1) | 稳定 | 带详细步骤演示 |
| **选择排序** | `selection_sort.cpp` | O(n²) | O(1) | 不稳定 | 交换次数最少 |
| **插入排序** | `insertion_sort.cpp` | O(n²) | O(1) | 稳定 | 部分有序数据高效 |
| **快速排序** | `quick_sort_enhanced.cpp` | O(n log n) | O(log n) | 不稳定 | 优化版实现 |

### 🎯 快速排序专题

| 文件 | 描述 | 算法特点 |
|------|------|---------|
| `Code01_Partition1.cpp` | 挖坑填数法 | 减少交换次数，效率高 |
| `Code02_Partition2.cpp` | 双指针法 | 代码简洁，易于理解 |
| `Code03_QuickSort.cpp` | 完整实现 | 包含多种测试场景 |

### 🔍 查找算法

| 算法 | 文件 | 时间复杂度 | 空间复杂度 | 适用场景 |
|------|------|-----------|-----------|---------|
| **二分查找** | `binary_search.cpp` | O(log n) | O(1) | 有序数组 |

### 📈 待扩展算法

- **动态规划** (`dp/`) - 斐波那契、背包问题、最长子序列等
- **图算法** (`graph/`) - BFS、DFS、最短路径、最小生成树等

---

## 🎯 算法模板

### 单文件算法模板（推荐）

```cpp
/**
 * @file my_algorithm.cpp
 * @brief 我的算法描述
 * @author Your Name
 * @version 1.0
 *
 * 时间复杂度: O(?)
 * 空间复杂度: O(?)
 * 稳定性: 稳定/不稳定
 */

#include "utility.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace algo;

/**
 * @brief 算法实现
 */
void myAlgorithm(vector<int>& arr) {
    // 你的算法实现
}

ALGORITHM_MAIN("我的算法名")

    // 测试数据
    vector<int> test_data = {5, 3, 1, 9, 2, 8};

    cout << "📊 原始数据: ";
    array_utils::print(test_data, "", 20);

    // 性能测试
    {
        auto data_copy = array_utils::copy(test_data);
        AlgorithmTester tester("我的算法");

        tester.testPerformance([&]() {
            myAlgorithm(data_copy);
        }, test_data.size());

        cout << "📊 处理结果: ";
        array_utils::print(data_copy, "", 20);

        // 验证结果（如果是排序算法）
        bool is_correct = array_utils::isSorted(data_copy);
        cout << "🔍 结果验证: " << (is_correct ? "✅ 正确" : "❌ 错误") << endl;
    }

    cout << "\n" << string(50, '=') << endl;

    // 算法特性说明
    cout << "📚 算法特性:" << endl;
    cout << "   • 时间复杂度: O(?)" << endl;
    cout << "   • 空间复杂度: O(?)" << endl;
    cout << "   • 稳定性: ?" << endl;
    cout << "   • 适用场景: ?" << endl;

ALGORITHM_END
```

---

## 🎨 输出示例

### 快速排序 - Partition1（挖坑填数法）

```
🎯 快速排序-Partition1（挖坑填数法） 算法演示
==================================================
📊 原始数组:
   大小: 9
   内容: 5 3 1 9 2 8 4 7 6

🚀 开始测试算法: Partition1
==================================================
⏱️  Partition1 执行时间:        3 μs (微秒)

🧠 内存分析:
   数据大小: 9 个元素 (36 B)
   算法类型: Partition1
   初始内存: 2.45 MB
   当前内存: 2.45 MB
   额外内存: 0 B
   理论额外空间: 12 B
   空间复杂度: O(1) - 原地排序
✅ 算法测试完成

📍 基准位置: 4
📍 基准值: 5
📊 Partition后数组:
   大小: 9
   内容: 3 1 4 2 5 8 9 7 6

🔍 Partition验证: ✅ 正确

📚 算法特性:
   • 方法: 挖坑填数法
   • 时间复杂度: O(n)
   • 空间复杂度: O(1)
   • 特点: 减少交换次数，效率较高
```

### 冒泡排序 - 详细步骤演示

```
🎯 冒泡排序 算法演示
==================================================
📊 原始数据:
   大小: 8
   内容: 64 34 25 12 22 11 90 5

🚀 开始测试算法: 冒泡排序
==================================================
⏱️  冒泡排序 执行时间:       45 μs (微秒)

🧠 内存分析:
   数据大小: 8 个元素 (32 B)
   算法类型: 冒泡排序
   初始内存: 2.45 MB
   当前内存: 2.45 MB
   额外内存: 0 B
   理论额外空间: 12 B
   空间复杂度: O(1) - 原地排序
✅ 算法测试完成

📊 排序结果:
   大小: 8
   内容: 5 11 12 22 25 34 64 90

🔍 排序验证: ✅ 正确

==================================================

🎬 详细步骤演示:
🔄 开始冒泡排序...

第 1 轮排序:
  比较 64 和 34 -> 交换
  比较 64 和 25 -> 交换
  ...
  第 1 轮结果: 34 25 12 22 11 5 64 90
  ...
```

---

## 💡 使用技巧

### VSCode 快捷键

- **Ctrl+Shift+B** - 快速编译运行当前文件
- **F5** - 运行当前文件（带调试）
- **Ctrl+F5** - 运行当前文件（不调试）
- **F9** - 设置/取消断点
- **F10** - 单步跳过
- **F11** - 单步进入

### 命令行技巧

```bash
# 快速运行多个算法
for algo in bubble_sort selection_sort insertion_sort; do
    ./run.sh $algo
done

# 性能对比测试
./run.sh Code01_Partition1 > partition1.log
./run.sh Code02_Partition2 > partition2.log
diff partition1.log partition2.log

# 批量编译
cd build && make -j$(nproc)
```

---

## 🤝 贡献指南

### 添加新算法

1. **在相应目录创建算法文件**
   ```bash
   # 例如：添加归并排序
   touch algorithms/sorting/merge_sort.cpp
   ```

2. **使用算法模板编写代码**
   - 复制上面的"算法模板"
   - 实现算法逻辑
   - 添加测试用例

3. **运行测试**
   ```bash
   ./run.sh merge_sort
   ```

4. **更新文档**
   - 在 README.md 的"已实现算法"中添加条目
   - 说明算法特点和复杂度

### 代码规范

- 使用 4 空格缩进
- 函数和变量使用驼峰命名
- 添加必要的注释和文档
- 遵循 C++17 标准

---

## 📝 常见问题

### Q: 为什么选择这种架构？

**A:** 这种架构专为算法练习场景设计：
- ✅ 每个算法独立，便于学习和测试
- ✅ 统一工具库，避免重复代码
- ✅ 一键运行，提高学习效率
- ✅ 真实内存监控，深入理解算法

### Q: 如何调试算法？

**A:** 三种方式：
1. **VSCode 调试**：按 F5，设置断点，单步执行
2. **打印调试**：使用 `array_utils::print()` 打印中间结果
3. **压力测试**：使用 `validation::stressTest()` 批量测试

### Q: 内存监控准确吗？

**A:**
- **实际内存**：使用系统 API 获取，相对准确（进程级）
- **理论空间**：基于算法分析计算，用于学习理解
- **建议**：两者结合使用，理解理论与实际的差异

### Q: 可以用于 LeetCode 等 OJ 平台吗？

**A:** 可以，但需要调整：
1. 提取算法核心函数（去掉 main 函数）
2. 去掉 `utility.h` 相关代码
3. 调整函数签名以匹配题目要求

---

## 📚 参考资源

- [C++ Reference](https://en.cppreference.com/)
- [CMake Documentation](https://cmake.org/documentation/)
- [算法导论 (CLRS)](https://mitpress.mit.edu/books/introduction-algorithms-third-edition)
- [LeetCode](https://leetcode.com/)

---

## 📄 许可证

MIT License - 详见 [LICENSE](LICENSE) 文件

---

## 🎉 致谢

感谢所有为这个项目做出贡献的开发者！

**特别感谢：**
- C++ 标准委员会 - 提供强大的语言特性
- CMake 团队 - 优秀的构建系统
- VSCode 团队 - 出色的编辑器

---

## 📮 联系方式

- **Issues**: [GitHub Issues](https://github.com/yourusername/algorithm-c/issues)
- **Pull Requests**: 欢迎贡献代码！

---

<div align="center">

**如果这个项目对你有帮助，请给一个 ⭐ Star！**

Made with ❤️ for algorithm learners

</div>
