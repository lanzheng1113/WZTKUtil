/**
 * \copyright (C)2016 �������
 * \file CommonWinFuns.h  
 * \brief ���峣����һЩδ�����windows���ܡ�
 * 
 * - v1.0
 *   -# GetAccountSid ����һ���û�����ȡ�û���sid��
 *   -# GetDefaultBrowserLaunchCommand ��ע����л�ȡĬ��������������С�
 *   -# SetPrivilege ���û��߽�ֹһ�����Ƶ�Ȩ�ޡ�
 *   -# GetIEPath ��ȡIE·����
 *   -# TakeOwnership ͨ������һ���ļ���/�ļ��ķ���Ȩ��ΪEveryOne�Ի�ȡ����Ȩ�ޡ�
 *   -# RestoreWow64FsRedir �ָ�WOW64�ļ��ض���
 *   -# DisableWow64FsRedir ����WOW64�ļ��ض���
 *
 * - v1.1 ������ȡ�ļ��汾��Ϣ�Ͱ�Ȩ��Ϣ�Ľӿڡ�
 *   -# GetPEFileVersionInfo ��ȡPE�ļ���ĳ��ָ������Դ����Ϣ��
 *   -# GetFileLegalCopyright ��ȡPE�ļ��еİ�Ȩ��Ϣ��
 *   -# AnalyseShortCut ��ȡһ����ݷ�ʽ����ϸ��Ϣ��
 * \author FDD
 * \date 2017/8/15
 * \version 1.1
 */
#pragma once
#include <string>
using std::wstring;


/**
 * \brief ����һ���û�����ȡ�û���sid.
 * \param[in] AccountName ������û���.
 * \param[out] Sid ָ��һ��PSID��ָ�룬���ڽ��շ��صĽ������ʹ����Sid��ע��ʹ��LocalFree�ͷ�����
 * \return �ɹ�����true,����Sid�����з����û�����Ӧ��SID,ʧ�ܷ���false��Sid������ΪNULL.
 * \note ��ʹ����Sid��ע��ʹ��LocalFree�ͷ�����
 */
bool GetAccountSid(LPSTR AccountName, OUT PSID *Sid);

/**
 * \brief ��ע����л�ȡĬ���������������.
 *  ����"C:\Program Files (x86)\Google\Chrome\Application\chrome.exe" -- "%1"
 * \param[out] default_browse Ĭ��������������У��������˺�������true��ʱ����Ч��
 * \return �ɹ�����true,ʧ�ܷ���false.
 */
bool GetDefaultBrowserLaunchCommand(std::string& default_browser);


/**
 * \brief ���û��߽�ֹһ�����Ƶ�Ȩ��
 * 
 * \param hToken �Ѿ��򿪵����ƾ��
 * \param lpszPrivilege ϵͳԤ�����һЩȨ�ޣ�����SE_TAKE_OWNERSHIP_NAME��
 * \param bEnablePrivilege �������ΪTRUE���������ƾ��д�Ȩ�ޣ������ֹ����ӵ�д�Ȩ�ޡ�
 * \return �ɹ�����TRUE��ʧ�ܷ���FALSE��
 */
BOOL SetPrivilege( HANDLE hToken, LPCSTR lpszPrivilege, BOOL bEnablePrivilege );


/**
 * \brief ��ȡIE·��
 * \return �ɹ�����IE��·����ʧ�ܷ��ؿ�ֵ��
 * \note:
 *	ͨ��HKEY_CLASSES_ROOT\IE.HTTP\shell\open\command��Ĭ��ֵ��ȡIE��·����"C:\Program Files (x86)\Internet Explorer\iexplore.exe" -nohome
 *	ͨ���ַ��������ȡ�����յĽ����C:\Program Files (x86)\Internet Explorer\iexplore.exe
 */
std::wstring GetIEPath();


