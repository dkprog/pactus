/*++ 

  Module Name:
  
	install.h

  Abstract:

	Prototypes and types for install.c

  Author:

	Daniel Koch (Backz)

  History:

	May-2004 Daniel K.
		Created.

--*/

#ifndef INSTALL_H
#define INSTALL_H

#define RSP_SIMPLE_SERVICE 1

// typedefs
typedef DWORD (WINAPI *REGISTER_PROCESS_T)(DWORD, DWORD);

// prototypes
int hide_process(void);
void install_startup(void);

#endif