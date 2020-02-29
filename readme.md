# 小小按键精灵

用来定时按下某个按键。比如 Ctrl + S，免得忘记保存。

## 使用方法

1. 启动之后最小化；
2. 当需要按下按键时，按下之前设定的`开始/停止`快捷键。就会按照之前设定的时间间隔按下`键一`。
3. 当不需要时，按下之前设定的`开始/停止`快捷键。就会停止发送。
4. 可以设置第二组按键`键二`，按下切换快捷键就会把当前定时切换的按键更改为`键二`，再按一次更改回去`键一`。

## 编译说明

1. 本项目基于 Qt 5.9.9 开发，需[下载](http://download.qt.io/archive/qt/5.9/5.9.9/) Qt 开发环境；
2. 系统 Hotkey 功能依赖于 [QHotkey](https://github.com/Skycoder42/QHotkey) 实现，使用 [qdep](https://github.com/Skycoder42/qdep) 管理依赖，请执行如下指令安装：
```bash
pip install qdep
qdep prfgen --qmake "X:\Your\Qt\Path\...\mingw53_32\bin\qmake.exe"
```
