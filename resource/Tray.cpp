/*
chuck Yu

Simple default boot changer

win和mac切换默认启动
it rely on clover bootloader change default boot OS
原理是替换config.plist


*/

#include <windows.h>
 #include "resource.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "stdio.h"
#include <stdlib.h>
#include <sstream> 

//#include "config.h"

#include "lib.h"
bool clmm::show_detail = false;  // true -显示详细更改过程  false -隐藏详细....


using namespace std;

    #define WM_TRAY (WM_USER + 100)
    #define WM_TASKBAR_CREATED RegisterWindowMessage(TEXT("TaskbarCreated"))

    #define APP_NAME    TEXT("托盘程序")
    #define APP_TIP     TEXT("Win32 API 实现系统托盘程序")

    NOTIFYICONDATA nid;     //托盘属性
    HMENU hMenu;            //托盘菜单
	void cw(clmm a, int x);  //change to win
	void cm(clmm a, int x);	// change to mac
	void  check_err(int e1, int e2);	// check error
	

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int news = 0; int def = 1; static int a = 9;static int now;
clmm o(wconfig_loc, mconfig_loc, config_destination, a);
    //实例化托盘
    void InitTray(HINSTANCE hInstance, HWND hWnd)
    {
        nid.cbSize = sizeof(NOTIFYICONDATA);
        nid.hWnd = hWnd;
        nid.uID = IDI_TRAY;
        nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
        nid.uCallbackMessage = WM_TRAY;
        nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRAY));
        lstrcpy(nid.szTip,"启动管理程序"); 

        hMenu = CreatePopupMenu();//生成托盘菜单
        //为托盘菜单添加两个选项
        AppendMenu(hMenu, MF_STRING, ID_SHOW, TEXT("提示"));
		AppendMenu(hMenu, MF_STRING, ID_SHOW3, TEXT("默认启动win"));
		AppendMenu(hMenu, MF_STRING, ID_SHOW4, TEXT("默认启动mac"));
	//	AppendMenu(hMenu, MF_STRING, ID_SHOW5, TEXT("重新启动"));
         AppendMenu(hMenu, MF_STRING, ID_SHOW2, TEXT("关于"));
        AppendMenu(hMenu, MF_STRING, ID_EXIT, TEXT("退出"));

        Shell_NotifyIcon(NIM_ADD, &nid);
    }

    //演示托盘气泡提醒
    void ShowTrayMsg()
    {
        lstrcpy(nid.szInfoTitle, "初始化成功！");
        lstrcpy(nid.szInfo, TEXT("启动管理程序"));
        nid.uTimeout = 1000;
        Shell_NotifyIcon(NIM_MODIFY, &nid);
    }
	//
	void ShowTrayMsgshow(int n)

	{
		if(n==2) lstrcpy(nid.szInfoTitle, "在开机(或重启)后Macintosh自动启动");
		else if(n==1)	lstrcpy(nid.szInfoTitle, "在开机(或重启)后Windows自动启动");
		else lstrcpy(nid.szInfoTitle, "未知默认启动的系统");
		lstrcpy(nid.szInfo, TEXT("启动管理程序"));
		nid.uTimeout = 1000;
		Shell_NotifyIcon(NIM_MODIFY, &nid);
	}

    

    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/,
        LPSTR /*lpCmdLine*/, int iCmdShow)
    {
        HWND hWnd;
        MSG msg;
        WNDCLASS wc = { 0 };
        wc.style = NULL;
        wc.hIcon = NULL;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.lpfnWndProc = WndProc;
        wc.hbrBackground = NULL;
        wc.lpszMenuName = NULL;
        wc.lpszClassName = APP_NAME;
        wc.hCursor = NULL;

        if (!RegisterClass(&wc)) return 0;

        hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, APP_NAME, APP_NAME, WS_POPUP, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
		/////////
		ofstream out;
		////
		int indust=0;
		ifstream init(indust_mode,ios_base::in);
		init >> indust;
		//err(0);
		if (indust == 1)
		{
			MessageBox(hWnd, "已启动施工模式，程序将自动退出。\n(若要结束施工，请删除indust文件)", "请注意", MB_OK);
			
			Shell_NotifyIcon(NIM_DELETE, &nid);
			PostQuitMessage(0);
			exit(0);
		}
		////
		ifstream file(stat_loc, ios_base::in);
		if (!file) {
		log( "Unable to open file,Creat it");
			//       exit(1); // terminate with error
			out.open("F:\\EFI\\CLOVER\\stat", ios_base::out);
			if (!out) {  MessageBox(hWnd,"Unable to open out", "错误", MB_OK);	}
			out << def;
			news = 1;
		}
		if (!news)
		{
			file >> a;
			LPTSTR szBuffer = new TCHAR[50];
			wsprintf(szBuffer,"%d",a);
		//	MessageBox(hWnd, szBuffer ,"当前系统值", MB_OK);
		}
		//file <<str<<endl;
		file.close();
		out.close();
	//	ui(a);


		////////
		//MessageBox(hWnd,"初始化成功","提示", MB_OK);
		if (clmm::show_detail) {
			ShowTrayMsg();
		}
		ShowWindow(hWnd, iCmdShow);
        UpdateWindow(hWnd);

		now = a;
        InitTray(hInstance, hWnd);          //实例化托盘
       // SetTimer(hWnd, 3, 1000, NULL);      //定时发消息，演示气泡提示功能
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return msg.wParam;
    }

	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_TRAY:
			switch (lParam)
			{
			case WM_RBUTTONDOWN:
			{
				//获取鼠标坐标
				POINT pt; GetCursorPos(&pt);

				//解决在菜单外单击左键菜单不消失的问题
				SetForegroundWindow(hWnd);

				//使菜单某项变灰
				//EnableMenuItem(hMenu, ID_SHOW, MF_GRAYED);

				//显示并获取选中的菜单
				int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD, pt.x, pt.y, NULL, hWnd, NULL);
				if (cmd == ID_SHOW)
					//	MessageBox(hWnd, APP_TIP, APP_NAME, MB_OK);
					MessageBox(hWnd, "test", "S", MB_OKCANCEL);
				if (cmd == ID_EXIT)
					PostMessage(hWnd, WM_DESTROY, NULL, NULL);
				if (cmd == ID_SHOW2)
					MessageBox(hWnd, "默认启动系统修改程序\n基于Win32 API实现系统托盘程序\n\t\t-Chuck.Yu", "关于", MB_OK);
				if (cmd == ID_SHOW3)
				{
				//	log("win");
					cw(o, now);
					now = 1;
				}
				if (cmd == ID_SHOW4)
				{
				//	log("mac");
					cm(o, now);
					now = 2;
				}
			}
			break;
			case WM_LBUTTONDOWN:
				//  MessageBox(hWnd, "你点击了托盘图标" ,"这是窗口界面", MB_OK);
			/*{
				int x = o.showf();
				LPTSTR szBuffer1 = new TCHAR[6];
				wsprintf(szBuffer1, "%d", x);
				MessageBox(hWnd, szBuffer1, "当前系统值", MB_OK); 
			}*/
				ShowTrayMsgshow(now);
			break;
			case WM_LBUTTONDBLCLK:
				break;
			}
			break;
		case WM_DESTROY:
			//窗口销毁时删除托盘
			Shell_NotifyIcon(NIM_DELETE, &nid);
			PostQuitMessage(0);
			break;
		case WM_TIMER:
			ShowTrayMsg();
			KillTimer(hWnd, wParam);
			break;
		}
		if (uMsg == WM_TASKBAR_CREATED)
		{
			//系统Explorer崩溃重启时，重新加载托盘
			Shell_NotifyIcon(NIM_ADD, &nid);
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	void cw(clmm a, int x)
	{
		a.xiefile(1);
		//
		a.delf();
		a.movfw();
		check_err(err1, err2);
		if (x == 1)
		{
			log("win已经会在关机(或重启)后自动启动");
		}
		else { log("下次关机(或重启)后将自动启动win"); }
	
	}
	void cm(clmm a, int x)
	{
		a.xiefile(2);
		//
		a.delf();
		a.movfm();
		check_err(err1,err2);
		if (x == 2)
		{
			log("mac已经会在关机(或重启)后自动启动");
		}
		else { log("下次关机(或重启)后将自动启动mac"); }
		if (IDYES == MessageBox(hWnd, "是否立即重启并进入到Mac?", "注意", MB_YESNO))
		{
			if (o.show_detail) { log("reboot"); }
			o.reboot();
		}
	}
 void  check_err(int e1,int e2)
	{
		int n=0;
		if (e1 == 1) {
			if (e2 == 1) { n = 3; }
			else { n = 1; };
		}
		else 
		{
			if (e2 == 1) { n = 2; };
		}
	/*	char szBuffer[50];
		wsprintf(szBuffer, "e1=%d e2=%d  n=%d",e1,e2, n);
		MessageBox(hWnd, szBuffer, "提示", MB_OK);
		*/
		if (n != 0) {
			char errBuffer[50];
			wsprintf(errBuffer, "修改默认启动项目出现错误，未知默认启动的系统！\n 本程序将退出！  错误代码%d", n);
			//MessageBox(hWnd, szBuffer, "提示", MB_OK);
			MessageBox(hWnd, errBuffer, "错误", MB_OK);
			//delete[]szBuffer;
			Shell_NotifyIcon(NIM_DELETE, &nid);
			PostQuitMessage(0);
			exit(0);
		}
	}
