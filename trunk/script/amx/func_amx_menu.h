#ifndef __FUNC_AMX_MENU_H__
#define __FUNC_AMX_MENU_H__

//#define FUNC_CreateMenu					0x00487FA0
//#define FUNC_DestroyMenu					0x00488050
//#define FUNC_AddMenuItem					0x00488080
//#define FUNC_SetMenuColumnHeader					0x00488140
//#define FUNC_ShowMenuForPlayer					0x004881F0
//#define FUNC_HideMenuForPlayer					0x00488260
//#define FUNC_IsValidMenu					0x004882C0
//#define FUNC_DisableMenu					0x004882F0
//#define FUNC_DisableMenuRow					0x00488330
//#define FUNC_GetPlayerMenu					0x00488370

//
//extern cell ( __cdecl* _funcCreateMenu )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcDestroyMenu )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcAddMenuItem )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcSetMenuColumnHeader )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcShowMenuForPlayer )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcHideMenuForPlayer )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcIsValidMenu )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcDisableMenu )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcDisableMenuRow )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGetPlayerMenu )( AMX* a_AmxInterface, cell* a_Params );


cell AMX_NATIVE_CALL funcCreateMenu ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDestroyMenu ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAddMenuItem ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetMenuColumnHeader ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcShowMenuForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcHideMenuForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsValidMenu ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDisableMenu ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDisableMenuRow ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerMenu ( AMX* a_AmxInterface, cell* a_Params );

#endif