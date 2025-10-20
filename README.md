# C++算法学习项目

这是一个专门用于学习C++算法程序设计的项目，采用模块化设计，每个算法都是独立的可执行文件。

## 项目结构

```
algorithm-Tsinghua-testbook-code/
├── 快速排序/                    # 快速排序算法相关文件
│   ├── Code01_Partition1.cpp   # Partition1实现
│   ├── Code02_Partition2.cpp   # Partition2实现
│   ├── Code03_QuickSort.cpp    # 快速排序实现
│   ├── QuickSort_interface.h   # 快速排序相关头文件
│   └── output/                 # 旧的可执行文件目录（已废弃）
├── common/                     # 通用头文件和工具
│   └── algorithm_interface.h   # 通用算法接口
├── templates/                  # 代码模板
│   └── algorithm_template.cpp  # 算法代码模板
├── build/                      # 构建输出目录（自动生成）
│   └── bin/Release/            # 可执行文件输出目录
├── .vscode/                    # VSCode配置文件
│   ├── tasks.json             # 构建任务配置
│   ├── launch.json            # 调试配置
│   └── settings.json          # 编辑器设置
├── CMakeLists.txt             # CMake构建配置
├── build.bat                  # 构建脚本
├── run.bat                    # 运行脚本
├── clean.bat                  # 清理脚本
├── create_algorithm.bat       # 创建新算法脚本
└── README.md                  # 项目说明文档
```

## 使用方法

### 1. 快速开始

```bash
# 编译所有算法
build.bat

# 运行算法测试
run.bat

# 清理构建文件
clean.bat
```

### 2. 创建新算法

```bash
# 创建新的算法文件
create_algorithm.bat [算法名称] [分类目录]

# 示例
create_algorithm.bat BubbleSort 排序算法
create_algorithm.bat BinarySearch 查找算法
```

### 3. VSCode集成

- **构建项目**: `Ctrl+Shift+P` → `Tasks: Run Task` → `构建项目`
- **运行算法**: `Ctrl+Shift+P` → `Tasks: Run Task` → `运行[算法名称]`
- **调试算法**: `F5` 或使用调试面板选择对应的调试配置

## 设计特点

### 1. 模块化设计
- 每个算法都是独立的可执行文件
- 统一的头文件管理
- 清晰的目录结构

### 2. 自动化构建
- CMake统一构建系统
- 批处理脚本简化操作
- VSCode任务集成

### 3. 开发友好
- 代码模板快速创建
- 统一的测试框架
- 性能测试工具

### 4. 文件管理
- 可执行文件统一输出到 `build/bin/Release/`
- 自动清理临时文件
- 版本控制友好（忽略构建文件）

## 扩展指南

### 添加新算法分类

1. 创建新的分类目录
2. 在 `CMakeLists.txt` 中添加对应的可执行文件配置
3. 更新 `run.bat` 脚本添加新的运行选项

### 自定义构建选项

修改 `CMakeLists.txt` 中的编译选项：
- 添加新的编译标志
- 修改输出目录
- 添加新的依赖库

## 注意事项

1. **编译器要求**: 需要安装Visual Studio 2022或更新版本
2. **CMake版本**: 需要CMake 3.10或更高版本
3. **文件编码**: 建议使用UTF-8编码保存源文件
4. **路径问题**: 避免在路径中使用中文字符和空格

## 故障排除

### 编译失败
- 检查Visual Studio是否正确安装
- 确认CMake版本是否满足要求
- 查看错误信息中的具体错误原因

### 运行失败
- 确认已成功编译
- 检查可执行文件是否存在
- 查看控制台输出的错误信息

### VSCode集成问题
- 确认已安装C/C++扩展
- 检查CMake Tools扩展是否安装
- 重新加载VSCode窗口
