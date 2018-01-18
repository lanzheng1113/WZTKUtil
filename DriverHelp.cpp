/************************************************************************/
/* Copyright(C)2015
 * All rights reserved
 * ��  �ƣ�DriverHelp.h
 * ժ  Ҫ������CDriverHelp������й��ܣ�
            CDriverHelp��Ҫ����Ϊ�������򴴽�����
			�����ṩ��������ͨ��
 * ��  ����v1.0
 * ��  ��: Run
 * ����ʱ�䣺2015.03.06
 * �޸ļ�¼����
*/
/************************************************************************/
#include "util/DriverHelp.h"
#include <tchar.h>
#include <stdio.h>

const int OPEN_SC_MANAGER = 1;
const int CLOSE_SC_MANAGER = 0;

#define DRIVER_HELP "DriverHelp"


CDriverHelp::CDriverHelp(void)
{
	m_nRefcount = 0;
    m_hScManager = NULL;
	m_hDevice = ((HANDLE)-1);
}


CDriverHelp::~CDriverHelp(void)
{
	if(m_hScManager&&!InterlockedDecrement(&m_nRefcount))
	{
		CloseServiceHandle(m_hScManager);
		m_hScManager = NULL;
	}

	if ( ((HANDLE)-1) != m_hDevice )
	{
		CloseHandle(m_hDevice);
		m_hDevice = (HANDLE)-1;
	}

}



/**************************************************
��  ��:drvOpenScManager@4
��  ��:�򿪷�����ƹ�����
��  ��:open - !0:��,0:�ر�
����ֵ:�ɹ�:0;ʧ��:����GetLastError������
˵  ��:�ڲ�����
2013-02-17:

**************************************************/
DWORD CDriverHelp::DrvOpenScManager(int v_nOpen)
{
	DWORD nRet = 0;

	switch (v_nOpen)
	{
	case OPEN_SC_MANAGER:
		//��������������Ϊ��˵���Ѿ���,ֱ�ӷ���
		if(m_hScManager)
		{
			InterlockedIncrement(&m_nRefcount);    
			break;
		}

		//�򿪷��������
		m_hScManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if(m_hScManager == NULL)
		{
			nRet = GetLastError();
			break;
		}

		InterlockedIncrement(&m_nRefcount);
		break;

	case CLOSE_SC_MANAGER://�رշ��������
		if(m_hScManager&&!InterlockedDecrement(&m_nRefcount))
		{
			CloseServiceHandle(m_hScManager);
			m_hScManager = NULL;
		}

		break;
	default:
		break;
	}

	return nRet;
}

/**************************************************
��  ��:drvCreateService@16
��  ��:�����·���,�����ط�����(if succeeded)
��  ��:	DriverAbsolutePath - �����ļ��ľ���·��
ServiceName - ������
ServiceDisplayName - �������ʾ��
*phService - ���صķ�����
����ֵ:�ɹ�:0;ʧ��:����GetLastError������
˵  ��:�ڲ�����
**************************************************/
DWORD CDriverHelp::DrvCreateService(const CHAR* v_szDriverAbsolutePath, const CHAR* v_szServiceName, 
								 const CHAR* v_szServiceDispalyName, SC_HANDLE* v_phService)
{

	SC_HANDLE hService = NULL;

	hService = CreateService(
			m_hScManager,			    //������������������
			v_szServiceName,			//���������
			v_szServiceDispalyName,		//�������ʾ����
			SERVICE_ALL_ACCESS,		    //�Ը÷���ķ���Ȩ��
			SERVICE_KERNEL_DRIVER,	    //���������:�ں�����
			SERVICE_DEMAND_START,	    //��������:�ֶ����� //SERVICE_AUTO_START,�Զ�����
			SERVICE_ERROR_NORMAL,	    //����������:����
			v_szDriverAbsolutePath,		//�����ļ��ľ���·��
			NULL,					    //û��������
			NULL,					    //������Ĭ�ϵı�ǩID
			NULL,					    //û�з���������
			NULL,					    //ʹ��Ĭ�϶�������
			NULL					    //û������
			);

	DWORD dwLastError = GetLastError();

	//����Ƿ����Ѿ�����,ֱ�Ӵ򿪷���
	if(dwLastError == ERROR_SERVICE_EXISTS)
	{
		dwLastError = 0;
		//�򿪷���
		hService = OpenService(
			m_hScManager,
			v_szServiceName,
			SERVICE_ALL_ACCESS
			);

		if (NULL == hService)
		{
			dwLastError = GetLastError();
		}
	}

	*v_phService = hService;
	return dwLastError;
}

