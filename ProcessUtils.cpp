/**
 * \copyright (C)2016 �������
 * \file ProcessUtils.cpp 
 * \brief ʵ��һЩ�Ͷ�ȡ������Ϣ�йصĺ�����\see ProcessUtils.h 
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
	//���н��̿���
	myhProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //�������н���
	//��ʼ���̲���
	mybRet = Process32First(myhProcess, &mype);
	//ѭ���Ƚϣ��ó�ProcessID
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
	//���н��̿���
	myhProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //�������н���
	//��ʼ���̲���
	mybRet = Process32First(myhProcess, &mype);
	//ѭ���Ƚϣ��ó�ProcessID
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
	// ͨ��GetLogicalDriveStringsW��ȡ���е��̷�CDEFG...
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
		// ����ϵͳ�����е��̷�������ѯ�߼�·����Ӧ��DOS�豸·����C: --> \\Device\\HarddiskVolume1��
		*szDrive = *p;
		// Look up each device name
		if (QueryDosDeviceW(szDrive, szName, _countof(szName))) 
		{
			UINT uNameLen = (UINT)wcslen(szName);
			if (uNameLen < MAX_PATH)
			{
				// ��������DOS�豸·���Ը��̷���DOS�豸·����ͷ
				bFound = _wcsnicmp(lpszDosPath, szName, uNameLen) == 0;
				if (bFound) 
				{
					// Reconstruct pszFilename using szTemp
					// Replace device path with DOS path
					// �ö�Ӧ���߼�·���滻DOS�豸·����\\Device\\HarddiskVolume1\A.sys --> C:\A.sys��
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

