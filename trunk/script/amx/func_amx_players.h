#ifndef __FUNC_AMX_PLAYERS_H__
#define __FUNC_AMX_PLAYERS_H__

//#define FUNC_IsPlayerConnected					0x00486450
//#define FUNC_IsPlayerStreamedIn					0x004854D0
//#define FUNC_GetPlayerSurfingVehicleID					0x00485B00
//#define FUNC_IsVehicleStreamedIn					0x00485530
//#define FUNC_GetPlayerTeam					0x00484FD0
//#define FUNC_SetPlayerSkillLevel					0x00489B50
//#define FUNC_SetPlayerName					0x0048AB30
#define FUNC_SetPlayerSkin					0x0048AD30
#define FUNC_GetPlayerSkin					0x00485020
#define FUNC_GetPlayerPos					0x00485160
#define FUNC_SetPlayerPos					0x0048B3E0
#define FUNC_SetPlayerPosFindZ					0x0048B510
#define FUNC_GetPlayerHealth					0x00485200
#define FUNC_SetPlayerHealth					0x0048B640
#define FUNC_SetPlayerColor					0x00485A50
#define FUNC_GetPlayerColor					0x00485A90
#define FUNC_GetPlayerVehicleID					0x00485AC0
#define FUNC_GetPlayerVehicleSeat					0x00485B50

#define FUNC_PutPlayerInVehicle					0x0048B730
#define FUNC_RemovePlayerFromVehicle					0x00485250
#define FUNC_IsPlayerInVehicle					0x00485320
#define FUNC_IsPlayerInAnyVehicle					0x00485370
#define FUNC_GetPlayerName					0x004853B0
#define FUNC_SetPlayerCheckpoint					0x00485BA0
#define FUNC_DisablePlayerCheckpoint					0x00485BF0
#define FUNC_IsPlayerInCheckpoint					0x00485C30
#define FUNC_SetPlayerRaceCheckpoint					0x00485C60
#define FUNC_DisablePlayerRaceCheckpoint					0x00485CC0
#define FUNC_IsPlayerInRaceCheckpoint					0x00485D00
#define FUNC_SetPlayerInterior					0x0048BFC0
#define FUNC_GetPlayerInterior					0x00485D30
#define FUNC_SetPlayerAttachedObject					0x0048A4E0
#define FUNC_RemovePlayerAttachedObject					0x0048A590
#define FUNC_SetPlayerAttachedObject					0x0048A4E0
#define FUNC_IsPlayerAttachedObjectSlotUsed					0x0048A5F0
#define FUNC_SetPlayerCameraLookAt					0x0048C2A0
#define FUNC_SetPlayerCameraPos					0x0048C180
#define FUNC_SetCameraBehindPlayer					0x00485F70
#define FUNC_GetPlayerCameraPos					0x00485DB0
#define FUNC_GetPlayerCameraFrontVector					0x00485E90
#define FUNC_TogglePlayerControllable					0x0048C3C0
#define FUNC_PlayerPlaySound					0x0048CBB0
#define FUNC_SetPlayerScore					0x00486200
#define FUNC_GetPlayerScore					0x00486240
#define FUNC_SetPlayerFacingAngle					0x0048C7E0
#define FUNC_GetPlayerFacingAngle					0x004864B0
#define FUNC_GivePlayerMoney					0x0048C5D0
#define FUNC_GetPlayerMoney					0x00486270
#define FUNC_ResetPlayerMoney					0x004862A0

