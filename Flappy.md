# Flappy

## OpenGL

*Open Graphics Library*开放式图形库是用于渲染2D、3D矢量图形的跨语言、跨平台的应用程序编程接口（API）。而另一种程序接口系统是仅用于Microsoft Windows上的Direct3D。OpenGL常用于CAD、虚拟现实、科学可视化程序和电子游戏开发。

2006年7月，OpenGL架构评审委员会投票决定将OpenGL API标准的控制权交给Khronos Group。

科纳斯组织（Khronos Group）是一个由成员资助的，专注于制定开放标准（Open standard）的行业协会，重点制定免费的API，使在各种平台和设备上创作或播放的多媒体可以得到硬件加速

## OpenGL ES

*OpenGL for Embedded Systems*是三维图形应用程序接口OpenGL的子集，针对手机、PDA和游戏主机等嵌入式设备而设计。

OpenGL ES是从OpenGL裁剪定制而来的，去除了glBegin/glEnd，四边形（GL_QUADS）、多边形（GL_POLYGONS）等复杂图元等许多非绝对必要的特性。

> 以上摘录自维基百科

学习OpenGL相关内容直接涵盖了OpenGL ES，所以只要学OpenGL的API即可，OpenGL优质学习网站：<https://learnopengl-cn.github.io/>

## Flappy bird小游戏

实现的最终效果

![](readme/flappy.gif)

整体关键类类图

![](readme/flappy_class.png)

### 引用的三方库

glm库，GLM是Open**GL** **M**athematics的缩写，它是一个**只有头文件的**库，也就是说我们只需包含对应的头文件就行了，不用链接和编译。利用glm初始化矩阵和矩阵的相关运算

stb_image.h 是Sean Barrett的一个非常流行的单头文件图像加载库，它能够加载大部分流行的文件格式。利用stb_image来加载png和jpg图片。

