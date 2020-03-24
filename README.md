## 结对编程项目 - 求解交点数目

### Developer

[@Lebway](https://github.com/Lebway)

[@trrrrht](https://github.com/trrrrht)

### 描述

一个带有GUI的几何图像求解软件，支持4种几何图像(射线、线段、直线、圆)。

功能有：
- 使用QT实现GUI界面，使用QCustome进行图像绘制。
- 支持文件输入，手动输入，指定图形删除，画图等。
- 实现异常检测，共有11种异常类型，详见[errorhandler.h](https://github.com/Lebway/IntersectPairWork/blob/master/src/errorhandler.h)


## 使用方法

运行`bin`目录下的intersect.exe即可

**命令行参数**：
使用以下参数进行文件的输入输出：

- `-i <path to input file>`    从`input file`输入
- `-o <path to output file>` 在`output file`输出

### GUI程序

GUI的代码仓库在`GUI`目录下，直接运行`exe`文件即可。

### 测试

单元测试在`test`目录下。