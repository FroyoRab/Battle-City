# C++练手坦克大战

> 是学C差不多转C++时候写的，为了练习面向对象，但是实际上 写的不是那么面向对象
>
> 这是很久之前的项目了，因为太久不写C++了想回来看看然后复习一下。所以文档可能跟代码有些差错。
![](https://github.com/FroyoRab/Battle-City/blob/master/image/%E5%B0%81%E9%9D%A2.jpg)

---

## 主要循环

==All_move.cpp==中是主要的游戏大循环

是通过比较标记时间与现在时间的大小来判断事件是否应该发生的。

`这个文件里只有一个函数没错……`是的没错，我自己后来看也蛮头疼的哈哈哈哈

单人和双人的貌似都写在里面了……

## 大概功能介绍

### 地图可在游戏中破坏和更改

- 可以通过开火来破坏普通墙体
- 通过激光来破坏黑墙
- 通过激光来更改水/草/沙漠地形

![](https://github.com/FroyoRab/Battle-City/blob/master/image/%E5%9C%B0%E5%9B%BE2.jpg)

### 地方电脑的A星寻路算法

- 写完就没优化过……debug掉一个内存泄露问题
- 可以调节寻路频率……
- 没有增加随机节点，但是破坏墙体可以改变路线……所以也还是有一点随机性

### 地形和子弹的互动

- 子弹经过沙地啦水啦都会有反应哈哈哈哈哈
- 👆很无聊写的，顺手加分

### 无边框 (假

- 把顶部状态栏给去掉了……
- 在主菜单增加了点击窗口直接拖拽窗口

### 菜单做了个下拉

- 就是下拉菜单，下级菜单在右边

- ![](https://github.com/FroyoRab/Battle-City/blob/master/image/%E8%8F%9C%E5%8D%95.jpg)

### 用心做了几张地图

1. ![](https://github.com/FroyoRab/Battle-City/blob/master/image/%E5%9C%B0%E5%9B%BE4.jpg)
2. ![](https://github.com/FroyoRab/Battle-City/blob/master/image/%E5%9C%B0%E5%9B%BE5.jpg)
3. ![](https://github.com/FroyoRab/Battle-City/blob/master/image/%E5%9C%B0%E5%9B%BE%E4%B8%89.jpg)



