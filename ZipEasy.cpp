#include <Windows.h>
#include <tchar.h>
#include <shlwapi.h>
#include "util/XUnzip.h"
#include "util/ZipEasy.h"
#include "util/File.h"
#include "util/StringEx.h"
#include <strsafe.h>

#ifndef KJLOG
#define COMMLOG
#endif

BOOL
UnzipFileToPath( LPCSTR lpszFilePath, LPCSTR lpszUnzipPath, std::vector<std::string>& ReleaseFiles )
{
	if( 
				NULL		== lpszFilePath
			||	'\0'	== lpszFilePath[0]
			||	NULL		== lpszUnzipPath 
			||	'\0'	== lpszUnzipPath[0]
	)
	{
		return FALSE;
	}

	BOOL bRet = FALSE;

	//���ļ�����ʽ��zip(֧��UNICODE|ANSI)
	HZIP hz = OpenZip((CHAR*)lpszFilePath,0,ZIP_FILENAME);

	int RetryCount = -1;
	while( (!hz) && (RetryCount++ < 5))
	{
		if (RetryCount == 0)
		{
			COMMLOG("DuoUpdate","��ZIP(%S)ʱ�����˴���OpenZip���ش���ľ����LastError=%d,�������´�",lpszFilePath,GetLastError());
		}else{
			COMMLOG("DuoUpdate","��ZIP(%S)ʱ�����˴���OpenZip���ش���ľ����LastError=%d,���Դ���=%d",lpszFilePath,GetLastError(),RetryCount);
		}
		Sleep(1000);
		hz = OpenZip((CHAR*)lpszFilePath,0,ZIP_FILENAME);
	}

	if (!hz)
	{
		COMMLOG("DuoUpdate","��ZIP(%S)ʱ�����˴���OpenZip���ش���ľ����LastError=%d,���Դ����ﵽ���ޡ�����ʧ��",lpszFilePath,GetLastError());
		return FALSE;
	}

	//ʹ�þֲ�����
	CHAR szUnzipPath[MAX_PATH *2] = "";
	StringCbPrintf(szUnzipPath, sizeof(szUnzipPath), "%s", lpszUnzipPath);
	//_sntprintf( szUnzipPath,SIZEOF_ARRAY(szUnzipPath)-1, "%s", lpszUnzipPath);

	size_t nLenUnzipPath = strlen(szUnzipPath);
	
	if( nLenUnzipPath <=0 )
	{
		COMMLOG("DuoUpdate","����Ŀ��·������Ϊ0");
		return FALSE;
	}

	//��ֹ��\��β
	if( szUnzipPath[strlen(szUnzipPath) -1 ] != '\\' )
	{
		strcat_s(szUnzipPath, sizeof(szUnzipPath), "\\");
	}

	std::string strUnzipPath = szUnzipPath;

	if (!File::exists(strUnzipPath))
	{
		File::createPath(strUnzipPath);
		if (!File::exists(strUnzipPath))
		{
			COMMLOG("DuoUpdate","����Ŀ¼%sʧ��",strUnzipPath.c_str());
			return FALSE;
		}
	}
	ZIPENTRY ze; 
	GetZipItem(hz,-1,&ze); 
	int numitems=ze.index;
	for (int i=0; i<numitems; i++)
	{ 
		if( ZR_OK != GetZipItem(hz,i,&ze))
		{
			continue;
		}
		CHAR szReleaseFullFileName[MAX_PATH * 2] = "";
		//_snwprintf( szReleaseFullFileName,SIZEOF_ARRAY(szReleaseFullFileName)-1, L"%s%s", szUnzipPath,ze.name);
		StringCbPrintf(szReleaseFullFileName, sizeof(szReleaseFullFileName), "%s%s", szUnzipPath, ze.name);
		if( StrStrI(ze.name,_T("..")) )
		{
			continue;
		}
		if ((ze.attr & FILE_ATTRIBUTE_DIRECTORY))//Ŀ¼
		{
			//�˴����ж��Ƿ񴴽�Ŀ¼�ɹ���
			File::createPath(szReleaseFullFileName);
		}
		else//�ļ�
		{
			//��ѹ����ļ���ӵ��ͷ��б���
			ReleaseFiles.push_back(szReleaseFullFileName);
			DWORD dwAttribute = INVALID_FILE_ATTRIBUTES;
			GetFileAttributes(szReleaseFullFileName);
			if( File::exists(szReleaseFullFileName) )
				 dwAttribute = 	GetFileAttributes(szReleaseFullFileName);
			if ( dwAttribute != INVALID_FILE_ATTRIBUTES )
			{
				dwAttribute &= ~FILE_ATTRIBUTE_READONLY;
				SetFileAttributes(szReleaseFullFileName, dwAttribute);
			}
			::DeleteFile(szReleaseFullFileName);
			//�ͷ�zip�ļ�
			UnzipItem(
						hz,						//Zip parse handle
						i,						//Zip index
						szReleaseFullFileName,	//Release full path file name
						0,						//FileType ingore
						ZIP_FILENAME			//Zip mode
						);
			dwAttribute = GetFileAttributes(szReleaseFullFileName);
			if (dwAttribute != INVALID_FILE_ATTRIBUTES)
			{
				dwAttribute &= ~FILE_ATTRIBUTE_READONLY;
				SetFileAttributes(szReleaseFullFileName, dwAttribute);
			}
		}
	}
	CloseZip(hz);
	return TRUE;
}