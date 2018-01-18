/**
 * \copyright (C)2016 �������
 * \file MD5Checksum.h
 * \brief ���� CMD5Checksum ����װMD5�ļ�У����ַ���У��
 * \version 1.1
 * \author duo
 * \date 20160826
 */
#pragma once
#include <Windows.h>

#include <string>
using std::wstring;
using std::string;

/**
 * \defgroup MD5CHECKS MD5У��
 * \{
 */

/**
 * \class CMD5Checksum
 * \brief �ṩMD5�ļ�У����ַ���У��Ľӿڡ�
 * \ingroup MD5У��
 */
class CMD5Checksum  
{
public:
	/**
	 * \brief ��ȡ�ַ�����MD5ֵ
	 * \param strString ��ҪУ����ַ���
	 * \return ���ؽ��ֵ
	 */
	static string GetMD5OfString(const string& strString);
	/**
	 * \brief ��ȡ�ļ���MD5ֵ
	 * \param strFilePath �ļ�·��
	 * \return �����ȡMD5ʧ�ܣ����ؿ��ַ�����
	 */
	static wstring GetMD5(const wstring& strFilePath);

	/**
	 * \brief ����һ����������MD5ֵ��
	 */
	static string GetMD5(char* pBuff, unsigned long nleng);
	
protected:
	//constructor/destructor
	CMD5Checksum();
	virtual ~CMD5Checksum() {};
	//RSA MD5 implementation
	void Transform(BYTE Block[64]);
	void Update(BYTE* Input, ULONG nInputLen);
	string Final();
	inline DWORD RotateLeft(DWORD x, int n);
	inline void FF( DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);
	inline void GG( DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);
	inline void HH( DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);
	inline void II( DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);
	//utility functions
	inline void DWordToByte(BYTE* Output, DWORD* Input, UINT nLength);
	inline void ByteToDWord(DWORD* Output, BYTE* Input, UINT nLength);
private:
	BYTE  m_lpszBuffer[64];	//input buffer
	ULONG m_nCount[2];			//number of bits, modulo 2^64 (lsb first)
	ULONG m_lMD5[4];			//MD5 checksum
};

/**
 * \}
 */