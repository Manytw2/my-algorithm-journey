@echo off
REM 针对Visual Studio 2022的专用构建脚本
echo ========================================
echo C++算法学习项目 - VS2022构建脚本
echo ========================================

REM 设置Visual Studio环境
echo 正在初始化Visual Studio 2022环境...
call "D:\VS2022\Community\VC\Auxiliary\Build\vcvars64.bat"

REM 检查编译器是否可用
cl >nul 2>&1
if %errorlevel% neq 0 (
    echo ❌ 编译器初始化失败
    echo 请检查Visual Studio 2022安装路径
    pause
    exit /b 1
)

echo ✅ Visual Studio 2022环境初始化成功

REM 创建输出目录
if not exist "build\bin" mkdir "build\bin"

echo.
echo 正在编译算法文件...

REM 编译快速排序相关文件
echo 编译 Code01_Partition1...
cl /EHsc /std:c++17 "快速排序\Code01_Partition1.cpp" /Fe:"build\bin\partition1.exe" /Fo:"build\bin\partition1.obj"
if %errorlevel% equ 0 (
    echo ✅ partition1.exe 编译成功
) else (
    echo ❌ partition1.exe 编译失败
)

echo 编译 Code02_Partition2...
cl /EHsc /std:c++17 "快速排序\Code02_Partition2.cpp" /Fe:"build\bin\partition2.exe" /Fo:"build\bin\partition2.obj"
if %errorlevel% equ 0 (
    echo ✅ partition2.exe 编译成功
) else (
    echo ❌ partition2.exe 编译失败
)

echo 编译 Code03_QuickSort...
cl /EHsc /std:c++17 "快速排序\Code03_QuickSort.cpp" /Fe:"build\bin\quicksort.exe" /Fo:"build\bin\quicksort.obj"
if %errorlevel% equ 0 (
    echo ✅ quicksort.exe 编译成功
) else (
    echo ❌ quicksort.exe 编译失败
)

REM 编译统一运行器
echo 编译 algorithm_runner...
cl /EHsc /std:c++17 "algorithm_runner.cpp" /Fe:"build\bin\algorithm_runner.exe" /Fo:"build\bin\algorithm_runner.obj"
if %errorlevel% equ 0 (
    echo ✅ algorithm_runner.exe 编译成功
) else (
    echo ❌ algorithm_runner.exe 编译失败
)

echo.
echo ========================================
echo 编译完成！可执行文件位于: build\bin\
echo ========================================

REM 询问是否运行测试
set /p choice="是否运行测试？(y/n): "
if /i "%choice%"=="y" (
    echo.
    echo 运行快速排序测试...
    build\bin\quicksort.exe
    echo.
    echo 运行Partition1测试...
    build\bin\partition1.exe
    echo.
    echo 运行Partition2测试...
    build\bin\partition2.exe
    echo.
    echo 运行统一算法器...
    build\bin\algorithm_runner.exe --list
)

pause
