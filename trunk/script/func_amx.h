#ifndef __FUNC_AMX_H_
#define __FUNC_AMX_H_

#define CHECK_PARAMS(n) { if (a_Params[0] != (n * sizeof(cell))) { logprintf("SCRIPT: Bad parameter count (Count is %d, Should be %d): ", a_Params[0] / sizeof(cell), n); return 0; } }

#define ADDR_ARRAY_CUSTOM_NATIVE			0x004CFAF0

#define FUNC_Print							0x00486700
#define FUNC_Printf							0x00486780
#define FUNC_Format							0x004867B0
#define FUNC_SetTimer						0x00486800
#define FUNC_KillTimer						0x00486880
#define FUNC_GetTickCount					0x004868A0
#define FUNC_GetMaxPlayers					0x004868B0
#define FUNC_SetTimerEx						0x00486C40
//#define FUNC_LimitGlobalChatRadius			0x004868D0
//#define FUNC_LimitPlayerMarkerRadius		0x004868F0
#define FUNC_SetWeather						0x00486F30
#define FUNC_SetPlayerWeather				0x0048D260
#define FUNC_CallRemoteFunction				0x00487300
#define FUNC_CallLocalFunction				0x004876B0
#define FUNC_Asin							0x00486F50
#define FUNC_Acos							0x00486F70
#define FUNC_Atan2							0x00486FB0
#define FUNC_Atan							0x00486F90
#define FUNC_Gpci							0x00485400

#define FUNC_GameModeExit					0x004842E0
#define FUNC_SetGameModeText				0x00484320
//#define FUNC_SetTeamCount					0x0040E460
//#define FUNC_AddPlayerClass					0x004843A0
//#define FUNC_AddPlayerClassEx				0x00484410
#define FUNC_AddStaticVehicle				0x00484480
#define FUNC_AddStaticVehicleEx				0x004845D0
#define FUNC_AddStaticPickup				0x00484AB0
#define FUNC_CreatePickup					0x00484B10
#define FUNC_DestroyPickup					0x00484B70
#define FUNC_SetPlayerWorldBounds			0x0048A900
#define FUNC_ShowNameTags					0x00486AD0

#define FUNC_ShowPlayerMarkers				0x00486AF0
#define FUNC_SetWorldTime					0x004865C0
#define FUNC_GetWeaponName					0x004855A0
#define FUNC_EnableTirePopping				0x00486F10
#define FUNC_AllowInteriorWeapons			0x00486B10
#define FUNC_SetGravity						0x00486FD0
#define FUNC_GetGravity						0x00487A10

#define FUNC_AllowAdminTeleport				0x00487240
#define FUNC_SetDeathDropAmount				0x004879F0
#define FUNC_CreateExplosion				0x0048E890
#define FUNC_SetDisabledWeapons				0x004883B0
#define FUNC_UsePlayerPedAnims				0x00486B30
#define FUNC_DisableInteriorEnterExits		0x00489080
#define FUNC_SetNameTagDrawDistance			0x00489090
#define FUNC_DisableNameTagLOS				0x004890B0
#define FUNC_ConnectNPC						0x00489760
#define FUNC_IsPlayerNPC					0x004899B0

#define FUNC_Create3DTextLabel					0x00489280
#define FUNC_Delete3DTextLabel					0x00489440
#define FUNC_Attach3DTextLabelToPlayer			0x004894F0
#define FUNC_Attach3DTextLabelToVehicle					0x00489550
#define FUNC_Update3DTextLabelText					0x004895B0
#define FUNC_CreatePlayer3DTextLabel					0x00489340
#define FUNC_DeletePlayer3DTextLabel					0x00489480
#define FUNC_UpdatePlayer3DTextLabelText					0x00489670

#define FUNC_ShowPlayerDialog					0x0048F760
#define FUNC_EnableZoneNames					0x004883D0



