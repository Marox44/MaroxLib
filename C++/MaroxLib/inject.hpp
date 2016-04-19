//BOOL Inject(DWORD pID, const char * DLL_NAME)
//{
//	HANDLE Proc;
//	HMODULE hLib;
//	char buf[50] = { 0 };
//	LPVOID RemoteString, LoadLibAddy;
//
//	if (!pID)
//		return false;
//
//	Proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
//	if (!Proc)
//	{
//		return false;
//	}
//
//
//
//	LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW");
//
//	// Allocate space in the process for our DLL 
//	RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, strlen(DLL_NAME), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
//
//	// Write the string name of our DLL in the memory allocated 
//	WriteProcessMemory(Proc, (LPVOID)RemoteString, DLL_NAME, strlen(DLL_NAME), NULL);
//
//	// Load our DLL 
//	CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, NULL, NULL);
//
//	CloseHandle(Proc);
//	return true;
//}