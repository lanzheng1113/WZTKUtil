#pragma once
#include <vector>
#include <string>

#ifndef OUT
#define OUT
#endif

/**
 * \addtogroup STRINGS
 * \{
 */

/**
 * \brief ��һ��std::vector<std::wstring>����inputת��Ϊ��СΪcbBufferMaxLen��WCHAR����outBuffer��
 * ʹ��NULL��Ϊ�ָ������������һ��λ�ö����һ��NULL
 *
 * \param outBuffer:���ת�����ַ�������Ļ�����
 * \param cbBufferMaxLen : outBuffer�Ĵ�С���ֽ�Ϊ��λ�������ַ�������
 * \param input : ��Ҫת�����ַ�����
 * \remark 
 * �������һ���WCharArrayToStringVector���������DLL��EXE֮�䴫���ַ������顣
 */
void StringVectorToWCharArray( 
	OUT wchar_t* outBuffer,
	int cbBufferMaxLen,
	const std::vector<std::wstring>& input
	);

/**
 * \brief ������StringVectorToWCharArray������ַ�������ת�����ַ������� @see StringVectorToWCharArray 
 * \remark 
 * �������һ���WCharArrayToStringVector���������DLL��EXE֮�䴫���ַ������顣
 */
std::vector<std::wstring> WCharArrayToStringVector( wchar_t* buf, int cbBuf );

/**
 * \brief ��ȡ����������ֵ��
 */
std::wstring GetEnvVar( IN const std::wstring& wstrEnvironVar );

/**
 * \brief ��չһ���ַ����������е�"%��������%"�滻Ϊ����·����
 */
BOOL ExpandEnvVar(IN OUT std::wstring& wszPath);

/**
 * \}
 */