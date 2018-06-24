/**
 * \copyright (C)2016 �������
 * \file ProcessUtils.h
 * \brief ����һЩ�Ͷ�ȡ������Ϣ�йصĺ���
 *
 * v1.0
 * - IsProcessExists �ж�ָ��PID�Ľ����Ƿ���ڡ�
 * - GetPathFromProcessId ��ȡָ��PID�Ľ��̵�·����
 * - GetProcessIdFromPath ��ȡ��һ��ƥ��ָ������·���Ľ���ID 
 * - DosDevicePath2LogicalPath ��DOS�豸·����\\Device\\HarddiskVolume1\x86.sys��ת��Ϊ�߼�·����C:\x86.sys��
 *
 * \author fanduoduo
 * \date 2016/11/10
 * \version 1.0
 */

#pragma once
#include <windows.h>
#include <string>

#ifndef OUT
#define OUT
#endif

/**
 * \defgroup PROCE_INFO ��ȡ������Ϣ
 * \{
 */

namespace Process
{
	/**
 * \brief �ж�ָ��PID�Ľ����Ƿ����
 * \return ���ڷ���TRUE�����򷵻�FALSE
 */
BOOL IsProcessExists(DWORD pid);


/**
 * \brief ��ȡָ��PID�Ľ��̵�·����
 * \return �ҵ��򷵻�ָ�����̵�·�������򷵻ؿ��ַ���
 */
std::string GetPathFromProcessId(DWORD pid);


/**
 * \brief ��ȡ��һ��ƥ��ָ������·���Ľ���ID
 * \return �ҵ��򷵻�PID�����򷵻�0
 */
DWORD GetProcessIdFromPath(const std::string& strFilePath);


/**
 * \brief ���ݽ�������ȡ����ID
 * \return ���ؽ���ID�����û���ҵ�����0
 */
DWORD GetProcessIdByName(const std::string& strProcessName);

/**
 * \brief ����һ�������������ֵĽ���ID
 * 
 * \param strProcessName ϣ���������а������ַ�����
 * \param processName �ҵ��Ľ����������û���ҵ������ֵ����������ַ�����
 * \return �ҵ��Ľ���ID�����û���ҵ��򷵻�0
 */
DWORD GetProcessIdLikeName(const std::string& strProcessName, OUT std::string& processName);

/**
 * \brief ɱ�����ж�Ӧ���ֵĽ���
 * \return ���ر�ɱ�����̵ĸ���
 */
DWORD KillProcess(const std::string& strProcessName);

/**
 * \brief ��DOS�豸·����\\Device\\HarddiskVolume1\x86.sys��ת��Ϊ�߼�·����C:\x86.sys��
 * \return ��ת��ʧ���򷵻ؿ��ַ�����
 */
std::string DosDevicePath2LogicalPath(const wchar_t* lpszDosPath);	


/**
 * \brief ���ݽ������ִ򿪽��̡�
 */
HANDLE OpenProcessByPName(const std::string& strProcessName);

/**
 * \brief �����������Ȩ��ΪDebug
 * \param TRUE enable,FALSE disable.
 * \return ��Ȩʧ�ܷ���false������GetlastError��ȡ��ϸ��Ϣ,��Ȩ�ɹ�����true.
 */
BOOL SetSeDebugPrivilege(BOOL bEnablePrivilege);

/**
 * \brief ��ָͣ��ID�Ľ���
 * 
 * \param ProcessId ��Ҫ��ͣ���̵�ID
 * \return ����һ��NTSTATUS״ֵ̬����Ҫʹ��NT_SUCCESS���ж��Ƿ�ɹ���
 */
NTSTATUS SuspendProcessById(DWORD ProcessId);

/**
 * \brief �ָ�ָ��ID�Ľ���
 * 
 * \param ProcessId ��Ҫ�ָ����н��̵�ID
 * \return ����һ��NTSTATUS״ֵ̬����Ҫʹ��NT_SUCCESS���ж��Ƿ�ɹ���
 */
NTSTATUS ResumeProcessById(DWORD ProcessId);

/**
 * \brief ��ͣһ���������У�������Ȼ�ȡ������̵ľ���Դ��ݸ����������
 * 
 * \param hProcess ��Ҫ��ͣ���еĽ��̵ľ����
 * \return ����һ��NTSTATUS״ֵ̬����Ҫʹ��NT_SUCCESS���жϲ����Ƿ�ɹ���
 */
NTSTATUS SuspendProcessByHandle(HANDLE hProcess);

/**
 * \brief �ָ����� 
 * 
 * \param hProcess ��Ҫ�ָ����еĽ��̵ľ��
 * \return ����һ��NTSTATUS״ֵ̬����Ҫʹ��NT_SUCCESS���жϲ����Ƿ�ɹ���
 */
NTSTATUS ResumeProcessByHandle(HANDLE hProcess);

/**
 * \brief ʹ��ShellExecuteִ������
 * 
 * \param strExeFile ��ִ�г���
 * \param strExeParam ���ݸ�����������в���
 * \param bShow �Ƿ���ʾ�ó���Ĵ���
 * \return �ɹ�����TRUE,���򷵻�FALSE��
 */
BOOL CallCmd(const std::string strExeFile, const std::string strExeParam, BOOL bShow);

/**
 * \brief �鿴�������̵������в���
 * 
 * \param strProcessName ϣ���鿴�Ľ�����
 * \param strParam ��ȡ���������в���
 * \return �ɹ����ҵ������в�������TRUE��û���ҵ����������߷����������󷵻�FALSE��
 */
BOOL PeekProcessCmdLine(const std::string strProcessName, OUT std::string& strParam);
};

/**
 * /}
 */