// 算法注册系统 - 统一管理所有算法
// 支持动态发现和注册算法，无需手动维护配置文件

#ifndef ALGORITHM_REGISTRY_H
#define ALGORITHM_REGISTRY_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <memory>

using namespace std;

// 算法接口基类
class Algorithm {
public:
    virtual ~Algorithm() = default;
    virtual void run() = 0;
    virtual string getName() const = 0;
    virtual string getDescription() const = 0;
};

// 算法注册表
class AlgorithmRegistry {
private:
    static map<string, shared_ptr<Algorithm>> algorithms;
    
public:
    // 注册算法
    static void registerAlgorithm(const string& name, shared_ptr<Algorithm> algorithm) {
        algorithms[name] = algorithm;
    }
    
    // 获取算法
    static shared_ptr<Algorithm> getAlgorithm(const string& name) {
        auto it = algorithms.find(name);
        return (it != algorithms.end()) ? it->second : nullptr;
    }
    
    // 获取所有算法名称
    static vector<string> getAllAlgorithmNames() {
        vector<string> names;
        for (const auto& pair : algorithms) {
            names.push_back(pair.first);
        }
        return names;
    }
    
    // 运行指定算法
    static bool runAlgorithm(const string& name) {
        auto algorithm = getAlgorithm(name);
        if (algorithm) {
            cout << "====== 运行算法: " << algorithm->getName() << " ======" << endl;
            cout << "描述: " << algorithm->getDescription() << endl;
            algorithm->run();
            return true;
        }
        return false;
    }
    
    // 运行所有算法
    static void runAllAlgorithms() {
        cout << "====== 运行所有算法 ======" << endl;
        for (const auto& pair : algorithms) {
            cout << "\n--- " << pair.first << " ---" << endl;
            pair.second->run();
        }
    }
    
    // 列出所有算法
    static void listAlgorithms() {
        cout << "====== 可用算法列表 ======" << endl;
        for (const auto& pair : algorithms) {
            cout << "• " << pair.first << ": " << pair.second->getDescription() << endl;
        }
    }
};

// 算法注册宏 - 简化注册过程
#define REGISTER_ALGORITHM(ClassName, Name, Description) \
    namespace { \
        struct ClassName##Registrar { \
            ClassName##Registrar() { \
                AlgorithmRegistry::registerAlgorithm(Name, make_shared<ClassName>()); \
            } \
        }; \
        static ClassName##Registrar ClassName##_registrar; \
    }

// 算法基类实现宏
#define IMPLEMENT_ALGORITHM(ClassName, Name, Description) \
    class ClassName : public Algorithm { \
    public: \
        void run() override; \
        string getName() const override { return Name; } \
        string getDescription() const override { return Description; } \
    }; \
    REGISTER_ALGORITHM(ClassName, Name, Description)

// 全局算法注册表实例
map<string, shared_ptr<Algorithm>> AlgorithmRegistry::algorithms;

#endif
