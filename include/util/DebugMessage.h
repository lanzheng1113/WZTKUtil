/**
* \copyright (C)2016 �������
* \file DebugMessage.h
* \brief ������ʵ�ִ�ӡ������Ϣ��DebugView�Ľӿ�
*
* - v1.0
*   -# DebugMessageA ��ӡANSI��ʽ���ַ�����DebugView
*   -# DebugMessageW ��ӡUNICODE�ַ�����DebugView
* \author UNI
* \date 2009-11-7
* \version 1.0
 */
#pragma once
#include <Windows.h>

#ifdef UNICODE
#define DebugMessage DebugMessageW
#else
#define DebugMessage DebugMessageA
#endif

void DebugMessageA(char * szDebugMsg,...);
void DebugMessageW(wchar_t * szDebugMsg,...);

//���а棬ȥ��������Ϣ
//#define __RELEASE_VERSION

/**
 * \defgroup LOG_AND_DEBUG_MSG ������Ϣ����־
 * \{
 */

/**
 * \brief ���������Ϣ
 * 
 * Usage:	DebugMessageA("������:%d",2);
 *
 * \param szDebugMsg Ҫ�������Ϣ,������format����
 * 
 */
inline void DebugMessageA(char * szDebugMsg,...)
{
#ifndef __RELEASE_VERSION
	va_list va_args;
	int len;
	char * buffer;

	va_start(va_args,szDebugMsg);
	//�ú������ظ�ʽ������ַ������ȣ�������Terminating Null
	len=_vscprintf(szDebugMsg,va_args)+1;		

	buffer=new char[len*sizeof(char)];
	if(!buffer)
	{
		OutputDebugStringA("���������Ϣ���󣬷���ռ�ʧ��\n");
		return;
	}
	vsprintf_s(buffer,len,szDebugMsg,va_args);
	OutputDebugStringA(buffer);
	delete[] buffer;
#else
	return;
#endif
}

/**
* \brief ���������Ϣ�����ַ��棩
*
* Usage:	DebugMessageW(L"������:%d",2);
*
* \param szDebugMsg Ҫ�������Ϣ,������format����
*
*/
inline void DebugMessageW(wchar_t * szDebugMsg,...)
{
#ifndef __RELEASE_VERSION
	va_list va_args;
	int len;
	wchar_t * buffer;

	va_start(va_args,szDebugMsg);
	len=_vscwprintf(szDebugMsg,va_args)+1;

	buffer=new wchar_t[len*sizeof(wchar_t)];
	if(!buffer)
	{
		OutputDebugStringW(L"���������Ϣ���󣬷���ռ�ʧ��\n");
		return;
	}
	vswprintf_s(buffer,len,szDebugMsg,va_args);
	OutputDebugStringW(buffer);

	delete[] buffer;
#else
	return;
#endif
}
/**
 * \}
 */
