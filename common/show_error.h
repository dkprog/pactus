/*++ 

  Module Name:
  
	show_error.h

  Abstract:
	
	Header file for error functions.

  Author:

	Daniel Koch (Backz)

  History:

	May-2004 Daniel K.
		Created.

--*/

#ifndef SHOW_ERROR_H
#define SHOW_ERROR_H

/* prototypes */
void show_error(const char *error_message);
void show_alert(const char *alert_message);
void show_last_hook_errors(void);
void set_show_error(BOOL reason);


#endif
