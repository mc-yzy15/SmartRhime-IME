@echo off

REM 智能拼音输入法编译脚本
REM 完全不依赖Python

REM 检查是否安装了MinGW
where mingw32-make >nul 2>&1
if errorlevel 1 (
    echo 未找到mingw32-make。请确保MinGW已安装并添加到系统环境变量。
    echo MinGW路径应为: C:\Qt\6.9.1\mingw_64\bin
    exit /b 1
)

REM 编译项目
echo 正在编译项目...
mingw32-make
if errorlevel 1 (
    echo 编译失败
    exit /b 1
)

echo 编译成功！生成了freepy.ime

REM 安装输入法
echo 正在安装输入法...
call install.bat

if errorlevel 1 (
    echo 安装失败
    exit /b 1
)

echo 安装成功！请通过控制面板添加"自由拼音输入法"