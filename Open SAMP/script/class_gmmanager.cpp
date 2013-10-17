#include "../main.h"

//

extern "C" int amx_CoreInit(AMX* amx);
extern "C" int amx_CoreCleanup(AMX* amx);
extern "C" int amx_FloatInit(AMX* amx);
extern "C" int amx_FloatCleanup(AMX* amx);
extern "C" int amx_StringInit(AMX* amx);
extern "C" int amx_StringCleanup(AMX* amx);
extern "C" int amx_FileInit(AMX* amx);
extern "C" int amx_FileCleanup(AMX* amx);
extern "C" int amx_TimeInit(AMX* amx);
extern "C" int amx_TimeCleanup(AMX* amx);
extern "C" int amx_DGramInit(AMX* amx);
extern "C" int amx_DGramCleanup(AMX* amx);
extern "C" int amx_sampDbInit(AMX *amx);
extern "C" int amx_sampDbCleanup(AMX *amx);

int AMXAPI aux_LoadProgram(AMX* amx, char* filename);
int AMXAPI aux_FreeProgram(AMX *amx);
char * AMXAPI aux_StrError(int errnum);
void AMXPrintError(CGamemodeManager* pGameMode, AMX *amx, int error);
int amx_CustomInit(AMX *amx);

char szGameModeFileName[256];

//

CGamemodeManager::CGamemodeManager ( )
{
	this->gmIsInit = false;
	this->gmIsSleeping = false;
}

CGamemodeManager::~CGamemodeManager ( )
{
	this->Unload();
}

bool CGamemodeManager::Load(char* gmFile)
{
	if (this->gmIsInit)
		Unload();

	FILE* f = fopen(gmFile, "rb");
	if (!f) return false;
	fclose(f);

	memset((void*)&(this->gmAMX), 0, sizeof(AMX));
	this->gmSleepTime = 0.0f;
	strcpy(szGameModeFileName, gmFile);

	int err = aux_LoadProgram(&(this->gmAMX), szGameModeFileName);
	if (err != AMX_ERR_NONE)
	{
		AMXPrintError(this, &(this->gmAMX), err);
		logprintf("Failed to load '%s' script.", szGameModeFileName);
		return false;
	}

	amx_CoreInit(&(this->gmAMX));
	amx_FloatInit(&(this->gmAMX));
	amx_StringInit(&(this->gmAMX));
	amx_FileInit(&(this->gmAMX));
	amx_TimeInit(&(this->gmAMX));
	//amx_DGramInit(&(this->gmAMX));
	amx_CustomInit(&(this->gmAMX));
	amx_sampDbInit(&(this->gmAMX));

	__Plugins->DoAmxLoad(&(this->gmAMX));

	this->gmIsInit = true;

	int tmp;
	if (!amx_FindPublic(&(this->gmAMX), "OnGameModeInit", &tmp))
		amx_Exec(&(this->gmAMX), (cell*)&tmp, tmp);

	__NetGame->filterscriptsManager->OnGameModeInit();

	cell ret = 0;
	err = amx_Exec(&(this->gmAMX), &ret, AMX_EXEC_MAIN);
	if (err == AMX_ERR_SLEEP)
	{
		this->gmIsSleeping = true;
		this->gmSleepTime = ((float)ret / 1000.0f);
	}
	else if (err != AMX_ERR_NONE)
	{
		this->gmIsSleeping = false;
		AMXPrintError(this, &(this->gmAMX), err);
	}

	return true;
}

