#ifndef __FUNC_AMX_H_
#define __FUNC_AMX_H_

#define CHECK_PARAMS(n) { if (a_Params[0] != (n * sizeof(cell))) { logprintf("SCRIPT: Bad parameter count (Count is %d, Should be %d): ", a_Params[0] / sizeof(cell), n); return 0; } }


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
cell AMX_NATIVE_CALL funcGetNetworkStats ( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcAddRule( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcEditRule( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRemoveRule( AMX* a_AmxInterface, cell* a_Params );

//cell AMX_NATIVE_CALL funcTogglePlayerWideScreen( AMX* a_AmxInterface, cell* a_Params ); // useless

cell AMX_NATIVE_CALL funcCreatePlayerExplosion( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcPlayAudioStreamForPlayer( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcStopAudioStreamForPlayer( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcRemoveBuildingForPlayer( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcPlayAudioStreamForAll( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcStopAudioStreamForAll( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcGetVehicleColor( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcTogglePlayerCollision( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcToggleVehicleCollision( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcToggleVehicleCollisionForPlayer( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcGetPlayerTargetPlayer( AMX* a_AmxInterface, cell* a_Params );

int amx_CustomInit ( AMX* a_AmxInterface );

// __FUNC_AMX_H_
#endif