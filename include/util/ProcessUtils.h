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
 * \brief ��DOS�豸·����\\Device\\HarddiskVolume1\x86.sys��ת��Ϊ�߼�·����C:\x86.sys��
 * \return ��ת��ʧ���򷵻ؿ��ַ�����
 */
std::string DosDevicePath2LogicalPath(const wchar_t* lpszDosPath);	

/**
 * /}
 */