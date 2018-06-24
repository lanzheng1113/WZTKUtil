#pragma once
#include <string>
#include <windows.h>
#include <string>
#include <map>
#include <vector>

using std::wstring;
using std::map;
using std::vector;

#ifndef OUT
#define OUT
#endif
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
BOOL RegistrySetValueDowrd(HKEY hKeyRoot, const char* regPath, const char* keyName,DWORD val,BOOL WriteTo64bitRegPath);


/**
 * \brief ����һ��ע���ļ�ֵΪָ�����ַ���ֵ
 * \param hKeyRoot HKLM/HKCU�ȸ���
 * \param regPath ·��
 * \param keyName ��
 * \param val ֵ
 * \param WriteTo64bitRegPath ��·���Ƿ�Ϊ64λϵͳ��ֵ
 * \return None
 */
BOOL RegistrySetValueString(HKEY hKeyRoot,const char* regPath, const char* keyName, const char* val,BOOL WriteTo64bitRegPath, bool isExpandStrType = false);

/**
 * \}
 */

class CWinRegKey
{
public:
	CWinRegKey(HKEY keyRoot, const wchar_t* subKey, BOOL bIs64) 
	{ 
		m_rootKey = keyRoot;
		m_subKey = subKey;
		m_bIs64 = bIs64;
	}
	~CWinRegKey() { ; }
public:
	/**
	 * \brief Set root key.
	 * \param keyRoot The root key.
	 */
	void SetRootKey(HKEY keyRoot) { m_rootKey = keyRoot; }
	/**
	 * \brief Set sub-key.
	 * \param subKey sub-key
	 */
	void SetSubKey(const wchar_t* subKey) { m_subKey = subKey; }
	/**
	 * \brief �趨�Ƿ�Ϊ64λ��ע���·��
	 */
	void SetIs64Entry(BOOL bIs64) { m_bIs64 = bIs64; }
	/**
	 * \brief Write an integer value to registry entry (with REG_DOWRD type).
	 * \param key The registry key.
	 * \param val The registry value.
	 */
	BOOL WriteInteger(const wchar_t* key, int val);

	/**
	 * \brief ��һ������
	 * 
	 * \param
	 * \return
	 */
	BOOL ReadInteger(const wchar_t* key, OUT int* val);
	/**
	 * \brief Write an string value to registry entry (with REG_STRING type)
	 * \param key The registry key.
	 * \param val The registry value.
	 */
	BOOL WriteString(const wchar_t* key, const wchar_t* val, bool isExpandStrType=false);

	/**
	 * \brief ��һ���ַ�����
	 * 
	 * \param
	 * \return
	 */
	BOOL ReadString(const wchar_t* key, OUT wchar_t* val, int nSize);

	/**
	 * \brief ������ǰ�����µ�����ֵ�ļ�ֵ��
	 * 
	 * \return ���ص�ǰ�����µļ�ֵ��
	 */
	std::map<std::wstring, std::wstring> EnumStringValues();

	/**
	 * \brief ������ǰ�����µ���������
	 * 
	 * \return ���ص�ǰ�����µ��������
	 */
	std::vector<std::wstring> EnumSubKeys();

	/**
	 * \brief Create a sub-key under root key specified by "keyRoot" parameter.
	 */
	static BOOL CreateSubKey(HKEY keyRoot, const wchar_t* subKey);

	// delete sub key.
	BOOL DeleteSubKey();

	// ɾ��ָ�����ֵ�ֵ
	BOOL DeleteValue(const wchar_t* pszValueName);

	/**
	 * \brief Adjust a token's privilege.
	 * 
	 * \param hToken access token handle
	 * \param nameOfPrivilege name of privilege to enable/disable
	 * \param bEnablePrivilege to enable or disable privilege
	 * \return �ɹ�����TRUE�����򷵻�FALSE������GetLastError��ȡ�����롣
	 */
	static BOOL SetPrivilege(HANDLE hToken, LPCWSTR nameOfPrivilege, BOOL bEnablePrivilege);
	/**
	 * \brief Load registry from a file.
	 * 
	 * \param KeyRoot
	 * \param lpSubKey
	 * \param lpFilePath
	 * \return
	 */
	static BOOL LoadKey(HKEY KeyRoot, LPCWSTR lpSubKey, LPCWSTR lpFilePath);

	/**
	 * \brief Unload Registry key.
	 */
	static BOOL UnLoadKey(HKEY KeyRoot, LPCWSTR lpSubKey);

private:
	BOOL DeleteSubKeyImp(HKEY hKey, LPWSTR subKey);

	CWinRegKey();
	CWinRegKey(const CWinRegKey&);
	CWinRegKey& operator=(const CWinRegKey& rh) {
		m_rootKey = rh.m_rootKey;
		m_subKey = rh.m_subKey;
		m_bIs64 = rh.m_bIs64;
		return *this; 
	}

private:
	HKEY m_rootKey;
	std::wstring m_subKey;
	BOOL m_bIs64;
};

