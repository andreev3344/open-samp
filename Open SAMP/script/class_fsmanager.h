#ifndef __CFSMANAGER_H__
#define __CFSMANAGER_H__

#ifndef _STANDALONE

#include "../../SDK/amx/amx.h"
#include "../../SDK/plugincommon.h"

#endif

#define MAX_FS 16

class CFilterscriptsManager
{
#pragma pack(1)
public:

	AMX* fsAMX[MAX_FS];
	char fsName[MAX_FS][255];
	uint32_t fsCount;

	bool LoadFilterScript(char* fsName);
	bool UnloadFilterScript(char* fsName);
	void UnloadFilterScripts();
	void RemoveFilterScript(int fsIdx);


	uint32_t CallPublic( char* functionName );

	uint32_t OnGameModeInit();
	uint32_t OnGameModeExit();
	uint32_t OnPlayerConnect(cell playerid);
	uint32_t OnPlayerDisconnect(cell playerid, cell reason);
	uint32_t OnPlayerSpawn(cell playerid);
	uint32_t OnPlayerDeath(cell playerid, cell killerid, cell reason);
	uint32_t OnVehicleSpawn(cell vehicleid);
	uint32_t OnVehicleDeath(cell vehicleid, cell killerid);
	uint32_t OnPlayerText(cell playerid, unsigned char * szText);
	uint32_t OnPlayerCommandText(cell playerid, unsigned char * szCommandText);
	//uint32_t OnPlayerInfoChange(cell playerid);
	uint32_t OnPlayerRequestClass(cell playerid, cell classid);
	uint32_t OnPlayerRequestSpawn(cell playerid);
	uint32_t OnPlayerEnterVehicle(cell playerid, cell vehicleid, cell ispassenger);
	uint32_t OnPlayerExitVehicle(cell playerid, cell vehicleid);
	uint32_t OnPlayerStateChange(cell playerid, cell newstate, cell oldstate);
	uint32_t OnPlayerEnterCheckpoint(cell playerid);
	uint32_t OnPlayerLeaveCheckpoint(cell playerid);
	uint32_t OnPlayerEnterRaceCheckpoint(cell playerid);
	uint32_t OnPlayerLeaveRaceCheckpoint(cell playerid);
	uint32_t OnRconCommand(char* szCommand);
	uint32_t OnObjectMoved(cell objectid);
	uint32_t OnPlayerObjectMoved(cell playerid, cell objectid);
	uint32_t OnPlayerPickedUpPickup(cell playerid, cell pickupid);
	uint32_t OnPlayerExitedMenu(cell playerid);
	uint32_t OnPlayerSelectedMenuRow(cell playerid, cell row);
	uint32_t OnVehicleRespray(cell playerid, cell vehicleid, cell color1, cell color2);
	uint32_t OnVehicleMod(cell playerid, cell vehicleid, cell componentid);
	uint32_t OnEnterExitModShop(cell playerid, cell enterexit, cell interiorid);
	uint32_t OnVehiclePaintjob(cell playerid, cell vehicleid, cell paintjobid);
	uint32_t OnPlayerInteriorChange(cell playerid, cell newid, cell oldid);
	uint32_t OnPlayerKeyStateChange(cell playerid, cell newkeys, cell oldkeys);
	
	uint32_t OnRconLoginAttempt( unsigned char* szIP, unsigned char* szPassword, cell success );
	uint32_t OnPlayerUpdate(cell playerid);
	uint32_t OnPlayerStreamIn(cell playerid, cell forplayerid);
	uint32_t OnPlayerStreamOut(cell playerid, cell forplayerid);
	uint32_t OnVehicleStreamIn(cell vehicleid, cell forplayerid);
	uint32_t OnVehicleStreamOut(cell vehicleid, cell forplayerid);
	
	uint32_t OnDialogResponse(cell playerid, cell dialogid, cell response, cell listitem, unsigned char *szInputText);
	uint32_t OnPlayerClickPlayer(cell playerid, cell clickedplayerid, cell source);
	uint32_t OnVehicleDamageStatusUpdate(cell vehicleid, cell playerid);

	uint32_t OnPlayerMoneyChange( cell playerid, cell old_value, cell new_value );
	uint32_t OnUnoccupiedVehicleUpdate( cell vehicleid, cell playerid, cell passenger_seat);
	uint32_t OnPlayerTakeDamage( cell playerID, cell attackerID, float damageAmount, cell weaponid, cell bodypart );

	uint32_t OnPlayerTargetPlayer( cell playerID, cell targetID );

	uint32_t OnPlayerClickMap( cell playerID, float posX, float posY, float posZ );

	CFilterscriptsManager();
	~CFilterscriptsManager();
};

#endif