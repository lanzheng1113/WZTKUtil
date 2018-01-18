/**
 * \copyright (C)2016 �������
 * \file OSVersion.h 
 * \brief �����ȡWindows�汾�š��ж��ǲ���win8����win8.1�Ľӿڡ�
 * 
 * v1.0
 * - GetWinMajorMinorVersion ��ȡ������ʽ�İ汾�š�
 * - GetWindowsVersion ��ȡWindows�汾��Ϣ��
 * - IsWindows8Or8Point1 �ж��Ƿ���win8����win8.1��
 * - isWow64 �жϱ������Ƿ���wow64���̡�
 * - IsOsWindowsVistaorLater �жϲ���ϵͳ�Ƿ���vista�Լ�֮��İ汾��
 *
 * \author fanduoduo
 * \date 2016/11/10
 * \version 1.0
 */

#pragma once

#include <windows.h>
#include <string>
using std::string;

/**
 * \defgroup WIN_VER ��ȡwindows�汾��Ϣ
 * \brief ��ȡwindows�汾��Ϣ
 * \{
 */

/**
 * \brief ��ȡ������ʽ�İ汾��
 * \param [out] major �߰汾��
 * \param [out] minor �Ͱ汾��
 * \return �ɹ�����true���򷵻�false.
 */
bool GetWinMajorMinorVersion(DWORD& major, DWORD& minor);


/**
 * \brief ��ȡWindows�汾��Ϣ
 * \param[out][opt] pOsVer ϵͳ�汾��Ϣ,�粻��Ҫ�����Ϣ���Դ���NULL��
 * \param[out][opt] pSysInfo ϵͳ��Ϣ���������Ҫ�����Ϣ���Դ���NULL��
 * \return �����ַ�����ʽ�İ汾��Ϣ����Я��SP��Ϣ������windows 7 sp1��
 * \remark 
 * ��������ֵΪ��%WinOSVer% Service Pack x.����Windows 10 Server Service Pack 3.
 * ����WinOSVer�������£�
 *   - Windows 10 Server 
 *   - Windows 10
 *   - Windows Server 2012 R2
 *   - Windows 8.1
 *   - Windows Server 2012
 *   - Windows 8
 *   - Windows Server 2008 R2
 *   - Windows 7
 *   - Windows Server 2008
 *   - Windows Vista
 *   - Windows XP x64
 *   - Windows Server 2003
 *   - Windows XP
 *   - Windows 2000
 * ���û��SP��û�к����Service Pack x.
 */
std::string GetWindowsVersion(OSVERSIONINFOEX* pOsVer,SYSTEM_INFO* pSysInfo);


/**
 * \brief �ж��Ƿ���win8����win8.1
 * \return �����win8����win8.1����TRUE,���򷵻�FALSE.
 */
BOOL IsWindows8Or8Point1();


/**
 * \brief �жϱ������Ƿ���wow64����
 * 
 * \return �����������WOW64���̷���TRUE,���򷵻�FALSE.
 * \note ������������32λ����ʱ�����̵ķ���ֵ���������ж��Ƿ���64λϵͳ��
 */
BOOL isWow64();


/**
 * \brief ͨ����ȡOS�汾���Ƿ� > 5�жϲ���ϵͳ�Ƿ���vista�Լ�֮��İ汾��
 * 
 * \return : ����Ƿ���TRUE�����򷵻�FALSE��
 */
BOOL IsOsWindowsVistaorLater();

/**
 * \}
 */
