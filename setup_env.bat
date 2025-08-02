@echo off

REM 检查Python是否安装
python --version >nul 2>&1
if errorlevel 1 (
    echo 未找到Python。请先安装Python 3.10+，然后重试。
    exit /b 1
)

REM 创建虚拟环境
echo 创建虚拟环境...
python -m venv .venv
if errorlevel 1 (
    echo 创建虚拟环境失败
    exit /b 1
)

REM 激活环境并安装依赖
echo 激活环境并安装依赖...
call .venv\Scripts\activate
if errorlevel 1 (
    echo 激活环境失败
    exit /b 1
)

pip install -r requirements.txt
if errorlevel 1 (
    echo 依赖安装失败
    exit /b 1
)

echo 环境配置完成！
echo 使用以下命令激活环境：
echo .venv\Scripts\activate