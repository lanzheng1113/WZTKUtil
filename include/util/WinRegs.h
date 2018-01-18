#pragma once
#include <string>
#include <windows.h>

/**
 * \addtogroup REG_FUN 
 * \{
 */

/**
 * \brief 获取HKEY_CURRENT_USER的正式路径.通过获取当前进程用户的SID，获取HKCU在HKUSER中的真实路径.
 * 例如“HKEY_USERS\S-1-5-21-1347714902-2505543936-4047459812-1000”
 * 
 * \return 返回HKEY_CURRENT_USER的路径，如果为空表示获取的过程中发生了错误，可以使用GetLastError()获取错误原因。
 * \note 此函数不可以用于服务进程，因为服务进程的用于是SYSTEM。
 * 对于服务进程来说没有登录用户的概念。
 */
std::string GetHKCURealPath();


/**
 * \brief 使当前进程获取注册表键的所有权以访问注册表键值.
 * \param hPrefKey 根键，例如HKEY_CURRENT_USER
 * \param lpczSubKey 需要获取所有权的注册表键所在的路径。
 * \return 成功返回0，否则返回一个错误ID（GetLastError）。
 */
DWORD TakeObjectsOwnerShip( HKEY hPrefKey, LPCSTR lpczSubKey );



/**
 * \brief 设置一个注册表的键值为指定的DWORD值
 * \param hKeyRoot HKLM/HKCU等根键
 * \param regPath 路径
 * \param keyName 键
 * \param val 值
 * \param WriteTo64bitRegPath 此路径是否为64位系统键值
 * \return None
 */
void RegistrySetValueDowrd(HKEY hKeyRoot,char* regPath,char* keyName,DWORD val,BOOL WriteTo64bitRegPath);


/**
 * \brief 设置一个注册表的键值为指定的字符串值
 * \param hKeyRoot HKLM/HKCU等根键
 * \param regPath 路径
 * \param keyName 键
 * \param val 值
 * \param WriteTo64bitRegPath 此路径是否为64位系统键值
 * \return None
 */
void RegistrySetValueString(HKEY hKeyRoot,char* regPath,char* keyName,char* val,BOOL WriteTo64bitRegPath);

/**
 * \}
 */