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

#include "convert.hpp"

#define CATCH catch(const std::exception& ex)
#define WAIT_FOR_ENTER() std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');



namespace Marox
{
	namespace Tools
	{
		namespace Autostart
		{
			/// <summary>
			/// Checks whether application is registered for autostart
			/// </summary>
			/// <param name="pszAppName">Application name</param>
			/// <returns></returns>
			BOOL isProgramRegisteredForStartup(PCWSTR pszAppName)
			{
				HKEY hKey = NULL;
				LONG lResult = 0;
				BOOL fSuccess = TRUE;
				DWORD dwRegType = REG_SZ;
				wchar_t szPathToExe[MAX_PATH] = {};
				DWORD dwSize = sizeof(szPathToExe);

				lResult = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey);

				fSuccess = (lResult == 0);

				if (fSuccess)
				{
					lResult = RegGetValueW(hKey, NULL, pszAppName, RRF_RT_REG_SZ, &dwRegType, szPathToExe, &dwSize);
					fSuccess = (lResult == 0);
				}

				if (fSuccess)
				{
					fSuccess = (wcslen(szPathToExe) > 0) ? TRUE : FALSE;
				}

				if (hKey != NULL)
				{
					RegCloseKey(hKey);
					hKey = NULL;
				}

				return fSuccess;
			}
			/// <summary>
			/// Registers program for autostart
			/// </summary>
			/// <param name="_appName">Application name</param>
			/// <returns></returns>
			BOOL registerMyProgramForStartup(PCWSTR _appName)
			{
				PCWSTR args = L"-foobar";

				wchar_t szPathToExe[MAX_PATH];
				GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
				PCWSTR pathToExe = (PCWSTR)szPathToExe;

				HKEY hKey = NULL;
				LONG lResult = 0;
				BOOL fSuccess = TRUE;
				DWORD dwSize;

				const size_t count = MAX_PATH * 2;
				wchar_t szValue[count] = {};


				wcscpy_s(szValue, count, L"\"");
				wcscat_s(szValue, count, pathToExe);
				wcscat_s(szValue, count, L"\" ");

				if (args != NULL)
				{
					// caller should make sure "args" is quoted if any single argument has a space
					// e.g. (L"-name \"Mark Voidale\"");
					wcscat_s(szValue, count, args);
				}

				lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);

				fSuccess = (lResult == 0);

				if (fSuccess)
				{
					dwSize = (wcslen(szValue) + 1) * 2;
					lResult = RegSetValueExW(hKey, _appName, 0, REG_SZ, (BYTE*)szValue, dwSize);
					fSuccess = (lResult == 0);
				}

				if (hKey != NULL)
				{
					RegCloseKey(hKey);
					hKey = NULL;
				}

