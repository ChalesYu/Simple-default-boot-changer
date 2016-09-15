#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "lib.h"
///////   Custom Area
#define wconfig_loc  "F:\\EFI\\CLOVER\\edit\\w.plist"
#define mconfig_loc  "F:\\EFI\\CLOVER\\edit\\m.plist"
#define config_destination  "F:\\EFI\\CLOVER\\config.plist"
///change you're configed file location @ here, e.g  "Your path" , please don't forget " "
///stat file path is in "lib.h" ,  please change it to fit your PC.
////////   Custom Area
using namespace std;
void cw(clmm a,int x);
void cm(clmm a,int x);
void ui_help (bool k);
void ui(const  int n);
void shutdown()
{ log ("shutdown");
       system("shutdown -s -t 0");
}
int reboot(int n){
   system("cls");
   getchar();
    log("\n\t  您确定现在重启吗？   \n");
    cout <<"\t\t 重启后将自动启动 ";
        (n==2)?   cout <<"Macintosh"<<endl : cout <<"windows"<<endl;
     log("\n\n\t 确认重启 -- 输入 y 后 按enter键  \n\n\t 取消 -- 按enter键  \n");
    char p;
   p=getchar();
    if(p=='y'){
      system("shutdown -r -t 0");
      }
      system("cls");
    return 0;}
int main()
{ system ("color F0");
/*
 0 = 黑色       8 = 灰色
    1 = 蓝色       9 = 淡蓝色
    2 = 绿色       A = 淡绿色
    3 = 湖蓝色     B = 淡浅绿色
    4 = 红色       C = 淡红色
    5 = 紫色       D = 淡紫色
    6 = 黄色       E = 淡黄色
    7 = 白色       F = 亮白色
    */
    int news=0;int def=1; int a=9;//ignore a
 /**********read&check*********/
    log("         NOT CopyRight     by Chuck.Yu");
    ofstream out;
    ifstream file("F:\\EFI\\CLOVER\\stat",ios_base::in);
    if(!file){
  cout << "Unable to open file,Creat it"<<endl;
                //       exit(1); // terminate with error
            out.open("F:\\EFI\\CLOVER\\stat",ios_base::out);
            if(!out) { cout << "Unable to open out"<<endl; }
            out<<def;
                news=1;
            }
            if (!news)
                {

                file>>a;
                    cout <<a<<endl;
                }
            else{
                    log("default set to 1");
            }
  //file <<str<<endl;
    file.close();
     out.close();
     ui(a);
     //////change file loc @ here
    clmm o(wconfig_loc,mconfig_loc,config_destination,a);
     /////   ( win config file location , mac config file location , bootloader read config location ,a)
/**********read&init_over*********/
log("\t初始化成功");
log("\n按 enter键 进入主界面");
getchar ();system("cls");
/**********************start************************/
/*  a is stat    def =1 */
int now=a;
if(news)
{
    ui_help (true);

}
else{
ui(o.showf());
ui_help (false);

}
  char  menu;
    cout<<"\n\t\t\t请输入选项：";
    cin>>menu;

while (1) {

    switch (menu) {
    case 'w':
   log("win");
   cw(o,now);
   now=1;
      break;
    case 'm':
       log("mac");
       cm(o,now);
        now=2;
      break;
       case 'r':
       log("restart");
     reboot(now);
      break;
        case 'g':
       log("shutdown");
     shutdown();
      break;
    case 'q':
      log("exit");
      o.q(now);
      exit(0);
      break;
    default:
  {system("cls");
          cout <<"\n\n\n\t\t输入错误,按 enter键 返回重新输入"<<endl;

     // defi(o);
     getchar();getchar();

system("cls");
     }
break ;
    }
   menu ='\0';
ui(o.showf());
ui_help (false);
cout<<"\n\t\t\t请输入选项：";
 cin>>menu;
  }

/*   /////    xiu gai qi dong
int s;
log ("please set");
cin>>s;
while (!o.judge(s))
{log("in error,rein");
cin>>s;
if (s==0) break;
}
if(s!=0)
o.xiefile(s); //写文件
else {log("file not change");};
cout <<o.showf()<<endl;
*/

return 0;
}
void cw(clmm a,int x)
{
    system ("cls");
    a.xiefile(1);
    //
    a.delf();
    a.movfw();
  if(x==1)
     {
         log("win已经会在关机(或重启)后自动启动");
     }
     else{ log("下次关机(或重启)后将自动启动win");}
    log("\n\t\t按 enter键 返回");
    getchar();getchar(); system ("cls");

}
void cm(clmm a,int x)
{system ("cls");
    a.xiefile(2);
    //
     a.delf();
     a.movfm();
     if(x==2)
     {
         log("mac已经会在关机(或重启)后自动启动");
     }
     else{ log("下次关机(或重启)后将自动启动mac");}

        log("\n\t\t按 enter键 返回");
    getchar(); getchar(); system ("cls");
}

void ui_help (bool k) // is new file ?
{
    if(k)
    {
      //   logui ();
cout<<"配置丢失，请重新设置默认启动的系统"<<endl;
cout<<"\n\t 输入w - 默认启动win \n\t 输入m - 默认启动mac\n\n\t   输入选项后按 enter键"<<endl;
  //  log ();
    }
    else
    {
         log ("\n\t 输入w - 默认启动win \n\t 输入m - 默认启动mac \n\t 输入r - 重启 \n\t 输入q - 退出程序\n\n\t   输入选项后按 enter键");

    }

}
void ui(const  int n)
{
log("\n\tOS 启动管理工具"); cout<<"\n\t\t ";
if( n==1)
    {
        log("Windows 将会在关机(或重启)后自动启动");
    }
else if(n==2) { //cout<<"now system:  ";
        log("Macintosh 将会在关机(或重启)后自动启动");}
    else if(n==9)
        { //cout<<"now system:  ";
            log("notset 原因：初始化");
        }
        else if(n==0)
        { //cout<<"now system:  ";
            log("notset");
        }
        else
        {  //  cout<<"now system:  ";
            log("unknow");
        }
}
