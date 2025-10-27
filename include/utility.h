/**
 * @file utility.h
 * @brief 通用工具函数库 - 高精度性能测量和算法辅助工具
 * @author Algorithm Learning Environment
 * @version 1.0
 *
 * 提供以下核心功能：
 * - 高精度计时器（微秒级）
 * - 内存使用分析
 * - 数组/容器操作工具
 * - 随机数据生成
 * - 算法验证工具
 */

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <iomanip>
#include <memory>
#include <algorithm>
#include <functional>
#include <cstring>
#include <cassert>
#include <sstream>
#include <cmath>

// 平台特定的内存监控头文件
#ifdef __APPLE__
#include <mach/mach.h>
#elif __linux__
#include <sys/resource.h>
#elif _WIN32
#include <windows.h>
#include <psapi.h>
#endif

namespace algo {

/**
 * @brief 高精度计时器类 - RAII风格
 *
 * 使用示例：
 * {
 *     Timer timer("算法名称");
 *     // 执行算法代码
 * } // 自动输出执行时间
 */
class Timer {
private:
    std::string name_;
    std::chrono::high_resolution_clock::time_point start_;
    bool stopped_;

public:
    explicit Timer(const std::string& name = "算法")
        : name_(name), stopped_(false) {
        start_ = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        if (!stopped_) {
            stop();
        }
    }

    /**
     * @brief 停止计时并输出结果
     * @return 执行时间（微秒）
     */
    long long stop() {
        if (stopped_) return 0;

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start_);

        std::cout << "⏱️  " << name_ << " 执行时间: "
                  << std::setw(8) << duration.count() << " μs (微秒)" << std::endl;

        stopped_ = true;
        return duration.count();
    }

    /**
     * @brief 获取当前已用时间（不停止计时）
     * @return 已用时间（微秒）
     */
    long long elapsed() const {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start_);
        return duration.count();
    }
};

/**
 * @brief 内存使用分析器 - 支持跨平台内存监控
 */
class MemoryAnalyzer {
private:
    size_t initial_memory_;

public:
    MemoryAnalyzer() {
        initial_memory_ = getCurrentMemoryUsage();
    }

    /**
     * @brief 获取当前内存使用量（RSS - Resident Set Size）
     * @return 当前进程的内存使用量（bytes）
     */
    size_t getCurrentMemoryUsage() const {
        #ifdef __APPLE__
        // macOS使用mach API
        struct mach_task_basic_info info;
        mach_msg_type_number_t size = MACH_TASK_BASIC_INFO_COUNT;
        kern_return_t kerr = task_info(mach_task_self(),
                                       MACH_TASK_BASIC_INFO,
                                       (task_info_t)&info,
                                       &size);
        if (kerr == KERN_SUCCESS) {
            return info.resident_size;
        }
        return 0;

        #elif __linux__
        // Linux使用getrusage
        struct rusage usage;
        if (getrusage(RUSAGE_SELF, &usage) == 0) {
            return usage.ru_maxrss * 1024; // KB转bytes
        }
        return 0;

        #elif _WIN32
        // Windows使用GetProcessMemoryInfo
        #include <windows.h>
        #include <psapi.h>
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
            return pmc.WorkingSetSize;
        }
        return 0;

