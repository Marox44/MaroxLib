#pragma once

#include <string>
#include <algorithm>
#include "detail\md5\md5.h"

namespace Marox
{
	namespace Tools
	{
		namespace MD5
		{
			std::string hashString(const char* str)
			{
				_MD5 md5;
				char* result = md5.digestString((char*)str);
				std::string s(result);
				std::transform(s.begin(), s.end(), s.begin(), ::toupper);
				return s;
			}
			std::string hashFile(const std::string& file)
			{
				_MD5 md5;
				char* result = md5.digestFile((char*)file.c_str());
				std::string s(result);
				std::transform(s.begin(), s.end(), s.begin(), ::toupper);
				return s;
			}
			std::string hashMemory(BYTE* memory, int size)
			{
				_MD5 md5;
				char* result = md5.digestMemory(memory, size);
				std::string s(result);
				std::transform(s.begin(), s.end(), s.begin(), ::toupper);
				return s;
			}
		}
	}
}