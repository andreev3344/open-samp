#ifndef __FUNC_AMX_DEPRECATED_RADARZONE_H_
#define __FUNC_AMX_DEPRECATED_RADARZONE_H_

//#define FUNC_GangZoneCreate					0x00488A50
//#define FUNC_GangZoneDestroy					0x00488A90
//#define FUNC_GangZoneShowForPlayer			0x00488AD0
//#define FUNC_GangZoneShowForAll				0x00488B30
//#define FUNC_GangZoneHideForPlayer			0x00488B70
//#define FUNC_GangZoneHideForAll				0x00488BD0
//#define FUNC_GangZoneFlashForPlayer			0x00488C10
//#define FUNC_GangZoneFlashForAll				0x00488C70
//#define FUNC_GangZoneStopFlashForPlayer		0x00488CB0
//#define FUNC_GangZoneStopFlashForAll			0x00488D10

//extern cell ( __cdecl* _funcGangZoneCreate )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGangZoneDestroy )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGangZoneShowForPlayer )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGangZoneShowForAll )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGangZoneHideForPlayer )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGangZoneHideForAll )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGangZoneFlashForPlayer )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGangZoneFlashForAll )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGangZoneStopFlashForPlayer )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGangZoneStopFlashForAll )( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcGangZoneCreate ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGangZoneDestroy ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGangZoneShowForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGangZoneShowForAll ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGangZoneHideForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGangZoneHideForAll ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGangZoneFlashForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGangZoneFlashForAll ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGangZoneStopFlashForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGangZoneStopFlashForAll ( AMX* a_AmxInterface, cell* a_Params );

// __FUNC_AMX_DEPRECATED_RADARZONE_H_
#endif