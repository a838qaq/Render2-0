# 一个简单的光线追踪渲染器
不依赖第三方库，输出图片为.ppm格式
## 运行程序
切换到当前目录下，输入
```cmd
mkdir build
cd build
cmake ..
make
./Render <参数>
```
<参数>为每像素采样次数，效果图为采样10000次时生成的图像。建议输入10--100之间的数字以在画质和渲染时间中取得平衡，缺省值为10
## 效果
![](photo.png)
![](photonice2.png)
## 模型
### 通过JSON文件配置模型
> 该功能并未完全实现，json解析器已经完成，即将整合进入渲染器中
>
目前只支持渲染球体
> 以后会支持立方体，.obj模型的渲染
## 加速结构
无
> 预计会使用BVH
## 参考
- https://www.bilibili.com/read/cv8996679
- https://forum.taichi-lang.cn/t/homework-0/756
- https://www.bilibili.com/video/BV1N8411h7hK/