#define FUNC_IsPlayerAdmin					0x00484D90
#define FUNC_Kick					0x00484B90
#define FUNC_Ban					0x00484BD0
#define FUNC_BanEx					0x00484C80
#define FUNC_SendRconCommand					0x00486D10
#define FUNC_GetServerVarAsString					0x00488D50
#define FUNC_GetServerVarAsInt					0x00488DE0
#define FUNC_GetServerVarAsBool					0x00488E50
#define FUNC_SetSpawnInfo					0x00484DC0
#define FUNC_SpawnPlayer					0x0048AA50
#define FUNC_SetPlayerTeam					0x0048B2C0

#define FUNC_SetPlayerName					0x0048AB30
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

#define FUNC_SetPlayerChatBubble					0x0048F250
#define FUNC_SetPVarInt					0x00489BA0
#define FUNC_SetPVarString					0x00489C70
#define FUNC_SetPVarFloat					0x00489DA0
#define FUNC_GetPVarInt					0x00489E70
#define FUNC_GetPVarString					0x00489FF0
#define FUNC_GetPVarFloat					0x00489F30
#define FUNC_DeletePVar					0x0048A0D0
#define FUNC_GetPVarType					0x0048A190
#define FUNC_GetPVarNameAtIndex					0x0048A250
#define FUNC_GetPVarsUpperIndex					0x0048A2D0
#define FUNC_IsValidVehicle					0x00487030
#define FUNC_CreateVehicle					0x004855E0
#define FUNC_DestroyVehicle					0x00485660
#define FUNC_GetVehiclePos					0x004856A0
#define FUNC_SetVehiclePos					0x00485730
#define FUNC_GetVehicleZAngle					0x00486910
#define FUNC_GetVehicleRotationQuat					0x00486A00
#define FUNC_SetVehicleZAngle					0x0048CA90
#define FUNC_SetVehicleParamsForPlayer					0x0048C4A0
#define FUNC_ManualVehicleEngineAndLights					0x00486030
#define FUNC_SetVehicleParamsEx					0x00486050
#define FUNC_GetVehicleParamsEx					0x004860E0
#define FUNC_SetVehicleToRespawn					0x00484720
#define FUNC_RepairVehicle					0x00484760
#define FUNC_AddVehicleComponent					0x004847A0
#define FUNC_RemoveVehicleComponent					0x004847E0
#define FUNC_ChangeVehicleColor					0x00484820
#define FUNC_ChangeVehiclePaintjob					0x00484870
#define FUNC_LinkVehicleToInterior					0x0048A7F0
#define FUNC_SetVehicleHealth					0x00486FF0
#define FUNC_GetVehicleHealth					0x00487060
#define FUNC_AttachTrailerToVehicle					0x0048D740
#define FUNC_DetachTrailerFromVehicle					0x0048D870
#define FUNC_IsTrailerAttachedToVehicle					0x00487260
#define FUNC_GetVehicleTrailer					0x004872B0
#define FUNC_SetVehicleNumberPlate					0x004848B0
#define FUNC_GetVehicleModel					0x004849D0
#define FUNC_GetVehicleComponentInSlot					0x00484A20
#define FUNC_GetVehicleComponentType					0x00484A80
#define FUNC_GetVehicleVelocity					0x004891B0
#define FUNC_SetVehicleVelocity					0x0048EED0
#define FUNC_SetVehicleAngularVelocity					0x0048F020
#define FUNC_GetVehicleDamageStatus					0x0048A390
#define FUNC_UpdateVehicleDamageStatus					0x0048A470
#define FUNC_SetVehicleVirtualWorld					0x004850E0
#define FUNC_GetVehicleVirtualWorld					0x00485120
#define FUNC_SendClientMessage					0x00485900
#define FUNC_SendClientMessageToAll					0x004859C0
#define FUNC_SendDeathMessage					0x0048BBF0
#define FUNC_GameTextForAll					0x0048BCD0
#define FUNC_GameTextForPlayer					0x0048BE30
#define FUNC_SendPlayerMessageToPlayer					0x0048B910
#define FUNC_SendPlayerMessageToAll					0x0048BA90





