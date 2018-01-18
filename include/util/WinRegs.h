#pragma once
#include <string>
#include <windows.h>

/**
 * \addtogroup REG_FUN 
 * \{
 */

/**
 * \brief ��ȡHKEY_CURRENT_USER����ʽ·��.ͨ����ȡ��ǰ�����û���SID����ȡHKCU��HKUSER�е���ʵ·��.
 * ���硰HKEY_USERS\S-1-5-21-1347714902-2505543936-4047459812-1000��
 * 
 * \return ����HKEY_CURRENT_USER��·�������Ϊ�ձ�ʾ��ȡ�Ĺ����з����˴��󣬿���ʹ��GetLastError()��ȡ����ԭ��
 * \note �˺������������ڷ�����̣���Ϊ������̵�������SYSTEM��
 * ���ڷ��������˵û�е�¼�û��ĸ��
 */
std::string GetHKCURealPath();


/**
 * \brief ʹ��ǰ���̻�ȡע����������Ȩ�Է���ע����ֵ.
 * \param hPrefKey ����������HKEY_CURRENT_USER
 * \param lpczSubKey ��Ҫ��ȡ����Ȩ��ע�������ڵ�·����
 * \return �ɹ�����0�����򷵻�һ������ID��GetLastError����
 */
DWORD TakeObjectsOwnerShip( HKEY hPrefKey, LPCSTR lpczSubKey );



/**
 * \brief ����һ��ע���ļ�ֵΪָ����DWORDֵ
 * \param hKeyRoot HKLM/HKCU�ȸ���
 * \param regPath ·��
 * \param keyName ��
 * \param val ֵ
 * \param WriteTo64bitRegPath ��·���Ƿ�Ϊ64λϵͳ��ֵ
 * \return None
 */
void RegistrySetValueDowrd(HKEY hKeyRoot,char* regPath,char* keyName,DWORD val,BOOL WriteTo64bitRegPath);


/**
 * \brief ����һ��ע���ļ�ֵΪָ�����ַ���ֵ
 * \param hKeyRoot HKLM/HKCU�ȸ���
 * \param regPath ·��
 * \param keyName ��
 * \param val ֵ
 * \param WriteTo64bitRegPath ��·���Ƿ�Ϊ64λϵͳ��ֵ
 * \return None
 */
void RegistrySetValueString(HKEY hKeyRoot,char* regPath,char* keyName,char* val,BOOL WriteTo64bitRegPath);

/**
 * \}
 */