/**
* \copyright (C)2016 �������
* \file crypt.h
* \brief ����ļ��������ٽ����߳�ͬ���ķ�����
*
* CLock_CS���CAutoLock��ʹ���ٽ�����������̼߳�ʹ�õ���Դ��
* ����ʹ�÷���������boost::mutex
* ʹ�÷������£�
* \code
* CLock_CS CriticalSec;
* char BufferTest[256] = {0};
* void threadFunction1(LPVOID threadParam)
* {
*	  CAutoLock(CLock_CS);
*     //do something with BufferTest
* }
* void threadFunction2(LPVOID threadParam)
* {
*	  CAutoLock(CLock_CS);
*     //do something with BufferTest
* }
* \endcode
*
* \version 1.0
* \author fanduoduo
* \date 2016/11/11
*/
#ifndef _AutoLock_H
#define _AutoLock_H

#include <windows.h>
#include <fstream>

//�ٽ�����
class CLock_CS
{
public:
	CLock_CS(void)
	{
		::InitializeCriticalSection(&m_cs);
	}

	virtual~CLock_CS(void)
	{
		::DeleteCriticalSection(&m_cs);
	}

	void Lock(void)
	{
		::EnterCriticalSection(&m_cs);
	}

	void Unlock(void)
	{
		::LeaveCriticalSection(&m_cs);
	}
private:
	CRITICAL_SECTION m_cs;
};

//�Զ���
class CAutoLock
{
public:
	CAutoLock(CLock_CS & lock)
		: m_lock(lock)
	{
		m_lock.Lock();
	}
	virtual~CAutoLock()
	{
		m_lock.Unlock();
	}
private:
	CLock_CS & m_lock;
};


//��ͬ����֮�����

//
//class CLock_Process
//{
//public:
//	CLock_Process(std::string  v_strEventName):m_strEventName(v_strEventName)
//	{
//	}
//
//
//	HANDLE  CreateEventEx(const TCHAR *v_tszEventName)
//	{
//		HANDLE hEvent;
//
//		//!< Run Add 2016-05-19  ����Ȩ�ޣ������ڷ�����߲���ϵͳ�»ᴴ��ʧ��  
//		SECURITY_DESCRIPTOR secutityDese;
//		SECURITY_ATTRIBUTES securityAttr;
//
//		::InitializeSecurityDescriptor(&secutityDese, SECURITY_DESCRIPTOR_REVISION);
//		::SetSecurityDescriptorDacl(&secutityDese, TRUE, NULL, FALSE);
//
//		//!< ���� SECURITY_ATTRIBUTES
//		securityAttr.nLength				= sizeof(SECURITY_ATTRIBUTES);
//		securityAttr.bInheritHandle			= FALSE;
//		securityAttr.lpSecurityDescriptor	= &secutityDese;
//
//		hEvent= CreateEvent(&securityAttr ,FALSE, FALSE, v_tszEventName);
//
//		if(NULL==hEvent)
//		{
//			OutputDebugStringW(L"CFunLib::CreateEventEx Event Handle is NUll");
//		}
//
//		return hEvent;
//
//	}
//
//
//	virtual~CLock_Process(void)
//	{
//
//	}
//
//	void Lock(void)
//	{
//
//	}
//
//	void Unlock(void)
//	{
//	}
//private:
//	HANDLE hEvent;
//	std::string  m_strEventName;
//};
//
////�Զ���
//class CProcessAutoLock
//{
//public:
//	CProcessAutoLock(CLock_Process & lock)
//		: m_lock(lock)
//	{
//		m_lock.Lock();
//	}
//	virtual~CProcessAutoLock()
//	{
//		m_lock.Unlock();
//	}
//private:
//	CLock_Process & m_lock;
//};


#endif