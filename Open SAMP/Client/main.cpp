#include "main.h"

uint32_t sampBaseAddr						= NULL;

CNetGame*					__NetGame		= NULL;
CChatBox*					__ChatBox		= NULL;
CCmdWindow*					__CmdWindow		= NULL;
CDXUTDialog*				__ScriptDialog	= NULL;
CDXUTDialogResourceManager* __DialogResourceManager = NULL;
CKeyBinder*					__KeyBinder		= NULL;
CGame*						__Game			= NULL;

void outputDebugText( char* text );
void outputDebugText( char* text )
{
	FILE* fichier = fopen( "debug.txt", "a" );
	if( fichier == 0 ) fichier = fopen( "debug.txt", "w" );

	fwrite( text, strlen( text ), 1, fichier );
	fputs( "\r\n", fichier );

	fclose( fichier );
}





void Init()
{
	sampBaseAddr = (uint32_t)GetModuleHandle("samp.dll");

	if( sampBaseAddr == 0 )
	{
		MessageBox( 0, "Unable to launch the mod, please restart Open SAMP", "Error: Unable to launch the mod", MB_OK | MB_ICONERROR );
		ExitProcess( 0 );
		return;
	}
	/* On fout un seul unlock de toute la dll ainsi que tout GTA pour être tranquille :p*/
	uint32_t tmp;
	VirtualProtect( (void*)sampBaseAddr, 0x27EFFC, PAGE_EXECUTE_READWRITE, &tmp ); // unlock samp.dll
	VirtualProtect( (void*)0x400000, 0x1176B68, PAGE_EXECUTE_READWRITE, &tmp ); // unlock GTA_SA.exe

	//_beginthread( ThreadLoop, 0, 0 );

	installSAMPHooks( );
	installGTAHooks( );

	// code

	__KeyBinder		= new CKeyBinder();

}

BOOL WINAPI DllMain( HINSTANCE dllHistance, uint32_t callReason, void* reserved )
{
	switch( callReason )
	{
	case DLL_PROCESS_ATTACH:
		{
			h_dllHistance = dllHistance;
			Init();
			break;
		}
	case DLL_PROCESS_DETACH:
		{
			break;
		}
	default:
		{
			break;
		}
	}
	return TRUE; // F*ck !!! il manquais le return TRUE; voila pourquoi nos hook ne fonctionnait pas ... 
}