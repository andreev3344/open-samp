#include "main.h"



void installRadarPatch( )
{
	uint8_t patchSize = 0x2D;
	memset( (void*)( sampBaseAddr + Addr_GetRadarColorsPatch ), 0x90, patchSize );
	/*

		to remove that shit and add our own colors

.text:1009E644                 cmp     eax, 1F4h
.text:1009E649                 jnz     short loc_1009E653
.text:1009E64B                 mov     eax, 89A4C440h
.text:1009E650                 retn    4
.text:1009E653 ; ---------------------------------------------------------------------------
.text:1009E653
.text:1009E653 loc_1009E653:                           ; CODE XREF: GetRadarColors+9j
.text:1009E653                 cmp     eax, 1F5h
.text:1009E658                 jnz     short loc_1009E662
.text:1009E65A                 mov     eax, 0AA0000FFh
.text:1009E65F                 retn    4
.text:1009E662 ; ---------------------------------------------------------------------------
.text:1009E662
.text:1009E662 loc_1009E662:                           ; CODE XREF: GetRadarColors+18j
.text:1009E662                 cmp     eax, 1F6h
.text:1009E667                 jnz     short loc_1009E671
.text:1009E669                 mov     eax, 0E2C063FFh
.text:1009E66E                 retn    4


	*/

	( ( uint32_t* )( sampBaseAddr + ArrayRadarColors ) )[ 0x1F4*4 ] = 0x89A4C440;
	( ( uint32_t* )( sampBaseAddr + ArrayRadarColors ) )[ 0x1F5*4 ] = 0xAA0000FF; // Checkpoints marker color
	( ( uint32_t* )( sampBaseAddr + ArrayRadarColors ) )[ 0x1F6*4 ] = 0xE2C063FF; // Vehicles marker color

}


void installSAMPHooks( )
{
	HookFunction(sampBaseAddr + Addr_CChatWindow_AddDebugHook, (uint32_t)CChatWindow_AddDebugMessage_Hook); // Hook CChatWindow::AddDebugMessage
	DetournCall((sampBaseAddr + Addr_CGame_DisplayHud_Call), (uint32_t)CGame__DisplayHud); // Hook the call of CGame::DisplayHud on the directX render function
	HookFunction( ( sampBaseAddr + Addr_CNetGame_JmpConnectionSuceeded ), ( uint32_t )Packet_ConnectionSucceeded ); // hook the call of Packet_ConnectionSucceeded
	DetournCall((sampBaseAddr + Addr_CNetGame_CallConnectionLost), (uint32_t)Packet_ConnectionLost);

	installRadarPatch( );
}


void installGTAHooks( )
{

	// from http://code.google.com/p/mtasa-blue/source/browse/trunk/MTA10/multiplayer_sa/CMultiplayerSA.cpp?spec=svn2325&r=2325
	// Disable the loading screen tune.
	memset ( (void *)0x748CF6, 0x90, 5 );

	// Do not render the loading screen.
	memset ( (void *)0x590D7C, 0x90, 5 );
	memset ( (void *)0x590DB3, 0x90, 5 );
	memcpy ( (void *)0x590D9F, "\xC3\x90\x90\x90\x90", 5 );
}


// trop moche

uint8_t dbgMessageCode[] = 
{
	0x55, 0x8B, 0xEC, 0x83, 0xE4, 0xF8
};
char* formatStr;
uint32_t retAddr = Addr_CChatWindow_AddDebugHook + sizeof( dbgMessageCode );
uint32_t ebxBackup;

void __declspec (naked) CChatWindow_AddDebugMessage_Hook()
{
	__asm
	{	
		push    ebp
		mov     ebp, esp
		and		esp, 0x0FFFFFFF8

		mov ebxBackup, ebx
		mov ebx, [ebp+0xC]
		mov formatStr, ebx
	}

	__asm pushad

	// init code

	strcat(formatStr, " (Open {EE5555}"OPEN_SAMP_VERSION"{FFFFFF})" );

	__NetGame				= *( CNetGame** )( sampBaseAddr + Addr_pNetGame );
	__ChatBox				= *( CChatBox** )( sampBaseAddr + Addr_pChatBox );
	__CmdWindow				= *( CCmdWindow** )( sampBaseAddr + Addr_pCmdWindow );
	__ScriptDialog			= *( CDXUTDialog** )( sampBaseAddr + Addr_pScriptDialog );
	__DialogResourceManager = *( CDXUTDialogResourceManager** )( sampBaseAddr + Addr_pDialogResourceManager );
	__Game					= *( CGame** )( sampBaseAddr + Addr_pGame );
	//

	retAddr += sampBaseAddr;
	memcpy((PVOID)(sampBaseAddr + Addr_CChatWindow_AddDebugHook), dbgMessageCode, 6);
	__asm popad

	__asm 
	{
		mov ebx, formatStr
		mov [ebp+0xC], ebx
	}

	__asm mov ebx, ebxBackup
	__asm jmp retAddr
}


