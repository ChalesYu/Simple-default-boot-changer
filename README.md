# Simple-default-boot-changer
一个基于win32 API实现的系统托盘程序

it rely on clover bootloader change default boot OS

类似于bootcamp的功能...
但原理是替换config.plist里面的内容

在我的asus s400ca上同时安装了hackintosh和windows

在硬盘上除了EFI分区外再分一个200MB以上的FAT32分区 （为了windows能够访问这个分区）

将配置好的clover文件夹放入  \EFI  （为了能方便修改clover文件夹）

我的是F盘，对应路径

在/resource/config.h 里修改为你的路径


在 VS2015上编译通过
在其他版本的VS上需建一个C++空项目，把文件加入项目(详见 HowToUse.md)
 
 以上
 
 祝好

Change Log
----------------

  -用新方法替换文件内容，使替换更加快速

  -添加 备份plist文件为config_backuped.plist
  
  -直接在config.plist内搜索名称进行替换 摆脱对edit文件夹的依赖 具体见config.h






 




