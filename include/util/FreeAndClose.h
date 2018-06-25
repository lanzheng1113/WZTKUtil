#pragma once
#include "util/NonCopyable.h"

/**
* \class DataArrayDeleteAgent
* DataArrayDeleteAgent ������δʹ��boost::scope_array�ĵط�������ʹ�á�
*
* �����������ͷ�һ���ڴ档�������Ķ����뿪��������Զ��ͷ����ڲ���ָ��ָ����ڴ�顣
* ע������������ڴ�����ʱʹ�á�
* ����ʹ��template���������ڷ�����Ե�ʱ��֪������һ�����͡�
*/
template <class T>
class DataArrayDeleteAgent : public NonCopyable
{
public:
	DataArrayDeleteAgent(T* ptr)
	{
		m_ptr = ptr;
	}
	~DataArrayDeleteAgent()
	{
		//psv Modify
		//		if (m_ptr)
		{
			delete[] m_ptr;
		}
	}
protected:
private:
	T* m_ptr;
};

class HandleCloser : public NonCopyable
{
public:
	HandleCloser(HANDLE hHandle)
	{
		m_hHandle = hHandle;
	}
	~HandleCloser()
	{
		CloseHandle(m_hHandle);
	}
private:
	HANDLE m_hHandle;
};