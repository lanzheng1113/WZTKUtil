#pragma once
#include <windows.h>
//�ٽ�����
class CUtilCriticalLock
{
public:
	CUtilCriticalLock(void)
	{
		::InitializeCriticalSection(&m_cs);
	}

	virtual ~CUtilCriticalLock(void)
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
class CUtilScopeLock
{
public:
	CUtilScopeLock(CUtilCriticalLock & lock)
		: m_lock(lock)
	{
		m_lock.Lock();
	}
	virtual ~CUtilScopeLock()
	{
		m_lock.Unlock();
	}
private:
	CUtilCriticalLock & m_lock;
};