HINSTANCE h_dllHistance = 0;
HHOOK KeyHook = 0;

LRESULT __stdcall KeyboardProc( int code, WPARAM wParam, LPARAM lParam )
{
	if( code < 0 ) 
		return CallNextHookEx( KeyHook, code, wParam, lParam );
		
	if( code == HC_ACTION )
	{
		if( __KeyBinder )
		{
			__KeyBinder->KeyProcessing( ( uint32_t )wParam, ( uint32_t )lParam );
		}
	}

	return CallNextHookEx( KeyHook, code, wParam, lParam );
}


void __stdcall Packet_ConnectionSucceeded( Packet* packet ) // 
{
	__ChatBox->addInfoMessage( "Connected. Joining the game..." );

	__NetGame		= *( CNetGame** )( sampBaseAddr + Addr_pNetGame );
	__ScriptDialog	= *( CDXUTDialog** )( sampBaseAddr + Addr_pDxutDialog );
	__Game			= *( CGame** )( sampBaseAddr + Addr_pGame );


	UNREGISTER_STATIC_RPC( __NetGame->getRakClientInterface(), ShowCheckpoint );
	UNREGISTER_STATIC_RPC( __NetGame->getRakClientInterface(), ShowRaceCheckpoint );

	__NetGame->registerRPCs( );

	if( KeyHook == 0 )
		KeyHook = SetWindowsHookEx( WH_KEYBOARD, KeyboardProc, h_dllHistance, GetCurrentThreadId() );

	RakNet::BitStream rStream( packet->data, packet->length, false );

	uint8_t packetID = 0;
	uint32_t binaryAddress = 0;
	uint16_t port = 0;
	uint32_t serverTicket = 0;
	_PlayerID playerID = 0;
	

	rStream.Read( packetID );
	rStream.Read( binaryAddress );
	rStream.Read( port );
	rStream.Read( playerID );
	rStream.Read( serverTicket );

	char serial[ 0x64 ] = "1D6B08A1E5440AB7DB645198D5BB085BEE437D586CA";

	RakNet::BitStream bStream;
	bStream.Write( ( uint32_t ) NETGAME_VERSION );
	bStream.Write( ( uint8_t ) GAME_BYTE_MOD );
	bStream.Write( ( uint8_t ) strlen( __NetGame->getPlayerPool()->GetLocalPlayerName() ) );
	bStream.Write( (char*)__NetGame->getPlayerPool()->GetLocalPlayerName() , ( uint8_t ) strlen( __NetGame->getPlayerPool()->GetLocalPlayerName() ) );
	bStream.Write( ( uint32_t )( ( serverTicket ^ NETGAME_VERSION ) ));
	bStream.Write( ( uint8_t ) strlen( (char*)serial ) );
	bStream.Write( ( char*)serial , strlen( (char*)serial ) );
	bStream.Write( ( uint32_t )( ( serverTicket ^ NETGAME_VERSION ) + 1 ));
	__NetGame->getRakClientInterface()->RPC( RPC_ClientJoin, &bStream, HIGH_PRIORITY, RELIABLE, 0, false );
	
}

void __stdcall Packet_ConnectionLost( uint32_t netgame_ptr, Packet* packet )
{

	// write your code between here ...


	__NetGame->unRegisterRPCs( );

	if( __KeyBinder )
		__KeyBinder->Clear( ); // à chaque deconnection à un serveur on retire les touches bindées





	// ... and here
	// don't touch this code

	_asm
	{
		pushad

		mov ebx, CNetGame_ConnectionLost
		add ebx, sampBaseAddr
		mov ecx, netgame_ptr

		push packet
		call ebx

		popad
	}

}

void CGame__ToggleRadar(int iToggle)
{
	*(PBYTE)0xBAA3FB = (BYTE)!iToggle;
}

void CGame__DisplayHud(BOOL bDisp)
{
	// custom code
	
	//

	if(bDisp) 
	{
		*(BYTE*)0xBA6769 = 1;
		CGame__ToggleRadar(1);
	} 
	else 
	{
		*(BYTE*)0xBA6769 = 0;
		CGame__ToggleRadar(0);
	}
}