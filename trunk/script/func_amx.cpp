#include "../main.h"
#include "../pool/class_pickuppool.h"
#include "../../SDK/amx/amx.h"
#include "../../SDK/plugincommon.h"

#include "func_amx.h"
#include "amx/func_amx_gangzone.h"
#include "amx/func_amx_object.h"
#include "amx/func_amx_textdraw.h"


AMX_NATIVE_INFO __AmxScriptNative[];

/**
 *	Original
 */
cell ( __cdecl* _funcPrint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Print;
cell ( __cdecl* _funcPrintf )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Printf;
cell ( __cdecl* _funcFormat )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Format;
cell ( __cdecl* _funcSetTimer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetTimer;
cell ( __cdecl* _funcKillTimer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_KillTimer;
cell ( __cdecl* _funcGetTickCount )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetTickCount;
cell ( __cdecl* _funcGetMaxPlayers )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetMaxPlayers;
cell ( __cdecl* _funcSetTimerEx )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetTimerEx;
cell ( __cdecl* _funcLimitGlobalChatRadius )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_LimitGlobalChatRadius;
cell ( __cdecl* _funcLimitPlayerMarkerRadius )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_LimitPlayerMarkerRadius;
cell ( __cdecl* _funcSetWeather )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetWeather;
cell ( __cdecl* _funcSetPlayerWeather )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerWeather;
cell ( __cdecl* _funcCallRemoteFunction )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_CallRemoteFunction;
cell ( __cdecl* _funcCallLocalFunction )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_CallLocalFunction;
cell ( __cdecl* _funcAsin )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Asin;
cell ( __cdecl* _funcAcos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Acos;
cell ( __cdecl* _funcAtan2 )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Atan2;
cell ( __cdecl* _funcAtan )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Atan;
cell ( __cdecl* _funcGpci )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Gpci;

cell ( __cdecl* _funcGameModeExit )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GameModeExit;
cell ( __cdecl* _funcSetGameModeText )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetGameModeText;
cell ( __cdecl* _funcSetTeamCount )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetTeamCount;
cell ( __cdecl* _funcAddPlayerClass )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AddPlayerClass;
cell ( __cdecl* _funcAddPlayerClassEx )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AddPlayerClassEx;
cell ( __cdecl* _funcAddStaticVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AddStaticVehicle;
cell ( __cdecl* _funcAddStaticVehicleEx )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AddStaticVehicleEx;
cell ( __cdecl* _funcAddStaticPickup )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AddStaticPickup;
cell ( __cdecl* _funcCreatePickup )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_CreatePickup;
cell ( __cdecl* _funcDestroyPickup )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DestroyPickup;
cell ( __cdecl* _funcSetPlayerWorldBounds )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerWorldBounds;
cell ( __cdecl* _funcShowNameTags )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ShowNameTags;
cell ( __cdecl* _funcShowPlayerMarkers )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ShowPlayerMarkers;
cell ( __cdecl* _funcSetWorldTime )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetWorldTime;
cell ( __cdecl* _funcGetWeaponName )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetWeaponName;
cell ( __cdecl* _funcEnableTirePopping )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_EnableTirePopping;
cell ( __cdecl* _funcAllowInteriorWeapons )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AllowInteriorWeapons;
cell ( __cdecl* _funcSetGravity )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetGravity;
cell ( __cdecl* _funcGetGravity )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetGravity;
cell ( __cdecl* _funcAllowAdminTeleport )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AllowAdminTeleport;
cell ( __cdecl* _funcSetDeathDropAmount )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetDeathDropAmount;
cell ( __cdecl* _funcCreateExplosion )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_CreateExplosion;
cell ( __cdecl* _funcSetDisabledWeapons )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetDisabledWeapons;
cell ( __cdecl* _funcUsePlayerPedAnims )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_UsePlayerPedAnims;
cell ( __cdecl* _funcDisableInteriorEnterExits )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DisableInteriorEnterExits;
cell ( __cdecl* _funcSetNameTagDrawDistance )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetNameTagDrawDistance;
cell ( __cdecl* _funcDisableNameTagLOS )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DisableNameTagLOS;
cell ( __cdecl* _funcConnectNPC )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ConnectNPC;
cell ( __cdecl* _funcIsPlayerNPC )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerNPC;

cell ( __cdecl* _funcCreate3DTextLabel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Create3DTextLabel;
cell ( __cdecl* _funcDelete3DTextLabel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Delete3DTextLabel;
cell ( __cdecl* _funcAttach3DTextLabelToPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Attach3DTextLabelToPlayer;
cell ( __cdecl* _funcAttach3DTextLabelToVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Attach3DTextLabelToVehicle;
cell ( __cdecl* _funcUpdate3DTextLabelText )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Update3DTextLabelText;
cell ( __cdecl* _funcCreatePlayer3DTextLabel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_CreatePlayer3DTextLabel;
cell ( __cdecl* _funcDeletePlayer3DTextLabel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DeletePlayer3DTextLabel;
cell ( __cdecl* _funcUpdatePlayer3DTextLabelText )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_UpdatePlayer3DTextLabelText;
cell ( __cdecl* _funcShowPlayerDialog )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ShowPlayerDialog;
cell ( __cdecl* _funcEnableZoneNames )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_EnableZoneNames;
cell ( __cdecl* _funcIsPlayerAdmin )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerAdmin;
cell ( __cdecl* _funcKick )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Kick;
cell ( __cdecl* _funcBan )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_Ban;
cell ( __cdecl* _funcBanEx )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_BanEx;
cell ( __cdecl* _funcSendRconCommand )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SendRconCommand;
cell ( __cdecl* _funcGetServerVarAsString )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetServerVarAsString;
cell ( __cdecl* _funcGetServerVarAsInt )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetServerVarAsInt;
cell ( __cdecl* _funcGetServerVarAsBool )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetServerVarAsBool;
cell ( __cdecl* _funcSetSpawnInfo )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetSpawnInfo;
cell ( __cdecl* _funcSpawnPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SpawnPlayer;
cell ( __cdecl* _funcSetPlayerTeam )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerTeam;
cell ( __cdecl* _funcGetPlayerTeam )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerTeam;
cell ( __cdecl* _funcSetPlayerName )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerName;
cell ( __cdecl* _funcSetPlayerSkin )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerSkin;
cell ( __cdecl* _funcGetPlayerSkin )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerSkin;
cell ( __cdecl* _funcGetPlayerPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerPos;
cell ( __cdecl* _funcSetPlayerPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerPos;
cell ( __cdecl* _funcSetPlayerPosFindZ )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerPosFindZ;
cell ( __cdecl* _funcGetPlayerHealth )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerHealth;
cell ( __cdecl* _funcSetPlayerHealth )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerHealth;
cell ( __cdecl* _funcSetPlayerColor )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerColor;
cell ( __cdecl* _funcGetPlayerColor )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerColor;
cell ( __cdecl* _funcGetPlayerVehicleID )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerVehicleID;
cell ( __cdecl* _funcGetPlayerVehicleSeat )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerVehicleSeat;
cell ( __cdecl* _funcGetPlayerSurfingVehicleID )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerSurfingVehicleID;
cell ( __cdecl* _funcPutPlayerInVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_PutPlayerInVehicle;
cell ( __cdecl* _funcRemovePlayerFromVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_RemovePlayerFromVehicle;
cell ( __cdecl* _funcIsPlayerInVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerInVehicle;
cell ( __cdecl* _funcIsPlayerInAnyVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerInAnyVehicle;
cell ( __cdecl* _funcGetPlayerName )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerName;
cell ( __cdecl* _funcSetPlayerCheckpoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerCheckpoint;
cell ( __cdecl* _funcDisablePlayerCheckpoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DisablePlayerCheckpoint;
cell ( __cdecl* _funcIsPlayerInCheckpoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerInCheckpoint;
cell ( __cdecl* _funcSetPlayerRaceCheckpoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerRaceCheckpoint;
cell ( __cdecl* _funcDisablePlayerRaceCheckpoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DisablePlayerRaceCheckpoint;
cell ( __cdecl* _funcIsPlayerInRaceCheckpoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerInRaceCheckpoint;
cell ( __cdecl* _funcSetPlayerInterior )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerInterior;
cell ( __cdecl* _funcGetPlayerInterior )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerInterior;
cell ( __cdecl* _funcSetPlayerAttachedObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerAttachedObject;
cell ( __cdecl* _funcRemovePlayerAttachedObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_RemovePlayerAttachedObject;
cell ( __cdecl* _funcIsPlayerAttachedObjectSlotUsed )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerAttachedObjectSlotUsed;
cell ( __cdecl* _funcSetPlayerCameraLookAt )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerCameraLookAt;
cell ( __cdecl* _funcSetPlayerCameraPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerCameraPos;
cell ( __cdecl* _funcSetCameraBehindPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetCameraBehindPlayer;
cell ( __cdecl* _funcGetPlayerCameraPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerCameraPos;
cell ( __cdecl* _funcGetPlayerCameraFrontVector )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerCameraFrontVector;
cell ( __cdecl* _funcTogglePlayerControllable )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_TogglePlayerControllable;
cell ( __cdecl* _funcPlayerPlaySound )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_PlayerPlaySound;
cell ( __cdecl* _funcSetPlayerScore )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerScore;
cell ( __cdecl* _funcGetPlayerScore )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerScore;
cell ( __cdecl* _funcSetPlayerFacingAngle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerFacingAngle;
cell ( __cdecl* _funcGetPlayerFacingAngle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerFacingAngle;
cell ( __cdecl* _funcGivePlayerMoney )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GivePlayerMoney;
cell ( __cdecl* _funcGetPlayerMoney )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerMoney;
cell ( __cdecl* _funcResetPlayerMoney )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ResetPlayerMoney;
cell ( __cdecl* _funcIsPlayerConnected )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerConnected;
cell ( __cdecl* _funcGetPlayerState )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerState;
cell ( __cdecl* _funcResetPlayerWeapons )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ResetPlayerWeapons;
cell ( __cdecl* _funcGivePlayerWeapon )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GivePlayerWeapon;
cell ( __cdecl* _funcSetPlayerArmedWeapon )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerArmedWeapon;
cell ( __cdecl* _funcGetPlayerIp )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerIp;
cell ( __cdecl* _funcGetPlayerPing )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerPing;
cell ( __cdecl* _funcGetPlayerWeapon )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerWeapon;
cell ( __cdecl* _funcSetPlayerArmour )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerArmour;
cell ( __cdecl* _funcGetPlayerArmour )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerArmour;
cell ( __cdecl* _funcSetPlayerMapIcon )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerMapIcon;
cell ( __cdecl* _funcRemovePlayerMapIcon )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_RemovePlayerMapIcon;
cell ( __cdecl* _funcGetPlayerKeys )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerKeys;
cell ( __cdecl* _funcSetPlayerMarkerForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerMarkerForPlayer;
cell ( __cdecl* _funcGetPlayerAmmo )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerAmmo;
cell ( __cdecl* _funcSetPlayerAmmo )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerAmmo;
cell ( __cdecl* _funcGetPlayerWeaponData )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerWeaponData;
cell ( __cdecl* _funcGetPlayerWeaponState )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerWeaponState;
cell ( __cdecl* _funcAllowPlayerTeleport )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AllowPlayerTeleport;
cell ( __cdecl* _funcForceClassSelection )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ForceClassSelection;
cell ( __cdecl* _funcSetPlayerWantedLevel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerWantedLevel;
cell ( __cdecl* _funcGetPlayerWantedLevel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerWantedLevel;
cell ( __cdecl* _funcGetPlayerFightingStyle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerFightingStyle;
cell ( __cdecl* _funcSetPlayerFightingStyle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerFightingStyle;
cell ( __cdecl* _funcGetPlayerVelocity )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerVelocity;
cell ( __cdecl* _funcSetPlayerVelocity )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerVelocity;
cell ( __cdecl* _funcIsPlayerInRangeOfPoint )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerInRangeOfPoint;
cell ( __cdecl* _funcIsPlayerStreamedIn )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsPlayerStreamedIn;
cell ( __cdecl* _funcIsVehicleStreamedIn )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsVehicleStreamedIn;
cell ( __cdecl* _funcSetPlayerVirtualWorld )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerVirtualWorld;
cell ( __cdecl* _funcGetPlayerVirtualWorld )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerVirtualWorld;
cell ( __cdecl* _funcShowPlayerNameTagForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ShowPlayerNameTagForPlayer;
cell ( __cdecl* _funcEnableStuntBonusForAll )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_EnableStuntBonusForAll;
cell ( __cdecl* _funcEnableStuntBonusForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_EnableStuntBonusForPlayer;
cell ( __cdecl* _funcTogglePlayerSpectating )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_TogglePlayerSpectating;
cell ( __cdecl* _funcGetPlayerDrunkLevel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerDrunkLevel;
cell ( __cdecl* _funcSetPlayerDrunkLevel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerDrunkLevel;
cell ( __cdecl* _funcPlayerSpectateVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_PlayerSpectateVehicle;
cell ( __cdecl* _funcPlayerSpectatePlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_PlayerSpectatePlayer;
cell ( __cdecl* _funcApplyAnimation )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ApplyAnimation;
cell ( __cdecl* _funcClearAnimations )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ClearAnimations;
cell ( __cdecl* _funcGetPlayerAnimationIndex )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerAnimationIndex;
cell ( __cdecl* _funcGetAnimationName )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetAnimationName;
cell ( __cdecl* _funcSetPlayerSpecialAction )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerSpecialAction;
cell ( __cdecl* _funcGetPlayerSpecialAction )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerSpecialAction;
cell ( __cdecl* _funcStartRecordingPlayerData )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_StartRecordingPlayerData;
cell ( __cdecl* _funcStopRecordingPlayerData )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_StopRecordingPlayerData;
cell ( __cdecl* _funcPlayCrimeReportForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_PlayCrimeReportForPlayer;
cell ( __cdecl* _funcSetPlayerShopName )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerShopName;
cell ( __cdecl* _funcSetPlayerSkillLevel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerSkillLevel;
cell ( __cdecl* _funcSetPlayerChatBubble )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerChatBubble;
cell ( __cdecl* _funcSetPVarInt )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPVarInt;
cell ( __cdecl* _funcSetPVarString )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPVarString;
cell ( __cdecl* _funcSetPVarFloat )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPVarFloat;
cell ( __cdecl* _funcGetPVarInt )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPVarInt;
cell ( __cdecl* _funcGetPVarString )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPVarString;
cell ( __cdecl* _funcGetPVarFloat )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPVarFloat;
cell ( __cdecl* _funcDeletePVar )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DeletePVar;
cell ( __cdecl* _funcGetPVarType )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPVarType;
cell ( __cdecl* _funcGetPVarNameAtIndex )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPVarNameAtIndex;
cell ( __cdecl* _funcGetPVarsUpperIndex )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPVarsUpperIndex;
cell ( __cdecl* _funcIsValidVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsValidVehicle;
cell ( __cdecl* _funcCreateVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_CreateVehicle;
cell ( __cdecl* _funcDestroyVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DestroyVehicle;
cell ( __cdecl* _funcGetVehiclePos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetVehiclePos;
cell ( __cdecl* _funcSetVehiclePos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetVehiclePos;
cell ( __cdecl* _funcGetVehicleZAngle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetVehicleZAngle;
cell ( __cdecl* _funcGetVehicleRotationQuat )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetVehicleRotationQuat;
cell ( __cdecl* _funcSetVehicleZAngle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetVehicleZAngle;
cell ( __cdecl* _funcSetVehicleParamsForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetVehicleParamsForPlayer;
cell ( __cdecl* _funcManualVehicleEngineAndLights )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ManualVehicleEngineAndLights;
cell ( __cdecl* _funcSetVehicleParamsEx )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetVehicleParamsEx;
cell ( __cdecl* _funcGetVehicleParamsEx )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetVehicleParamsEx;
cell ( __cdecl* _funcSetVehicleToRespawn )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetVehicleToRespawn;
cell ( __cdecl* _funcRepairVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_RepairVehicle;
cell ( __cdecl* _funcAddVehicleComponent )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AddVehicleComponent;
cell ( __cdecl* _funcRemoveVehicleComponent )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_RemoveVehicleComponent;
cell ( __cdecl* _funcChangeVehicleColor )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ChangeVehicleColor;
cell ( __cdecl* _funcChangeVehiclePaintjob )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ChangeVehiclePaintjob;
cell ( __cdecl* _funcLinkVehicleToInterior )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_LinkVehicleToInterior;
cell ( __cdecl* _funcSetVehicleHealth )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetVehicleHealth;
cell ( __cdecl* _funcGetVehicleHealth )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetVehicleHealth;
cell ( __cdecl* _funcAttachTrailerToVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AttachTrailerToVehicle;
cell ( __cdecl* _funcDetachTrailerFromVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DetachTrailerFromVehicle;
cell ( __cdecl* _funcIsTrailerAttachedToVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsTrailerAttachedToVehicle;
cell ( __cdecl* _funcGetVehicleTrailer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetVehicleTrailer;
cell ( __cdecl* _funcSetVehicleNumberPlate )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetVehicleNumberPlate;
cell ( __cdecl* _funcGetVehicleModel )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetVehicleModel;
cell ( __cdecl* _funcGetVehicleComponentInSlot )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetVehicleComponentInSlot;
cell ( __cdecl* _funcGetVehicleComponentType )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetVehicleComponentType;
cell ( __cdecl* _funcGetVehicleVelocity )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetVehicleVelocity;
cell ( __cdecl* _funcSetVehicleVelocity )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetVehicleVelocity;
cell ( __cdecl* _funcSetVehicleAngularVelocity )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetVehicleAngularVelocity;
cell ( __cdecl* _funcGetVehicleDamageStatus )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetVehicleDamageStatus;
cell ( __cdecl* _funcUpdateVehicleDamageStatus )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_UpdateVehicleDamageStatus;
cell ( __cdecl* _funcSetVehicleVirtualWorld )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetVehicleVirtualWorld;
cell ( __cdecl* _funcGetVehicleVirtualWorld )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetVehicleVirtualWorld;
cell ( __cdecl* _funcSendClientMessage )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SendClientMessage;
cell ( __cdecl* _funcSendClientMessageToAll )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SendClientMessageToAll;
cell ( __cdecl* _funcSendDeathMessage )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SendDeathMessage;
cell ( __cdecl* _funcGameTextForAll )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GameTextForAll;
cell ( __cdecl* _funcGameTextForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GameTextForPlayer;
cell ( __cdecl* _funcSendPlayerMessageToPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SendPlayerMessageToPlayer;
cell ( __cdecl* _funcSendPlayerMessageToAll )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SendPlayerMessageToAll;

cell ( __cdecl* _funcCreateMenu )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_CreateMenu;
cell ( __cdecl* _funcDestroyMenu )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DestroyMenu;
cell ( __cdecl* _funcAddMenuItem )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AddMenuItem;
cell ( __cdecl* _funcSetMenuColumnHeader )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetMenuColumnHeader;
cell ( __cdecl* _funcShowMenuForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_ShowMenuForPlayer;
cell ( __cdecl* _funcHideMenuForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_HideMenuForPlayer;
cell ( __cdecl* _funcIsValidMenu )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsValidMenu;
cell ( __cdecl* _funcDisableMenu )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DisableMenu;
cell ( __cdecl* _funcDisableMenuRow )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DisableMenuRow;
cell ( __cdecl* _funcGetPlayerMenu )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerMenu;
cell ( __cdecl* _funcSetPlayerTime )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerTime;
cell ( __cdecl* _funcTogglePlayerClock )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_TogglePlayerClock;
cell ( __cdecl* _funcGetPlayerTime )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerTime;
cell ( __cdecl* _funcHTTP )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_HTTP;

/**
 *	Detoured
 */
cell AMX_NATIVE_CALL funcPrint ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcPrint()" );
	return _funcPrint ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcPrintf ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcPrintf()" );
	return _funcPrintf ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcFormat ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcFormat()" );
	return _funcFormat ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcSetTimer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetTimer()" );
	return _funcSetTimer ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcKillTimer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcKillTimer()" );
	return _funcKillTimer ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcGetTickCount ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetTickCount()" );
	return _funcGetTickCount ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcGetMaxPlayers ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetMaxPlayers()" );
	return _funcGetMaxPlayers ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcSetTimerEx ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetTimerEx()" );
	return _funcSetTimerEx ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcLimitGlobalChatRadius ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcLimitGlobalChatRadius()" );
	return _funcLimitGlobalChatRadius ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcLimitPlayerMarkerRadius ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcLimitPlayerMarkerRadius()" );
	return _funcLimitPlayerMarkerRadius ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcSetWeather ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetWeather()" );
	return _funcSetWeather ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcSetPlayerWeather ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerWeather()" );
	return _funcSetPlayerWeather ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcCallRemoteFunction ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCallRemoteFunction()" );
	return _funcCallRemoteFunction ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcCallLocalFunction ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCallLocalFunction()" );
	return _funcCallLocalFunction ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcAsin ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAsin()" );
	return _funcAsin ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcAcos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAcos()" );
	return _funcAcos ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcAtan2 ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAtan2()" );
	return _funcAtan2 ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcAtan ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAtan()" );
	return _funcAtan ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcGpci ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGpci()" );
	return _funcGpci ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcGameModeExit ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGameModeExit()" );
	return _funcGameModeExit ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcSetGameModeText ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetGameModeText()" );
	return _funcSetGameModeText ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcSetTeamCount ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetTeamCount()" );
	return _funcSetTeamCount ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcAddPlayerClass ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAddPlayerClass()" );
	return _funcAddPlayerClass ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcAddPlayerClassEx ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAddPlayerClassEx()" );
	return _funcAddPlayerClassEx ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcAddStaticVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAddStaticVehicle()" );
	return _funcAddStaticVehicle ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcAddStaticVehicleEx ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAddStaticVehicleEx()" );
	return _funcAddStaticVehicleEx ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcAddStaticPickup ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAddStaticPickup()" );
	/*
	CHECK_PARAMS ( 6 );

	if ( __PickupPool->New ( a_Params[1],a_Params[2],amx_ctof(a_Params[3]),amx_ctof(a_Params[4]),amx_ctof(a_Params[5]),amx_ctof(a_Params[6])) != -1) return 1;
	return 0;
	*/
	return _funcAddStaticPickup ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcCreatePickup ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCreatePickup()" );
	/*
	CHECK_PARAMS ( 6 );

	if ( __PickupPool->New ( a_Params[1],a_Params[2],amx_ctof(a_Params[3]),amx_ctof(a_Params[4]),amx_ctof(a_Params[5]),amx_ctof(a_Params[6])) != -1) return 1;
	return 0;*/
	return _funcCreatePickup ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcDestroyPickup ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDestroyPickup()" );
	return _funcDestroyPickup ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcSetPlayerWorldBounds ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerWorldBounds()" );
	return _funcSetPlayerWorldBounds ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcShowNameTags ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcShowNameTags()" );
	return _funcShowNameTags ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcShowPlayerMarkers ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcShowPlayerMarkers()" );
	return _funcShowPlayerMarkers ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcSetWorldTime ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetWorldTime()" );
	return _funcSetWorldTime ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcGetWeaponName ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetWeaponName()" );
	return _funcGetWeaponName ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcEnableTirePopping ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcEnableTirePopping()" );
	return _funcEnableTirePopping ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcAllowInteriorWeapons ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAllowInteriorWeapons()" );
	return _funcAllowInteriorWeapons ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcSetGravity ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetGravity()" );
	return _funcSetGravity ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcGetGravity ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetGravity()" );
	return _funcGetGravity ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcAllowAdminTeleport ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAllowAdminTeleport()" );
	return _funcAllowAdminTeleport ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcSetDeathDropAmount ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetDeathDropAmount()" );
	return _funcSetDeathDropAmount ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcCreateExplosion ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCreateExplosion()" );
	return _funcCreateExplosion ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcSetDisabledWeapons ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetDisabledWeapons()" );
	return _funcSetDisabledWeapons ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcUsePlayerPedAnims ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcUsePlayerPedAnims()" );
	return _funcUsePlayerPedAnims ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcDisableInteriorEnterExits ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDisableInteriorEnterExits()" );
	return _funcDisableInteriorEnterExits ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcSetNameTagDrawDistance ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetNameTagDrawDistance()" );
	return _funcSetNameTagDrawDistance ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcDisableNameTagLOS ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDisableNameTagLOS()" );
	return _funcDisableNameTagLOS ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcConnectNPC ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcConnectNPC()" );
	return _funcConnectNPC ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcIsPlayerNPC ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsPlayerNPC()" );
	return _funcIsPlayerNPC ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcCreate3DTextLabel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCreate3DTextLabel()" );
	return _funcCreate3DTextLabel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcDelete3DTextLabel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDelete3DTextLabel()" );
	return _funcDelete3DTextLabel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcAttach3DTextLabelToPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAttach3DTextLabelToPlayer()" );
	return _funcAttach3DTextLabelToPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcAttach3DTextLabelToVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAttach3DTextLabelToVehicle()" );
	return _funcAttach3DTextLabelToVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcUpdate3DTextLabelText ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcUpdate3DTextLabelText()" );
	return _funcUpdate3DTextLabelText ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcCreatePlayer3DTextLabel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCreatePlayer3DTextLabel()" );
	return _funcCreatePlayer3DTextLabel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcDeletePlayer3DTextLabel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDeletePlayer3DTextLabel()" );
	return _funcDeletePlayer3DTextLabel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcUpdatePlayer3DTextLabelText ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcUpdatePlayer3DTextLabelText()" );
	return _funcUpdatePlayer3DTextLabelText ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcShowPlayerDialog ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcShowPlayerDialog()" );
	return _funcShowPlayerDialog ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcEnableZoneNames ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcEnableZoneNames()" );
	return _funcEnableZoneNames ( a_AmxInterface, a_Params );
}


cell AMX_NATIVE_CALL funcIsPlayerAdmin ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsPlayerAdmin()" );
	return _funcIsPlayerAdmin ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcKick ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcKick()" );
	return _funcKick ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcBan ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcBan()" );
	return _funcBan ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcBanEx ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcBanEx()" );
	return _funcBanEx ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSendRconCommand ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSendRconCommand()" );
	return _funcSendRconCommand ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetServerVarAsString ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetServerVarAsString()" );
	return _funcGetServerVarAsString ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetServerVarAsInt ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetServerVarAsInt()" );
	return _funcGetServerVarAsInt ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetServerVarAsBool ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetServerVarAsBool()" );
	return _funcGetServerVarAsBool ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetSpawnInfo ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetSpawnInfo()" );
	return _funcSetSpawnInfo ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSpawnPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSpawnPlayer()" );
	return _funcSpawnPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerTeam ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerTeam()" );
	return _funcSetPlayerTeam ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerTeam ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerTeam()" );
	return _funcGetPlayerTeam ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerName ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerName()" );
	return _funcSetPlayerName ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerSkin ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerSkin()" );
	return _funcSetPlayerSkin ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerSkin ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerSkin()" );
	return _funcGetPlayerSkin ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerPos()" );
	return _funcGetPlayerPos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerPos()" );
	return _funcSetPlayerPos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerPosFindZ ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerPosFindZ()" );
	return _funcSetPlayerPosFindZ ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerHealth ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerHealth()" );
	return _funcGetPlayerHealth ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerHealth ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerHealth()" );
	return _funcSetPlayerHealth ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerColor ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerColor()" );
	return _funcSetPlayerColor ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerColor ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerColor()" );
	return _funcGetPlayerColor ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerVehicleID ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerVehicleID()" );
	return _funcGetPlayerVehicleID ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerVehicleSeat ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerVehicleSeat()" );
	return _funcGetPlayerVehicleSeat ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerSurfingVehicleID ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerSurfingVehicleID()" );
	return _funcGetPlayerSurfingVehicleID ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcPutPlayerInVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcPutPlayerInVehicle()" );
	return _funcPutPlayerInVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcRemovePlayerFromVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcRemovePlayerFromVehicle()" );
	return _funcRemovePlayerFromVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsPlayerInVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsPlayerInVehicle()" );
	return _funcIsPlayerInVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsPlayerInAnyVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsPlayerInAnyVehicle()" );
	return _funcIsPlayerInAnyVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerName ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerName()" );
	return _funcGetPlayerName ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerCheckpoint()" );
	return _funcSetPlayerCheckpoint ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcDisablePlayerCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDisablePlayerCheckpoint()" );
	return _funcDisablePlayerCheckpoint ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsPlayerInCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsPlayerInCheckpoint()" );
	return _funcIsPlayerInCheckpoint ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerRaceCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerRaceCheckpoint()" );
	return _funcSetPlayerRaceCheckpoint ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcDisablePlayerRaceCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDisablePlayerRaceCheckpoint()" );
	return _funcDisablePlayerRaceCheckpoint ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsPlayerInRaceCheckpoint ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsPlayerInRaceCheckpoint()" );
	return _funcIsPlayerInRaceCheckpoint ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerInterior ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerInterior()" );
	return _funcSetPlayerInterior ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerInterior ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerInterior()" );
	return _funcGetPlayerInterior ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerAttachedObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerAttachedObject()" );
	return _funcSetPlayerAttachedObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcRemovePlayerAttachedObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcRemovePlayerAttachedObject()" );
	return _funcRemovePlayerAttachedObject ( a_AmxInterface, a_Params );
}

cell AMX_NATIVE_CALL funcIsPlayerAttachedObjectSlotUsed ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsPlayerAttachedObjectSlotUsed()" );
	return _funcIsPlayerAttachedObjectSlotUsed ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerCameraLookAt ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerCameraLookAt()" );
	return _funcSetPlayerCameraLookAt ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerCameraPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerCameraPos()" );
	return _funcSetPlayerCameraPos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetCameraBehindPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetCameraBehindPlayer()" );
	return _funcSetCameraBehindPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerCameraPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerCameraPos()" );
	return _funcGetPlayerCameraPos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerCameraFrontVector ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerCameraFrontVector()" );
	return _funcGetPlayerCameraFrontVector ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcTogglePlayerControllable ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcTogglePlayerControllable()" );
	return _funcTogglePlayerControllable ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcPlayerPlaySound ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcPlayerPlaySound()" );
	return _funcPlayerPlaySound ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerScore ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerScore()" );
	return _funcSetPlayerScore ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerScore ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerScore()" );
	return _funcGetPlayerScore ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerFacingAngle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerFacingAngle()" );
	return _funcSetPlayerFacingAngle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerFacingAngle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerFacingAngle()" );
	return _funcGetPlayerFacingAngle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGivePlayerMoney ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGivePlayerMoney()" );
	return _funcGivePlayerMoney ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerMoney ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerMoney()" );
	return _funcGetPlayerMoney ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcResetPlayerMoney ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcResetPlayerMoney()" );
	return _funcResetPlayerMoney ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsPlayerConnected ( AMX* a_AmxInterface, cell* a_Params )
{
	//logprintf ( "[Call]-> funcIsPlayerConnected()" );
	return _funcIsPlayerConnected ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerState ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerState()" );
	return _funcGetPlayerState ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcResetPlayerWeapons ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcResetPlayerWeapons()" );
	return _funcResetPlayerWeapons ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGivePlayerWeapon ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGivePlayerWeapon()" );
	return _funcGivePlayerWeapon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerArmedWeapon ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerArmedWeapon()" );
	return _funcSetPlayerArmedWeapon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerIp ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerIp()" );
	return _funcGetPlayerIp ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerPing ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerPing()" );
	return _funcGetPlayerPing ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerWeapon ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerWeapon()" );
	return _funcGetPlayerWeapon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerArmour ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerArmour()" );
	return _funcSetPlayerArmour ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerArmour ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerArmour()" );
	return _funcGetPlayerArmour ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerMapIcon ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerMapIcon()" );
	return _funcSetPlayerMapIcon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcRemovePlayerMapIcon ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcRemovePlayerMapIcon()" );
	return _funcRemovePlayerMapIcon ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerKeys ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerKeys()" );
	return _funcGetPlayerKeys ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerMarkerForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerMarkerForPlayer()" );
	return _funcSetPlayerMarkerForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerAmmo ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerAmmo()" );
	return _funcGetPlayerAmmo ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerAmmo ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerAmmo()" );
	return _funcSetPlayerAmmo ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerWeaponData ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerWeaponData()" );
	return _funcGetPlayerWeaponData ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerWeaponState ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerWeaponState()" );
	return _funcGetPlayerWeaponState ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcAllowPlayerTeleport ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAllowPlayerTeleport()" );
	return _funcAllowPlayerTeleport ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcForceClassSelection ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcForceClassSelection()" );
	return _funcForceClassSelection ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerWantedLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerWantedLevel()" );
	return _funcSetPlayerWantedLevel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerWantedLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerWantedLevel()" );
	return _funcGetPlayerWantedLevel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerFightingStyle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerFightingStyle()" );
	return _funcGetPlayerFightingStyle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerFightingStyle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerFightingStyle()" );
	return _funcSetPlayerFightingStyle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerVelocity ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerVelocity()" );
	return _funcGetPlayerVelocity ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerVelocity ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerVelocity()" );
	return _funcSetPlayerVelocity ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsPlayerInRangeOfPoint ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsPlayerInRangeOfPoint()" );
	return _funcIsPlayerInRangeOfPoint ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsPlayerStreamedIn ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsPlayerStreamedIn()" );
	return _funcIsPlayerStreamedIn ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsVehicleStreamedIn ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsVehicleStreamedIn()" );
	return _funcIsVehicleStreamedIn ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerVirtualWorld ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerVirtualWorld()" );
	return _funcSetPlayerVirtualWorld ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerVirtualWorld ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerVirtualWorld()" );
	return _funcGetPlayerVirtualWorld ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcShowPlayerNameTagForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcShowPlayerNameTagForPlayer()" );
	return _funcShowPlayerNameTagForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcEnableStuntBonusForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcEnableStuntBonusForAll()" );
	return _funcEnableStuntBonusForAll ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcEnableStuntBonusForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcEnableStuntBonusForPlayer()" );
	return _funcEnableStuntBonusForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcTogglePlayerSpectating ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcTogglePlayerSpectating()" );
	return _funcTogglePlayerSpectating ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerDrunkLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerDrunkLevel()" );
	return _funcGetPlayerDrunkLevel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerDrunkLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerDrunkLevel()" );
	return _funcSetPlayerDrunkLevel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcPlayerSpectateVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcPlayerSpectateVehicle()" );
	return _funcPlayerSpectateVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcPlayerSpectatePlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcPlayerSpectatePlayer()" );
	return _funcPlayerSpectatePlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcApplyAnimation ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcApplyAnimation()" );
	return _funcApplyAnimation ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcClearAnimations ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcClearAnimations()" );
	return _funcClearAnimations ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerAnimationIndex ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerAnimationIndex()" );
	return _funcGetPlayerAnimationIndex ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetAnimationName ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetAnimationName()" );
	return _funcGetAnimationName ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerSpecialAction ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerSpecialAction()" );
	return _funcSetPlayerSpecialAction ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerSpecialAction ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerSpecialAction()" );
	return _funcGetPlayerSpecialAction ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcStartRecordingPlayerData ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcStartRecordingPlayerData()" );
	return _funcStartRecordingPlayerData ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcStopRecordingPlayerData ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcStopRecordingPlayerData()" );
	return _funcStopRecordingPlayerData ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcPlayCrimeReportForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcPlayCrimeReportForPlayer()" );
	return _funcPlayCrimeReportForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerShopName ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerShopName()" );
	return _funcSetPlayerShopName ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerSkillLevel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerSkillLevel()" );
	return _funcSetPlayerSkillLevel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerChatBubble ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerChatBubble()" );
	return _funcSetPlayerChatBubble ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPVarInt ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPVarInt()" );
	return _funcSetPVarInt ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPVarString ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPVarString()" );
	return _funcSetPVarString ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPVarFloat ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPVarFloat()" );
	return _funcSetPVarFloat ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPVarInt ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPVarInt()" );
	return _funcGetPVarInt ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPVarString ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPVarString()" );
	return _funcGetPVarString ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPVarFloat ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPVarFloat()" );
	return _funcGetPVarFloat ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcDeletePVar ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDeletePVar()" );
	return _funcDeletePVar ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPVarType ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPVarType()" );
	return _funcGetPVarType ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPVarNameAtIndex ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPVarNameAtIndex()" );
	return _funcGetPVarNameAtIndex ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPVarsUpperIndex ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPVarsUpperIndex()" );
	return _funcGetPVarsUpperIndex ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsValidVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsValidVehicle()" );
	return _funcIsValidVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcCreateVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCreateVehicle()" );
	return _funcCreateVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcDestroyVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDestroyVehicle()" );
	return _funcDestroyVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetVehiclePos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetVehiclePos()" );
	return _funcGetVehiclePos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetVehiclePos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetVehiclePos()" );
	return _funcSetVehiclePos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetVehicleZAngle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetVehicleZAngle()" );
	return _funcGetVehicleZAngle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetVehicleRotationQuat ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetVehicleRotationQuat()" );
	return _funcGetVehicleRotationQuat ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetVehicleZAngle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetVehicleZAngle()" );
	return _funcSetVehicleZAngle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetVehicleParamsForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetVehicleParamsForPlayer()" );
	return _funcSetVehicleParamsForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcManualVehicleEngineAndLights ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcManualVehicleEngineAndLights()" );
	return _funcManualVehicleEngineAndLights ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetVehicleParamsEx ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetVehicleParamsEx()" );
	return _funcSetVehicleParamsEx ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetVehicleParamsEx ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetVehicleParamsEx()" );
	return _funcGetVehicleParamsEx ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetVehicleToRespawn ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetVehicleToRespawn()" );
	return _funcSetVehicleToRespawn ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcRepairVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcRepairVehicle()" );
	return _funcRepairVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcAddVehicleComponent ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAddVehicleComponent()" );
	return _funcAddVehicleComponent ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcRemoveVehicleComponent ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcRemoveVehicleComponent()" );
	return _funcRemoveVehicleComponent ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcChangeVehicleColor ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcChangeVehicleColor()" );
	return _funcChangeVehicleColor ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcChangeVehiclePaintjob ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcChangeVehiclePaintjob()" );
	return _funcChangeVehiclePaintjob ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcLinkVehicleToInterior ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcLinkVehicleToInterior()" );
	return _funcLinkVehicleToInterior ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetVehicleHealth ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetVehicleHealth()" );
	return _funcSetVehicleHealth ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetVehicleHealth ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetVehicleHealth()" );
	return _funcGetVehicleHealth ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcAttachTrailerToVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAttachTrailerToVehicle()" );
	return _funcAttachTrailerToVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcDetachTrailerFromVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDetachTrailerFromVehicle()" );
	return _funcDetachTrailerFromVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsTrailerAttachedToVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsTrailerAttachedToVehicle()" );
	return _funcIsTrailerAttachedToVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetVehicleTrailer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetVehicleTrailer()" );
	return _funcGetVehicleTrailer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetVehicleNumberPlate ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetVehicleNumberPlate()" );
	return _funcSetVehicleNumberPlate ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetVehicleModel ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetVehicleModel()" );
	return _funcGetVehicleModel ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetVehicleComponentInSlot ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetVehicleComponentInSlot()" );
	return _funcGetVehicleComponentInSlot ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetVehicleComponentType ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetVehicleComponentType()" );
	return _funcGetVehicleComponentType ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetVehicleVelocity ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetVehicleVelocity()" );
	return _funcGetVehicleVelocity ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetVehicleVelocity ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetVehicleVelocity()" );
	return _funcSetVehicleVelocity ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetVehicleAngularVelocity ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetVehicleAngularVelocity()" );
	return _funcSetVehicleAngularVelocity ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetVehicleDamageStatus ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetVehicleDamageStatus()" );
	return _funcGetVehicleDamageStatus ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcUpdateVehicleDamageStatus ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcUpdateVehicleDamageStatus()" );
	return _funcUpdateVehicleDamageStatus ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetVehicleVirtualWorld ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetVehicleVirtualWorld()" );
	return _funcSetVehicleVirtualWorld ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetVehicleVirtualWorld ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetVehicleVirtualWorld()" );
	return _funcGetVehicleVirtualWorld ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSendClientMessage ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSendClientMessage()" );
	return _funcSendClientMessage ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSendClientMessageToAll ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSendClientMessageToAll()" );
	return _funcSendClientMessageToAll ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSendDeathMessage ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSendDeathMessage()" );
	return _funcSendDeathMessage ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGameTextForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGameTextForAll()" );
	return _funcGameTextForAll ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGameTextForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGameTextForPlayer()" );
	return _funcGameTextForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSendPlayerMessageToPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSendPlayerMessageToPlayer()" );
	return _funcSendPlayerMessageToPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSendPlayerMessageToAll ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSendPlayerMessageToAll()" );
	return _funcSendPlayerMessageToAll ( a_AmxInterface, a_Params );
}


cell AMX_NATIVE_CALL funcCreateMenu ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCreateMenu()" );
	return _funcCreateMenu ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcDestroyMenu ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDestroyMenu()" );
	return _funcDestroyMenu ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcAddMenuItem ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAddMenuItem()" );
	return _funcAddMenuItem ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetMenuColumnHeader ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetMenuColumnHeader()" );
	return _funcSetMenuColumnHeader ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcShowMenuForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcShowMenuForPlayer()" );
	return _funcShowMenuForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcHideMenuForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcHideMenuForPlayer()" );
	return _funcHideMenuForPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsValidMenu ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsValidMenu()" );
	return _funcIsValidMenu ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcDisableMenu ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDisableMenu()" );
	return _funcDisableMenu ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcDisableMenuRow ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDisableMenuRow()" );
	return _funcDisableMenuRow ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerMenu ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerMenu()" );
	return _funcGetPlayerMenu ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerTime ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerTime()" );
	return _funcSetPlayerTime ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcTogglePlayerClock ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcTogglePlayerClock()" );
	return _funcTogglePlayerClock ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerTime ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerTime()" );
	return _funcGetPlayerTime ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcHTTP ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcHTTP()" );
	return _funcHTTP ( a_AmxInterface, a_Params );
}

/**
 *	Reference:
 *		[CALL] 0x004807B7
 *		[CALL] 0x00480902
 *		[CALL] 0x00483E7F
 *
.text:0048A7D0 amx_CustomInit  proc near               ; CODE XREF: CFilterScripts__LoadFilterScript+117p
.text:0048A7D0                                         ; CFilterScripts__LoadFilterScriptFromMemory+C2p ...
.text:0048A7D0
.text:0048A7D0 a_AmxInstance   = dword ptr  4
.text:0048A7D0
.text:0048A7D0                 mov     eax, [esp+a_AmxInstance]
.text:0048A7D4                 push    0FFFFFFFFh      ; a_Number
.text:0048A7D6                 push    offset __ArrayCustomNative ; a_NativeInfoList
.text:0048A7DB                 push    eax             ; a_AmxInstance
.text:0048A7DC                 call    amx_Register
.text:0048A7E1                 add     esp, 0Ch
.text:0048A7E4                 retn
.text:0048A7E4 amx_CustomInit  endp
**/
int amx_CustomInit ( AMX* a_AmxInterface )
{
	logprintf ( "[Call]-> amx_CustomInit()" );
	return amx_Register ( a_AmxInterface, __AmxScriptNative, -1 );
}

AMX_NATIVE_INFO __AmxScriptNative[] =
{
	{ "print",									funcPrint },								// 0
	{ "printf",									funcPrintf },								// 1
	{ "format",									funcFormat },								// 2
	{ "SetTimer",								funcSetTimer },								// 3
	{ "KillTimer",								funcKillTimer },							// 4
	{ "GetTickCount",							funcGetTickCount },							// 5
	{ "GetMaxPlayers",							funcGetMaxPlayers },						// 6
	{ "SetTimerEx",								funcSetTimerEx },							// 7
	{ "LimitGlobalChatRadius",					funcLimitGlobalChatRadius },				// 8
	{ "LimitPlayerMarkerRadius",				funcLimitPlayerMarkerRadius },				// 9
	{ "SetWeather",								funcSetWeather },							// 10
	{ "SetPlayerWeather",						funcSetPlayerWeather },						// 11
	{ "CallRemoteFunction",						funcCallRemoteFunction },					// 12
	{ "CallLocalFunction",						funcCallLocalFunction },					// 13
	{ "asin",									funcAsin },									// 14
	{ "acos",									funcAcos },									// 15
	{ "atan2",									funcAtan2 },								// 16
	{ "atan",									funcAtan },									// 17
	{ "gpci",									funcGpci },									// 18
	{ "GameModeExit",							funcGameModeExit },							// 19
	{ "SetGameModeText",						funcSetGameModeText },						// 20
	{ "SetTeamCount",							funcSetTeamCount },							// 21
	{ "AddPlayerClass",							funcAddPlayerClass },						// 22
	{ "AddPlayerClassEx",						funcAddPlayerClassEx },						// 23
	{ "AddStaticVehicle",						funcAddStaticVehicle },						// 24
	{ "AddStaticVehicleEx",						funcAddStaticVehicleEx },					// 25
	{ "AddStaticPickup",						funcAddStaticPickup },						// 26
	{ "CreatePickup",							funcCreatePickup },							// 27
	{ "DestroyPickup",							funcDestroyPickup },						// 28
	{ "SetPlayerWorldBounds",					funcSetPlayerWorldBounds },					// 29
	{ "ShowNameTags",							funcShowNameTags },							// 30
	{ "ShowPlayerMarkers",						funcShowPlayerMarkers },					// 31
	{ "SetWorldTime",							funcSetWorldTime },							// 32
	{ "GetWeaponName",							funcGetWeaponName },						// 33
	{ "EnableTirePopping",						funcEnableTirePopping },					// 34
	{ "AllowInteriorWeapons",					funcAllowInteriorWeapons },					// 35
	{ "SetGravity",								funcSetGravity },							// 36
	{ "GetGravity",								funcGetGravity },							// 37
	{ "AllowAdminTeleport",						funcAllowAdminTeleport },					// 38
	{ "SetDeathDropAmount",						funcSetDeathDropAmount },					// 39
	{ "CreateExplosion",						funcCreateExplosion },						// 40
	{ "SetDisabledWeapons",						funcSetDisabledWeapons },					// 41
	{ "UsePlayerPedAnims",						funcUsePlayerPedAnims },					// 42
	{ "DisableInteriorEnterExits",				funcDisableInteriorEnterExits },			// 43
	{ "SetNameTagDrawDistance",					funcSetNameTagDrawDistance },				// 44
	{ "DisableNameTagLOS",						funcDisableNameTagLOS },					// 45
	{ "ConnectNPC",								funcConnectNPC },							// 46
	{ "IsPlayerNPC",							funcIsPlayerNPC },							// 47
	{ "Create3DTextLabel",						funcCreate3DTextLabel },					// 48
	{ "Delete3DTextLabel",						funcDelete3DTextLabel },					// 49
	{ "Attach3DTextLabelToPlayer",				funcAttach3DTextLabelToPlayer },			// 50
	{ "Attach3DTextLabelToVehicle",				funcAttach3DTextLabelToVehicle },			// 51
	{ "Update3DTextLabelText",					funcUpdate3DTextLabelText },				// 52
	{ "CreatePlayer3DTextLabel",				funcCreatePlayer3DTextLabel },				// 53
	{ "DeletePlayer3DTextLabel",				funcDeletePlayer3DTextLabel },				// 54
	{ "UpdatePlayer3DTextLabelText",			funcUpdatePlayer3DTextLabelText },			// 55
	{ "ShowPlayerDialog",						funcShowPlayerDialog },					// 56
	{ "EnableZoneNames",						funcEnableZoneNames },					// 57

	{ "GangZoneCreate",							funcGangZoneCreate },					// 58
	{ "GangZoneDestroy",						funcGangZoneDestroy },					// 59
	{ "GangZoneShowForPlayer",					funcGangZoneShowForPlayer },					// 60
	{ "GangZoneShowForAll",						funcGangZoneShowForAll },					// 61
	{ "GangZoneHideForPlayer",					funcGangZoneHideForPlayer },					// 62
	{ "GangZoneHideForAll",						funcGangZoneHideForAll },					// 63
	{ "GangZoneFlashForPlayer",					funcGangZoneFlashForPlayer },					// 64
	{ "GangZoneFlashForAll",					funcGangZoneFlashForAll },					// 65
	{ "GangZoneStopFlashForPlayer",				funcGangZoneStopFlashForPlayer },					// 66
	{ "GangZoneStopFlashForAll",				funcGangZoneStopFlashForAll },					// 67
	
	{ "IsPlayerAdmin",							funcIsPlayerAdmin },					// 68
	{ "Kick",									funcKick },					// 69
	{ "Ban",									funcBan },					// 70
	{ "BanEx",									funcBanEx },					// 71
	{ "SendRconCommand",						funcSendRconCommand },					// 72
	{ "GetServerVarAsString",					funcGetServerVarAsString },					// 73
	{ "GetServerVarAsInt",						funcGetServerVarAsInt },					// 74
	{ "GetServerVarAsBool",						funcGetServerVarAsBool },					// 75
	{ "SetSpawnInfo",							funcSetSpawnInfo },					// 76
	{ "SpawnPlayer",							funcSpawnPlayer },					// 77
	{ "SetPlayerTeam",							funcSetPlayerTeam },					// 78
	{ "GetPlayerTeam",					funcGetPlayerTeam },					// 79
	{ "SetPlayerName",					funcSetPlayerName },					// 80
	{ "SetPlayerSkin",					funcSetPlayerSkin },					// 81
	{ "GetPlayerSkin",					funcGetPlayerSkin },					// 82
	{ "GetPlayerPos",					funcGetPlayerPos },					// 83
	{ "SetPlayerPos",					funcSetPlayerPos },					// 84
	{ "SetPlayerPosFindZ",					funcSetPlayerPosFindZ },					// 85
	{ "GetPlayerHealth",					funcGetPlayerHealth },					// 86
	{ "SetPlayerHealth",					funcSetPlayerHealth },					// 87
	{ "SetPlayerColor",					funcSetPlayerColor },					// 88
	{ "GetPlayerColor",					funcGetPlayerColor },					// 89
	{ "GetPlayerVehicleID",					funcGetPlayerVehicleID },					// 90
	{ "GetPlayerVehicleSeat",					funcGetPlayerVehicleSeat },					// 91
	{ "GetPlayerSurfingVehicleID",					funcGetPlayerSurfingVehicleID },					// 92
	{ "PutPlayerInVehicle",					funcPutPlayerInVehicle },					// 93
	{ "RemovePlayerFromVehicle",					funcRemovePlayerFromVehicle },					// 94
	{ "IsPlayerInVehicle",					funcIsPlayerInVehicle },					// 95
	{ "IsPlayerInAnyVehicle",					funcIsPlayerInAnyVehicle },					// 96
	{ "GetPlayerName",					funcGetPlayerName },					// 97
	{ "SetPlayerCheckpoint",					funcSetPlayerCheckpoint },					// 98
	{ "DisablePlayerCheckpoint",					funcDisablePlayerCheckpoint },					// 99
	{ "IsPlayerInCheckpoint",					funcIsPlayerInCheckpoint },					// 100
	{ "SetPlayerRaceCheckpoint",					funcSetPlayerRaceCheckpoint },					// 101
	{ "DisablePlayerRaceCheckpoint",					funcDisablePlayerRaceCheckpoint },					// 102
	{ "IsPlayerInRaceCheckpoint",					funcIsPlayerInRaceCheckpoint },					// 103
	{ "SetPlayerInterior",					funcSetPlayerInterior },					// 104
	{ "GetPlayerInterior",					funcGetPlayerInterior },					// 105
	{ "SetPlayerAttachedObject",					funcSetPlayerAttachedObject },					// 106
	{ "RemovePlayerAttachedObject",					funcRemovePlayerAttachedObject },					// 107
	{ "SetPlayerAttachedObject",					funcSetPlayerAttachedObject },					// 108
	{ "IsPlayerAttachedObjectSlotUsed",					funcIsPlayerAttachedObjectSlotUsed },					// 109
	{ "SetPlayerCameraLookAt",					funcSetPlayerCameraLookAt },					// 110
	{ "SetPlayerCameraPos",					funcSetPlayerCameraPos },					// 111
	{ "SetCameraBehindPlayer",					funcSetCameraBehindPlayer },					// 112
	{ "GetPlayerCameraPos",					funcGetPlayerCameraPos },					// 113
	{ "GetPlayerCameraFrontVector",					funcGetPlayerCameraFrontVector },					// 114
	{ "TogglePlayerControllable",					funcTogglePlayerControllable },					// 115
	{ "PlayerPlaySound",					funcPlayerPlaySound },					// 116
	{ "SetPlayerScore",					funcSetPlayerScore },					// 117
	{ "GetPlayerScore",					funcGetPlayerScore },					// 118
	{ "SetPlayerFacingAngle",					funcSetPlayerFacingAngle },					// 119
	{ "GetPlayerFacingAngle",					funcGetPlayerFacingAngle },					// 120
	{ "GivePlayerMoney",					funcGivePlayerMoney },					// 121
	{ "GetPlayerMoney",					funcGetPlayerMoney },					// 122
	{ "ResetPlayerMoney",					funcResetPlayerMoney },					// 123
	{ "IsPlayerConnected",					funcIsPlayerConnected },					// 124
	{ "GetPlayerState",					funcGetPlayerState },					// 125
	{ "ResetPlayerWeapons",					funcResetPlayerWeapons },					// 126
	{ "GivePlayerWeapon",					funcGivePlayerWeapon },					// 127
	{ "SetPlayerArmedWeapon",					funcSetPlayerArmedWeapon },					// 128
	{ "GetPlayerIp",					funcGetPlayerIp },					// 129
	{ "GetPlayerPing",					funcGetPlayerPing },					// 130
	{ "GetPlayerWeapon",					funcGetPlayerWeapon },					// 131
	{ "SetPlayerArmour",					funcSetPlayerArmour },					// 132
	{ "GetPlayerArmour",					funcGetPlayerArmour },					// 133
	{ "SetPlayerMapIcon",					funcSetPlayerMapIcon },					// 134
	{ "RemovePlayerMapIcon",					funcRemovePlayerMapIcon },					// 135
	{ "GetPlayerKeys",					funcGetPlayerKeys },					// 136
	{ "SetPlayerMarkerForPlayer",					funcSetPlayerMarkerForPlayer },					// 137
	{ "GetPlayerAmmo",					funcGetPlayerAmmo },					// 138
	{ "SetPlayerAmmo",					funcSetPlayerAmmo },					// 139
	{ "GetPlayerWeaponData",					funcGetPlayerWeaponData },					// 140
	{ "GetPlayerWeaponState",					funcGetPlayerWeaponState },					// 141
	{ "AllowPlayerTeleport",					funcAllowPlayerTeleport },					// 142
	{ "ForceClassSelection",					funcForceClassSelection },					// 143
	{ "SetPlayerWantedLevel",					funcSetPlayerWantedLevel },					// 144
	{ "GetPlayerWantedLevel",					funcGetPlayerWantedLevel },					// 145
	{ "GetPlayerFightingStyle",					funcGetPlayerFightingStyle },					// 146
	{ "SetPlayerFightingStyle",					funcSetPlayerFightingStyle },					// 147
	{ "GetPlayerVelocity",					funcGetPlayerVelocity },					// 148
	{ "SetPlayerVelocity",					funcSetPlayerVelocity },					// 149
	{ "IsPlayerInRangeOfPoint",					funcIsPlayerInRangeOfPoint },					// 150
	{ "IsPlayerStreamedIn",					funcIsPlayerStreamedIn },					// 151
	{ "IsVehicleStreamedIn",					funcIsVehicleStreamedIn },					// 152
	{ "SetPlayerVirtualWorld",					funcSetPlayerVirtualWorld },					// 153
	{ "GetPlayerVirtualWorld",					funcGetPlayerVirtualWorld },					// 154
	{ "ShowPlayerNameTagForPlayer",					funcShowPlayerNameTagForPlayer },					// 155
	{ "EnableStuntBonusForAll",					funcEnableStuntBonusForAll },					// 156
	{ "EnableStuntBonusForPlayer",					funcEnableStuntBonusForPlayer },					// 157
	{ "TogglePlayerSpectating",					funcTogglePlayerSpectating },					// 158
	{ "GetPlayerDrunkLevel",					funcGetPlayerDrunkLevel },					// 159
	{ "SetPlayerDrunkLevel",					funcSetPlayerDrunkLevel },					// 160
	{ "PlayerSpectateVehicle",					funcPlayerSpectateVehicle },					// 161
	{ "PlayerSpectatePlayer",					funcPlayerSpectatePlayer },					// 162
	{ "ApplyAnimation",					funcApplyAnimation },					// 163
	{ "ClearAnimations",					funcClearAnimations },					// 164
	{ "GetPlayerAnimationIndex",					funcGetPlayerAnimationIndex },					// 165
	{ "GetAnimationName",					funcGetAnimationName },					// 166
	{ "SetPlayerSpecialAction",					funcSetPlayerSpecialAction },					// 167
	{ "GetPlayerSpecialAction",					funcGetPlayerSpecialAction },					// 168
	{ "StartRecordingPlayerData",					funcStartRecordingPlayerData },					// 169
	{ "StopRecordingPlayerData",					funcStopRecordingPlayerData },					// 170
	{ "PlayCrimeReportForPlayer",					funcPlayCrimeReportForPlayer },					// 171
	{ "SetPlayerShopName",					funcSetPlayerShopName },					// 172
	{ "SetPlayerSkillLevel",					funcSetPlayerSkillLevel },					// 173
	{ "SetPlayerChatBubble",					funcSetPlayerChatBubble },					// 174
	{ "SetPVarInt",					funcSetPVarInt },					// 175
	{ "SetPVarString",					funcSetPVarString },					// 176
	{ "SetPVarFloat",					funcSetPVarFloat },					// 177
	{ "GetPVarInt",					funcGetPVarInt },					// 178
	{ "GetPVarString",					funcGetPVarString },					// 179
	{ "GetPVarFloat",					funcGetPVarFloat },					// 180
	{ "DeletePVar",					funcDeletePVar },					// 181
	{ "GetPVarType",					funcGetPVarType },					// 182
	{ "GetPVarNameAtIndex",					funcGetPVarNameAtIndex },					// 183
	{ "GetPVarsUpperIndex",					funcGetPVarsUpperIndex },					// 184
	{ "IsValidVehicle",					funcIsValidVehicle },					// 185
	{ "CreateVehicle",					funcCreateVehicle },					// 186
	{ "DestroyVehicle",					funcDestroyVehicle },					// 187
	{ "GetVehiclePos",					funcGetVehiclePos },					// 188
	{ "SetVehiclePos",					funcSetVehiclePos },					// 189
	{ "GetVehicleZAngle",					funcGetVehicleZAngle },					// 190
	{ "GetVehicleRotationQuat",					funcGetVehicleRotationQuat },					// 191
	{ "SetVehicleZAngle",					funcSetVehicleZAngle },					// 192
	{ "SetVehicleParamsForPlayer",					funcSetVehicleParamsForPlayer },					// 193
	{ "ManualVehicleEngineAndLights",					funcManualVehicleEngineAndLights },					// 194
	{ "SetVehicleParamsEx",					funcSetVehicleParamsEx },					// 195
	{ "GetVehicleParamsEx",					funcGetVehicleParamsEx },					// 196
	{ "SetVehicleToRespawn",					funcSetVehicleToRespawn },					// 197
	{ "RepairVehicle",					funcRepairVehicle },					// 198
	{ "AddVehicleComponent",					funcAddVehicleComponent },					// 199
	{ "RemoveVehicleComponent",					funcRemoveVehicleComponent },					// 200
	{ "ChangeVehicleColor",					funcChangeVehicleColor },					// 201
	{ "ChangeVehiclePaintjob",					funcChangeVehiclePaintjob },					// 202
	{ "LinkVehicleToInterior",					funcLinkVehicleToInterior },					// 203
	{ "SetVehicleHealth",					funcSetVehicleHealth },					// 204
	{ "GetVehicleHealth",					funcGetVehicleHealth },					// 205
	{ "AttachTrailerToVehicle",					funcAttachTrailerToVehicle },					// 206
	{ "DetachTrailerFromVehicle",					funcDetachTrailerFromVehicle },					// 207
	{ "IsTrailerAttachedToVehicle",					funcIsTrailerAttachedToVehicle },					// 208
	{ "GetVehicleTrailer",					funcGetVehicleTrailer },					// 209
	{ "SetVehicleNumberPlate",					funcSetVehicleNumberPlate },					// 210
	{ "GetVehicleModel",					funcGetVehicleModel },					// 211
	{ "GetVehicleComponentInSlot",					funcGetVehicleComponentInSlot },					// 212
	{ "GetVehicleComponentType",					funcGetVehicleComponentType },					// 213
	{ "GetVehicleVelocity",					funcGetVehicleVelocity },					// 214
	{ "SetVehicleVelocity",					funcSetVehicleVelocity },					// 215
	{ "SetVehicleAngularVelocity",					funcSetVehicleAngularVelocity },					// 216
	{ "GetVehicleDamageStatus",					funcGetVehicleDamageStatus },					// 217
	{ "UpdateVehicleDamageStatus",					funcUpdateVehicleDamageStatus },					// 218
	{ "SetVehicleVirtualWorld",					funcSetVehicleVirtualWorld },					// 219
	{ "GetVehicleVirtualWorld",					funcGetVehicleVirtualWorld },					// 220
	{ "SendClientMessage",					funcSendClientMessage },					// 221
	{ "SendClientMessageToAll",					funcSendClientMessageToAll },					// 222
	{ "SendDeathMessage",					funcSendDeathMessage },					// 223
	{ "GameTextForAll",					funcGameTextForAll },					// 224
	{ "GameTextForPlayer",					funcGameTextForPlayer },					// 225
	{ "SendPlayerMessageToPlayer",					funcSendPlayerMessageToPlayer },					// 226
	{ "SendPlayerMessageToAll",					funcSendPlayerMessageToAll },					// 227
	{ "TextDrawCreate",					funcTextDrawCreate },					// 228
	{ "TextDrawSetString",					funcTextDrawSetString },					// 229
	{ "TextDrawLetterSize",					funcTextDrawLetterSize },					// 230
	{ "TextDrawTextSize",					funcTextDrawTextSize },					// 231
	{ "TextDrawAlignment",					funcTextDrawAlignment },					// 232
	{ "TextDrawColor",					funcTextDrawColor },					// 233
	{ "TextDrawUseBox",					funcTextDrawUseBox },					// 234
	{ "TextDrawBoxColor",					funcTextDrawBoxColor },					// 235
	{ "TextDrawSetShadow",					funcTextDrawSetShadow },					// 236
	{ "TextDrawSetOutline",					funcTextDrawSetOutline },					// 237
	{ "TextDrawBackgroundColor",					funcTextDrawBackgroundColor },					// 238
	{ "TextDrawFont",					funcTextDrawFont },					// 239
	{ "TextDrawSetProportional",					funcTextDrawSetProportional },					// 240
	{ "TextDrawShowForPlayer",					funcTextDrawShowForPlayer },					// 241
	{ "TextDrawShowForAll",					funcTextDrawShowForAll },					// 242
	{ "TextDrawHideForPlayer",					funcTextDrawHideForPlayer },					// 243
	{ "TextDrawHideForAll",					funcTextDrawHideForAll },					// 244
	{ "TextDrawDestroy",					funcTextDrawDestroy },					// 245
	{ "CreateObject",					funcCreateObject },					// 246
	{ "AttachObjectToVehicle",					funcAttachObjectToVehicle },					// 247
	{ "SetObjectPos",					funcSetObjectPos },					// 248
	{ "SetObjectRot",					funcSetObjectRot },					// 249
	{ "GetObjectPos",					funcGetObjectPos },					// 250
	{ "GetObjectRot",					funcGetObjectRot },					// 251
	{ "IsValidObject",					funcIsValidObject },					// 252
	{ "DestroyObject",					funcDestroyObject },					// 253
	{ "MoveObject",					funcMoveObject },					// 254
	{ "StopObject",					funcStopObject },					// 255
	{ "CreatePlayerObject",					funcCreatePlayerObject },					// 256
	{ "SetPlayerObjectPos",					funcSetPlayerObjectPos },					// 257
	{ "SetPlayerObjectRot",					funcSetPlayerObjectRot },					// 258
	{ "GetPlayerObjectPos",					funcGetPlayerObjectPos },					// 259
	{ "GetPlayerObjectRot",					funcGetPlayerObjectRot },					// 260
	{ "IsValidPlayerObject",					funcIsValidPlayerObject },					// 261
	{ "DestroyPlayerObject",					funcDestroyPlayerObject },					// 262
	{ "MovePlayerObject",					funcMovePlayerObject },					// 263
	{ "StopPlayerObject",					funcStopPlayerObject },					// 264
	{ "AttachObjectToPlayer",					funcAttachObjectToPlayer },					// 265
	{ "AttachPlayerObjectToPlayer",					funcAttachPlayerObjectToPlayer },					// 266
	{ "CreateMenu",					funcCreateMenu },					// 267
	{ "DestroyMenu",					funcDestroyMenu },					// 268
	{ "AddMenuItem",					funcAddMenuItem },					// 269
	{ "SetMenuColumnHeader",					funcSetMenuColumnHeader },					// 270
	{ "ShowMenuForPlayer",					funcShowMenuForPlayer },					// 271
	{ "HideMenuForPlayer",					funcHideMenuForPlayer },					// 272
	{ "IsValidMenu",					funcIsValidMenu },					// 273
	{ "DisableMenu",					funcDisableMenu },					// 274
	{ "DisableMenuRow",					funcDisableMenuRow },					// 275
	{ "GetPlayerMenu",					funcGetPlayerMenu },					// 276
	{ "SetPlayerTime",					funcSetPlayerTime },					// 277
	{ "TogglePlayerClock",					funcTogglePlayerClock },					// 278
	{ "GetPlayerTime",					funcGetPlayerTime },					// 279
	{ "HTTP",					funcHTTP },
	{ NULL, NULL }
};