				return fSuccess;
			}
		}
		namespace Console
		{
			/// <summary>
			/// Hides the console window.
			/// </summary>
			void hideConsoleWindow()
			{
				ShowWindow(GetConsoleWindow(), SW_HIDE);
			}
			/// <summary>
			/// Shows the console window.
			/// </summary>
			void showConsoleWindow()
			{
				ShowWindow(GetConsoleWindow(), SW_SHOW);
			}
			bool progressBar(double d)
			{
				int max = 50;
				std::cout << std::fixed << std::setprecision(2) << d << "% ";
				std::cout << " [";
				int steps = (int)((d / 100) * max);
				for (int i = 0; i < steps; i++)
				{
					std::cout << "=";
				}
				std::cout << ">" << "\r";
				if (steps == max)
				{
					//std::cout << std::endl;
				}

				return 0;
			}
		}
		/// <summary>
		/// Returns current time and date
		/// </summary>
		/// <returns>Returns <c>string</c> in the following format: <c>YYYY-MM-DD HH:MM:SS</c></returns>
		std::string return_current_time_and_date()
		{
			auto now = std::chrono::system_clock::now();
			auto in_time_t = std::chrono::system_clock::to_time_t(now);

			std::stringstream ss;
			ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
			return ss.str();
		}
		bool isInt(const std::string& s)
		{
			if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
				return false;

			char * p;
			strtol(s.c_str(), &p, 10);
			return (*p == 0);
		}

		struct FileVersionInfo
		{
			FileVersionInfo(int _MajorVersion, int _MinorVersion, int _BuildNumber, int _RevisionNumber) : MajorVersion(_MajorVersion), MinorVersion(_MinorVersion), BuildNumber(_BuildNumber), RevisionNumber(_RevisionNumber)
			{}

			//todo: const & zrobiæ operator= !
			int MajorVersion;
			int MinorVersion;
			int BuildNumber;
			int RevisionNumber;
			//todo: add: parse from string?

			std::string ToString() const
			{
				std::stringstream ss;
				ss << this->MajorVersion << "." << this->MinorVersion << "." << this->BuildNumber << "." << this->RevisionNumber;
				return ss.str();
			}

			explicit operator std::string() const 
			{
				return this->ToString();
			}

			static FileVersionInfo* Parse(const std::string& str)
			{
				int dot[3] = { 0, 0, 0 };
				int cnt = 0;
				for (int i = 0; i < str.length(); i++)
				{
					if (str[i] == '.')
					{
						dot[cnt] = i;
						cnt++;
					}
					if (cnt > 2)
						break;
				}

				if (cnt != 3)
					return nullptr;

				for (const auto& i : dot)
				{
					if (i == 0)
						return nullptr;
				}

				std::string major, minor, build, revision;
				for (int i = 0; i < dot[0]; i++)
				{
					major += str[i];
				}
				for (int i = dot[0] + 1; i < dot[1]; i++)
				{
					minor += str[i];
				}
				for (int i = dot[1] + 1; i < dot[2]; i++)
				{
					build += str[i];
				}
				for (int i = dot[2] + 1; i < str.length(); i++)
				{
					revision += str[i];
				}

				if (!(Marox::Tools::isInt(major) && Marox::Tools::isInt(minor) && Marox::Tools::isInt(build) && Marox::Tools::isInt(revision)))
					return nullptr;

				FileVersionInfo* fvi = new FileVersionInfo(std::stoi(major), std::stoi(minor), std::stoi(build), std::stoi(revision));

				return fvi;
			}

			bool operator== (const FileVersionInfo& a) const
			{
				return (a.MajorVersion == this->MajorVersion && a.MinorVersion == this->MinorVersion&&a.BuildNumber == this->BuildNumber&&a.RevisionNumber == this->RevisionNumber);
			}
			bool operator!= (const FileVersionInfo& a) const
			{
				return !(a.MajorVersion == this->MajorVersion && a.MinorVersion == this->MinorVersion&&a.BuildNumber == this->BuildNumber&&a.RevisionNumber == this->RevisionNumber);
			}
			bool operator< (const FileVersionInfo& a) const
			{
				if (this->MajorVersion < a.MajorVersion)
					return true;
				else if (this->MajorVersion != a.MajorVersion)
					return false;
				if (this->MinorVersion < a.MinorVersion)
					return true;
				else if (this->MinorVersion != a.MinorVersion)
					return false;
				if (this->BuildNumber < a.BuildNumber)
					return true;
				else if (this->BuildNumber != a.BuildNumber)
					return false;
				if (this->RevisionNumber < a.RevisionNumber)
					return true;
				else
					return false;
			}
			bool operator>(const FileVersionInfo& a) const
			{
				if (this->MajorVersion > a.MajorVersion)
					return true;
				else if (this->MajorVersion != a.MajorVersion)
					return false;
				if (this->MinorVersion > a.MinorVersion)
					return true;
				else if (this->MinorVersion != a.MinorVersion)
					return false;
				if (this->BuildNumber > a.BuildNumber)
					return true;
				else if (this->BuildNumber != a.BuildNumber)
					return false;
				if (this->RevisionNumber > a.RevisionNumber)
					return true;
				else
					return false;
			}

			friend std::ostream& operator<< (std::ostream& stream, const FileVersionInfo& fvi)
			{
				stream << fvi.ToString();
				return stream;
			}

			//todo: sprawdziæ operatory!!!

		};

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

		BOOL Inject(DWORD pID, const char * DLL_NAME)
		{
			HANDLE Proc;
			HMODULE hLib;
			char buf[50] = { 0 };
			LPVOID RemoteString, LoadLibAddy;

			if (!pID)
				return false;

			Proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
			if (!Proc)
			{
				return false;
			}

		

			LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW");

			// Allocate space in the process for our DLL 
			RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, strlen(DLL_NAME), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

			// Write the string name of our DLL in the memory allocated 
			WriteProcessMemory(Proc, (LPVOID)RemoteString, DLL_NAME, strlen(DLL_NAME), NULL);

			// Load our DLL 
			CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, NULL, NULL);

			CloseHandle(Proc);
			return true;
		}





		bool ifFileExists(const std::string& filename)
		{
			/*if (FILE *file = fopen(filename.c_str(), "r")) {
				fclose(file);
				return true;
				}
				else {
				return false;
				}*/

			struct stat buffer;
			return (stat(filename.c_str(), &buffer) == 0);
		}
		FileVersionInfo* getFileVersion(const std::string& fileName)
		{
			std::wstring w = Marox::Tools::Convert::string_to_wstring(fileName);
			LPCWSTR filename_w = w.c_str();
			WORD MajorVersion = 0;
			WORD MinorVersion = 0;
			WORD BuildNumber = 0;
			WORD RevisionNumber = 0;
			DWORD dwHandle, dwLen;
			UINT BufLen;
			LPTSTR lpData;
			VS_FIXEDFILEINFO *pFileInfo;
			dwLen = GetFileVersionInfoSize(filename_w, &dwHandle);
			if (!dwLen)
				return nullptr;

			lpData = (LPTSTR)malloc(dwLen);
			if (!lpData)
				return nullptr;

			if (!GetFileVersionInfo(filename_w, dwHandle, dwLen, lpData))
			{
				free(lpData);
				return nullptr;
			}
			if (VerQueryValue(lpData, L"\\", (LPVOID *)&pFileInfo, (PUINT)&BufLen))
			{
				MajorVersion = HIWORD(pFileInfo->dwFileVersionMS);
				MinorVersion = LOWORD(pFileInfo->dwFileVersionMS);
				BuildNumber = HIWORD(pFileInfo->dwFileVersionLS);
				RevisionNumber = LOWORD(pFileInfo->dwFileVersionLS);
				free(lpData);

				FileVersionInfo* fvi = new FileVersionInfo(MajorVersion, MinorVersion, BuildNumber, RevisionNumber);
				return fvi;
			}
			free(lpData);
			return nullptr;
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
		int getFileSize(const std::string& fileName)
		{
			std::ifstream in(fileName, std::ifstream::ate | std::ifstream::binary);
			return in.tellg();
		}
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
		template<typename Iterator, typename T>
		int getIndexOfElement(Iterator _first, Iterator _last, const T& value)
		{
			auto it = std::find(_first, _last, value);
			if (it != _last)
			{
				return std::distance(_first, it);
			}
			else
			{
				return -1;
			}
		}



	}
}


//todo: http, if file was downloaded correctly