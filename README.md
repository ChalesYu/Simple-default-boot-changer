# Simple-default-boot-changer
it rely on clover bootloader change default boot OS
类似于bootcamp的功能...
但原理是替换config.plist

在我的asus s400ca上同时安装了hackintosh和windows

在硬盘上除了EFI分区外再分一个200MB以上的FAT32分区 （为了windows能够访问这个分区）

将配置好的clover文件夹放入  \EFI  （为了能方便修改clover文件夹）

修改  / resource / lib.h 的这段 


我的是F盘，对应路径


//// 以下自定义区域 custom area 

//#define indust_mode  "F:\\EFI\\CLOVER\\indust" //判断是否施工文件，可不管 

//#define stat_loc  "F:\\EFI\\CLOVER\\stat"   //状态文件  

//#define wconfig_loc  "F:\\EFI\\CLOVER\\edit\\w.plist"  //默认win 

//#define mconfig_loc  "F:\\EFI\\CLOVER\\edit\\m.plist"   //默认mac 

//#define config_destination  "F:\\EFI\\CLOVER\\config.plist"  //clover读取位置 

/////以上自定义区域  custom area    

////////cn: 在自定义区域更改 plist 文件位置 例如 "你的路径" ，请不要忘记加上双引号 " "  

///en: change  .plist  file location @ custom area , e.g  "Your path" , please don't forget to add " " 


s400ca 在 VS2015上编译通过
 
 以上




 




