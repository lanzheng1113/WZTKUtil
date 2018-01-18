/**
 * \copyright (C)2016 �������
 * \file FileSignature.h
 * \brief ������ȡǩ����Ϣ�Ľӿڡ�
 *
 * - v1.0 
 *   -# GetSignatureInfo ��ȡһ��PE�ļ�������ǩ����Ϣ
 *
 * \author FDD
 * \date 2017/8/15
 * \version 1.0
 */
#pragma once
#include <string>

#ifndef OUT
#define OUT
#endif

/**
 * \defgroup PE_SIGN ��ȡPE�ļ�������ǩ����Ϣ
 * \brief ��ȡPE�ļ�������ǩ����Ϣ
 * \{
 */

/**
 * \brief ǩ����Ϣ
 */
struct SignerCertificate
{
	std::wstring IssuerName;	///< ֤��䷢��
	std::wstring SubjectName;   ///< ǩ�����������磺GuangZhou KuGou Computer Technology Co.,Ltd.
};

/**
 * \brief ��ȡһ��PE�ļ�������ǩ����Ϣ
 * \param path �ļ�·��
 * \param SignerInfo ǩ����Ϣ
 * \return �ɹ�����0�����򷵻�����ֵ��
 */
int GetSignatureInfo(const std::wstring& path, OUT SignerCertificate &SignerInfo);

/**
 * \}
 */