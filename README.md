# HoloLib_CPP
Computer-generated holography (CGH) C++ library based on OpenCV

开发日志 | [Development log](./DevLog.md)

## 项目简介
计算全息算法库，构建 C++ 全息计算程序。

## 功能特性
```
copyMakeBorder          % 扩充图像边界 超过图像区域补零
expandMAT               % 对矩阵行向和列向扩展
getAxilens              % 获取大焦比轴锥透镜相位
getBlaze                % 获取闪耀光栅相位
getLens                 % 获取菲涅尔球面透镜相位
iterFourier             % 迭代傅里叶算法
iterFresnel             % 迭代菲涅尔算法
propDFFT                % 菲涅尔传播-两次傅里叶计算法方法
propTFFT                % 菲涅尔传播-三次傅里叶计算法方法
propDOE                 % DOE元件菲涅尔传播
recFourier              % 迭代傅里叶计算重构
recFresnel              % 迭代菲涅尔计算重构
repImage                % 图像重复拼接
savePhase               % 保存相位图
stepPhase               % 相位分阶函数
```

## 部署步骤
- OpenCV 版本 3.4.12
- 需要开发者自行配置开发环境

## Note
- 所有程序围绕 CComplexMat 类展开

## 协议
- GNU GPLv3