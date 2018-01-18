/**
 * \file CommonTools.h 
 * \brief ���ļ�����CRegKeyCloseHelper��
 * \version 1.0.0.1
 * \author duo
 * \date 20160823
 */

#pragma once

/**
 * @defgroup REG_FUN ע������
 * @{
 */

/**
 * @class CRegKeyCloseHelper
 * \brief ������������뿪������ʱ�ر�һ��ע����
 * 
 */
class CRegKeyCloseHelper
{
public:
	/**
	 * CRegKeyCloseHelper�Ĺ��캯����Ҫ����һ���Ѿ��򿪵�HKEY�����뿪��������Զ��ر�����
	 * \param hk �뿪������ʱ��Ҫ�رյ�ע������
	 */
	CRegKeyCloseHelper(HKEY hkey);
	~CRegKeyCloseHelper();
protected:
private:
	HKEY _hkey;
};

/** @} */