/*++ 

  Module Name:
  
	hook_manip.h

  Abstract:
	
	Header file containing definitions, function prototypes, and other
    stuff for manipulate hooks

  Author:

	Daniel Koch (Backz)

  History:

	May-2004 Daniel K.
		Created.

--*/

#ifndef HOOK_MANIP_H
#define HOOK_MANIP_H

// prototypes
BOOL create_GetMessage_hook(HINSTANCE hinstDll, LPCSTR path);
BOOL create_CBT_hook(HINSTANCE hinstDll);
BOOL destroy_GetMessage_hook(void);
BOOL destroy_CBT_hook(void);
LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam);
HHOOK *return_message_hook(void);
HHOOK *return_cbt_hook(void);

#endif