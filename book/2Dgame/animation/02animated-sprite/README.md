# [animated sprite](https://github.com/SFML/SFML/wiki/Source:-AnimatedSprite)

## 思路

也有 progress, 但是 duration 是固定的, 要想实现和上一个章节, 不同帧的 duration 不同,
可以通过多个相同的 frame 来实现, 这样就达到了不动 duration 的目的(需要取一个基本时间段
作为基地)