#define FUNC_SetPlayerTime					0x004865E0
#define FUNC_TogglePlayerClock					0x004866C0
#define FUNC_GetPlayerTime					0x00486620
#define FUNC_HTTP					0x0048A640


/**
 *	Original
 */
extern cell ( __cdecl* _funcPrint )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcPrintf )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcFormat )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetTimer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcKillTimer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetTickCount )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetMaxPlayers )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetTimerEx )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcLimitGlobalChatRadius )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcLimitPlayerMarkerRadius )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetWeather )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerWeather )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcCallRemoteFunction )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcCallLocalFunction )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAsin )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAcos )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAtan2 )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAtan )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGpci )( AMX* a_AmxInterface, cell* a_Params );

extern cell ( __cdecl* _funcGameModeExit )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetGameModeText )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcSetTeamCount )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcAddPlayerClass )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcAddPlayerClassEx )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAddStaticVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAddStaticVehicleEx )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAddStaticPickup )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcCreatePickup )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcDestroyPickup )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerWorldBounds )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcShowNameTags )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcShowPlayerMarkers )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetWorldTime )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetWeaponName )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcEnableTirePopping )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAllowInteriorWeapons )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetGravity )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetGravity )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAllowAdminTeleport )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetDeathDropAmount )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcCreateExplosion )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetDisabledWeapons )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcUsePlayerPedAnims )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcDisableInteriorEnterExits )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetNameTagDrawDistance )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcDisableNameTagLOS )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcConnectNPC )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcIsPlayerNPC )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcCreate3DTextLabel )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcDelete3DTextLabel )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAttach3DTextLabelToPlayer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAttach3DTextLabelToVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcUpdate3DTextLabelText )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcCreatePlayer3DTextLabel )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcDeletePlayer3DTextLabel )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcUpdatePlayer3DTextLabelText )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcShowPlayerDialog )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcEnableZoneNames )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcIsPlayerAdmin )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcKick )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcBan )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcBanEx )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSendRconCommand )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetServerVarAsString )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetServerVarAsInt )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetServerVarAsBool )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetSpawnInfo )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSpawnPlayer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPlayerTeam )( AMX* a_AmxInterface, cell* a_Params );

extern cell ( __cdecl* _funcSetPlayerName )( AMX* a_AmxInterface, cell* a_Params );
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

extern cell ( __cdecl* _funcSetPlayerChatBubble )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPVarInt )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPVarString )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetPVarFloat )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPVarInt )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPVarString )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPVarFloat )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcDeletePVar )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPVarType )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPVarNameAtIndex )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPVarsUpperIndex )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcIsValidVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcCreateVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcDestroyVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetVehiclePos )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetVehiclePos )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetVehicleZAngle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetVehicleRotationQuat )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetVehicleZAngle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetVehicleParamsForPlayer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcManualVehicleEngineAndLights )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetVehicleParamsEx )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetVehicleParamsEx )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetVehicleToRespawn )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcRepairVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAddVehicleComponent )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcRemoveVehicleComponent )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcChangeVehicleColor )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcChangeVehiclePaintjob )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcLinkVehicleToInterior )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetVehicleHealth )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetVehicleHealth )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcAttachTrailerToVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcDetachTrailerFromVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcIsTrailerAttachedToVehicle )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetVehicleTrailer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetVehicleNumberPlate )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetVehicleModel )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetVehicleComponentInSlot )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetVehicleComponentType )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetVehicleVelocity )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetVehicleVelocity )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetVehicleAngularVelocity )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetVehicleDamageStatus )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcUpdateVehicleDamageStatus )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSetVehicleVirtualWorld )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetVehicleVirtualWorld )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSendClientMessage )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSendClientMessageToAll )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSendDeathMessage )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGameTextForAll )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGameTextForPlayer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSendPlayerMessageToPlayer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcSendPlayerMessageToAll )( AMX* a_AmxInterface, cell* a_Params );



