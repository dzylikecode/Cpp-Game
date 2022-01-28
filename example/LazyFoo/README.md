- [notice](#notice)
  - [issue](#issue)
  - [变化分割](#变化分割)

# notice

> 1. Create a folder **_Build_** in currrent directory
> 2. Move each resource file to folder **_Build_** `(such as bitmap file)`
> 3. Modify some code in file \***_.cpp_** , `(such as path 02_getting_an_image_on_the_screen/hello_world.bmp -> hello_world.bmp)`

## issue

> - launch.json set **cwd** = **_current Build Folder_** , otherwise it
>   can't load bmp successfully `(`from **_07_texture_loading_and_rendering_**`)`
> - launch.json set **cwd** = **_gdb path_** , otherwise it
>   can't debug successfully `(`from **_08_geometry_rendering_**`)`

## 变化分割

以上是在 windows 平台上的,现在采用 Linux 平台
