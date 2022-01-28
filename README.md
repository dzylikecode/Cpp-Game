- [配置教程](#配置教程)
  - [extension](#extension)
  - [文件结构](#文件结构)
  - [构建库](#构建库)
  - [计划](#计划)
  - [新的开始](#新的开始)
    - [安装](#安装)

# [配置教程](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php)

## [extension](https://github.com/nothings/stb)

> 10-23-21 <br>
> 我不想过多配置有关环境变量的库,不愿使用 **[image 的扩展](https://www.libsdl.org/projects/SDL_image/)** 图片加载 <br>
> 根据 **_[image example](https://wiki.libsdl.org/SDL_CreateRGBSurfaceFrom)_** ，
> 我决定使用 **[stb 库](https://github.com/nothings/stb)** <br>
> 另一个 **_[image example](https://glumes.com/post/android/stb-image-introduce/)_** <br>

> 10-28-21 <br>
> 我遇到了字体加载的困难，准备重新使用 **[font 的扩展](https://www.libsdl.org/projects/SDL_ttf/)** <---- **[tutorial](https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/windows/index.php)** <br>
> 但是我参考了 SDL 与 stb 加载字体的方案:
>
> > **[sdl_stb_font](https://github.com/SnapperTT/sdl_stb_font)** <br> >> **[stb_font](https://stackoverflow.com/questions/51276586/how-to-render-text-in-directx9-with-stb-truetype)**

## 文件结构

> ~~**_`struct.km`_**~~ **_`main.km`_** 以思维导图形式描述核心结构 <br> > **_`<funtionName>.txt`_** 伪代码形式描述算法

## 构建库

> 仿照 stb 库的 **[做法](https://github.com/nothings/stb/blob/master/docs/stb_howto.txt)** ，以 **_single-file library_** 形式做些封装

## 计划

| name                                                   | position                       | date       | description |
| ------------------------------------------------------ | ------------------------------ | ---------- | ----------- |
| **[Lazyfoo 教程](https://lazyfoo.net/tutorials/SDL/)** | **[Lazyfoo](example/LazyFoo)** | 10.23.21-? | 入门教程    |

## 新的开始

采用 Windows 子系统

### 安装

```bash
$ sudo apt-get install libsdl2-dev
```
