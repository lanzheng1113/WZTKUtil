/**
 * \copyright (C)2016 �������
 * \file StringConverter.h
 * \brief ����utf8�����ϵͳĬ���ַ��������ת������������ϵͳ��ӦGB2312��
 * 
 * - v1.0
 *   -# LocalStringToUtf8 ϵͳĬ���ַ���ת��Ϊutf-8��
 *   -# UTF8ToLocalString utf-8�ַ���ת��ΪϵͳĬ�ϡ�
 * - v1.1
 *   -# UTF8ToUnicode utf-8ת��ΪUNICODE
 *   -# UnicodeToUTF8 Unicodeת��ΪUTF-8
 *
 * \author FDD
 * \date 2017/8/17
 * \version 1.1
 */
#pragma once

#include <string>
using std::string;
using std::wstring;

/**
 * \brief �ַ���ת����
 * \ingroup  STRINGS
 */
class StringConverter
{
public:
	/**
	 * \brief ϵͳĬ��ת��Ϊutf-8
	 */
	static string LocalStringToUtf8( const string& localString );
	/**
	 * \brief utf-8ת��ΪϵͳĬ��
	 */
	static string UTF8ToLocalString( const string& utfString );
	/**
	 * \brief utf-8ת��ΪUNICODE
	 */
	static std::wstring UTF8ToUnicode( const string& utfString );
	/**
	 * \brief UNICODEת��Ϊutf-8
	 */
	static std::string UnicodeToUTF8(const wstring& str);
protected:
private:
};