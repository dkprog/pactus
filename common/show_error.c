/*++ 

  Module Name:
  
	show_error.c

  Abstract:
	
	Functions used to show error messages within MessageBox

  Author:

	Daniel Koch (Backz)

  History:

	May-2004 Daniel K.
		Created.

--*/

#include <windows.h>
#include "show_error.h"

// control var
static BOOL debug_mode = FALSE;

void show_error(const char *error_message)
{
	if(debug_mode) MessageBox(NULL, error_message, "Error:", MB_OK+MB_ICONERROR);
}

void show_alert(const char *alert_message)
{
	if(debug_mode) MessageBox(NULL, alert_message, "Alert:", MB_OK+MB_ICONINFORMATION);
}

void show_last_hook_errors(void)
{
	if(debug_mode)
	{
		switch(GetLastError())
		{
		case ERROR_INVALID_HOOK_FILTER:
			show_error("Error: The hook code is invalid");
			break;
		case ERROR_INVALID_FILTER_PROC:
			show_error("Error: The filter function is invalid");
			break;
		case ERROR_HOOK_NEEDS_HMOD:
			show_error("Error: A global hook is begin set with a NULL hInstance");
			break;
		case ERROR_GLOBAL_ONLY_HOOK:
			show_error("Error: A hook that can only be a system hook is begin installed to a specific thread");
			break;
		case ERROR_INVALID_PARAMETER:
			show_error("Error: The thread ID is invalid");
			break;
		case ERROR_MOD_NOT_FOUND:
			show_error("Error: The hInstance parameter for a global hook was not a library");
			break;
		default:
			show_error("Error: Security does not allow this hook to be set");
		}
	}
}

void set_show_error(BOOL reason)
{
	debug_mode = reason;
}