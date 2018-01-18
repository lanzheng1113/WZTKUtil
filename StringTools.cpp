#include <Windows.h>
#include <string>
#include <vector>
#include "util/StringTools.h"
#include "util/Path.h"

void StringVectorToWCharArray( OUT wchar_t* outBuffer,int cbBufferMaxLen,const std::vector<std::wstring>& input)
{
	if (cbBufferMaxLen < 2)
	{
		return;
	}
	if (input.empty())
	{
		outBuffer[0] = 0;
		outBuffer[1] = 0;
		return;
	}
	int index = 0;
	int iStringLen = 0;
	bool isFirstOne = true;
	for (int i=0; i!=input.size(); i++)
	{
		std::wstring m_strInstalledBrName = input[i];
		if (m_strInstalledBrName.empty())
		{
			continue;
		}
		if (!isFirstOne)
		{
			//��һ��֮ǰ���ӷָ���
			outBuffer[index] = 0;
			index ++;
		}
		else
		{
			isFirstOne = false;
		}

		iStringLen = m_strInstalledBrName.length();
		if (cbBufferMaxLen < (index+iStringLen+1)*sizeof(wchar_t))
		{
			//log("���뻺����̫С��");
			return;
		}
		memcpy(outBuffer+index,m_strInstalledBrName.c_str(),iStringLen*sizeof(wchar_t));
		index += iStringLen;
	}
	//�����һ��λ���ٶ����һ��0
	outBuffer[index] = 0;
	//log("�ɹ���֯������塣");
	return;
}


std::vector<std::wstring> WCharArrayToStringVector(wchar_t* buf,int cbBuf)
{
	std::vector<std::wstring> ret;
	if (cbBuf == 0)
	{
		return ret;
	}
	if(buf[0]=='\0')
		return ret;       //�����һ���ַ�����0����˵��ini��һ����Ҳû��

	wchar_t *pBrowserName;	//�����ҵ���ĳ�������ַ������׵�ַ
	int i;					//iָ������buf��ĳ��λ�ã���0��ʼ��˳�����
	int j=0;				//j����������һ�������ַ������׵�ַ����ڵ�ǰi��λ��ƫ����
	int count=0;			//ͳ�ƽڵĸ���

	for(i=0; i<cbBuf-1; i++,j++)
	{
		if( buf[i] == 0 )
		{
			pBrowserName = &buf[i-j]; //�ҵ�һ��0����˵��������ַ���ǰ������j��ƫ����������һ������������׵�ַ
			j = -1; //�ҵ�һ�����������j��ֵҪ��ԭ����ͳ����һ�����������ַ��ƫ��������-1����Ϊ��������ַ��������һ���ַ�0����ֹ����
			ret.push_back(pBrowserName);//�Ѷ�������ֵ����vec
			if( buf[i+1]==0 )
			{
				break;      //���������ڵ��ַ�����0ʱ�������е�������������ҵ���ѭ����ֹ
			} 
		}			
	}   
	return ret;
}

BOOL ExpandEnvVar( IN OUT std::wstring& wszPath )
{
	std::wstring::size_type pos1, pos2;
	std::wstring wszVar, wszDir;
	int len;

	pos1 = pos2 = 0;
	do 
	{
		pos1 = wszPath.find_first_of(TEXT('%'), pos2);
		if (pos1 == std::wstring::npos){
			break;
		}

		pos2 = wszPath.find_first_of(TEXT('%'), pos1 + 1);
		if (pos2 == std::wstring::npos){
			break;
		}

		len = pos2 - pos1 - 1;
		wszVar = wszPath.substr(pos1+1, len);
		wszDir = GetEnvVar(wszVar.c_str());    //��ȫ�ֱ�����չ������
		if (!wszDir.empty())
		{
			Path::PathRemoveBackslash(wszDir);
			len = pos2 - pos1 + 1;
			wszPath.replace(pos1, len, wszDir);
		}

	} while (1);

	return TRUE;
}

std::wstring GetEnvVar( IN const std::wstring& wstrEnvironVar )
{
	wchar_t wszPath[MAX_PATH + 1];
	memset(wszPath, 0, sizeof(wszPath));
	GetEnvironmentVariableW(wstrEnvironVar.c_str(), wszPath, MAX_PATH);
	return wszPath;
}

