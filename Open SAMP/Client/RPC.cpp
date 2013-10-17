#include "main.h"


char* RPC_SetPlayerArmedWeapon= "\x5A";
char* RPC_SetCustomSpawn= "\x5B";
char* RPC_SetPlayerTeam= "\x5C";
char* RPC_SetPlayerSkin= "\x5D";
char* RPC_SetPlayerName= "\x5E";
char* RPC_SetPlayerPosition= "\x5F";
char* RPC_SetPlayerPositionFindZ= "\x60";
char* RPC_SetPlayerHealth= "\x61";
char* RPC_PutPlayerInVehicle= "\x62";
char* RPC_RemovePlayerFromVehicle= "\x63";
char* RPC_SetPlayerColor= "\x64";

char* RPC_ShowGameTextForPlayer = "\x65";
char* RPC_SetPlayerInterior= "\x48";
char* RPC_SetPlayerCameraPos= "\x49";
char* RPC_SetPlayerCameralookAt= "\x4A";
char* RPC_SetVehiclePos= "\x4B";
char* RPC_SetVehicleZAngle= "\x4C";
char* RPC_SetVehicleParamsForPlayer= "\x4D";
char* RPC_SetPlayerCameraBehindPlayer= "\x4E";
char* RPC_TogglePlayerControllable= "\x4F";
char* RPC_PlayerPlaySound= "\x50";

char* RPC_GivePlayerMoney= "\x52";
char* RPC_SetPlayerFacingAngle= "\x53";
char* RPC_ResetPlayerMoney= "\x54";
char* RPC_ResetPlayerWeapons= "\x55";
char* RPC_GivePlayerWeapon= "\x56";

char* RPC_LinkVehicleToInterior = "\x58";
char* RPC_SetPlayerArmour= "\x59";
char* RPC_SendDeathMessage = "\x66";
char* RPC_SetPlayerMapIcon= "\x67";
char* RPC_RemovePlayerMapIcon= "\x68";
char* RPC_SetPlayerAmmo= "\x69";

char* RPC_SetVehicleHealth = "\x6B";	
char* RPC_AttachTrailerToVehicle = "\x6C";
char* RPC_DetachTrailerFromVehicle = "\x6D";
char* RPC_SpawnObject= "\x8E";
char* RPC_SetObjectPosition= "\x8F";
char* RPC_SetObjectRotation= "\x90";
char* RPC_DestroyObject= "\x91";
char* RPC_ShowPlayerNameTagForPlayer= "\x95";
char* RPC_MoveObject= "\x96";
char* RPC_TogglePlayerSpectating= "\x99";
char* RPC_StopObject= "\x97";


char* RPC_SetPlayerSpectatingPlayer= "\x9B";
char* RPC_SetPlayerSpectatingVehicle= "\x9C";
char* RPC_RemoveComponent= "\x6E";
char* RPC_ForceClassSelection= "\x6F";
char* RPC_AttachObjectToPlayer= "\x70";
char* RPC_Menu_InitForPlayer= "\x71";
char* RPC_Menu_ShowForPlayer= "\x72";
char* RPC_Menu_HideForPlayer= "\x73";
char* RPC_SetPlayerWantedLevel= "\x74";
char* RPC_ShowTextDraw= "\x75";
char* RPC_HideTextDraw= "\x76";
char* RPC_EnableStuntBonus= "\x77";
char* RPC_TextDraw_SetString= "\x78";
char* RPC_AddGangZone= "\x79";
char* RPC_RemoveGangZone= "\x7A";
char* RPC_FlashGangZone= "\x7B";
char* RPC_StopFlashGangZone= "\x7C";
char* RPC_ApplyAnimation= "\x7D";
char* RPC_ClearAnimation= "\x7E";
char* RPC_SetPlayerSpecialAction= "\x7F";
char* RPC_SetPlayerFightingStyle= "\x80";
char* RPC_SetPlayerVelocity= "\x81";
char* RPC_SetVehicleVelocity = "\x82";

