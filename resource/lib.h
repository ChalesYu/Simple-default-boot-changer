#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include <string.h>
#include "config.h"

using namespace std;
HWND hWnd;
 static void log(const char *p) { MessageBox(hWnd, p,"提示" , MB_OK); }
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
if (!w) { log("无法写stat文件\n 请检查路径是否正确! \n 状态值将会丢失..."); err1 = 1; }
int gai=0;
gai=stat;
w<<gai;
w.close();
//log("writed");
if (show_detail&&err1!=1) {
	char szBuffer[50];
	wsprintf(szBuffer, "%d已写入stat状态文件在 %s", gai, stat_loc);
	MessageBox(hWnd, szBuffer, "提示", MB_OK);
		}
}
	void shutdown()
	{
		if (show_detail) {
			MessageBox(hWnd, "windows将立即关机！", "警告", MB_OK);

			//log("shutdown");
		}
		system("shutdown -s -t 0");
	}
	void reboot()
	{
		if (show_detail) {
			MessageBox(hWnd, "windows将立即重启！", "警告", MB_OK);

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
 clmm(const char *fromw,const char *fromm,const char *to,int orgin):core(orgin){fw=fromw;fm=fromm;t=to;a=to;}

/////
void  delf ()
{
if( remove(a))
{err2 = 1;
	//printf("Could not delete the file %s \n",a);
	LPTSTR szBuffer= new TCHAR[1024];
	wsprintf(szBuffer,"无法删除文件 %s", a);
	MessageBox(hWnd, szBuffer, "错误", MB_OK);
	
}
else
{
	//log("rm complete");
	if (show_detail) {
		LPTSTR csz = new TCHAR[1024];
		wsprintf(csz, "成功删除文件 %s", a);
		MessageBox(hWnd, csz, "提示", MB_OK);
	}
	}
}
/////
void  movfw ()
{
	if (!CopyFile(fw, t, false))
	{//printf("Could not move the file %s \n",fw);
		err2 = 1;
		LPTSTR szBuffer = new TCHAR[1024];
		wsprintf(szBuffer, "win : 无法移动文件%s到%s", fw,t);
		MessageBox(hWnd, szBuffer, "错误", MB_OK);
		delete szBuffer;
		
	}
	else {
		//log("win mov complete");
		if (show_detail) {
			LPTSTR szBuffer = new TCHAR[1024];
			wsprintf(szBuffer, "win : 成功移动文件%s到%s", fw, t);
			MessageBox(hWnd, szBuffer, "提示", MB_OK);
			delete szBuffer;
		}
	}
}
/////
void  movfm ()
{
	if (!CopyFile(fm, t, false))
	{err2 = 1;
		//printf("Could not move the file %s \n", fm);
		LPTSTR szBuffer = new TCHAR[1024];
		wsprintf(szBuffer, "mac : 无法移动文件%s到%s", fw, t);
		MessageBox(hWnd, szBuffer, "错误", MB_OK);
		
	}
	else {
		//log("mac mov complete");
		if (show_detail) {
			LPTSTR szBuffer = new TCHAR[1024];
			wsprintf(szBuffer, "mac : 成功移动文件%s到%s", fw, t);
			MessageBox(hWnd, szBuffer, "提示", MB_OK);
		}
	}
}
/////
private:
const char *fm,*fw,*t,*a;
//static bool show_detail;
};