/**
 * \brief ͨ������һ���ļ���/�ļ��ķ���Ȩ��ΪEveryOne�Ի�ȡ����Ȩ�ޡ�
 * \return �ɹ�TRUE��ʧ�ܷ���FALSE��
 * \note:
 *	���ļ��еķ���Ȩ�ޱ�����Ϊ�����û����޷�����ʱ����ʹ��ǰ�û�ӵ�й���ԱȨ��Ҳ�޷�ֱ�ӷ��ʣ�
 *	������ʹ�ù���ԱȨ�����޸�Ȩ�ޡ��������ʵ�����޸�Ȩ�޵Ĺ��ܡ�
 */
BOOL TakeOwnershipOfFilePath(LPSTR lpszOwnFile);


/**
 * \brief �ָ�WOW64�ļ��ض���
 */
BOOL RestoreWow64FsRedir();


/**
 * \brief ����WOW64�ļ��ض��� 
 */
BOOL DisableWow64FsRedir();


/**
 * \brief ��ȡPE�ļ���ĳ��ָ������Դ����Ϣ��
 * �ɸ��ݲ��� strVersionKey ��ֵ��ȡPE�ļ��İ汾��Ȩ��Ϣ�ȣ�������strVersionKey��˵����
 * \param strFilePath �ļ�·��
 * \param ϣ����ȡ���ļ���Ϣ�����£�
 * - CompanyName
 * - FileDescription
 * - FileVersion
 * - InternalName
 * - LegalCopyright
 * - OriginalFilename
 * - ProductName
 * - ProductVersion
 * - Comments
 * - LegalTrademarks
 * - PrivateBuild
 * - SpecialBuild
 * \return ���ػ�ȡ����Դ��Ϣ��
 */
std::string GetPEFileVersionInfo(const std::string& strFilePath, const std::string& strVersionKey);


/**
 * \brief ��ȡPE�ļ��еİ�Ȩ��Ϣ��@see GetPEFileVersionInfo ��������һ��������
 * \param strFilePath �ļ�·��
 * \return �����ļ��İ�Ȩ��Ϣ
 */
std::string GetFileLegalCopyright(CHAR * strFilePath);


typedef struct _LNKHEAD
{
	DWORD		dwID;
	DWORD		dwGUID[4];
	DWORD		dwFlags;
	DWORD		dwFileAttributes;
	FILETIME	dwCreationTime;
	FILETIME	dwModificationTime;
	FILETIME	dwLastaccessTime;
	DWORD		dwFileLen;
	DWORD		dwIconNum;
	DWORD		dwWinStyle;
	DWORD		dwHotkey;
	DWORD		dwReserved1;
	DWORD		dwReserved2;
}LNKHEAD, *PLNKHEAD;
typedef struct _FILELOCATIONINFO
{
	DWORD		dwSize;
	DWORD		dwFirstOffset;
	DWORD		dwFlags;
	DWORD		dwOffsetOfVolume;
	DWORD		dwOffsetOfBasePath;
	DWORD		dwOffsetOfNetworkVolume;
	DWORD		dwOffsetOfRemainingPath;
}FILELOCATIONINFO, *PFILELOCATIONINFO;
enum LinkKindEnum
{
	LNK_LOCALVOLUME = 0x1,
	LNK_NETSHARE = 0x2
};
enum LinkTypeEnum
{
	LNK_HASIDLIST = 0x1,
	LNK_FILEDIR = 0x2,
	LNK_HASDES = 0x4,
	LNK_HASPATH = 0x8,
	LNK_HASWORKDIR = 0x10,
	LNK_HASCMD = 0x20
};

/**
 * \brief AnalyseShortCut ������ݷ�ʽ
 * \param pFileName ��ݷ�ʽ(.lnk�ļ�)������ļ�·��
 * \param strRealPath ִ�к��ſ�ݷ�ʽ��ָ����ļ�·��
 * \param strCommand ִ�к��ſ�ݷ�ʽ��Ŀ�꣬���������в���
 * \param strDescription ִ�к��ſ�ݷ�ʽ������
 */
void AnalyseShortCut(const char *pFileName, 
	OUT std::string& strRealPath, 
	OUT std::string& strCommand, 
	OUT std::string& strDescription );