char* RPC_ToggleWidescreen = "\x59"; // useless
char* RPC_PlayCrimeReportForPlayer= "\x89";
char* RPC_AttachAttachedObject= "\x8A";

char* RPC_NewPlayer= "\x13";
char* RPC_PlayerLeave= "\x14";
char* RPC_InitGame = "\x15";

char* RPC_spawnPlayerForPlayer= "\x20";
char* RPC_HidePlayerForPlayer = "\x21";

char* RPC_ShowVehicleToPlayer= "\x22";
char* RPC_HideVehicleToPlayer= "\x23";

char* RPC_PlayerDeath = "\x24";
char* RPC_DamageVehicle= "\x25";
char* RPC_ShowCheckpoint= "\x26";
char* RPC_HideCheckpoint= "\x27";
char* RPC_ShowRaceCheckpoint= "\x28";
char* RPC_HideRaceCheckpoint= "\x29";

char* RPC_ShowPickupForPlayer = "\x19";
char* RPC_HidePickupForPlayer = "\x1A";

char* RPC_SetPlayerTime = "\x1D";
char* RPC_TogglePlayerClock = "\x1E";

char* RPC_AddPlayerMessage = "\x2C";

char* RPC_SetPlayerShopName= "\x38";
char* RPC_SetSkillLevel= "\x39";

char* RPC_SetPlayerDrunkLevel= "\x3A";
char* RPC_ShowText3DLabels= "\x3B";
char* RPC_HideText3DLabel= "\x3C";
char* RPC_SetPlayerChatBubble= "\x3D";
char* RPC_SendTime= "\x3E";
char* RPC_ChangeWeather= "\x1C";
char* RPC_ScmEvent= "\x2E";
char* RPC_SetTimeEx= "\x79";
char* RPC_WorldTime= "\x18";
char* RPC_SetGravity= "\x6A";
char* RPC_SetWorldBounds= "\x51";
char* RPC_CreateExplosion= "\x94";
char* RPC_ShowPlayerDialog= "\x3F";

char* RPC_SetVehicleParamsEx = "\x42";

char* RPC_GameModeRestart = "\x2A";
char* RPC_ClientMessage = "\x17";

char* RPC_PlayAudioStream = "\x8B";
char* RPC_StopAudioStream = "\x8C";
char* RPC_RemoveBuilding = "\x8D";

char* RPC_TogglePlayerCollision = "TogglePlayerCollision";
char* RPC_ToggleVehicleCollision = "ToggleVehicleCollision";
char* RPC_RegisterBindKey = "RegisterBind";
char* RPC_UnregisterBindKey = "UnregisterBind";

char* RPC_ConnectionRejected= "\x16";
char* RPC_RequestClass= "\x43";
char* RPC_RequestSpawn= "\x44";
char* RPC_UpdateScoreboard= "\x82";

char* RPC_ClientJoin = "\x9D";
char* RPC_NPCJoin = "\x0E";
char* RPC_Chat = "\x2C";
char* RPC_Spawn = "\x0B";
char* RPC_Death = "\x0C";
char* RPC_EnterVehicle = "\x45";
char* RPC_ExitVehicle = "\x46";
char* RPC_ScriptCash = "\x1F";
char* RPC_ServerCommand = "\x0F";
char* RPC_ServerStats = "\x2D";
char* RPC_SetInteriorID = "\x10";
char* RPC_OnPlayerClickMap = "\x11";
char* RPC_VehicleDestroyed = "\x61"; // à trouver
char* RPC_WeaponPickup = "\x85"; // à trouver
char* RPC_PickUpPickup = "\x30";
char* RPC_MenuSelect = "\x31";
char* RPC_MenuQuit = "\x32";
char* RPC_PlayerDialogResponse = "\x40";
char* RPC_PlayerClickPlayer = "\x41";
char* RPC_OnPlayerTakeDamage = "\x9E";
char* RPC_PlayerPressKeyBinded = "PlayerPressBind";



