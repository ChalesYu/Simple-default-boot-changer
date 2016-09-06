/*
chuck Yu

Simple default boot changer

win��mac�л�Ĭ������
it rely on clover bootloader change default boot OS
ԭ�����滻config.plist


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
bool clmm::show_detail = false;  // true -��ʾ��ϸ���Ĺ���  false -������ϸ....


using namespace std;

    #define WM_TRAY (WM_USER + 100)
    #define WM_TASKBAR_CREATED RegisterWindowMessage(TEXT("TaskbarCreated"))

    #define APP_NAME    TEXT("���̳���")
    #define APP_TIP     TEXT("Win32 API ʵ��ϵͳ���̳���")

    NOTIFYICONDATA nid;     //��������
    HMENU hMenu;            //���̲˵�
	void cw(clmm a, int x);  //change to win
	void cm(clmm a, int x);	// change to mac
	void  check_err(int e1, int e2);	// �ж���;���ִ���
	

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int news = 0; 
const int reset_OS_num = 1; //incase if don't have (or not read) stat number.  GET RESET
static int Default_OS_num = 9;  //if had read stat.  This is a temp
static int Now_OS_num;
clmm o(wconfig_loc, mconfig_loc, config_destination, config_backup_destination, Default_OS_num);

//ʵ��������
    void InitTray(HINSTANCE hInstance, HWND hWnd)
    {
        nid.cbSize = sizeof(NOTIFYICONDATA);
        nid.hWnd = hWnd;
        nid.uID = IDI_TRAY;
        nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
        nid.uCallbackMessage = WM_TRAY;
        nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRAY));
        lstrcpy(nid.szTip,"�����������"); 

        hMenu = CreatePopupMenu();//�������̲˵�
        //Ϊ���̲˵����ѡ��
        AppendMenu(hMenu, MF_STRING, ID_SHOW, TEXT("��ʾ"));
		AppendMenu(hMenu, MF_STRING, ID_SHOW5, TEXT("���������� OS X"));
		AppendMenu(hMenu, MF_STRING, ID_SHOW3, TEXT("Ĭ������win"));
		AppendMenu(hMenu, MF_STRING, ID_SHOW4, TEXT("Ĭ������mac"));
         AppendMenu(hMenu, MF_STRING, ID_SHOW2, TEXT("����"));
        AppendMenu(hMenu, MF_STRING, ID_EXIT, TEXT("�˳�"));

        Shell_NotifyIcon(NIM_ADD, &nid);
    }

    //��ʾ������������
    void ShowTrayMsg()
    {
        lstrcpy(nid.szInfoTitle, "��ʼ���ɹ���");
        lstrcpy(nid.szInfo, TEXT("�����������"));
        nid.uTimeout = 1000;
        Shell_NotifyIcon(NIM_MODIFY, &nid);
    }
	//
	void ShowTrayMsgshow(int n)

	{
		if(n==2) lstrcpy(nid.szInfoTitle, "�ڿ���(������)��Macintosh�Զ�����");
		else if(n==1)	lstrcpy(nid.szInfoTitle, "�ڿ���(������)��Windows�Զ�����");
		else lstrcpy(nid.szInfoTitle, "δ֪Ĭ��������ϵͳ");
		lstrcpy(nid.szInfo, TEXT("�����������"));
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
		///////////��ʼ��...
		ofstream out_default_file;
		////
		int indust=0;
		ifstream init(indust_mode,ios_base::in);
		init >> indust;
		//
		//err(�Ƿ���ʩ��ģʽ);
		if (indust == 1)
		{
			MessageBox(hWnd, "������ʩ��ģʽ�������Զ��˳���\n(��Ҫ����ʩ������ɾ��indust�ļ�)", "��ע��", MB_OK);
			
			Shell_NotifyIcon(NIM_DELETE, &nid);
			PostQuitMessage(0);
			exit(0);
		}
		////

		///  backup config.plist as config_backuped.plist
		if (CopyFile(config_destination, config_backup_destination, true)) {
			lstrcpy(nid.szInfoTitle, "�ѱ���config.plistΪconfig_backuped.plist");
			lstrcpy(nid.szInfo, TEXT("�����������"));
			nid.uTimeout = 1000;
			Shell_NotifyIcon(NIM_MODIFY, &nid);
		
		}
		else
		{
			if (o.show_detail) {
				lstrcpy(nid.szInfoTitle, "config�Ѵ���");
				lstrcpy(nid.szInfo, TEXT("�����������"));
				nid.uTimeout = 1000;
				Shell_NotifyIcon(NIM_MODIFY, &nid);
			}
		};
		// hmm... end backup config  now safely

		/////
		/// file== stat  
		ifstream file(stat_loc, ios_base::in);
		if (!file) {
		log( "Unable to open file,Creat it");
			 // terminate with error
			out_default_file.open("F:\\EFI\\CLOVER\\stat", ios_base::out);
			if (!out_default_file) {  MessageBox(hWnd,"Unable to open out and set out_default_file with '1'", "����", MB_OK);	}
			out_default_file << reset_OS_num;
			news = 1;
		}
		if (!news)
		{
			file >> Default_OS_num; //stat_loc
			LPTSTR szBuffer = new TCHAR[50];
			wsprintf(szBuffer,"%d",Default_OS_num);
		//	MessageBox(hWnd, szBuffer ,"��ǰϵͳֵ", MB_OK);
		}
		//file <<str<<endl;
		file.close();
		out_default_file.close();
	//	ui(a);

		////////
	
		if (clmm::show_detail) {
			ShowTrayMsg();
		}
		ShowWindow(hWnd, iCmdShow);
        UpdateWindow(hWnd);
		Now_OS_num = Default_OS_num; 
  InitTray(hInstance, hWnd);          //ʵ��������
		/*����Ҫ���õ�ѡ��*/
		if (Now_OS_num == 2) {
			EnableMenuItem(hMenu, ID_SHOW4, MF_GRAYED);
			EnableMenuItem(hMenu, ID_SHOW3, MF_ENABLED);
		}//lstrcpy(nid.szInfoTitle, "�ڿ���(������)��Macintosh�Զ�����");
		else if (Now_OS_num == 1) {
			EnableMenuItem(hMenu, ID_SHOW3, MF_GRAYED);
			EnableMenuItem(hMenu, ID_SHOW4, MF_ENABLED);
		}	//lstrcpy(nid.szInfoTitle, "�ڿ���(������)��Windows�Զ�����");
		else
		{
			//////.....
		};
		/*����Ҫ���õ�ѡ��*/
	
		
		//MessageBox(hWnd,"��ʼ���ɹ�","��ʾ", MB_OK);
      
       // SetTimer(hWnd, 3, 1000, NULL);      //��ʱ����Ϣ����ʾ������ʾ����
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
				//��ȡ�������
				POINT pt; GetCursorPos(&pt);

				//����ڲ˵��ⵥ������˵�����ʧ������
				SetForegroundWindow(hWnd);

				//ʹ�˵�ĳ����
				EnableMenuItem(hMenu, ID_SHOW5, MF_GRAYED);
				
				//��ʾ����ȡѡ�еĲ˵�
				int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD, pt.x, pt.y, NULL, hWnd, NULL);
				if (cmd == ID_SHOW)
					//	MessageBox(hWnd, APP_TIP, APP_NAME, MB_OK);
					MessageBox(hWnd, "����д......", "��ʾ", MB_OK);     //��ʾ
				if (cmd == ID_EXIT)
					PostMessage(hWnd, WM_DESTROY, NULL, NULL);
				if (cmd == ID_SHOW2)
					MessageBox(hWnd, "Ĭ������ϵͳ�޸ĳ���\n����Win32 APIʵ��ϵͳ���̳���\n\t\t-Chales.Yu", "����", MB_OK);
				if (cmd == ID_SHOW3)
				{
				//	log("win");
					cw(o, Now_OS_num);
					Now_OS_num = 1;
					EnableMenuItem(hMenu, ID_SHOW3, MF_GRAYED);
					EnableMenuItem(hMenu, ID_SHOW4, MF_ENABLED);
				}
				if (cmd == ID_SHOW4)
				{
				//	log("mac");
					cm(o, Now_OS_num);
					Now_OS_num = 2;
					EnableMenuItem(hMenu, ID_SHOW4, MF_GRAYED);
					EnableMenuItem(hMenu, ID_SHOW3, MF_ENABLED);
				}
				////////////////////////////////////////
		/*		if (cmd == ID_SHOW5) // ������OS X
				{
					o.xiefile(2);
					//
					o.delf();
					o.movfm();
					o.reboot();
					//	log("now restart mac");

				//	cm(o, now);
				//	now = 2;
				}
				*/
				///////////////////////////////////////////
			}
			break;
			case WM_LBUTTONDOWN:
				//  MessageBox(hWnd, "����������ͼ��" ,"���Ǵ��ڽ���", MB_OK);
			/*{
				int x = o.showf();
				LPTSTR szBuffer1 = new TCHAR[6];
				wsprintf(szBuffer1, "%d", x);
				MessageBox(hWnd, szBuffer1, "��ǰϵͳֵ", MB_OK); 
			}*/
				ShowTrayMsgshow(Now_OS_num);
			break;
			case WM_LBUTTONDBLCLK:
				break;
			}
			break;
		case WM_DESTROY:
			//��������ʱɾ������
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
			//ϵͳExplorer��������ʱ�����¼�������
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
			log("win�Ѿ����ڹػ�(������)���Զ�����");
		}
		else { log("�´ιػ�(������)���Զ�����win"); }
	
	}
	void cm(clmm a, int x)
	{
		a.xiefile(2);
		//
		a.delf();
		a.movfm();
		check_err(err1,err2);


		o.askreboot_m(x);
 

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
		MessageBox(hWnd, szBuffer, "��ʾ", MB_OK);
		*/
		if (n != 0) {
			char errBuffer[50];
			wsprintf(errBuffer, "�޸�Ĭ��������Ŀ���ִ���δ֪Ĭ��������ϵͳ��\n �������˳���  �������%d", n);
			//MessageBox(hWnd, szBuffer, "��ʾ", MB_OK);
			MessageBox(hWnd, errBuffer, "����", MB_OK);
			//delete[]szBuffer;
			Shell_NotifyIcon(NIM_DELETE, &nid);
			PostQuitMessage(0);
			exit(0);
		}
	}
