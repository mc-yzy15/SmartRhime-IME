# SmartRhime-IME 智韵输入法

![输入法演示](screenshots/preview.gif)

## 项目描述

智能拼音输入法解决方案，支持词库热更新和个性化皮肤功能。采用混合算法模型实现高精度输入预测，包含40万条核心词库和20个专业领域词库。

## 功能特性

- 多模式输入支持（全拼/简拼/混拼）
- 智能词频动态调整
- 领域词库自动加载（IT/医学/法律等）
- 基于CSS的皮肤定制系统
- 增量词库更新机制
- 用户词典云同步

## 安装指南

### 系统要求

- Windows 10/11 64位
- .NET Framework 4.8
- Python 3.10+（用于词库管理）

### 安装步骤

1. 右键单击`install.bat`选择"以管理员身份运行"
2. 同意UAC权限提示
3. 等待自动完成以下操作：
   - 注册输入法组件
   - 部署运行时文件到%SystemRoot%\system32
   - 创建Python虚拟环境
   - 安装依赖包
4. 通过控制面板 > 语言 > 输入法设置添加"智韵输入法"

## 使用说明

### 输入法切换

- `Ctrl + Shift`：循环切换输入法
- `Win + Space`：直接切换至智韵输入法

### 词库管理

```bash
# 更新核心词库
python scripts/merge_dicts.py --update

# 添加自定义词库
python scripts/merge_dicts.py --add dict/THUOCL_IT.txt
```

## 开发规范

### 分支策略

- `main`：稳定版本
- `dev`：功能开发分支
- `hotfix-*`：紧急修复分支

### 提交规范

```text
类型(范围): 简要描述

详细说明（可选）

关联Issue：#123
```

## 授权协议

版权所有 (c) 2024-2025 mc-yzy15 (<yaoziying@yzit7.wecom.work>)
本程序是专有软件，未经明确授权不得：

- 逆向工程
- 重新分发
- 商业性使用

## 技术支持

联系邮箱：<public@yzit7.wecom.work>（备用：<yingmoliuguang@yeah.net>）
紧急问题请提交Issues
