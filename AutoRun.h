#pragma once
#include <Windows.h>
//#include <shlobj_core.h>
#include <stdio.h>
#include<Psapi.h>

class AutoRun
{
public:
	//����ע�������
	static BOOL RegAutoRun();
	//StartUp Directory
	static BOOL StartUpFloderAutoRun(char* szTargetFilePath,const char* szAutoRunFileName);
	//��������ƻ�����
	static BOOL TaskScheduleAutoRun();
	//����������ϵͳ����
	static BOOL ServiceStartUp();
	//DLL�ٳ�ϵͳ�ؼ������������explorer.exe...��
	static BOOL DllHijackAutoRun();

};

