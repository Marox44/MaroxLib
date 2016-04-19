#pragma once

#include <vector>
#include <sstream>
#include <string>


namespace Marox
{
	namespace Tools
	{
		std::vector<std::string> explodeString(const std::string &s, char delim)
		{
			std::vector<std::string> elems;
			std::stringstream ss(s);
			std::string item;
			while (std::getline(ss, item, delim)) {
				elems.push_back(item);
			}
			return elems;
		}

		bool isInt(const std::string& s)
		{
			if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
				return false;

			char * p;
			strtol(s.c_str(), &p, 10);
			return (*p == 0);
		}
	}
}