#define FUNC_GetPlayerState					0x00486480
#define FUNC_ResetPlayerWeapons					0x00486500
#define FUNC_GivePlayerWeapon					0x0048C8C0
#define FUNC_SetPlayerArmedWeapon					0x0048C9B0
#define FUNC_GetPlayerIp					0x00486B40
#define FUNC_GetPlayerPing					0x00486BB0
#define FUNC_GetPlayerWeapon					0x00486C10
#define FUNC_SetPlayerArmour					0x0048CDE0
#define FUNC_GetPlayerArmour					0x00486D90
#define FUNC_SetPlayerMapIcon					0x0048CFE0
#define FUNC_RemovePlayerMapIcon					0x0048D170
#define FUNC_GetPlayerKeys					0x00486DE0
#define FUNC_SetPlayerMarkerForPlayer					0x0048CEC0
#define FUNC_GetPlayerAmmo					0x00486370
#define FUNC_SetPlayerAmmo					0x0048C6E0
#define FUNC_GetPlayerWeaponData					0x004863C0
#define FUNC_GetPlayerWeaponState					0x0048A330
#define FUNC_AllowPlayerTeleport					0x00487200
#define FUNC_ForceClassSelection					0x00484F10
#define FUNC_SetPlayerWantedLevel					0x0048EB80
#define FUNC_GetPlayerWantedLevel					0x00488410
#define FUNC_GetPlayerFightingStyle					0x00488440
#define FUNC_SetPlayerFightingStyle					0x0048EC70
#define FUNC_GetPlayerVelocity					0x004890C0
#define FUNC_SetPlayerVelocity					0x0048EDC0
#define FUNC_IsPlayerInRangeOfPoint					0x00485450


#define FUNC_SetPlayerVirtualWorld					0x00485060
#define FUNC_GetPlayerVirtualWorld					0x004850A0
#define FUNC_ShowPlayerNameTagForPlayer					0x0048CCD0
#define FUNC_EnableStuntBonusForAll					0x00488ED0
#define FUNC_EnableStuntBonusForPlayer					0x00488F90
#define FUNC_TogglePlayerSpectating					0x0048AE90
#define FUNC_GetPlayerDrunkLevel					0x00489240
#define FUNC_SetPlayerDrunkLevel					0x0048F170
#define FUNC_PlayerSpectateVehicle					0x0048AF90
#define FUNC_PlayerSpectatePlayer					0x0048B130
#define FUNC_ApplyAnimation					0x0048D340
#define FUNC_ClearAnimations					0x0048D640
#define FUNC_GetPlayerAnimationIndex					0x004870C0
#define FUNC_GetAnimationName					0x00487120
#define FUNC_SetPlayerSpecialAction					0x0048C0A0
#define FUNC_GetPlayerSpecialAction					0x00485D60
#define FUNC_StartRecordingPlayerData					0x00485810
#define FUNC_StopRecordingPlayerData					0x004858C0
#define FUNC_PlayCrimeReportForPlayer					0x0048F450
#define FUNC_SetPlayerShopName					0x00489A00


//extern cell ( __cdecl* _funcIsPlayerConnected )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcIsPlayerStreamedIn )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcIsVehicleStreamedIn )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGetPlayerSurfingVehicleID )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGetPlayerTeam )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcSetPlayerSkillLevel )( AMX* a_AmxInterface, cell* a_Params );

//extern cell ( __cdecl* _funcSetPlayerName )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerSkin )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerSkin )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerPos )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerPos )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerPosFindZ )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerHealth )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerHealth )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerColor )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerColor )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerVehicleID )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerVehicleSeat )( AMX* a_AmxInterface, cell* a_Params );

extern cell ( __cdecl* _funcPutPlayerInVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcRemovePlayerFromVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcIsPlayerInVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcIsPlayerInAnyVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerName )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerCheckpoint )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcDisablePlayerCheckpoint )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcIsPlayerInCheckpoint )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerRaceCheckpoint )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcDisablePlayerRaceCheckpoint )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcIsPlayerInRaceCheckpoint )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerInterior )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerInterior )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerAttachedObject )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcRemovePlayerAttachedObject )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerAttachedObject )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcIsPlayerAttachedObjectSlotUsed )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerCameraLookAt )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerCameraPos )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetCameraBehindPlayer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerCameraPos )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerCameraFrontVector )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTogglePlayerControllable )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcPlayerPlaySound )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerScore )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerScore )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerFacingAngle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerFacingAngle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGivePlayerMoney )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerMoney )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcResetPlayerMoney )( AMX* a_AmxInterface, cell* a_Params );

