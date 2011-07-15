#ifndef __FUNC_AMX_PLAYERS_H__
#define __FUNC_AMX_PLAYERS_H__

//#define FUNC_IsPlayerConnected					0x00486450
//#define FUNC_IsPlayerStreamedIn					0x004854D0
//#define FUNC_GetPlayerSurfingVehicleID					0x00485B00
//#define FUNC_IsVehicleStreamedIn					0x00485530
//#define FUNC_GetPlayerTeam					0x00484FD0
//#define FUNC_SetPlayerSkillLevel					0x00489B50



//extern cell ( __cdecl* _funcIsPlayerConnected )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcIsPlayerStreamedIn )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcIsVehicleStreamedIn )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGetPlayerSurfingVehicleID )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGetPlayerTeam )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcSetPlayerSkillLevel )( AMX* a_AmxInterface, cell* a_Params );


cell AMX_NATIVE_CALL funcIsPlayerConnected ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsPlayerStreamedIn ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsVehicleStreamedIn ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerSurfingVehicleID ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerTeam ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerSkillLevel ( AMX* a_AmxInterface, cell* a_Params );



#endif