        #else
        // 其他平台返回理论估算
        return 0;
        #endif
    }

    /**
     * @brief 格式化内存大小显示
     */
    std::string formatMemorySize(size_t bytes) const {
        std::ostringstream oss;
        if (bytes < 1024) {
            oss << bytes << " B";
        } else if (bytes < 1024 * 1024) {
            oss << std::fixed << std::setprecision(2) << (bytes / 1024.0) << " KB";
        } else {
            oss << std::fixed << std::setprecision(2) << (bytes / (1024.0 * 1024.0)) << " MB";
        }
        return oss.str();
    }

    /**
     * @brief 理论空间复杂度计算
     */
    size_t calculateTheoreticalSpace(const std::string& algorithm_type, size_t n) const {
        if (algorithm_type.find("快速排序") != std::string::npos) {
            // 快速排序：递归栈深度 O(log n)，每层需要常数空间
            return static_cast<size_t>(std::log2(n) * sizeof(void*) * 3);
        } else if (algorithm_type.find("归并排序") != std::string::npos) {
            // 归并排序：需要O(n)辅助空间
            return n * sizeof(int);
        } else if (algorithm_type.find("堆排序") != std::string::npos ||
                   algorithm_type.find("冒泡排序") != std::string::npos ||
                   algorithm_type.find("插入排序") != std::string::npos ||
                   algorithm_type.find("选择排序") != std::string::npos) {
            // 原地排序：O(1)
            return sizeof(int) * 3; // 几个临时变量
        }
        return 0;
    }

    /**
     * @brief 分析额外内存使用
     * @param data_size 数据大小
     * @param algorithm_type 算法类型
     */
    void analyzeMemoryUsage(size_t data_size, const std::string& algorithm_type) {
        size_t current_memory = getCurrentMemoryUsage();
        size_t additional_memory = (current_memory > initial_memory_)
                                   ? (current_memory - initial_memory_)
                                   : 0;
        size_t theoretical_space = calculateTheoreticalSpace(algorithm_type, data_size);

        std::cout << "\n🧠 内存分析:" << std::endl;
        std::cout << "   数据大小: " << data_size << " 个元素 ("
                  << formatMemorySize(data_size * sizeof(int)) << ")" << std::endl;
        std::cout << "   算法类型: " << algorithm_type << std::endl;

        if (current_memory > 0) {
            std::cout << "   初始内存: " << formatMemorySize(initial_memory_) << std::endl;
            std::cout << "   当前内存: " << formatMemorySize(current_memory) << std::endl;
            std::cout << "   额外内存: " << formatMemorySize(additional_memory) << std::endl;
        }

        if (theoretical_space > 0) {
            std::cout << "   理论额外空间: " << formatMemorySize(theoretical_space) << std::endl;
        }

        // 理论空间复杂度分析
        if (algorithm_type.find("快速排序") != std::string::npos) {
            std::cout << "   空间复杂度: O(log n) 平均，O(n) 最坏 - 递归栈" << std::endl;
        } else if (algorithm_type.find("归并排序") != std::string::npos) {
            std::cout << "   空间复杂度: O(n) - 需要辅助数组" << std::endl;
        } else if (algorithm_type.find("堆排序") != std::string::npos) {
            std::cout << "   空间复杂度: O(1) - 原地排序" << std::endl;
        } else if (algorithm_type.find("冒泡排序") != std::string::npos ||
                   algorithm_type.find("插入排序") != std::string::npos ||
                   algorithm_type.find("选择排序") != std::string::npos) {
            std::cout << "   空间复杂度: O(1) - 原地排序" << std::endl;
        }
    }
};

/**
 * @brief 数组/容器操作工具
 */
