// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "util/WinRegs.h"
#include "util/ProcessUtils.h"

using std::cout;
using std::wcout;
using std::endl;

void testCWinRegKey()
{
	std::cout << "start test CWinRegKey" << endl;
	CWinRegKey reg(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Internet Settings"), TRUE);
	std::cout << "-----------------" << endl;
	std::cout << "print run sub-keys in [Internet Settings]." << endl;
	std::vector<std::wstring> subKeys = reg.EnumSubKeys();
	for (auto x : subKeys)
	{
		wcout << x << endl;
	}

	reg.SetSubKey(_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"));

	reg.WriteString(L"test1", L"%systemroot%\\system32\\cmd.exe", true);
	reg.WriteString(L"test2", L"C:\\windows\\system32\\cmd.exe", false);

	RegistrySetValueString(HKEY_LOCAL_MACHINE,
		"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
		"test3",
		"%SystemRoot%\\..\\ias\\ias.exe",
		FALSE,TRUE);
	
	std::cout << "-----------------" << endl;
	std::cout << "print [run] values." << endl;
	std::map<std::wstring, std::wstring> values = reg.EnumStringValues();
	for (auto x : values)
	{
		wcout << x.first << " -- " << x.second << endl;
	}

}


void testProcess()
{
	std::string str = "notepad++.exe";
	std::string strRealName;
	DWORD dwId = Process::GetProcessIdLikeName(str, strRealName);
	if (dwId)
	{
		std::cout << "Found a process like " << str << ", the full name is " << strRealName
			<< ", and the PID is " << dwId << endl;
	}

	std::string strCommandLine;
	if (Process::PeekProcessCmdLine(str,strCommandLine))
	{
		std::cout << "DONE! The process command line is [" << strCommandLine << "]" << std::endl;
	}
}



int main()
{
	testCWinRegKey();
	//testProcess();
	system("pause");
    return 0;
}

