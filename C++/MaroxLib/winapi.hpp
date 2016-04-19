#pragma once

#include <chrono>
#include <sstream>
//#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <random>
#include <Windows.h>
#include <tlhelp32.h>
#include <Shlwapi.h>
#include <tchar.h>
#include <Lmcons.h>
#include <sys/stat.h>
#include <string>
#include <limits>
#define WIN32_LEAN_AND_MEAN 
#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ) 

#pragma comment(lib, "Version.lib")
#pragma comment(lib, "Shlwapi.lib")

#include "FileVersion.hpp"
#include "console.hpp"
#include "autostart.hpp"

//
#include "convert.hpp"

namespace Marox
{
	namespace Tools
	{
		namespace WinAPI
		{
			std::string getFullFilePath(const std::string& fileName)
			{
				wchar_t buf[MAX_PATH] = { 0 };
				GetFullPathName(Marox::Tools::Convert::string_to_wstring(fileName).c_str(), MAX_PATH, buf, NULL);

				std::wstring ws;
				for (size_t i = 0; i < MAX_PATH; i++)
				{
					if (buf[i] != '\0')
					{
						ws += buf[i];
					}
					else
					{
						break;
					}
				}

				return Marox::Tools::Convert::wstring_to_string(ws);
			}

			//todo: inny folder przy uruchamianiu w VS!
			std::string ExePath()
			{
				wchar_t buffer[MAX_PATH];
				GetModuleFileName(NULL, buffer, MAX_PATH);
				std::string::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
				return Marox::Tools::Convert::wstring_to_string(std::wstring(buffer).substr(0, pos));
			}
			std::string ExePath2()
			{
				TCHAR infoBuf[MAX_PATH];
				// Get the current working directory
				if (!GetCurrentDirectory(MAX_PATH, infoBuf))
					return std::string();
				//printf("Your current directory is: %S\n", infoBuf);
				return Marox::Tools::Convert::wstring_to_string(std::wstring(infoBuf));
			}

			std::string getComputerName()
			{
				std::wstring w;
				wchar_t buffer[MAX_COMPUTERNAME_LENGTH + 1];
				DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
				if (GetComputerName(buffer, &size))
				{
					w = std::wstring(buffer, size);
					return Marox::Tools::Convert::wstring_to_string(w);
				}
				else
				{
					return Marox::Tools::Convert::wstring_to_string(L"UNKNOWN");
				}

			}
			std::string getCurrentUserName()
			{
				TCHAR username[UNLEN + 1];
				DWORD size = UNLEN + 1;
				GetUserName((TCHAR*)username, &size);

				std::stringstream ss;

				for (int i = 0; i < size; i++)
					if (isalpha(username[i]))
						ss << (char)(username[i]);

				return ss.str();
			}
			std::string getTemporaryFile()
			{
				TCHAR lpTempPathBuffer[MAX_PATH];
				TCHAR szTempFileName[MAX_PATH];
				GetTempPath(MAX_PATH, lpTempPathBuffer);
				GetTempFileName(lpTempPathBuffer, TEXT("tmp"), 0, szTempFileName);

				std::string path = Marox::Tools::Convert::wstring_to_string(szTempFileName);
				return path;
			}
			std::string getTemporaryFilePath()
			{
				TCHAR lpTempPathBuffer[MAX_PATH];
				GetTempPath(MAX_PATH, lpTempPathBuffer);

				std::string path = Marox::Tools::Convert::wstring_to_string(lpTempPathBuffer);
				return path;
			}
			std::string getLastError_AsString()
			{
				//Get the error message, if any.
				DWORD errorMessageID = ::GetLastError();
				if (errorMessageID == 0)
					return std::string(); //No error message has been recorded

				LPSTR messageBuffer = nullptr;
				size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

				std::string message(messageBuffer, size);

				//Free the buffer.
				LocalFree(messageBuffer);

				return message;
			}
			HANDLE getProcessByName(PCWSTR _processName)
			{
				HANDLE p = NULL;
				PROCESSENTRY32 entry;
				entry.dwSize = sizeof(PROCESSENTRY32);

				HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

				if (Process32First(snapshot, &entry) == TRUE)
				{
					while (Process32Next(snapshot, &entry) == TRUE)
					{
						if (_tcsicmp(entry.szExeFile, _processName) == 0)
						{
							p = OpenProcess(SYNCHRONIZE, FALSE, entry.th32ProcessID);
						}
					}
				}

				return p;
			}
			DWORD getTargetThreadIDFromProcessName(PCWSTR _processName)
			{
				PROCESSENTRY32 pe;
				HANDLE thSnapShot;
				BOOL retval, ProcFound = false;

				thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
				if (thSnapShot == INVALID_HANDLE_VALUE)
				{
					return NULL;
				}

				pe.dwSize = sizeof(PROCESSENTRY32);

				retval = Process32First(thSnapShot, &pe);
				while (retval)
				{
					if (StrStrI(pe.szExeFile, _processName))
					{
						return pe.th32ProcessID;
					}
					retval = Process32Next(thSnapShot, &pe);
				}
				return NULL;
			}
		}
	}
}