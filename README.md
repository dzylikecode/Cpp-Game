- [SDL](#sdl)
  - [configuration](#configuration)
  - [卸载](#卸载)
  - [NOTES](#notes)
  - [test](#test)
  - [Wiki](#wiki)
  - [final](#final)

# SDL

## configuration

参考: [配置教程](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php)

```bash
$ sudo apt-get install libsdl2-dev
$ sudo apt-get install libsdl2-image-dev
$ sudo apt-get install libsdl2-ttf-dev
$ sudo apt-get install libsdl2-mixer-dev
```

参考: [新版 SDL2](https://wiki.libsdl.org/Installation)

发现不会安装扩展, 于是

## 卸载

```bash
$ sudo apt-get --purge remove libsdl2-dev
$ sudo apt-get --purge remove libsdl2-image-dev
$ sudo apt-get --purge remove libsdl2-ttf-dev
$ sudo apt-get --purge remove libsdl2-mixer-dev
```

只需要执行第一句就可以了, 其他的都会自动删除

## NOTES

Lazy foo 教程中 `#include <SDL.h>` 应该改为 `#include <SDL2/SDL.h>`

## test

download [hello_SDL](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/01_hello_SDL.zip)
and then execute it

## Wiki

[all](https://wiki.libsdl.org/)

[API](https://wiki.libsdl.org/APIByCategory)

## final

I give up the branch, because I can't run the program 04 and 17 well.

不过, 我还是像学习一下教程, 教程里面有些东西是与平台, 与实现方式无关的

我解决了这个问题: 增加了编译选项

```shell
$ gcc `sdl2-config --cflags --libs` hello_SDL.c -o hello_SDL
```

so I can run it. haha
