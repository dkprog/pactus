/*++ 

  Module Name:
  
	dllmain.h

  Abstract:
	
	Header file containing definitions, function prototypes, and other
    stuff to work with this DLL

  Author:

	Daniel Koch (Backz)

  History:

	May-2004 Daniel K.
		Created.

--*/

#ifndef MAIN_H
#define MAIN_H

#define CALL __stdcall

// prototypes
BOOL CALL WSARunStack(const char *log_filename_ent, BOOL show_error_reason);
BOOL CALL WSACleanStack(void);


#endif