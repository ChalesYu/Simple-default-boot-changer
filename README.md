# Simple-default-boot-changer
it rely on clover bootloader change default boot OS
类似于bootcamp的功能...
但原理是替换config.plist

在我的asus s400ca上同时安装了hackintosh和windows

在硬盘上除了EFI分区外再分一个200MB以上的FAT32分区 （为了windows能够访问这个分区）

将配置好的clover文件夹放入  \EFI  （为了能方便修改clover文件夹）

我的是F盘，对应路径

在/resource/config.h 里修改为你的路径

s400ca 在 VS2015上编译通过
 
 以上
 
 祝好




 




