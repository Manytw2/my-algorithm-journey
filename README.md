# C++算法练习环境

一个现代化的C++算法学习环境，支持多文件独立运行、高精度性能测量和优雅的工具函数复用。

## 🎯 项目特性

- **多文件独立运行**: 每个算法文件都有独立的`main`函数，可独立编译和运行
- **高精度性能测量**: 基于`<chrono>`的微秒级计时器，支持RAII风格的`Timer`类
- **内存使用分析**: 提供理论空间复杂度分析和近似测量
- **优雅的工具函数**: 统一的`utility.h`头文件，包含数组操作、随机数据生成等工具
- **现代化构建系统**: 基于CMake的自动发现和编译系统
- **跨平台支持**: 支持Linux、macOS、Windows

## 📁 项目结构

```
algorithm-c/
├── include/                    # 通用头文件
│   └── utility.h              # 高精度计时器和工具函数库
├── algorithms/                 # 算法实现目录
│   ├── sorting/               # 排序算法
│   │   ├── bubble_sort.cpp    # 冒泡排序
│   │   ├── selection_sort.cpp # 选择排序
│   │   ├── insertion_sort.cpp # 插入排序
│   │   └── quick_sort_enhanced.cpp # 增强版快速排序
│   └── searching/             # 查找算法
│       └── binary_search.cpp  # 二分查找
├── QuickSort/                 # 原有快速排序算法（保持不变）
│   ├── Code01_Partition1.cpp
│   ├── Code02_Partition2.cpp
│   ├── Code03_QuickSort.cpp
│   └── QuickSort_interface.h
├── .vscode/                   # VSCode配置
│   ├── launch.json           # 调试配置
│   ├── tasks.json            # 任务配置
│   ├── settings.json         # 工作区设置
│   └── extensions.json       # 推荐扩展
├── bin/                       # 编译输出目录
├── CMakeLists.txt             # 构建配置
├── build.sh                   # CMake构建脚本
├── simple_build.sh           # 简单构建脚本
├── run.sh                     # 运行脚本
└── README.md                  # 项目说明
```

## 🚀 快速开始

### 1. 构建项目

```bash
# 推荐：使用简单构建脚本（不依赖CMake）
./simple_build.sh

# 或者使用CMake构建（需要先安装CMake）
./build.sh

# 构建Debug版本
./build.sh --debug

# 清理并重新构建
./build.sh --clean
```

### 2. 运行算法

```bash
# 交互式选择算法
./run.sh

# 运行指定算法
./run.sh bubble_sort
./run.sh quick_sort_enhanced
./run.sh binary_search

# 列出所有可用算法
./run.sh --list

# 运行所有算法
./run.sh --all

# 性能测试
./run.sh --test
```

### 3. 使用VSCode（推荐）

#### 🎯 F5 直接运行当前文件

现在您可以直接在VSCode中按 **F5** 运行当前打开的算法文件！

**使用方法：**
1. 打开任意算法文件（如 `algorithms/sorting/bubble_sort.cpp`）
2. 按 **F5** 或点击调试面板的"运行"按钮
3. 算法自动编译并运行

**可用的运行方式：**
- **F5 运行**：自动编译当前文件并运行（推荐）
- **Ctrl+F5**：运行但不进入调试模式
- **Code Runner**：按 `Ctrl+Alt+N` 快速运行

**调试功能：**
- 在代码行号左侧点击设置断点
- 按 `F5` 开始调试
- 支持查看变量值、单步执行等

**推荐扩展：**
- **C/C++** (Microsoft)
- **Code Runner** (Jun Han)
- **CMake Tools** (Microsoft)
- **C/C++ Extension Pack** (Microsoft)

## 🛠️ 工具函数使用

### 高精度计时器

```cpp
#include "utility.h"

{
    Timer timer("算法名称");
    // 执行算法代码
} // 自动输出执行时间
```

### 数组操作工具

```cpp
// 生成随机数组
auto data = array_utils::generateRandom(1000);

// 打印数组
array_utils::print(data, "数组内容");

// 验证排序
bool is_sorted = array_utils::isSorted(data);
```

### 算法测试框架

```cpp
AlgorithmTester tester("算法名称");
tester.testPerformance([&]() {
    // 算法实现
}, data_size);
```

## 📊 性能测量特性

- **微秒级精度**: 使用`std::chrono::high_resolution_clock`
- **RAII风格**: 自动计时，无需手动管理
- **内存分析**: 理论空间复杂度分析
- **性能对比**: 支持多算法性能比较
- **压力测试**: 自动验证算法正确性

## 🎯 算法实现示例

### 冒泡排序

```cpp
#include "utility.h"

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

ALGORITHM_MAIN("冒泡排序")
    auto data = array_utils::generateRandom(1000);
    AlgorithmTester tester("冒泡排序");
    tester.testPerformance([&]() {
        bubbleSort(data);
    }, data.size());
ALGORITHM_END
```

## 🔧 构建系统特性

- **自动发现**: 自动发现所有算法文件
- **独立编译**: 每个算法文件独立编译为可执行文件
- **跨平台**: 支持不同操作系统和编译器
- **优化选项**: 自动设置Release/Debug编译选项
- **并行构建**: 支持多核并行编译

## 📈 性能基准

| 算法 | 时间复杂度 | 空间复杂度 | 稳定性 | 适用场景 |
|------|------------|------------|--------|----------|
| 冒泡排序 | O(n²) | O(1) | 稳定 | 小规模数据 |
| 选择排序 | O(n²) | O(1) | 不稳定 | 交换成本高 |
| 插入排序 | O(n²) | O(1) | 稳定 | 部分有序数据 |
| 快速排序 | O(n log n) | O(log n) | 不稳定 | 大规模数据 |
| 二分查找 | O(log n) | O(1) | - | 已排序数据 |

## 🎨 输出示例

```
🎯 冒泡排序 算法演示
==================================================
📊 原始数据:
   大小: 8
   内容: 64 34 25 12 22 11 90 5 

🚀 开始测试算法: 冒泡排序
==================================================
⏱️  冒泡排序 执行时间:     1234 μs (微秒)
🧠 内存分析:
   数据大小: 8 个元素
   算法类型: 冒泡排序
   额外内存: 0 bytes
   理论空间复杂度: O(1) - 原地排序
✅ 算法测试完成
📊 排序结果:
   大小: 8
   内容: 5 11 12 22 25 34 64 90 
🔍 排序验证: ✅ 正确
```

## 🤝 贡献指南

1. 在`algorithms/`目录下创建新的算法文件
2. 使用`utility.h`中的工具函数
3. 遵循现有的代码风格和注释规范
4. 添加性能测试和验证
5. 更新README文档

## 📝 许可证

MIT License

## 🚀 快速开始示例

### 使用VSCode（最简单）
1. 打开 `algorithms/sorting/bubble_sort.cpp`
2. 按 **F5**
3. 享受算法演示！

### 使用命令行
```bash
# 构建所有算法
./simple_build.sh

# 运行冒泡排序
./bin/bubble_sort

# 运行原有QuickSort算法
./bin/Code01_Partition1
```

## 🙏 致谢

感谢所有为这个项目做出贡献的开发者们！