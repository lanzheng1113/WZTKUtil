#include <Windows.h>
#include "util/CommonWinFuns.h"
#include <string>

using std::string;

std::string GetFileLegalCopyright(CHAR * strFilePath)
{
	DWORD dwSize;
	DWORD dwRtn;
	string szVersion;
	//��ȡ�汾��Ϣ��С
	dwSize = GetFileVersionInfoSizeA(string(strFilePath).c_str(), NULL);
	if (dwSize == 0)
	{
		return "";
	}
	CHAR *pBuf;
	pBuf = new CHAR[dwSize + 1];
	memset(pBuf, 0, dwSize + 1);
	//��ȡ�汾��Ϣ
	dwRtn = GetFileVersionInfoA(string(strFilePath).c_str(), NULL, dwSize, pBuf);
	if (dwRtn == 0)
	{
		delete [] pBuf;
		return "";
	}
	LPVOID lpBuffer = NULL;
	UINT uLen = 0;
	//�汾��Դ�л�ȡ��Ϣ
	dwRtn = VerQueryValueA(pBuf,
		"\\StringFileInfo\\080404b0\\LegalCopyright",
		//0804����
		//04b0��1252,ANSI
		//���Դ�ResourceView�е�Version��BlockHeader�п���
		//���Բ��Ե�����
		/*
		CompanyName
		FileDescription
		FileVersion
		InternalName
		LegalCopyright
		OriginalFilename
		ProductName
		ProductVersion
		Comments
		LegalTrademarks
		PrivateBuild
		SpecialBuild
		*/
		&lpBuffer,
		&uLen);
	if (dwRtn == 0)
	{
		delete [] pBuf;
		return "";
	}
	szVersion = (CHAR*)lpBuffer;
	delete [] pBuf;
	return szVersion;
}


std::string GetPEFileVersionInfo(const std::string& strFilePath, const std::string& strVersionKey)
{
	DWORD dwSize;
	DWORD dwRtn;
	string szVersion;
	//��ȡ�汾��Ϣ��С
	dwSize = GetFileVersionInfoSizeA(strFilePath.c_str(), NULL);
	if (dwSize == 0)
	{
		return "";
	}
	CHAR *pBuf;
	pBuf = new CHAR[dwSize + 1];
	memset(pBuf, 0, dwSize + 1);
	//��ȡ�汾��Ϣ
	dwRtn = GetFileVersionInfoA(strFilePath.c_str(), NULL, dwSize, pBuf);
	if (dwRtn == 0)
	{
		delete []pBuf;
		return "";
	}
	LPVOID lpBuffer = NULL;
	UINT uLen = 0;
	//�汾��Դ�л�ȡ��Ϣ
	string versionKeyZh = "\\StringFileInfo\\080404b0\\";
	versionKeyZh += strVersionKey;
	string versionKeyEn = "\\StringFileInfo\\040904b0\\";		
	versionKeyEn += strVersionKey;
	string versionKeyEn2 = "\\StringFileInfo\\040904e4\\";
	versionKeyEn2 += strVersionKey;
	//������Դ
	dwRtn = VerQueryValueA(pBuf,
		versionKeyZh.c_str(),
		&lpBuffer,
		&uLen);
	//Ӣ����Դ
	if (dwRtn == 0)
	{
		dwRtn = VerQueryValueA(pBuf,
			versionKeyEn.c_str(),
			&lpBuffer,
			&uLen);
	}
	//Ӣ����Դ2
	if (dwRtn == 0)
	{
		dwRtn = VerQueryValueA(pBuf,
			versionKeyEn2.c_str(),
			&lpBuffer,
			&uLen);
	}
	//ʧ����
	if (dwRtn == 0)
	{
		delete []pBuf;
		return "";
	}		
	szVersion = (CHAR*)lpBuffer;
	delete [] pBuf;
	return szVersion;
}
