#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include <string.h>
#include "config.h"

using namespace std;
HWND hWnd;
 static void log(const char *p) { MessageBox(hWnd, p,"��ʾ" , MB_OK); }
 static int err1=0, err2=0;
class core {
public :
    core (int rec ): org(rec)  { }
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
/////
private:
	const char *fm, *fw, *mt, *dt;
//static bool show_detail;
};
