@echo off
REM C++算法学习项目 - 清理脚本
REM 用于清理编译产生的文件

echo ========================================
echo C++算法学习项目 - 清理构建文件
echo ========================================

REM 询问用户确认
set /p confirm="确定要清理所有构建文件吗？这将删除build目录和所有可执行文件 (y/n): "
if /i not "%confirm%"=="y" (
    echo 取消清理操作
    pause
    exit /b 0
)

REM 删除build目录
if exist "build" (
    echo 正在删除build目录...
    rmdir /s /q build
    echo build目录已删除
) else (
    echo build目录不存在
)

REM 删除其他可能的临时文件
if exist "*.exe" (
    echo 正在删除根目录下的exe文件...
    del /q *.exe
)

if exist "快速排序\output\*.exe" (
    echo 正在删除快速排序output目录下的exe文件...
    del /q "快速排序\output\*.exe"
)

echo ========================================
echo 清理完成！
echo ========================================
pause