extern cell ( __cdecl* _funcGetPlayerState )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcResetPlayerWeapons )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGivePlayerWeapon )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerArmedWeapon )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerIp )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerPing )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerWeapon )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerArmour )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerArmour )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerMapIcon )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcRemovePlayerMapIcon )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerKeys )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerMarkerForPlayer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerAmmo )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerAmmo )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerWeaponData )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerWeaponState )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAllowPlayerTeleport )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcForceClassSelection )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerWantedLevel )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerWantedLevel )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerFightingStyle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerFightingStyle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerVelocity )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerVelocity )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcIsPlayerInRangeOfPoint )( AMX* a_AmxInterface, cell* a_Params );


extern cell ( __cdecl* _funcSetPlayerVirtualWorld )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerVirtualWorld )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcShowPlayerNameTagForPlayer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcEnableStuntBonusForAll )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcEnableStuntBonusForPlayer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTogglePlayerSpectating )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerDrunkLevel )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerDrunkLevel )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcPlayerSpectateVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcPlayerSpectatePlayer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcApplyAnimation )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcClearAnimations )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerAnimationIndex )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetAnimationName )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerSpecialAction )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerSpecialAction )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcStartRecordingPlayerData )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcStopRecordingPlayerData )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcPlayCrimeReportForPlayer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerShopName )( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcIsPlayerConnected ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsPlayerStreamedIn ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsVehicleStreamedIn ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerSurfingVehicleID ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerTeam ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerSkillLevel ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerName ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerSkin ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerSkin ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerPos ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerPos ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerPosFindZ ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerHealth ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerHealth ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerColor ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerColor ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerVehicleID ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerVehicleSeat ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcPutPlayerInVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRemovePlayerFromVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsPlayerInVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsPlayerInAnyVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerName ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerCheckpoint ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDisablePlayerCheckpoint ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsPlayerInCheckpoint ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerRaceCheckpoint ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDisablePlayerRaceCheckpoint ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsPlayerInRaceCheckpoint ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerInterior ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerInterior ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerAttachedObject ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRemovePlayerAttachedObject ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerAttachedObject ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsPlayerAttachedObjectSlotUsed ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerCameraLookAt ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerCameraPos ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetCameraBehindPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerCameraPos ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerCameraFrontVector ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTogglePlayerControllable ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcPlayerPlaySound ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerScore ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerScore ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerFacingAngle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerFacingAngle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGivePlayerMoney ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerMoney ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcResetPlayerMoney ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcGetPlayerState ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcResetPlayerWeapons ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGivePlayerWeapon ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerArmedWeapon ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerIp ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerPing ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerWeapon ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerArmour ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerArmour ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerMapIcon ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRemovePlayerMapIcon ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerKeys ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerMarkerForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerAmmo ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerAmmo ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerWeaponData ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerWeaponState ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAllowPlayerTeleport ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcForceClassSelection ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerWantedLevel ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerWantedLevel ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerFightingStyle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerFightingStyle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerVelocity ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerVelocity ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsPlayerInRangeOfPoint ( AMX* a_AmxInterface, cell* a_Params );


cell AMX_NATIVE_CALL funcSetPlayerVirtualWorld ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerVirtualWorld ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcShowPlayerNameTagForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcEnableStuntBonusForAll ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcEnableStuntBonusForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTogglePlayerSpectating ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerDrunkLevel ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerDrunkLevel ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcPlayerSpectateVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcPlayerSpectatePlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcApplyAnimation ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcClearAnimations ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerAnimationIndex ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetAnimationName ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerSpecialAction ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerSpecialAction ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcStartRecordingPlayerData ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcStopRecordingPlayerData ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcPlayCrimeReportForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerShopName ( AMX* a_AmxInterface, cell* a_Params );



#endif