namespace array_utils {

/**
 * @brief 打印数组/容器
 */
template<typename Container>
void print(const Container& container, const std::string& title = "数组内容",
           size_t max_elements = 20) {
    std::cout << "📊 " << title << ":" << std::endl;
    std::cout << "   大小: " << container.size() << std::endl;
    std::cout << "   内容: ";

    size_t count = 0;
    for (const auto& element : container) {
        if (count >= max_elements) {
            std::cout << "... (显示前" << max_elements << "个元素)";
            break;
        }
        std::cout << element << " ";
        ++count;
    }
    std::cout << std::endl;
}

/**
 * @brief 生成随机数组
 */
template<typename T = int>
std::vector<T> generateRandom(size_t size, T min_val = 1, T max_val = 100) {
    std::vector<T> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dis(min_val, max_val);

    for (size_t i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
    return arr;
}

/**
 * @brief 生成有序数组
 */
template<typename T = int>
std::vector<T> generateSorted(size_t size, T start = 1, T step = 1) {
    std::vector<T> arr(size);
    for (size_t i = 0; i < size; ++i) {
        arr[i] = start + i * step;
    }
    return arr;
}

/**
 * @brief 生成逆序数组
 */
template<typename T = int>
std::vector<T> generateReverse(size_t size, T start = 100) {
    std::vector<T> arr(size);
    for (size_t i = 0; i < size; ++i) {
        arr[i] = start - i;
    }
    return arr;
}

/**
 * @brief 验证数组是否已排序
 */
template<typename Container>
bool isSorted(const Container& container, bool ascending = true) {
    if (container.size() <= 1) return true;

    for (size_t i = 1; i < container.size(); ++i) {
        if (ascending && container[i] < container[i-1]) {
            return false;
        } else if (!ascending && container[i] > container[i-1]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief 复制数组
 */
template<typename T>
std::vector<T> copy(const std::vector<T>& original) {
    return std::vector<T>(original);
}

} // namespace array_utils

/**
 * @brief 算法性能测试框架
 */
class AlgorithmTester {
private:
    std::string algorithm_name_;
    MemoryAnalyzer memory_analyzer_;

public:
    explicit AlgorithmTester(const std::string& name) : algorithm_name_(name) {}

    /**
     * @brief 测试算法性能
     */
    template<typename Func>
    long long testPerformance(Func func, size_t data_size = 0) {
        std::cout << "\n🚀 开始测试算法: " << algorithm_name_ << std::endl;
        std::cout << "=" << std::string(50, '=') << std::endl;

        Timer timer(algorithm_name_);
        func();
        long long execution_time = timer.stop();

        if (data_size > 0) {
            memory_analyzer_.analyzeMemoryUsage(data_size, algorithm_name_);
        }

        std::cout << "✅ 算法测试完成" << std::endl;
        return execution_time;
    }

    /**
     * @brief 比较多个算法的性能
     */
    template<typename... Funcs>
    void compareAlgorithms(const std::vector<std::string>& names, Funcs... funcs) {
        std::cout << "\n🏆 算法性能比较" << std::endl;
        std::cout << "=" << std::string(50, '=') << std::endl;

        std::vector<std::function<void()>> functions = {funcs...};
        std::vector<long long> times;

        for (size_t i = 0; i < functions.size() && i < names.size(); ++i) {
            Timer timer(names[i]);
            functions[i]();
            times.push_back(timer.stop());
        }

        // 找出最快的算法
        auto min_it = std::min_element(times.begin(), times.end());
        size_t fastest_index = std::distance(times.begin(), min_it);

        std::cout << "\n🏅 性能排名:" << std::endl;
        for (size_t i = 0; i < names.size() && i < times.size(); ++i) {
            std::cout << "   " << (i + 1) << ". " << names[i]
                      << ": " << times[i] << " μs";
            if (i == fastest_index) {
                std::cout << " ⭐ (最快)";
            }
            std::cout << std::endl;
        }
    }
};

/**
 * @brief 算法验证工具
 */
namespace validation {

/**
 * @brief 验证排序算法
 */
template<typename SortFunc>
bool validateSorting(SortFunc sort_func, const std::vector<int>& test_data) {
    auto data_copy = array_utils::copy(test_data);
    sort_func(data_copy);

    bool is_correct = array_utils::isSorted(data_copy);

    std::cout << "🔍 排序验证: " << (is_correct ? "✅ 正确" : "❌ 错误") << std::endl;
    if (!is_correct) {
        std::cout << "   原始数据: ";
        array_utils::print(test_data, "", 10);
        std::cout << "   排序结果: ";
        array_utils::print(data_copy, "", 10);
    }

    return is_correct;
}

/**
 * @brief 压力测试
 */
template<typename Func>
void stressTest(Func func, size_t iterations = 1000, size_t data_size = 100) {
    std::cout << "💪 开始压力测试: " << iterations << " 次迭代，数据大小: " << data_size << std::endl;

    size_t success_count = 0;
    Timer total_timer("压力测试总时间");

    for (size_t i = 0; i < iterations; ++i) {
        auto test_data = array_utils::generateRandom(data_size);
        auto original_data = array_utils::copy(test_data);

        func(test_data);

        if (array_utils::isSorted(test_data)) {
            ++success_count;
        }
    }

    long long total_time = total_timer.stop();

    std::cout << "📊 压力测试结果:" << std::endl;
    std::cout << "   成功率: " << success_count << "/" << iterations
              << " (" << (100.0 * success_count / iterations) << "%)" << std::endl;
    std::cout << "   平均时间: " << (total_time / iterations) << " μs" << std::endl;
}

} // namespace validation

/**
 * @brief 打印算法标题
 * @param algorithm_name 算法名称
 */
inline void printAlgorithmTitle(const std::string& algorithm_name) {
    std::cout << "🎯 " << algorithm_name << " 算法演示" << std::endl;
    std::cout << "=" << std::string(50, '=') << std::endl;
}

#define TIMER_START(name) Timer timer(name)
#define TIMER_STOP() timer.stop()

#define PRINT_ARRAY(arr, title) array_utils::print(arr, title)
#define GENERATE_RANDOM(size) array_utils::generateRandom(size)
#define IS_SORTED(arr) array_utils::isSorted(arr)

} // namespace algo

// 为了向后兼容，提供全局命名空间别名
using algo::Timer;
using algo::array_utils::print;
using algo::array_utils::generateRandom;
using algo::array_utils::isSorted;

#endif // UTILITY_H
