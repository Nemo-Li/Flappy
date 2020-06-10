# OpenGL ES 3.0 flappy bird

参考的[Flappy的桌面版本](https://github.com/TheCherno/Flappy)

实现了Android移动端的小游戏。使用了OpenGL ES 3.0，surfaceView的渲染通过jni调用到native的OpenGL，图片解析使用stb_image，矩阵运算使用glm。

同时支持手机端和Tv端，设备需要支持OpenGL3.0

![](readme/flappy.gif)

