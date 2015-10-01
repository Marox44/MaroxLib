#pragma once

#include <Windows.h>
#include <string>
#include <map>

#include "convert.hpp"

#ifndef DLL_FUNC_RETURN
#define DLL_FUNC_RETURN int
#endif

#ifndef DLL_FUNC_PARAMS
#define DLL_FUNC_PARAMS void
#endif


typedef DLL_FUNC_RETURN(*dll_import_function_type)(DLL_FUNC_PARAMS);

namespace Marox
{
	namespace DLL
	{
		class DLL_Loader final
		{
		public:
			DLL_Loader() = delete;
			~DLL_Loader() = delete;
			DLL_Loader(const DLL_Loader&) = delete;
			DLL_Loader(DLL_Loader&&) = delete;
			DLL_Loader& operator=(const DLL_Loader&) = delete;
			DLL_Loader& operator=(DLL_Loader&&) = delete;

			static bool loadDLL(const std::string& DLL_fileName)
			{
				HINSTANCE dllHandle;
				dllHandle = LoadLibrary(Marox::Tools::Convert::string_to_wstring(DLL_fileName).c_str());
				if (!dllHandle)
				{
					return false;
				}

				DLL_Loader::m_handles[DLL_fileName] = dllHandle;
				return true;
			}

			static dll_import_function_type GetFunctionFromDLL(const std::string& DLL_fileName, const std::string& functionName)
			{
				dll_import_function_type f = (dll_import_function_type)GetProcAddress(DLL_Loader::m_handles[DLL_fileName], functionName.c_str());
				if (!f)
				{
					return nullptr;
				}

				return f;
			}

			static bool unloadDLL(const std::string& DLL_fileName)
			{
				if (!DLL_Loader::m_handles.count(DLL_fileName))
				{
					return false;
				}
				if (!FreeLibrary(DLL_Loader::m_handles[DLL_fileName]))
				{
					return false;
				}
				if (!DLL_Loader::m_handles.erase(DLL_fileName))
				{
					return false;
				}
				return true;
			}

		private:
			static std::map<std::string, HINSTANCE> m_handles;
		};
		std::map<std::string, HINSTANCE> DLL::DLL_Loader::m_handles;
	}
}


