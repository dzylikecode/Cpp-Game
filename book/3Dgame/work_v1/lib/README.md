# 3D

## main process

### ver1

#### frame

- local coordinate
- world coordinate
- camera coordinate
- perspective projection
- screen coordinate

- local coordinate

我觉得不需要储存模型, 而只要一个 local, 模型采用从外部引用的办法, local 是会改变模型的,
如果需要恢复模型, 则重新导入即可.

## function log

mobject 添加 getWorldPosition(Vector3) 方法, 返回世界坐标
getLocalPosition(Vector3) 方法, 返回本地坐标
