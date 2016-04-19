#pragma once

#include <fstream>
#include <string>

namespace Marox
{
	namespace Tools
	{
		int getFileSize(const std::string& fileName)
		{
			std::ifstream in(fileName, std::ifstream::ate | std::ifstream::binary);
			return in.tellg();
		}
		bool ifFileExists(const std::string& filename)
		{
			std::ifstream f(filename.c_str());
			if (f.good()) {
				f.close();
				return true;
			}
			else {
				f.close();
				return false;
			}
		}

	}
}