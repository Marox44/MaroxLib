#pragma once

#include <Windows.h>

namespace Marox
{
	namespace Tools
	{
		namespace WinAPI
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
		}
	}
}