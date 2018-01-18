/**
* \copyright (C)2016 �������
* \file DriverHelp.h 
* \brief DriverHelp.h ���� CDriverHelp �࣬CDriverHelp��װ�����������һЩ������
* \version v1.0
* \author Run
* \date 2015.03.06
*/

#pragma once
#include <windows.h>

/**
 * @defgroup DRIVER_OPEATION ��������
 * \brief ���������Ĳ����ӿ�
 * @{
 */

/**
 * \brief CDriverHelp��װ�����������һЩ������
 *
 * �������¹��ܣ�
 * - ��������
 * - ж��ָ�����Ƶ���������
 * - ������ͨ��
 * - �ر�����ͨ��
 * - �������㷢������
 * 
 */
class CDriverHelp
{
public:
	CDriverHelp(void);
	~CDriverHelp(void);


	/**
	 * \brief ��  ��:����ָ������
	 * \param DriverAbsPath �����������·��
	 * \param ServiceName ������
	 * \param DisplayName ������ʾ��
	 * \return �ɹ�:0;ʧ��:����GetLastError������
	 */
	DWORD DrvLoadDriver(const CHAR* v_szDriverAbsPath, 
		              const CHAR* v_szServiceName, 
		              const CHAR* v_szDisplayName);

	/**
	 * \brief ��  ��:ж��ָ�����Ƶ���������
	 * \param ServiceName ���������
	 * \return �ɹ�:0;ʧ��:����GetLastError������,�Բ����ڵķ��񷵻�-1(�ɹ�)
	*/
	DWORD DrvUnloadDriver(const CHAR* v_szServiceName);

	/**
	 * \brief ��  ��:������ͨ��
	 * \param v_szDeviceName �豸����
	 * \return �ɹ�:TRUE; ʧ��:FALSE
	*/
	BOOL DrvOpenDriver(const CHAR* v_szDeviceName);

	/**
	 * \brief ��  ��:�ر�����ͨ��
	 * \return �ɹ�:TRUE; ʧ��:FALSE
	 */
	BOOL DrvCloseDriver();

	/**
	 * \brief ��  ��:�������㷢������
	 * \param v_nCtrlCode  ������������
	 * \param v_szData     ���͵�����������
	 * \param v_iDataLen   �������ݳ���
	 * \param v_szResult   �������ؽ��
	 * \param v_iResultLen �������ؽ������
	 * \return �ɹ�:TRUE; ʧ��:FALSE
	*/
	BOOL DrvSendCommand(const DWORD v_nCtrlCode, 
		const char*    v_szData, 
		const DWORD    v_iDataLen, 
		char*          v_szResult, 
		DWORD&         v_iResultLen);


protected:

private:

	SC_HANDLE m_hScManager;  //������ƹ��������
	long      m_nRefcount;
	HANDLE    m_hDevice;     //�豸���

	//�򿪷��������
	DWORD DrvOpenScManager(int open);
	//��������
	DWORD DrvCreateService(const CHAR* v_szDriverAbsolutePath, 
		const CHAR* ServiceName,const CHAR* ServiceDispalyName,SC_HANDLE* phService);
    //��ӷ���
	DWORD DrvAddService(const CHAR* DriverAbsPath, const CHAR* ServiceName, 
		const CHAR* DisplayName);
	//ɾ������
	DWORD DrvDeleteService(const CHAR* ServiceName);


};

/** @} */