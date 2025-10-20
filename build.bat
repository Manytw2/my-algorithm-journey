@echo off
REM C++算法学习项目 - 构建脚本
REM 用于快速编译和运行算法代码

echo ========================================
echo C++算法学习项目构建脚本
echo ========================================

REM 检查是否存在build目录，不存在则创建
if not exist "build" mkdir build
cd build

REM 配置CMake项目
echo 正在配置CMake项目...
cmake .. -G "Visual Studio 17 2022" -A x64
if %errorlevel% neq 0 (
    echo CMake配置失败！
    pause
    exit /b 1
)

REM 编译项目
echo 正在编译项目...
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo 编译失败！
    pause
    exit /b 1
)

echo ========================================
echo 编译完成！可执行文件位于: build\bin\Release\
echo ========================================

REM 返回上级目录
cd ..

REM 询问是否运行测试
set /p choice="是否运行快速排序测试？(y/n): "
if /i "%choice%"=="y" (
    echo 运行快速排序测试...
    build\bin\Release\quicksort.exe
    echo.
    echo 运行Partition1测试...
    build\bin\Release\partition1.exe
    echo.
    echo 运行Partition2测试...
    build\bin\Release\partition2.exe
)

pause
