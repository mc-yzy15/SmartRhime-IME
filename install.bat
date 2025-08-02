REM 自由拼音输入法安装脚本
REM 请以管理员身份运行
REM 完全不依赖Python

set SYS_DIR=%SystemRoot%\system32

REM 注册输入法
regedit /s register.reg

REM 复制文件到系统目录
copy freepy.ime %SYS_DIR%\freepy.ime
copy freepy.tab %SYS_DIR%\freepy.tab
copy freepy.hlp %SYS_DIR%\freepy.hlp
copy userdict.dat %SYS_DIR%\userdict.dat

REM 检查词库更新
if exist %SYS_DIR%\freepy.tab (
    echo 正在检查词库更新...
    powershell -Command "$webClient = New-Object System.Net.WebClient; $webClient.DownloadFile('https://example.com/freepy/latest.tab', '%TEMP%\latest.tab')"
    if exist %TEMP%\latest.tab (
        fc %TEMP%\latest.tab %SYS_DIR%\freepy.tab >nul
        if %errorlevel% neq 0 (
            echo 发现新版本词库，正在更新...
            move /Y %TEMP%\latest.tab %SYS_DIR%\freepy.tab
        ) else (
            echo 词库已是最新版本
        )
    ) else (
        echo 无法下载最新词库
    )
)

echo 安装完成，请通过控制面板添加"自由拼音输入法"
pause