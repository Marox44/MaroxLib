#pragma once

#include <algorithm>

namespace Marox
{
	namespace Tools
	{
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