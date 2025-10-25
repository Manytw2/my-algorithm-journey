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
 * @brief 内存使用分析器
 */
class MemoryAnalyzer {
private:
    size_t initial_memory_;
    
public:
    MemoryAnalyzer() {
        // 简化的内存使用估算（实际项目中可能需要更复杂的实现）
        initial_memory_ = getCurrentMemoryUsage();
    }
    
    /**
     * @brief 获取当前内存使用量（近似值）
     */
    size_t getCurrentMemoryUsage() const {
        // 这里是一个简化的实现，实际项目中可能需要使用系统特定的API
        return 0; // 占位符
    }
    
    /**
     * @brief 分析额外内存使用
     * @param data_size 数据大小
     * @param algorithm_type 算法类型
     */
    void analyzeMemoryUsage(size_t data_size, const std::string& algorithm_type) {
        size_t current_memory = getCurrentMemoryUsage();
        size_t additional_memory = current_memory - initial_memory_;
        
        std::cout << "🧠 内存分析:" << std::endl;
        std::cout << "   数据大小: " << data_size << " 个元素" << std::endl;
        std::cout << "   算法类型: " << algorithm_type << std::endl;
        std::cout << "   额外内存: " << additional_memory << " bytes" << std::endl;
        
        // 理论空间复杂度分析
        if (algorithm_type == "快速排序") {
            std::cout << "   理论空间复杂度: O(log n) - O(n)" << std::endl;
        } else if (algorithm_type == "归并排序") {
            std::cout << "   理论空间复杂度: O(n)" << std::endl;
        } else if (algorithm_type == "堆排序") {
            std::cout << "   理论空间复杂度: O(1)" << std::endl;
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
 * @brief 便捷宏定义
 */
#define ALGORITHM_MAIN(algorithm_name) \
    int main() { \
        std::cout << "🎯 " << algorithm_name << " 算法演示" << std::endl; \
        std::cout << "=" << std::string(50, '=') << std::endl;

#define ALGORITHM_END \
        return 0; \
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
