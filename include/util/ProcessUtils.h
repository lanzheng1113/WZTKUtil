/**
 * \copyright (C)2016 万兆天空
 * \file ProcessUtils.h
 * \brief 声明一些和读取进程信息有关的函数
 *
 * v1.0
 * - IsProcessExists 判断指定PID的进程是否存在。
 * - GetPathFromProcessId 获取指定PID的进程的路径。
 * - GetProcessIdFromPath 获取第一个匹配指定进程路径的进程ID 
 * - DosDevicePath2LogicalPath 将DOS设备路径（\\Device\\HarddiskVolume1\x86.sys）转换为逻辑路径（C:\x86.sys）
 *
 * \author fanduoduo
 * \date 2016/11/10
 * \version 1.0
 */

#pragma once
#include <windows.h>
#include <string>

#ifndef OUT
#define OUT
#endif

/**
 * \defgroup PROCE_INFO 获取进程信息
 * \{
 */

/**
 * \brief 判断指定PID的进程是否存在
 * \return 存在返回TRUE，否则返回FALSE
 */
BOOL IsProcessExists(DWORD pid);


/**
 * \brief 获取指定PID的进程的路径。
 * \return 找到则返回指定进程的路径，否则返回空字符串
 */
std::string GetPathFromProcessId(DWORD pid);


/**
 * \brief 获取第一个匹配指定进程路径的进程ID
 * \return 找到则返回PID，否则返回0
 */
DWORD GetProcessIdFromPath(const std::string& strFilePath);


/**
 * \brief 将DOS设备路径（\\Device\\HarddiskVolume1\x86.sys）转换为逻辑路径（C:\x86.sys）
 * \return 如转换失败则返回空字符串。
 */
std::string DosDevicePath2LogicalPath(const wchar_t* lpszDosPath);	

/**
 * /}
 */