void CGamemodeManager::Unload()
{
	for( _PlayerID playerid = 0; playerid < MAX_PLAYERS; playerid ++ )
	{
		if( __NetGame->playerPool->GetSlotState( playerid ) )
		{
			__NetGame->playerPool->GetPlayer( playerid )->GetKeyBinder()->OnGameModeUnloaded();
		}
	}

	int tmp;
	if (!amx_FindPublic(&this->gmAMX, "OnGameModeExit", &tmp))
		amx_Exec(&this->gmAMX, (cell*)&tmp, tmp);

	__NetGame->filterscriptsManager->OnGameModeExit();
	if(__NetGame->scriptTimerManager) 
		__NetGame->scriptTimerManager->DeleteForMode(&this->gmAMX);

	if (this->gmIsInit)
	{

		aux_FreeProgram(&this->gmAMX);
		__Plugins->DoAmxUnload(&this->gmAMX);
		amx_sampDbCleanup(&this->gmAMX);
		//amx_DGramCleanup(&this->gmAMX);
		amx_TimeCleanup(&this->gmAMX);
		amx_FileCleanup(&this->gmAMX);
		amx_StringCleanup(&this->gmAMX);
		amx_FloatCleanup(&this->gmAMX);
		amx_CoreCleanup(&this->gmAMX);
	}

	this->gmIsInit = false;
	this->gmIsSleeping = false;
}


void CGamemodeManager::Frame(float time)
{
	if (!this->gmIsInit)
		return;

	if (!this->gmIsSleeping)
		return;

	if (this->gmSleepTime > 0.0f)
	{
		this->gmSleepTime -= time;
	}
	else
	{
		cell ret;
		int err = amx_Exec(&(this->gmAMX), &ret, AMX_EXEC_CONT);
		if (err == AMX_ERR_SLEEP)
		{
			this->gmIsSleeping = true;
			this->gmSleepTime = ((float)ret / 1000.0f);
		}
		else
		{
			this->gmIsSleeping = false;
			AMXPrintError(this, &(this->gmAMX), err);
		}
	}
}

