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

### 简单的矩阵介绍

矩阵、矩阵乘法最初出现的目的就是为了解线性方程组。[参考马同学](https://www.matongxue.com/madocs/755/)

#### 单位矩阵

在OpenGL中，由于某些原因我们通常使用**4×4**的变换矩阵，而其中最重要的原因就是大部分的向量都是4分量的。

$$\left[ \begin{matrix} {\color{red} 1} & {\color{red} 0} & {\color{red} 0} & {\color{red} 0} \\ {\color{green} 0} & {\color{green} 1}  & {\color{green} 0}  & {\color{green} 0}  \\ {\color{blue} 0}  & {\color{blue} 0} & {\color{blue} 1} & {\color{blue} 0} \\ {\color{purple} 0} & {\color{purple} 0} & {\color{purple} 0} & {\color{purple} 1} \end{matrix}\right] $$ $$\cdot$$ $$\left[\begin{matrix} 1 \\ 2 \\ 3 \\ 4 \end{matrix}\right]$$ = $$\left[ \begin{matrix} {\color{red} 1} \cdot 1 \\ {\color{green} 1} \cdot 2 \\ {\color{blue} 1} \cdot 3 \\ {\color{purple} 1} \cdot 4 \end{matrix} \right]$$ = $$\left[ \begin{matrix} 1 \\ 2 \\ 3 \\ 4  \end{matrix} \right]$$ 

#### 缩放

$$\left[ \begin{matrix} {\color{red} {S_1}} & {\color{red} 0} & {\color{red} 0} & {\color{red} 0} \\ {\color{green} 0} & {\color{green} {S_2}}  & {\color{green} 0}  & {\color{green} 0}  \\ {\color{blue} 0}  & {\color{blue} 0} & {\color{blue} {S_3}} & {\color{blue} 0} \\ {\color{purple} 0} & {\color{purple} 0} & {\color{purple} 0} & {\color{purple} 1} \end{matrix}\right] $$ $$\cdot$$ $$\left( \begin{matrix}  x \\ y \\ z \\ 1 \end{matrix} \right)$$ = $$\left( \begin{matrix} \color{red}{S_1} \cdot x \\ \color{green} {S_2} \cdot y \\ \color{blue}{S_3} \cdot z \\ 1  \end{matrix}\right)$$

#### 位移

$$\left[ \begin{matrix} {\color{red} 1} & {\color{red} 0} & {\color{red} 0} & {\color{red} {T_x}} \\ {\color{green} 0} & {\color{green} 1}  & {\color{green} 0}  & {\color{green} {T_y}}  \\ {\color{blue} 0}  & {\color{blue} 0} & {\color{blue} 1} & {\color{blue} {T_z}} \\ {\color{purple} 0} & {\color{purple} 0} & {\color{purple} 0} & {\color{purple} 1} \end{matrix}\right] $$ $$\cdot$$ $$ \left( \begin{matrix}  x \\ y \\ z \\ 1 \end{matrix} \right) $$ = $$\left( \begin{matrix} x + \color{red}{T_x} \\ y + \color{green} {T_y} \\  z + \color{blue}{T_z} \\ 1  \end{matrix}\right)$$



> **齐次坐标(Homogeneous Coordinates)**
>
> 向量的w分量也叫齐次坐标。想要从齐次向量得到3D向量，我们可以把x、y和z坐标分别除以w坐标。我们通常不会注意这个问题，因为w分量通常是1.0。使用齐次坐标有几点好处：它允许我们在3D向量上进行位移（如果没有w分量我们是不能位移向量的）
>
> 如果一个向量的齐次坐标是0，这个坐标就是方向向量(Direction Vector)，因为w坐标是0，这个向量就不能位移（译注：这也就是我们说的不能位移一个方向）。

#### 旋转

沿x轴旋转：

$$\left[ \begin{matrix} {\color{red} 1} & {\color{red} 0} & {\color{red} 0} & {\color{red} 0} \\ {\color{green} 0} & {\color{green} {cos\theta}}  & {\color{green} {-sin\theta}}  & {\color{green} 0}  \\ {\color{blue} 0}  & {\color{blue} {sin\theta}} & {\color{blue} {cos\theta}} & {\color{blue} 0} \\ {\color{purple} 0} & {\color{purple} 0} & {\color{purple} 0} & {\color{purple} 1} \end{matrix}\right] $$ $$\cdot$$ $$ \left( \begin{matrix}  x \\ y \\ z \\ 1 \end{matrix} \right) $$ = $$\left( \begin{matrix} x  \\ \color{green} {cos\theta} \cdot y - \color{green}{sin\theta} \cdot z  \\  \color{blue}{sin\theta} \cdot y + \color{blue}{cos\theta} \cdot z \\ 1  \end{matrix}\right)$$

这里$x$不变，只有$y,z$坐标在变化，我们得到了计算变换后的$(y', z')$坐标

$y'=\color{green} {cos\theta} \cdot y - \color{green}{sin\theta} \cdot z$

$z'= \color{blue}{sin\theta} \cdot y + \color{blue}{cos\theta} \cdot z$

$y'^2 + z'^2 = (\color{green} {cos\theta} \cdot y - \color{green}{sin\theta} \cdot z)^2 + ( \color{blue}{sin\theta} \cdot y + \color{blue}{cos\theta} \cdot z)^2$

$= y^2 + z^2$

从上面推导得到矩阵运算后$y,z$坐标的平方和不变，最终结论就是$y,z$坐标都在一个圆上，所以是绕x轴旋转，下面的矩阵变换同理可证

矩阵的变化如下图所示：

![](readme/x.gif)

沿y轴旋转：

$\left[ \begin{matrix} {\color{red} {\color{red} {cos\theta}}} & {\color{red} 0} & {\color{red} {sin\theta}}& {\color{red} 0} \\ {\color{green} 0} & {\color{green} 1} &  {\color{green} 0} & {\color{green} 0}  \\ {\color{blue} {-sin\theta}}  & {\color{blue} 0} & {\color{blue} {cos\theta}} & {\color{blue} 0} \\ {\color{purple} 0} & {\color{purple} 0} & {\color{purple} 0} & {\color{purple} 1} \end{matrix}\right] $$\cdot$ $ \left( \begin{matrix}  x \\ y \\ z \\ 1 \end{matrix} \right) $ = $\left( \begin{matrix} \color{red} {cos\theta} \cdot x + \color{red}{sin\theta} \cdot z  \\ y  \\  \color{blue}{-sin\theta} \cdot x + \color{blue}{cos\theta} \cdot z \\ 1  \end{matrix}\right)$

动图展示：

![](readme/y.gif)

沿z轴旋转：

$\left[ \begin{matrix} {\color{red} {\color{red} {cos\theta}}} & {\color{red} {-sin\theta}} & \color{red}0 & {\color{red} 0} \\ {\color{green} {sin\theta}}  & {\color{green} {cos\theta}} & {\color{green} 0}& {\color{green} 0} \\ {\color{blue} 0} &  {\color{blue} 0} & {\color{blue} 1}  & \color{blue} 0 \\ {\color{purple} 0} & {\color{purple} 0} & {\color{purple} 0} & {\color{purple} 1} \end{matrix}\right] $ $\cdot$ $ \left( \begin{matrix}  x \\ y \\ z \\ 1 \end{matrix} \right) $ = $\left( \begin{matrix} \color{red} {cos\theta} \cdot x - \color{red}{sin\theta} \cdot y  \\  \color{green}{sin\theta} \cdot x + \color{green}{cos\theta} \cdot z  \\  z  \\ 1  \end{matrix}\right)$

动图展示：

![](readme/z.gif)

#### 矩阵的组合

### 游戏实现