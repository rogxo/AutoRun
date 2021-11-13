#include "Main.h"
#include "AutoRun.h"

int main()
{
	//char szFilePath[] = "C:\\Users\\Administrator\\Desktop\\Temp\\WinHex.exe";
	//AutoRun::StartUpFloderAutoRun(szFilePath,"SyncShare.exe");
	AutoRun::StartUpFloderAutoRun(NULL,"SyncShare.exe");

	return 0;
}