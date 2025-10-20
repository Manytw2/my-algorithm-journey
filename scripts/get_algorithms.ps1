# PowerShell脚本：自动发现所有可用的算法
# 扫描build/bin/Release目录，返回所有.exe文件名（不含扩展名）

$buildDir = Join-Path $PSScriptRoot "..\build\bin\Release"
$algorithms = @()

if (Test-Path $buildDir) {
    $exeFiles = Get-ChildItem -Path $buildDir -Filter "*.exe" -File
    foreach ($file in $exeFiles) {
        $name = [System.IO.Path]::GetFileNameWithoutExtension($file.Name)
        if ($name -ne "algorithm_runner") {
            $algorithms += $name
        }
    }
}

# 如果没有找到算法，返回默认列表
if ($algorithms.Count -eq 0) {
    $algorithms = @("quicksort", "partition1", "partition2")
}

# 输出算法列表，用换行分隔
$algorithms -join "`n"
