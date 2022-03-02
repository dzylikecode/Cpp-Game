# freak out

## task

控制 paddle, 调整 ball 的方向, 撞击砖块

## analyze

1. 键盘控制 paddle, 左右移动
2. ball 会自行移动, 通过物理碰撞, 撞击砖块

## process

通过迭代的方案来实现

1. 一个可以移动的 paddle
2. 添加帧率显示
3. 添加一个运动的 ball
4. 添加 ball 与 paddle 的碰撞

发现需要想清楚, 然后再来实现. 框架不搭好就非常失败. 比如在写 collision 的时候,
除了 ball 与 paddle 需要检测碰撞, 还需要检测 ball 与 brick 需要检测碰撞,
这部分的代码是可以复用的, 如果采用继承的话, 就非常好实现.

我发现一个更妙的事实, 按照刚才的想法, 不会动的 paddle 就是一个 block