extern cell ( __cdecl* _funcSetPlayerTime )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTogglePlayerClock )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcGetPlayerTime )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcHTTP )( AMX* a_AmxInterface, cell* a_Params );


/**
 *	Detoured
 */
cell AMX_NATIVE_CALL funcPrint ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcPrintf ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcFormat ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetTimer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcKillTimer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetTickCount ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetMaxPlayers ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetTimerEx ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcLimitGlobalChatRadius ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcLimitPlayerMarkerRadius ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetWeather ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerWeather ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcCallRemoteFunction ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcCallLocalFunction ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAsin ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAcos ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAtan2 ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAtan ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGpci ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcGameModeExit ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetGameModeText ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetTeamCount ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAddPlayerClass ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAddPlayerClassEx ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAddStaticVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAddStaticVehicleEx ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAddStaticPickup ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcCreatePickup ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDestroyPickup ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerWorldBounds ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcShowNameTags ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcShowPlayerMarkers ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetWorldTime ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetWeaponName ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcEnableTirePopping ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAllowInteriorWeapons ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetGravity ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetGravity ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAllowAdminTeleport ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetDeathDropAmount ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcCreateExplosion ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetDisabledWeapons ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcUsePlayerPedAnims ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDisableInteriorEnterExits ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetNameTagDrawDistance ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDisableNameTagLOS ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcConnectNPC ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsPlayerNPC ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcCreate3DTextLabel ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDelete3DTextLabel ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAttach3DTextLabelToPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAttach3DTextLabelToVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcUpdate3DTextLabelText ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcCreatePlayer3DTextLabel ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDeletePlayer3DTextLabel ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcUpdatePlayer3DTextLabelText ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcShowPlayerDialog ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcEnableZoneNames ( AMX* a_AmxInterface, cell* a_Params );


cell AMX_NATIVE_CALL funcIsPlayerAdmin ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcKick ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcBan ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcBanEx ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSendRconCommand ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetServerVarAsString ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetServerVarAsInt ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetServerVarAsBool ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetSpawnInfo ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSpawnPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerTeam ( AMX* a_AmxInterface, cell* a_Params );

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

cell AMX_NATIVE_CALL funcSetPlayerChatBubble ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPVarInt ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPVarString ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPVarFloat ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPVarInt ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPVarString ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPVarFloat ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDeletePVar ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPVarType ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPVarNameAtIndex ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPVarsUpperIndex ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsValidVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcCreateVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDestroyVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetVehiclePos ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetVehiclePos ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetVehicleZAngle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetVehicleRotationQuat ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetVehicleZAngle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetVehicleParamsForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcManualVehicleEngineAndLights ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetVehicleParamsEx ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetVehicleParamsEx ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetVehicleToRespawn ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRepairVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAddVehicleComponent ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRemoveVehicleComponent ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcChangeVehicleColor ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcChangeVehiclePaintjob ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcLinkVehicleToInterior ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetVehicleHealth ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetVehicleHealth ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAttachTrailerToVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDetachTrailerFromVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsTrailerAttachedToVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetVehicleTrailer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetVehicleNumberPlate ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetVehicleModel ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetVehicleComponentInSlot ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetVehicleComponentType ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetVehicleVelocity ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetVehicleVelocity ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetVehicleAngularVelocity ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetVehicleDamageStatus ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcUpdateVehicleDamageStatus ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetVehicleVirtualWorld ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetVehicleVirtualWorld ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSendClientMessage ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSendClientMessageToAll ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSendDeathMessage ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGameTextForAll ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGameTextForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSendPlayerMessageToPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSendPlayerMessageToAll ( AMX* a_AmxInterface, cell* a_Params );



cell AMX_NATIVE_CALL funcSetPlayerTime ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTogglePlayerClock ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerTime ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcHTTP ( AMX* a_AmxInterface, cell* a_Params );

int amx_CustomInit ( AMX* a_AmxInterface );

// __FUNC_AMX_H_
#endif