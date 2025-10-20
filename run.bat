@echo off
REM C++算法学习项目 - 快速运行脚本
REM 用于快速运行已编译的算法程序

echo ========================================
echo C++算法学习项目 - 快速运行
echo ========================================

REM 检查是否已编译
if not exist "build\bin\Release\quicksort.exe" (
    echo 错误：未找到编译后的可执行文件！
    echo 请先运行 build.bat 进行编译
    pause
    exit /b 1
)

echo 可用的算法程序：
echo 1. 快速排序 (quicksort)
echo 2. Partition1 算法
echo 3. Partition2 算法
echo 4. 运行所有测试
echo.

set /p choice="请选择要运行的程序 (1-4): "

if "%choice%"=="1" (
    echo 运行快速排序...
    build\bin\Release\quicksort.exe
) else if "%choice%"=="2" (
    echo 运行Partition1...
    build\bin\Release\partition1.exe
) else if "%choice%"=="3" (
    echo 运行Partition2...
    build\bin\Release\partition2.exe
) else if "%choice%"=="4" (
    echo 运行所有测试...
    echo.
    echo ========== 快速排序测试 ==========
    build\bin\Release\quicksort.exe
    echo.
    echo ========== Partition1测试 ==========
    build\bin\Release\partition1.exe
    echo.
    echo ========== Partition2测试 ==========
    build\bin\Release\partition2.exe
) else (
    echo 无效选择！
)

echo.
pause
