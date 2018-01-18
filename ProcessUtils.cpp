/**
 * \copyright (C)2016 万兆天空
 * \file ProcessUtils.cpp 
 * \brief 实现一些和读取进程信息有关的函数。\see ProcessUtils.h 
 * \author fanduoduo
 * \date 2016/11/10
 * \version 1.0
 */

#include "util/ProcessUtils.h"
#include<Tlhelp32.h>
#include <Psapi.h>
#include "util/StringEx.h"
#pragma comment (lib,"Psapi.lib") 

BOOL IsProcessExists(DWORD pid)
{
	HANDLE myhProcess;
	PROCESSENTRY32 mype;
	mype.dwSize = sizeof(PROCESSENTRY32);
	BOOL mybRet;
	//进行进程快照
	myhProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //快照所有进程
	//开始进程查找
	mybRet = Process32First(myhProcess, &mype);
	//循环比较，得出ProcessID
	while (mybRet)
	{
		if (mype.th32ProcessID == pid)
		{
			return TRUE;
		}			
		mybRet = Process32Next(myhProcess, &mype);
	}
	return FALSE;
}

std::string GetPathFromProcessId(DWORD pid)
{
	std::string   path;
	WCHAR szBuf[MAX_PATH] = { 0 };
	HANDLE h_Process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	if (h_Process)
	{
		GetProcessImageFileNameW(h_Process, szBuf, MAX_PATH * sizeof(WCHAR));
		path = DosDevicePath2LogicalPath(szBuf);
	}
	return path;
}

DWORD GetProcessIdFromPath(const std::string& FilePath)
{
	HANDLE myhProcess;
	PROCESSENTRY32 mype;
	mype.dwSize = sizeof(PROCESSENTRY32);
	BOOL mybRet;
	//进行进程快照
	myhProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //快照所有进程
	//开始进程查找
	mybRet = Process32First(myhProcess, &mype);
	//循环比较，得出ProcessID
	while (mybRet)
	{
		std::string   path;
		WCHAR szBuf[MAX_PATH] = { 0 };
		HANDLE h_Process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, mype.th32ProcessID);
		if (!h_Process)
		{
			mybRet = Process32Next(myhProcess, &mype);
			continue;
		}
		GetProcessImageFileNameW(h_Process, szBuf, MAX_PATH * sizeof(WCHAR));
		path = DosDevicePath2LogicalPath(szBuf);

		if (String(FilePath).toUpperCase() == String(path).toUpperCase())
			return mype.th32ProcessID;
		else
			mybRet = Process32Next(myhProcess, &mype);
	}
	return 0;
}

std::string DosDevicePath2LogicalPath(const wchar_t* lpszDosPath)
{
	std::string strResult;
	// Translate path with device name to drive letters.
	// 通过GetLogicalDriveStringsW获取所有的盘符CDEFG...
	wchar_t szTemp[MAX_PATH];
	szTemp[0] = '\0';
	if (lpszDosPath == NULL || !GetLogicalDriveStringsW(_countof(szTemp) - 1, szTemp))
	{
		return strResult;
	}
	
	wchar_t szName[MAX_PATH];
	wchar_t szDrive[3] = L" :";
	BOOL bFound = FALSE;
	wchar_t* p = szTemp;
	do {
		// Copy the drive letter to the template string
		// 遍历系统上所有的盘符，将查询逻辑路径对应的DOS设备路径（C: --> \\Device\\HarddiskVolume1）
		*szDrive = *p;
		// Look up each device name
		if (QueryDosDeviceW(szDrive, szName, _countof(szName))) 
		{
			UINT uNameLen = (UINT)wcslen(szName);
			if (uNameLen < MAX_PATH)
			{
				// 如果输入的DOS设备路径以该盘符的DOS设备路径开头
				bFound = _wcsnicmp(lpszDosPath, szName, uNameLen) == 0;
				if (bFound) 
				{
					// Reconstruct pszFilename using szTemp
					// Replace device path with DOS path
					// 用对应的逻辑路径替换DOS设备路径（\\Device\\HarddiskVolume1\A.sys --> C:\A.sys）
					wchar_t szTempFile[MAX_PATH];
					swprintf_s(szTempFile, L"%s%s", szDrive, lpszDosPath + uNameLen);
					strResult = String::fromStdWString(szTempFile);
				}
			}
		}
		// Go to the next NULL character.
		while (*p++);
	} while (!bFound && *p); // end of string
	return strResult;
}

