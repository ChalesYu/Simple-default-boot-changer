#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream> 
#include <windows.h>
#include <string.h>
#include "config.h"
#include "DblNode.h"

using namespace std;
HWND hWnd;
 static void log(const char *p) { MessageBox(hWnd, p,"��ʾ" , MB_OK); }
 static int err1=0, err2=0;
class core {
public :
    core (int rec ): org(rec)  { }
	bool start( ) //check if it opened
	{
		HANDLE hmutex;
	//	CString= strClassName = "clmm";
		hmutex=OpenMutex(MUTEX_ALL_ACCESS, FALSE,"clmm");
		if (hmutex == NULL)

		{//��ʾû������ʵ��������.����  

			hmutex = CreateMutex(NULL, TRUE,"clmm");
			return TRUE;
		}
		else

		{//��ʾ�Ѿ���һ��ʵ��������  

			MessageBox(hWnd, "�����Ѿ���������", "����", MB_OK);

			return FALSE;

		}
	}
int  showf(){
    /*********debug********/
    int b;
    ifstream d(stat_loc);
    d>>b;
    //cout <<b<<endl;
    d.close();
    return b;
            }
    void xiefile(int stat)
{
/**********write*********/
ofstream w(stat_loc);
if (!w) { log("�޷�дstat�ļ�\n ����·���Ƿ���ȷ! \n ״ֵ̬���ᶪʧ..."); err1 = 1; }
int gai=0;
gai=stat;
w<<gai;
w.close();
//log("writed");
if (show_detail&&err1!=1) {
	char szBuffer[50];
	wsprintf(szBuffer, "%d��д��stat״̬�ļ��� %s", gai, stat_loc);
	MessageBox(hWnd, szBuffer, "��ʾ", MB_OK);
		}
}
	void shutdown()
	{
		if (show_detail) {
			MessageBox(hWnd, "windows�������ػ���", "����", MB_OK);

			//log("shutdown");
		}
		system("shutdown -s -t 0");
	}
	void reboot()
	{
		if (show_detail) {
			MessageBox(hWnd, "windows������������", "����", MB_OK);

			//log("reboot");
		}
		system("shutdown -r -t 0");
	}
	
	static bool show_detail;

private:

int org;


};
class clmm :public core   //clover loader manage maker
{
private:
	const char *fm, *fw, *mt, *dt;
	//static bool show_detail;
public: 
	clmm(const char *fromw, const char *fromm, const char *to, const char *backup, int orgin) :core(orgin) {
		fw = fromw; fm = fromm; dt = to; mt = to;
 //////backup config.plist
		//remove(backup);
		//CopyFile(,, false);
	//	CopyFile(to, backup, false);

		/////
 }
/////
 void askreboot_m(int now)
 {

	 if (now == 2)
	 {
		// log("mac�Ѿ����ڹػ�(������)���Զ�����");
		// o.askreboot_m(x);
		 if (IDYES == MessageBox(hWnd, "mac�Ѿ����ڹػ�(������)���Զ�����\n�Ƿ��������������뵽Mac?", "ע��", MB_YESNO))
	 {
		 if (show_detail) { log("reboot"); }
		reboot();
	 }

	 }
	 else {
		 //log("�´ιػ�(������)���Զ�����mac");
		 if (IDYES == MessageBox(hWnd, "�´ιػ�(������)���Զ�����mac\n�Ƿ��������������뵽Mac?", "ע��", MB_YESNO))
		 {
			 if (show_detail) { log("reboot"); }
			 reboot();
		 }
	 }

	
 }
 ////////OLD WAY
/////
void  delf ()
{
if( remove(dt))
{err2 = 1;
	//printf("Could not delete the file %s \n",a);
	LPTSTR szBuffer= new TCHAR[1024];
	wsprintf(szBuffer,"�޷�ɾ���ļ� %s", dt);
	MessageBox(hWnd, szBuffer, "����", MB_OK);
	
}
else
{
	//log("rm complete");
	if (show_detail) {
		LPTSTR csz = new TCHAR[1024];
		wsprintf(csz, "�ɹ�ɾ���ļ� %s", dt);
		MessageBox(hWnd, csz, "��ʾ", MB_OK);
	}
	}
}
/////
void  movfw ()
{
	if (!CopyFile(fw, mt, false))
	{//printf("Could not move the file %s \n",fw);
		err2 = 1;
		LPTSTR szBuffer = new TCHAR[1024];
		wsprintf(szBuffer, "win : �޷��ƶ��ļ�%s��%s", fw,mt);
		MessageBox(hWnd, szBuffer, "����", MB_OK);
		delete szBuffer;
		
	}
	else {
		//log("win mov complete");
		if (show_detail) {
			LPTSTR szBuffer = new TCHAR[1024];
			wsprintf(szBuffer, "win : �ɹ��ƶ��ļ�%s��%s", fw, mt);
			MessageBox(hWnd, szBuffer, "��ʾ", MB_OK);
			delete szBuffer;
		}
	}
}
/////
void  movfm ()
{
	if (!CopyFile(fm, mt, false))
	{err2 = 1;
		//printf("Could not move the file %s \n", fm);
		LPTSTR szBuffer = new TCHAR[1024];
		wsprintf(szBuffer, "mac : �޷��ƶ��ļ�%s��%s", fw, mt);
		MessageBox(hWnd, szBuffer, "����", MB_OK);
		
	}
	else {
		//log("mac mov complete");
		if (show_detail) {
			LPTSTR szBuffer = new TCHAR[1024];
			wsprintf(szBuffer, "mac : �ɹ��ƶ��ļ�%s��%s", fw, mt);
			MessageBox(hWnd, szBuffer, "��ʾ", MB_OK);
		}
	}
}
////////OLD WAY end
/////
/////////////NEW WAY updated
////
bool config_file_change(int sys_num)
{
	DblLinkList <char> d;
	d.Insert_file(1, dt);
	if (sys_num==2)
	{
	//��win_str�滻Ϊmac_str
		d.strstr_replace_once(win_str, mac_str);
	}
	else if (sys_num == 1)
	{
	//��mac_str�滻Ϊwin_str
		d.strstr_replace_once(mac_str, win_str);
	}
	else { return FALSE; };
	d.push_out_file(dt);
	d.~DblLinkList();
	return TRUE;
}
//
/////////NEW WAY

};
