#pragma once
#include <locale>
#include <codecvt>
#include <string>

namespace Marox
{
	namespace Tools
	{
		class Convert final
		{
		public:
			final() = delete;
			/// <summary>
			/// Converts <c>wstring</c> to <c>string</c>
			/// </summary>
			/// <param name="_val">Source <c>wstring</c></param>
			/// <returns>std::string</returns>
			static std::string wstring_to_string(const std::wstring& _val)
			{
				std::wstring_convert<std::codecvt_utf8<wchar_t>> cv;
				return cv.to_bytes(_val);
			}
			/// <summary>
			/// Converts <c>string</c> to <c>wstring</c>
			/// </summary>
			/// <param name="_val">Source <c>string</c></param>
			/// <returns>std::wstring</returns>
			static std::wstring string_to_wstring(const std::string& _val)
			{
				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
				return converter.from_bytes(_val);
			}
		}
	}

}
