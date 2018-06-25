#pragma once

#include <string>
using std::wstring;

class CWinINI
{
public:
	void SetIniFile(const wchar_t* szIniFile) { m_wstrIniFile = szIniFile; }
	void SetSectionName(const wchar_t* szSection) { m_wstrSection = szSection; }
	void DeleteSection(const wchar_t* szSection);
	void WriteString( const wchar_t* szKey, const wchar_t* szValue);
	/**
	 * \brief 读字符串，最多支持4095个字符。
	 * 
	 * \param INI的键
	 * \return 对应字符串值
	 */
	std::wstring ReadString( const wchar_t* key );
protected:
private:
	std::wstring m_wstrIniFile;
	std::wstring m_wstrSection;
};