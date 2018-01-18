#pragma once

#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(A) (sizeof(A)/sizeof((A)[0]))
#endif

#ifndef OUT
#define OUT
#endif

#include <vector>
#include <string>


/**
 * \defgroup ZIPS ѹ���ͽ�ѹ��
 * \brief ѹ���ͽ�ѹ��
 * \{
 */

/**
 * \brief ��lpszFilePathָ����ZIP�ļ��ͷŵ�Ŀ��Ŀ¼lpszUnzipPath�С�ReleaseFiles��Ϊ���������¼�����ͷŵ������ļ���ȫ·������
 * \return �ɹ�����TRUE���򷵻�FALSE��
 */
BOOL UnzipFileToPath(LPCSTR lpszFilePath, LPCSTR lpszUnzipPath, OUT std::vector<std::string>& ReleaseFiles);

/**
 * \}
 */