/**************************************************
��  ��:drvDeleteService@4
��  ��:ɾ��ָ���������ĵķ���
��  ��:ServiceName - ������
����ֵ:�ɹ�:0;ʧ��:����GetLastError������
˵  ��:	�ڲ�����
�Բ����ڵķ��񷵻�-1(�ɹ�)
**************************************************/
DWORD CDriverHelp::DrvDeleteService(const CHAR* v_szServiceName)
{
	SERVICE_STATUS ServiceStatus;
	SC_HANDLE hService=NULL;
	DWORD dwLastError = 0;

	__try{
		hService=OpenService(m_hScManager, v_szServiceName, SERVICE_ALL_ACCESS);
		if(hService==NULL)
		{
			dwLastError = GetLastError();
			//������������ڣ���������Ϊɾ���ɹ�
			if(dwLastError==ERROR_SERVICE_DOES_NOT_EXIST)
			{
				dwLastError = 0;
			}

			__leave;
		}

		if(!ControlService(hService,SERVICE_CONTROL_STOP,&ServiceStatus))
		{//ֹͣ����ʧ��
			dwLastError = GetLastError();
			if(dwLastError != ERROR_SERVICE_NOT_ACTIVE)
			{//��������Ϊû������������
				__leave;
			}

			//�����������û��������������Ϊ���β���Ҳ�ǳɹ���
			dwLastError = 0;
		}

		if(!DeleteService(hService))
		{
			dwLastError = GetLastError();
			__leave;
		}

	}
	__finally{
		if(hService)
		{
			CloseServiceHandle(hService);
			hService=NULL;
		}
	}
	return dwLastError;
}

/**************************************************
��  ��:drvAddService@12
��  ��:���ָ���ķ���
��  ��:	DriverAbsPath - �����������·��
ServiceName - ������
DisplayName - ������ʾ��
1:ɾ�������´���
0:���ټ���,����-1(�ɹ�)
-1:��ʾ�Ƿ����
����ֵ:�ɹ�:0;ʧ��:����GetLastError������
˵  ��:	�ڲ�����
��ѡ���˲��ټ���,����-1(�ɹ�)
**************************************************/
DWORD CDriverHelp::DrvAddService(const CHAR* v_szDriverAbsPath, 
							  const CHAR* v_szServiceName, 
							  const CHAR* v_szDisplayName)
{
	SC_HANDLE hService = NULL;		//����/�򿪵ķ�����
	DWORD dwErrCode = 0;
	__try{
		//�ٶ����񲻴��ڲ�����������Ѿ��������

		dwErrCode = DrvCreateService(v_szDriverAbsPath, v_szServiceName, 
			                         v_szDisplayName, &hService);
		if(dwErrCode)
		{
			__leave;
		}
		//����ɹ�������������
		if(!StartService(hService,0,NULL))
		{
			dwErrCode = GetLastError();
			//����Ƿ���������
			if(dwErrCode == ERROR_SERVICE_ALREADY_RUNNING)
			{
				dwErrCode = 0;
			}

			__leave;

		}

	}
	__finally{
		if(hService){
			CloseServiceHandle(hService);
			hService=NULL;
		}
	}
	return dwErrCode;
}

/**************************************************
��  ��:LoadDriver@12
��  ��:����ָ������
��  ��:	DriverAbsPath - �����������·��
        ServiceName - ������
        DisplayName - ������ʾ��

����ֵ:�ɹ�:0;ʧ��:����GetLastError������
˵  ��:	�ⲿ����
**************************************************/
DWORD CDriverHelp::DrvLoadDriver(const CHAR* v_szDriverAbsPath, 
							   const CHAR* v_szServiceName, 
							  const CHAR* v_szDisplayName)
{
	//�򿪷��������
	DWORD dwErr = DrvOpenScManager(OPEN_SC_MANAGER);

	//�򿪳ɹ�����贴������
	if(!dwErr)
	{
		dwErr = DrvAddService(v_szDriverAbsPath, v_szServiceName, v_szDisplayName);
	}
		
	return dwErr;
}

