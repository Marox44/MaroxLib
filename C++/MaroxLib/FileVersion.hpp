#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <string>
#include <Windows.h>

#include "convert.hpp"
#include "string.hpp"


namespace Marox
{

	namespace Tools
	{
		namespace WinAPI
		{
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
		}
	}

}