void __cdecl RegisterBindKey( RPCParameters* params ) 
{
	char* data = reinterpret_cast<char*>(params->input);
	int bitLen = params->numberOfBitsOfData;
	if(!data || !bitLen) return;

	RakNet::BitStream bStream(data, (bitLen/8) + 1, false);
	
	uint32_t keyIndex = 0;
	uint8_t keyCode = 0;
	bool callOnPush = false;

	bStream.Read( keyIndex );
	bStream.Read( keyCode );
	bStream.Read( callOnPush );

	__KeyBinder->BindKey( keyIndex, keyCode, callOnPush );
}

void __cdecl UnregisterBindKey( RPCParameters* params ) 
{
	char* data = reinterpret_cast<char*>(params->input);
	int bitLen = params->numberOfBitsOfData;
	if(!data || !bitLen) return;

	RakNet::BitStream bStream(data, (bitLen/8) + 1, false);
	
	uint32_t keyIndex = 0;

	bStream.Read( keyIndex );
	__KeyBinder->UnBindKey( keyIndex );
}


// http://gtag.gtagaming.com/opcode-database.php?opcode=0619
void __cdecl TogglePlayerCollision( RPCParameters* params ) 
{
	if( __ChatBox )
		__ChatBox->addDebugMessage( "TogglePlayerCollision has been disabled." );
	return;
	//char* data = reinterpret_cast<char*>(params->input);
	//int bitLen = params->numberOfBitsOfData;
	//if(!data || !bitLen) return;

	//RakNet::BitStream bsData(data, (bitLen/8) + 1, false);


}
// http://gtag.gtagaming.com/opcode-database.php?opcode=099A

void __cdecl ToggleVehicleCollision( RPCParameters* params ) 
{
	if( __ChatBox )
		__ChatBox->addDebugMessage( "ToggleVehicleCollision has been disabled." );
	return;

	//char* data = reinterpret_cast<char*>(params->input);
	//int bitLen = params->numberOfBitsOfData;
	//if(!data || !bitLen) return;

	//RakNet::BitStream bStream(data, (bitLen/8) + 1, false);
	//_VehicleID vehicleID = 0;
	//bool toggle = false;


	//bStream.Read( vehicleID );
	//bStream.Read( toggle );
	//
	//if( __NetGame->getVehiclePool()->GetSlotState( vehicleID ) )
	//{
	//	CVehicle* vehicle = __NetGame->getVehiclePool()->GetVehicle( vehicleID );
	//	if( vehicle == 0 ) return;
	//

	//	if( vehicle->GetGtaVehiclePtr() )
	//	{
	//		vehicle->ToggleCollision( toggle );
	//	}
	//	
	//}

}

void __cdecl ShowCheckpoint( RPCParameters* params )
{
	char* data = reinterpret_cast<char*>(params->input);
	int bitLen = params->numberOfBitsOfData;
	if(!data || !bitLen) return;

	RakNet::BitStream bsData(data, (bitLen/8) + 1, false);

	float posX, posY, posZ, size;
	uint32_t color;

	bsData.Read( posX );
	bsData.Read( posY );
	bsData.Read( posZ );
	bsData.Read( color );

	if( __Game )
		__Game->CreateCheckpoint( posX, posY, posZ, size, color );

}


void __cdecl ShowRaceCheckpoint( RPCParameters* params )
{
	char* data = reinterpret_cast<char*>(params->input);
	int bitLen = params->numberOfBitsOfData;
	if(!data || !bitLen) return;

	RakNet::BitStream bsData(data, (bitLen/8) + 1, false);

	uint8_t type;
	float posX, posY, posZ, nextPosX, nextPosY, nextPosZ, size;
	uint32_t color;

	bsData.Read( type );
	bsData.Read( posX );
	bsData.Read( posY );
	bsData.Read( posZ );
	bsData.Read( nextPosX );
	bsData.Read( nextPosY );
	bsData.Read( nextPosZ );
	bsData.Read( color );

	if( __Game )
		__Game->CreateRaceCheckpoint( posX, posY, posZ, nextPosX, nextPosY, nextPosZ, size, color );

}
