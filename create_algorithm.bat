@echo off
REM 智能算法创建脚本 - 支持交互式创建和自动分类
REM 用法: create_algorithm.bat [算法名称] [分类目录]

echo ========================================
echo C++算法学习项目 - 智能算法创建器
echo ========================================

REM 如果没有提供参数，进入交互模式
if "%1"=="" (
    echo 请选择创建模式：
    echo 1. 交互式创建（推荐）
    echo 2. 命令行创建
    echo.
    set /p mode="请选择模式 (1-2): "
    
    if "%mode%"=="1" goto :interactive_mode
    if "%mode%"=="2" goto :command_mode
    echo 无效选择，使用交互模式
    goto :interactive_mode
) else (
    goto :command_mode
)

:interactive_mode
echo.
echo ========== 交互式创建模式 ==========
echo.

REM 获取算法名称
set /p ALGORITHM_NAME="请输入算法名称 (如: BubbleSort): "
if "%ALGORITHM_NAME%"=="" (
    echo 错误：算法名称不能为空！
    pause
    exit /b 1
)

REM 选择算法分类
echo.
echo 请选择算法分类：
echo 1. 排序算法
echo 2. 查找算法  
echo 3. 图算法
echo 4. 动态规划
echo 5. 其他算法
echo 6. 自定义分类
echo.
set /p category_choice="请选择分类 (1-6): "

if "%category_choice%"=="1" set CATEGORY=排序算法
if "%category_choice%"=="2" set CATEGORY=查找算法
if "%category_choice%"=="3" set CATEGORY=图算法
if "%category_choice%"=="4" set CATEGORY=动态规划
if "%category_choice%"=="5" set CATEGORY=其他算法
if "%category_choice%"=="6" (
    set /p CATEGORY="请输入自定义分类名称: "
    if "%CATEGORY%"=="" set CATEGORY=其他算法
)

goto :create_algorithm

:command_mode
set ALGORITHM_NAME=%1
set CATEGORY=%2
if "%CATEGORY%"=="" set CATEGORY=其他算法

:create_algorithm
echo.
echo ========== 创建算法文件 ==========
echo 算法名称: %ALGORITHM_NAME%
echo 分类目录: %CATEGORY%

REM 创建分类目录（如果不存在）
if not exist "%CATEGORY%" (
    echo 创建分类目录: %CATEGORY%
    mkdir "%CATEGORY%"
)

REM 创建算法文件
set ALGORITHM_FILE=%CATEGORY%\Code_%ALGORITHM_NAME%.cpp
if exist "%ALGORITHM_FILE%" (
    echo 警告：文件 %ALGORITHM_FILE% 已存在！
    set /p overwrite="是否覆盖？(y/n): "
    if /i not "%overwrite%"=="y" (
        echo 取消创建
        pause
        exit /b 0
    )
)

echo 正在创建算法文件: %ALGORITHM_FILE%

REM 从模板创建文件
(
echo #include "common/algorithm_interface.h"
echo.
echo // %ALGORITHM_NAME% 算法实现
echo // 分类: %CATEGORY%
echo // 时间复杂度: TODO
echo // 空间复杂度: TODO
echo // 算法描述: TODO
echo.
echo void %ALGORITHM_NAME%(vector^<int^>^& arr^) {
echo     // TODO: 实现 %ALGORITHM_NAME% 算法
echo     // 提示: 使用 print_array^(arr^) 打印数组
echo }
echo.
echo // 测试函数
echo void test_%ALGORITHM_NAME%^(^) {
echo     cout ^<^< "====== %ALGORITHM_NAME% 算法测试 ======" ^<^< endl;
echo     vector^<int^> arr = {5, 3, 1, 9, 2, 8, 4, 7, 6};
echo     cout ^<^< "测试前: " ^<^< endl;
echo     print_array^(arr^);
echo     %ALGORITHM_NAME%^(arr^);
echo     cout ^<^< "测试后: " ^<^< endl;
echo     print_array^(arr^);
echo     if ^(is_sorted^(arr^)^) {
echo         cout ^<^< "✓ 排序结果正确" ^<^< endl;
echo     } else {
echo         cout ^<^< "✗ 排序结果错误" ^<^< endl;
echo     }
echo }
echo.
echo // 临时main函数，用于单独运行检验
echo int main^(^) {
echo     test_%ALGORITHM_NAME%^(^);
echo     return 0;
echo }
) > "%ALGORITHM_FILE%"

echo ✓ 算法文件创建成功: %ALGORITHM_FILE%
echo.

REM 询问是否立即编译和测试
set /p build_now="是否立即编译和测试？(y/n): "
if /i "%build_now%"=="y" (
    echo 正在编译项目...
    call build.bat
    if %errorlevel% equ 0 (
        echo 编译成功！正在运行测试...
        "%ALGORITHM_FILE:.cpp=.exe" 2>nul
        if %errorlevel% neq 0 (
            echo 注意：可执行文件可能还未生成，请稍后运行
        )
    )
)

echo.
echo ========== 创建完成 ==========
echo 下一步操作：
echo 1. 编辑 %ALGORITHM_FILE% 实现算法逻辑
echo 2. 运行 build.bat 编译项目
echo 3. 运行 algorithm_runner.exe 测试算法
echo 4. 使用VSCode的"运行指定算法"任务
echo.
pause
