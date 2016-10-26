#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream> 
#include <windows.h>
#include <string>
#include "config.h"

using namespace std;
HWND hWnd;
 static void log(const char *p) { MessageBox(hWnd, p,"提示" , MB_OK); }
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

		{//表示没有其它实例在运行.创建  

			hmutex = CreateMutex(NULL, TRUE,"clmm");
			return TRUE;
		}
		else

		{//表示已经有一个实例在运行  

			MessageBox(hWnd, "程序已经在运行了", "错误", MB_OK);

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
		// log("mac已经会在关机(或重启)后自动启动");
		// o.askreboot_m(x);
		 if (IDYES == MessageBox(hWnd, "mac已经会在关机(或重启)后自动启动\n是否立即重启并进入到Mac?", "注意", MB_YESNO))
	 {
		 if (show_detail) { log("reboot"); }
		reboot();
	 }

	 }
	 else {
		 //log("下次关机(或重启)后将自动启动mac");
		 if (IDYES == MessageBox(hWnd, "下次关机(或重启)后将自动启动mac\n是否立即重启并进入到Mac?", "注意", MB_YESNO))
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
	wsprintf(szBuffer,"无法删除文件 %s", dt);
	MessageBox(hWnd, szBuffer, "错误", MB_OK);
	
}
else
{
	//log("rm complete");
	if (show_detail) {
		LPTSTR csz = new TCHAR[1024];
		wsprintf(csz, "成功删除文件 %s", dt);
		MessageBox(hWnd, csz, "提示", MB_OK);
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
		wsprintf(szBuffer, "win : 无法移动文件%s到%s", fw,mt);
		MessageBox(hWnd, szBuffer, "错误", MB_OK);
		delete szBuffer;
		
	}
	else {
		//log("win mov complete");
		if (show_detail) {
			LPTSTR szBuffer = new TCHAR[1024];
			wsprintf(szBuffer, "win : 成功移动文件%s到%s", fw, mt);
			MessageBox(hWnd, szBuffer, "提示", MB_OK);
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
		wsprintf(szBuffer, "mac : 无法移动文件%s到%s", fw, mt);
		MessageBox(hWnd, szBuffer, "错误", MB_OK);
		
	}
	else {
		//log("mac mov complete");
		if (show_detail) {
			LPTSTR szBuffer = new TCHAR[1024];
			wsprintf(szBuffer, "mac : 成功移动文件%s到%s", fw, mt);
			MessageBox(hWnd, szBuffer, "提示", MB_OK);
		}
	}
}
////////OLD WAY end
/////
/////////////NEW WAY
////
bool config_file_change(int sys_num)
{
	fstream foutfile(dt, ios::out | ios::in);
	char ch;
	char buffer[65534];
	int i = 0, k = 0;
	if (!foutfile) {
		log("不能打开目的文件：config.plist  exiting...");
		//cout << "不能打开目的文件：test.txt" << '\n';
		exit(1);
	}

	foutfile.unsetf(ios::skipws);
	while (foutfile >> ch) {//将文件全部内容读出到buffer

		buffer[i] = ch; //cout<<buffer[i];
		i++;
	}
	foutfile.close();
	ofstream tinfile(dt);
	char *show;
	if (sys_num==2)
	{
		show = strstr_rep(buffer, win_str, mac_str);//将win_str替换为mac_str
	}
	else if (sys_num == 1)
	{
		show = strstr_rep(buffer, mac_str, win_str);//将mac_str替换为win_str
	}
	else { return FALSE; };
	tinfile << show;
	tinfile.close();
	return TRUE;

	


}
//
///find&replace function
char *strstr_rep(char *source, const char *old, const char *ne)//字符替换
{
//	cout << "replace" << '\n';
	char *org = source;
	char temp[65535];
	int old_length = (int) strlen(old);//获得将被替换的字符串的大小
//	int new_length = strlen(ne);
	int i, j, k,location = -1;
	for (i = 0; source[i] && (location == -1); ++i)//location查找将被替换的字符串的位置
	{
		for (j = i, k = 0; source[j] == old[k]; j++, k++)
		{
			if (!old[k + 1])
				location = i;
		}
	}
	if (location != -1)//开始替换
	{
		for (j = 0; j<location; j++)//先把被替换的字符串的前一部分COPY到temp
			temp[j] = source[j];
		for (i = 0; ne[i]; i++, j++)//再把替换的新字符串COPY到temp
			temp[j] = ne[i];
		for (k = location + old_length; source[k]; k++, j++)//把剩下的内容COPY到temp
			temp[j] = source[k];
		//   temp[j]=NULL;
		 for(i=0;source[i]=temp[i];i++); //把临时字符串temp复制给source
		//strcpy(source, temp);
	}

	return org;
}
///find&replace function end
///
/////////NEW WAY
private:
	const char *fm, *fw, *mt, *dt;
//static bool show_detail;
};
