#include "windows.h"
#include "util/crypt.h"



const char enkey[] = "dxxikwoxnixbccvamiwopoikdnwdvnwezdelfgac";
void SimpleXor_Crype(char *dest, const char *src, int len)
{
	if ((dest == NULL )||(src == NULL)||(len <= 0))
	{
//		ASSERT(0);
		return;
	}

	int iKey = 0;

	__try
	{
		for (int i = 0; i != len; i++)
		{
			dest[i] = (src[i] ^ (enkey[iKey] + len));
			if (iKey == sizeof(enkey) - 1)
			{
				iKey = 0;
			}
			else
			{
				iKey++;
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
//		ASSERT(0);
	}
}