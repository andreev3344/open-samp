#include "../../main.h"

#ifndef _STANDALONE
#include "../../../SDK/amx/amx.h"
#endif

#include "../func_amx.h"
#include "func_amx_menu.h"

//cell ( __cdecl* _funcCreateMenu )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_CreateMenu;
//cell ( __cdecl* _funcDestroyMenu )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DestroyMenu;
//cell ( __cdecl* _funcAddMenuItem )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AddMenuItem;
//cell ( __cdecl* _funcSetMenuColumnHeader )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetMenuColumnHeader;
//cell ( __cdecl* _funcShowMenuForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ShowMenuForPlayer;
//cell ( __cdecl* _funcHideMenuForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_HideMenuForPlayer;
//cell ( __cdecl* _funcIsValidMenu )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsValidMenu;
//cell ( __cdecl* _funcDisableMenu )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DisableMenu;
//cell ( __cdecl* _funcDisableMenuRow )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DisableMenuRow;
//cell ( __cdecl* _funcGetPlayerMenu )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerMenu;


cell AMX_NATIVE_CALL funcCreateMenu ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcCreateMenu()" );

	char* str = 0;
	amx_StrParam( a_AmxInterface, a_Params[1], str );


	

	uint8_t ret = __NetGame->menuPool->New( str, amx_ctof( a_Params[3] ), amx_ctof( a_Params[4] ), (uint8_t)a_Params[2], amx_ctof( a_Params[5] ), amx_ctof( a_Params[6] ) );
	return (cell) ret;
}
cell AMX_NATIVE_CALL funcDestroyMenu ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcDestroyMenu()" );
	return __NetGame->menuPool->Destroy( (uint8_t)a_Params[1] );
}
cell AMX_NATIVE_CALL funcAddMenuItem ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcAddMenuItem()" );
	uint8_t menuID = (uint8_t)a_Params[ 1 ];
	if( 0 > menuID || menuID >= MAX_MENUS ) return 0;
	if( __NetGame->menuPool->isCreated[ menuID ] == 0 ) return 0;

	char* str = 0;
	amx_StrParam( a_AmxInterface, a_Params[ 3 ], str );

	__NetGame->menuPool->menu[ menuID ]->AddMenuItem( (uint8_t)a_Params[ 2 ], str );
	return 1;
}
cell AMX_NATIVE_CALL funcSetMenuColumnHeader ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetMenuColumnHeader()" );
	uint8_t menuID = (uint8_t)a_Params[ 1 ];

	if( 0 > menuID || menuID >= MAX_MENUS ) return 0;
	if( __NetGame->menuPool->isCreated[ menuID ] == 0 ) return 0;

	char* str = 0;
	amx_StrParam( a_AmxInterface, a_Params[3], str );

	__NetGame->menuPool->menu[ menuID ]->SetColumnHeader( (uint8_t)a_Params[2], str );
	return 1;



	//return _funcSetMenuColumnHeader ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcShowMenuForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcShowMenuForPlayer()" );

	uint8_t menuID = (uint8_t)a_Params[ 1 ];

	if( 0 > menuID || menuID >= MAX_MENUS ) return 0;
	if( __NetGame->menuPool->isCreated[ menuID ] == 0 ) return 0;

	if( __NetGame->playerPool->isCreated[ (_PlayerID)a_Params[2] ] == 0 ) return 0;

	__NetGame->menuPool->menu[ menuID ]->showForPlayer( (_PlayerID)a_Params[2] );

	__NetGame->menuPool->playerMenu[ (_PlayerID)a_Params[2] ] = menuID;

	return 1;
}
cell AMX_NATIVE_CALL funcHideMenuForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcHideMenuForPlayer()" );
	
	uint8_t menuID = (uint8_t)a_Params[ 1 ];

	if( 0 > menuID || menuID >= MAX_MENUS ) return 0;
	if( __NetGame->menuPool->isCreated[ menuID ] == 0 ) return 0;

	if( __NetGame->playerPool->isCreated[ (_PlayerID)a_Params[2] ] == 0 ) return 0;

	__NetGame->menuPool->menu[ menuID ]->hideForPlayer( (_PlayerID)a_Params[2] );
	return 1;
//	return _funcHideMenuForPlayer ( a_AmxInterface, a_Params );
}



cell AMX_NATIVE_CALL funcIsValidMenu ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcIsValidMenu()" );
	uint8_t menuID = (uint8_t)a_Params[ 1 ];

	if( 0 > menuID || menuID >= MAX_MENUS ) return 0;
	return (cell)__NetGame->menuPool->isCreated[ menuID ];
}
cell AMX_NATIVE_CALL funcDisableMenu ( AMX* a_AmxInterface, cell* a_Params ) // Utile ? Inutile ? telle est la question. :p
{
	if(bScriptDebug) logprintf ( "[Call]-> funcDisableMenu()" );
	uint8_t menuID = (uint8_t)a_Params[ 1 ];
	if( 0 > menuID || menuID >= MAX_MENUS ) return 0;
	if( __NetGame->menuPool->isCreated[ menuID ] == 0 ) return 0;
	
	__NetGame->menuPool->menu[ menuID ]->interaction.Menu = 0;
	
	return 1;
}
cell AMX_NATIVE_CALL funcDisableMenuRow ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcDisableMenuRow()" );
	
	uint8_t menuID = (uint8_t)a_Params[ 1 ];
	
	if( 0 > menuID || menuID >= MAX_MENUS ) return 0;
	if( __NetGame->menuPool->isCreated[ menuID ] == 0 ) return 0;
	
	uint8_t row = (uint8_t)a_Params[ 2 ];
	
	if( 0 > row  || row >= MAX_ITEMS ) return 0;

	__NetGame->menuPool->menu[ menuID ]->interaction.Row[ row ] = 0;

	return 1;
}

cell AMX_NATIVE_CALL funcGetPlayerMenu ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerMenu()" );
	_PlayerID playerID = (_PlayerID)a_Params[ 1 ];

	if( 0 > playerID || playerID >= MAX_PLAYERS) return -1;

	return __NetGame->menuPool->playerMenu[playerID];
}