uint32_t CGamemodeManager::CallPublic( char* functionName )
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "functionName", &idx))
	{
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerConnect(cell playerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerConnect", &idx))
	{
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerDisconnect(cell playerid, cell reason)
{
	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerDisconnect", &idx))
	{
		amx_Push(&gmAMX, reason);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerSpawn(cell playerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerSpawn", &idx))
	{
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerDeath(cell playerid, cell killerid, cell reason)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerDeath", &idx))
	{
		amx_Push(&gmAMX, reason);
		amx_Push(&gmAMX, killerid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnVehicleSpawn(cell vehicleid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnVehicleSpawn", &idx))
	{
		amx_Push(&gmAMX, vehicleid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnVehicleDeath(cell vehicleid, cell killerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnVehicleDeath", &idx))
	{
		amx_Push(&gmAMX, killerid);
		amx_Push(&gmAMX, vehicleid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerText(cell playerid, unsigned char * szText)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 1;
	uint32_t orig_strlen = strlen((char*)szText) + 1;


	if (!amx_FindPublic(&gmAMX, "OnPlayerText", &idx))
	{
		cell amx_addr, *phys_addr;
		amx_PushString(&gmAMX, &amx_addr, &phys_addr, (char*)szText, 0, 0);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
		amx_GetString((char*)szText, phys_addr, 0, orig_strlen);
		amx_Release(&gmAMX, amx_addr);
	}

	if (ret && __NetGame->playerPool->GetSlotState((_PlayerID)playerid)) {
		__NetGame->playerPool->GetPlayer((_PlayerID)playerid)->Say((char*)szText, strlen((char*)szText));
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerCommandText(cell playerid, unsigned char * szCommandText)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;
	uint32_t orig_strlen = strlen((char*)szCommandText);

	if(!__NetGame->playerPool->GetSlotState((_PlayerID)playerid)) return 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerCommandText", &idx))
	{
		cell amx_addr, *phys_addr;
		amx_PushString(&gmAMX, &amx_addr, &phys_addr, (char*)szCommandText, 0, 0);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
		amx_Release(&gmAMX, amx_addr);
	}

	return (uint32_t)ret;
}

//uint32_t CGamemodeManager::OnPlayerInfoChange(cell playerid)
//{
//	if (!gmIsInit) return 0;
//
//	int idx;
//	cell ret = 0;
//
//	if (!amx_FindPublic(&gmAMX, "OnPlayerInfoChange", &idx))
//	{
//		amx_Push(&gmAMX, playerid);
//		amx_Exec(&gmAMX, &ret, idx);
//	}
//	return (uint32_t)ret;
//}

uint32_t CGamemodeManager::OnPlayerRequestClass(cell playerid, cell classid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 1;
	
	if(!__NetGame->playerPool->GetSlotState((_PlayerID)playerid)) return 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerRequestClass", &idx))
	{
		amx_Push(&gmAMX, classid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerRequestSpawn(cell playerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 1;

	if(!__NetGame->playerPool->GetSlotState((_PlayerID)playerid)) return 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerRequestSpawn", &idx))
	{
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerEnterVehicle(cell playerid, cell vehicleid, cell ispassenger)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if(!__NetGame->playerPool->GetSlotState((_PlayerID)playerid)) return 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerEnterVehicle", &idx))
	{
		amx_Push(&gmAMX, ispassenger);
		amx_Push(&gmAMX, vehicleid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerExitVehicle(cell playerid, cell vehicleid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;
	
	if(!__NetGame->playerPool->GetSlotState((_PlayerID)playerid)) return 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerExitVehicle", &idx))
	{
		amx_Push(&gmAMX, vehicleid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerStateChange(cell playerid, cell newstate, cell oldstate)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;
	
	if(!__NetGame->playerPool->GetSlotState((_PlayerID)playerid)) return 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerStateChange", &idx))
	{
		amx_Push(&gmAMX, oldstate);
		amx_Push(&gmAMX, newstate);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerInteriorChange(cell playerid, cell newid, cell oldid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;
	
	if(!__NetGame->playerPool->GetSlotState((_PlayerID)playerid)) return 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerInteriorChange", &idx))
	{
		amx_Push(&gmAMX, oldid);
		amx_Push(&gmAMX, newid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerEnterCheckpoint(cell playerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;
	
	if(!__NetGame->playerPool->GetSlotState((_PlayerID)playerid)) return 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerEnterCheckpoint", &idx))
	{
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerLeaveCheckpoint(cell playerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerLeaveCheckpoint", &idx))
	{
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerEnterRaceCheckpoint(cell playerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerEnterRaceCheckpoint", &idx))
	{
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerLeaveRaceCheckpoint(cell playerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerLeaveRaceCheckpoint", &idx))
	{
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerKeyStateChange(cell playerid, cell newkeys, cell oldkeys)
{
	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerKeyStateChange", &idx))
	{
		amx_Push(&gmAMX, oldkeys);
		amx_Push(&gmAMX, newkeys);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnRconCommand(char* szCommand)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;
	uint32_t orig_strlen = strlen(szCommand);

	if (!amx_FindPublic(&gmAMX, "OnRconCommand", &idx))
	{
		cell amx_addr, *phys_addr;
		amx_PushString(&gmAMX, &amx_addr, &phys_addr, szCommand, 0, 0);
		amx_Exec(&gmAMX, &ret, idx);
		amx_Release(&gmAMX, amx_addr);
	}

	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnObjectMoved(cell objectid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnObjectMoved", &idx))
	{
		amx_Push(&gmAMX, objectid);
		amx_Exec(&gmAMX, &ret, idx);
	}

	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerObjectMoved(cell playerid, cell objectid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerObjectMoved", &idx))
	{
		amx_Push(&gmAMX, objectid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}

	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerPickedUpPickup(cell playerid, cell pickupid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerPickUpPickup", &idx))
	{
		amx_Push(&gmAMX, pickupid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerExitedMenu(cell playerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerExitedMenu", &idx))
	{
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerSelectedMenuRow(cell playerid, cell row)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if (!amx_FindPublic(&gmAMX, "OnPlayerSelectedMenuRow", &idx))
	{
		amx_Push(&gmAMX, row);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnVehicleRespray(cell playerid, cell vehicleid, cell color1, cell color2)
{
	if (!gmIsInit) return 0;
	int idx;
	cell ret = 1;

	if (!amx_FindPublic(&gmAMX, "OnVehicleRespray", &idx))
	{
		amx_Push(&gmAMX, color2);
		amx_Push(&gmAMX, color1);
		amx_Push(&gmAMX, vehicleid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnVehicleMod(cell playerid, cell vehicleid, cell componentid)
{
	if (!gmIsInit) return 0;
	int idx;
	cell ret = 1;

	if (!amx_FindPublic(&gmAMX, "OnVehicleMod", &idx))
	{
		amx_Push(&gmAMX, componentid);
		amx_Push(&gmAMX, vehicleid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnEnterExitModShop(cell playerid, cell enterexit, cell uint32_teriorid)
{
	if (!gmIsInit) return 0;
	int idx;
	cell ret = 1;

	if (!amx_FindPublic(&gmAMX, "OnEnterExitModShop", &idx))
	{
		amx_Push(&gmAMX, uint32_teriorid);
		amx_Push(&gmAMX, enterexit);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnVehiclePaintjob(cell playerid, cell vehicleid, cell pauint32_tjobid)
{
	if (!gmIsInit) return 0;
	int idx;
	cell ret = 1;

	if (!amx_FindPublic(&gmAMX, "OnVehiclePaintjob", &idx))
	{
		amx_Push(&gmAMX, pauint32_tjobid);
		amx_Push(&gmAMX, vehicleid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnRconLoginAttempt( unsigned char* szIP, unsigned char* szPassword, cell success )
{
	if (!gmIsInit) return 0;
	int idx;
	cell retval;
	
	if ( !amx_FindPublic(&gmAMX, "OnRconLoginAttempt", &idx ) )
	{
		cell amx_addr, amx_addr2, *phys_addr;

		amx_Push( &gmAMX, success );
		amx_PushString(&gmAMX, &amx_addr, &phys_addr, (char*)szPassword, 0, 0);
		amx_PushString(&gmAMX, &amx_addr2, &phys_addr, (char*)szIP, 0, 0);

		amx_Exec( &gmAMX, &retval, idx );

		amx_Release(&gmAMX, amx_addr );
		amx_Release(&gmAMX, amx_addr2 );
	}

	return 1;
}

uint32_t CGamemodeManager::OnPlayerUpdate(cell playerid)
{
	if (!gmIsInit) return 0;
	int idx;
	cell ret = 1;

	if(!amx_FindPublic(&gmAMX, "OnPlayerUpdate", &idx))
	{
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerStreamIn(cell playerid, cell forplayerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 1;

	if(!amx_FindPublic(&gmAMX, "OnPlayerStreamIn", &idx))
	{
		amx_Push(&gmAMX, forplayerid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerStreamOut(cell playerid, cell forplayerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 1;

	if(!amx_FindPublic(&gmAMX, "OnPlayerStreamOut", &idx))
	{
		amx_Push(&gmAMX, forplayerid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnVehicleStreamIn(cell vehicleid, cell forplayerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 1;

	if(!amx_FindPublic(&gmAMX, "OnVehicleStreamIn", &idx))
	{
		amx_Push(&gmAMX, forplayerid);
		amx_Push(&gmAMX, vehicleid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnVehicleStreamOut(cell vehicleid, cell forplayerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 1;

	if(!amx_FindPublic(&gmAMX, "OnVehicleStreamOut", &idx))
	{
		amx_Push(&gmAMX, forplayerid);
		amx_Push(&gmAMX, vehicleid);
		amx_Exec(&gmAMX, &ret, idx);
	}
	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnDialogResponse(cell playerid, cell dialogid, cell response, cell listitem, unsigned char *szInputText)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if(!__NetGame->playerPool->GetSlotState((_PlayerID)playerid)) return 0;

	if(!amx_FindPublic(&gmAMX, "OnDialogResponse", &idx))
	{
		cell amx_addr, *phys_addr;
		amx_PushString(&gmAMX, &amx_addr, &phys_addr, (char*)szInputText, 0, 0);
		amx_Push(&gmAMX, listitem);
		amx_Push(&gmAMX, response);
		amx_Push(&gmAMX, dialogid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
		amx_Release(&gmAMX, amx_addr);
	}

	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerClickPlayer(cell playerid, cell clickedplayerid, cell source)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if(!__NetGame->playerPool->GetSlotState((_PlayerID)playerid)) return 0;

	if(!amx_FindPublic(&gmAMX, "OnPlayerClickPlayer", &idx))
	{
		amx_Push(&gmAMX, source);
		amx_Push(&gmAMX, clickedplayerid);
		amx_Push(&gmAMX, playerid);
		amx_Exec(&gmAMX, &ret, idx);
	}

	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnVehicleDamageStatusUpdate(cell vehicleid, cell playerid)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if(!amx_FindPublic(&gmAMX, "OnVehicleDamageStatusUpdate", &idx)) {
		amx_Push(&gmAMX, playerid);
		amx_Push(&gmAMX, vehicleid);
		amx_Exec(&gmAMX, &ret, idx);
	}

	return (uint32_t)ret;
}


uint32_t CGamemodeManager::OnPlayerMoneyChange( cell playerid, cell old_value, cell new_value ) // useful for anticheat
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if(!amx_FindPublic(&gmAMX, "OnPlayerMoneyChange", &idx)) {
		// stack à l'envers
		amx_Push(&gmAMX, new_value);
		amx_Push(&gmAMX, old_value );
		amx_Push(&gmAMX, playerid );
		amx_Exec(&gmAMX, &ret, idx);
	}

	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnUnoccupiedVehicleUpdate(cell vehicleid, cell playerid, cell passenger_seat)
{
	if (!gmIsInit) return 0;

	int idx;
	cell ret = 0;

	if(!amx_FindPublic(&gmAMX, "OnUnoccupiedVehicleUpdate", &idx)) {
		amx_Push(&gmAMX, passenger_seat);
		amx_Push(&gmAMX, playerid );
		amx_Push(&gmAMX, vehicleid );
		amx_Exec(&gmAMX, &ret, idx);
	}

	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerTakeDamage( cell playerID, cell attackerID, float damageAmount, cell weaponid, cell bodypart )
{
	int idx;
	cell ret = 0;

	if(!amx_FindPublic(&gmAMX, "OnPlayerTakeDamage", &idx)) {

		amx_Push(&gmAMX, bodypart );
		amx_Push(&gmAMX, weaponid );
		amx_Push(&gmAMX, amx_ftoc( damageAmount ) );
		amx_Push(&gmAMX, attackerID );
		amx_Push(&gmAMX, playerID);
		amx_Exec(&gmAMX, &ret, idx);
	}

	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerTargetPlayer( cell playerID, cell targetID )
{
	int idx;
	cell ret = 0;

	if(!amx_FindPublic(&gmAMX, "OnPlayerTargetPlayer", &idx)) {

		amx_Push(&gmAMX, targetID );
		amx_Push(&gmAMX, playerID);
		amx_Exec(&gmAMX, &ret, idx);
	}

	return (uint32_t)ret;
}

uint32_t CGamemodeManager::OnPlayerClickMap( cell playerID, float posX, float posY, float posZ )
{
	int idx;
	cell ret = 0;

	if(!amx_FindPublic(&gmAMX, "OnPlayerClickMap", &idx)) {

		amx_Push(&gmAMX, amx_ftoc( posZ ) );
		amx_Push(&gmAMX, amx_ftoc( posY ) );
		amx_Push(&gmAMX, amx_ftoc( posX ) );
		amx_Push(&gmAMX, playerID);
		amx_Exec(&gmAMX, &ret, idx);
	}

	return (uint32_t)ret;
}