/**************************************************
��  ��:UnloadDriver@4
��  ��:ж��ָ�����Ƶ���������
��  ��:ServiceName - ���������
����ֵ:�ɹ�:0;ʧ��:����GetLastError������
˵  ��:	�ⲿ����
�Բ����ڵķ��񷵻�-1(�ɹ�)
**************************************************/
DWORD CDriverHelp::DrvUnloadDriver(const CHAR* v_szServiceName)
{
	DWORD ret = 0;

	DrvOpenScManager(OPEN_SC_MANAGER);
	ret = DrvDeleteService(v_szServiceName);
	DrvOpenScManager(CLOSE_SC_MANAGER);
	return ret;
}

/**************************************************
��  ��:DrvOpenDriver
��  ��:������ͨ��
��  ��:v_szDeviceName -�豸����
����ֵ:�ɹ�:0;ʧ��:����GetLastError������
˵  ��:	�ⲿ����
**************************************************/
BOOL CDriverHelp::DrvOpenDriver(const CHAR* v_szDeviceName)
{
//	TCHAR    completeDeviceName[64] = {0};

	if ( ((HANDLE)-1) == m_hDevice && v_szDeviceName)
	{
		/*
		if( (GetVersion() & 0xFF) >= 5 ) 
		{
			_stprintf_s( completeDeviceName, 64*sizeof(TCHAR), TEXT("\\\\.\\Global\\%s"), v_szDeviceName );
		} 
		else 
		{
			_stprintf_s( completeDeviceName, 64*sizeof(TCHAR), TEXT("\\\\.\\%s"), v_szDeviceName );
		}*/

		m_hDevice = CreateFile( v_szDeviceName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
		if ( ((HANDLE)-1) == m_hDevice)
		{
			return FALSE;
		}

	}
	
	return TRUE;
}

/**************************************************
��  ��:DrvCloseDriver
��  ��:�ر�����ͨ��
��  ��:
����ֵ:�ɹ�:TRUE; ʧ��:FALSE
˵  ��:	�ⲿ����
**************************************************/
BOOL CDriverHelp::DrvCloseDriver()
{
	BOOL bRet = FALSE;
	if ( ((HANDLE)-1) != m_hDevice )
	{
		CloseHandle(m_hDevice);
		m_hDevice = (HANDLE)-1;
		bRet = TRUE;
	}

	return bRet;
}

/**************************************************
��  ��:DrvSendCommand
��  ��:�������㷢������
��  ��:v_nCtrlCode  - ������������
        v_szData     - ���͵�����������
		v_iDataLen   - �������ݳ���
		v_szResult   - �������ؽ��
        v_iResultLen - �������ؽ������

����ֵ:�ɹ�:TRUE; ʧ��:FALSE
˵  ��:	�ⲿ���������GetLastError()==ERROR_BAD_UNIT,���ʾ�����豸��δ�򿪡�
**************************************************/
BOOL CDriverHelp::DrvSendCommand(const DWORD v_nCtrlCode, 
						   const char*    v_szData, 
						   const DWORD    v_iDataLen, 
						   char*          v_szResult, 
						   DWORD&         v_iResultLen)
{
	BOOL	bResult = FALSE;
	DWORD	dwInBufLen = v_iDataLen;
	DWORD	dwOutBufLen = v_iResultLen;

	if (((HANDLE)-1) != m_hDevice)
	{
		bResult = DeviceIoControl(
			m_hDevice,
			v_nCtrlCode,
			(void *)v_szData,
			dwInBufLen,
			v_szResult,
			dwOutBufLen,
			&dwOutBufLen,
			NULL
			);
		v_iResultLen = dwOutBufLen;
	}else{
		SetLastError(ERROR_BAD_UNIT);
	}
	return bResult;
}
