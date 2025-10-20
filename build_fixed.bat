@echo off
chcp 65001 >nul
REM 修复版构建脚本 - 解决编码和路径问题
echo ========================================
echo C++算法学习项目 - 修复版构建脚本
echo ========================================

REM 设置Visual Studio环境
echo 正在初始化Visual Studio 2022环境...
call "D:\VS2022\Community\VC\Auxiliary\Build\vcvars64.bat"

REM 检查编译器是否可用
cl >nul 2>&1
if %errorlevel% neq 0 (
    echo ❌ 编译器初始化失败
    pause
    exit /b 1
)

echo ✅ Visual Studio 2022环境初始化成功

REM 创建输出目录
if not exist "build\bin" mkdir "build\bin"

echo.
echo 正在编译算法文件...

REM 编译快速排序相关文件 - 使用绝对路径
echo 编译 Code01_Partition1...
cl /EHsc /std:c++17 /utf-8 "快速排序\Code01_Partition1.cpp" /Fe:"build\bin\partition1.exe" /Fo:"build\bin\partition1.obj"
if %errorlevel% equ 0 (
    echo ✅ partition1.exe 编译成功
) else (
    echo ❌ partition1.exe 编译失败
)

echo 编译 Code02_Partition2...
cl /EHsc /std:c++17 /utf-8 "快速排序\Code02_Partition2.cpp" /Fe:"build\bin\partition2.exe" /Fo:"build\bin\partition2.obj"
if %errorlevel% equ 0 (
    echo ✅ partition2.exe 编译成功
) else (
    echo ❌ partition2.exe 编译失败
)

echo 编译 Code03_QuickSort...
cl /EHsc /std:c++17 /utf-8 "快速排序\Code03_QuickSort.cpp" /Fe:"build\bin\quicksort.exe" /Fo:"build\bin\quicksort.obj"
if %errorlevel% equ 0 (
    echo ✅ quicksort.exe 编译成功
) else (
    echo ❌ quicksort.exe 编译失败
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
    if exist "build\bin\quicksort.exe" (
        build\bin\quicksort.exe
    ) else (
        echo quicksort.exe 不存在
    )
    echo.
    echo 运行Partition1测试...
    if exist "build\bin\partition1.exe" (
        build\bin\partition1.exe
    ) else (
        echo partition1.exe 不存在
    )
    echo.
    echo 运行Partition2测试...
    if exist "build\bin\partition2.exe" (
        build\bin\partition2.exe
    ) else (
        echo partition2.exe 不存在
    )
)

pause
