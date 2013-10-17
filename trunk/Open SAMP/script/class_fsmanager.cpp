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
int AMXAPI aux_LoadProgramFromMemory(AMX* amx, char* filedata);
int AMXAPI aux_FreeProgram(AMX *amx);
int amx_CustomInit(AMX *amx);

//

CFilterscriptsManager::CFilterscriptsManager ( )
{
	this->fsCount = 0;
	for (int i=0; i < MAX_FS; i++)
		this->fsAMX[i] = NULL;
}

CFilterscriptsManager::~CFilterscriptsManager( )
{
	this->UnloadFilterScripts();
}

bool CFilterscriptsManager::LoadFilterScript(char* fsName)
{
	char szFilterScriptFile[256];
	sprintf(szFilterScriptFile, "filterscripts/%s.amx", fsName);
	if (this->fsCount >= MAX_FS)
		return false;

	FILE* f = fopen(&szFilterScriptFile[0], "rb");
	if (!f) return false;
	fclose(f);

	uint8_t iSlot;
	for (iSlot = 0; iSlot < MAX_FS; iSlot++)
	{
		if (this->fsAMX[iSlot] == NULL) break;
		if (strcmp(fsName, this->fsName[iSlot]) == 0) return false;
	}
	if (iSlot == MAX_FS) return false;

	this->fsAMX[iSlot] = new AMX;
	AMX* amx = this->fsAMX[iSlot];

	memset((void*)amx, 0, sizeof(AMX));
	int err = aux_LoadProgram(amx, &szFilterScriptFile[0]);
	if (err != AMX_ERR_NONE)
	{
		logprintf("Failed to load '%s.amx' filter script.", szFilterScriptFile);
		return false;
	}

	amx_CoreInit(amx);
	amx_FloatInit(amx);
	amx_StringInit(amx);
	amx_FileInit(amx);
	amx_TimeInit(amx);
	//amx_DGramInit(amx);
	amx_CustomInit(amx);
	amx_sampDbInit(amx);

	__Plugins->DoAmxLoad(amx);

	int tmp;
	if (!amx_FindPublic(amx, "OnFilterScriptInit", &tmp))
		amx_Exec(amx, (cell*)&tmp, tmp);
		
	strcpy(this->fsName[iSlot], fsName);

	this->fsCount++;

	return true;
}

bool CFilterscriptsManager::UnloadFilterScript(char* fsName)
{
	uint8_t i;
	for(i = 0; i < MAX_FS; i++)
		if (strcmp(fsName, this->fsName[i]) == 0) break;

	if(i == MAX_FS) return false;
	if(this->fsAMX[i])
	{
		RemoveFilterScript(i);
		return true;
	}
	return false;
}

void CFilterscriptsManager::UnloadFilterScripts()
{
	for (int i=0; i < MAX_FS; i++)
	{
		if (this->fsAMX[i])
		{
			this->RemoveFilterScript(i);
		}
	}

	this->fsCount = 0;
}

void CFilterscriptsManager::RemoveFilterScript(int fsIdx)
{
	for( _PlayerID playerid = 0; playerid < MAX_PLAYERS; playerid ++ )
	{
		if( __NetGame->playerPool->GetSlotState( playerid ) )
		{
			__NetGame->playerPool->GetPlayer( playerid )->GetKeyBinder()->OnFilterScriptUnloaded( fsIdx );
		}
	}

	int tmp;
	if (!amx_FindPublic(this->fsAMX[fsIdx], "OnFilterScriptExit", &tmp))
		amx_Exec(this->fsAMX[fsIdx], (cell*)&tmp, tmp);

	if(__NetGame->scriptTimerManager) 
		__NetGame->scriptTimerManager->DeleteForMode(this->fsAMX[fsIdx]);

	aux_FreeProgram(this->fsAMX[fsIdx]);

	__Plugins->DoAmxUnload(this->fsAMX[fsIdx]);

	//amx_DGramCleanup(m_pFilterScripts[iIndex]);
	amx_TimeCleanup(this->fsAMX[fsIdx]);
	amx_FileCleanup(this->fsAMX[fsIdx]);
	amx_StringCleanup(this->fsAMX[fsIdx]);
	amx_FloatCleanup(this->fsAMX[fsIdx]);
	amx_CoreCleanup(this->fsAMX[fsIdx]);
	amx_sampDbCleanup(this->fsAMX[fsIdx]);

	delete (this->fsAMX[fsIdx]);
	this->fsAMX[fsIdx] = NULL;

	this->fsName[fsIdx][0] = '\0';

	this->fsCount--;
}

uint32_t CFilterscriptsManager::CallPublic( char* functionName )
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], functionName, &idx))
			{
				amx_Exec(fsAMX[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerConnect(cell playerid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerConnect", &idx))
			{
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
				//if (!ret) return ret;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerDisconnect(cell playerid, cell reason)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX && fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerDisconnect", &idx))
			{
				amx_Push(fsAMX[i], reason);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnGameModeInit()
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnGameModeInit", &idx))
			{
				amx_Exec(fsAMX[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnGameModeExit()
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnGameModeExit", &idx))
			{
				amx_Exec(fsAMX[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerSpawn(cell playerid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerSpawn", &idx))
			{
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerDeath(cell playerid, cell killerid, cell reason)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerDeath", &idx))
			{
				amx_Push(fsAMX[i], reason);
				amx_Push(fsAMX[i], killerid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnVehicleSpawn(cell vehicleid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnVehicleSpawn", &idx))
			{
				amx_Push(fsAMX[i], vehicleid);
				amx_Exec(fsAMX[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnVehicleDeath(cell vehicleid, cell killerid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnVehicleDeath", &idx))
			{
				amx_Push(fsAMX[i], killerid);
				amx_Push(fsAMX[i], vehicleid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerText(cell playerid, unsigned char* szText)
{
	int idx;
	cell ret = 1;

	uint32_t orig_strlen = strlen((char*)szText) + 1;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerText", &idx))
			{
				cell amx_addr, *phys_addr;
				amx_PushString(fsAMX[i], &amx_addr, &phys_addr, (char*)szText, 0, 0);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
				amx_GetString((char*)szText, phys_addr, 0, orig_strlen);
				amx_Release(fsAMX[i], amx_addr);
				if (!ret) return 0;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerCommandText(cell playerid, unsigned char* szCommandText)
{
	int idx;
	cell ret = 0;

	uint32_t orig_strlen = strlen((char*)szCommandText);

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerCommandText", &idx))
			{
				cell amx_addr, *phys_addr;
				amx_PushString(fsAMX[i], &amx_addr, &phys_addr, (char*)szCommandText, 0, 0);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
				amx_Release(fsAMX[i], amx_addr);
				if (ret) return 1;
			}
		}
	}
	return (uint32_t)ret;
}
//
//uint32_t CFilterscriptsManager::OnPlayerInfoChange(cell playerid)
//{
//	int idx;
//	cell ret = 0;
//
//	for (uint32_t i=0; i < MAX_FS; i++)
//	{
//		if (fsAMX[i])
//		{
//			if (!amx_FindPublic(fsAMX[i], "OnPlayerInfoChange", &idx))
//			{
//				amx_Push(fsAMX[i], playerid);
//				amx_Exec(fsAMX[i], &ret, idx);
//			}
//		}
//	}
//	return (uint32_t)ret;
//}

uint32_t CFilterscriptsManager::OnPlayerRequestClass(cell playerid, cell classid)
{
	int idx;
	cell ret = 1;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerRequestClass", &idx))
			{
				amx_Push(fsAMX[i], classid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerRequestSpawn(cell playerid)
{
	int idx;
	cell ret = 1;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerRequestSpawn", &idx))
			{
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
				if (!ret) return ret;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerEnterVehicle(cell playerid, cell vehicleid, cell ispassenger)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerEnterVehicle", &idx))
			{
				amx_Push(fsAMX[i], ispassenger);
				amx_Push(fsAMX[i], vehicleid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerExitVehicle(cell playerid, cell vehicleid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerExitVehicle", &idx))
			{
				amx_Push(fsAMX[i], vehicleid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerStateChange(cell playerid, cell newstate, cell oldstate)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerStateChange", &idx))
			{
				amx_Push(fsAMX[i], oldstate);
				amx_Push(fsAMX[i], newstate);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerInteriorChange(cell playerid, cell newid, cell oldid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerInteriorChange", &idx))
			{
				amx_Push(fsAMX[i], oldid);
				amx_Push(fsAMX[i], newid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerEnterCheckpoint(cell playerid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerEnterCheckpoint", &idx))
			{
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerLeaveCheckpoint(cell playerid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerLeaveCheckpoint", &idx))
			{
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerEnterRaceCheckpoint(cell playerid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerEnterRaceCheckpoint", &idx))
			{
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerLeaveRaceCheckpoint(cell playerid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerLeaveRaceCheckpoint", &idx))
			{
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerKeyStateChange(cell playerid, cell newkeys, cell oldkeys)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerKeyStateChange", &idx))
			{
				amx_Push(fsAMX[i], oldkeys);
				amx_Push(fsAMX[i], newkeys);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}

	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnRconCommand(char* szCommand)
{
	int idx;
	cell ret = 1;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnRconCommand", &idx))
			{
				cell amx_addr, *phys_addr;
				amx_PushString(fsAMX[i], &amx_addr, &phys_addr, szCommand, 0, 0);
				amx_Exec(fsAMX[i], &ret, idx);
			} 
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnObjectMoved(cell objectid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnObjectMoved", &idx))
			{
				amx_Push(fsAMX[i], objectid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerObjectMoved(cell playerid, cell objectid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerObjectMoved", &idx))
			{
				amx_Push(fsAMX[i], objectid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}

	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerPickedUpPickup(cell playerid, cell pickupid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerPickUpPickup", &idx))
			{
				amx_Push(fsAMX[i], pickupid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerExitedMenu(cell playerid)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerExitedMenu", &idx))
			{
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerSelectedMenuRow(cell playerid, cell row)
{
	int idx;
	cell ret = 0;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnPlayerSelectedMenuRow", &idx))
			{
				amx_Push(fsAMX[i], row);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnVehicleRespray(cell playerid, cell vehicleid, cell color1, cell color2)
{
	int idx;
	cell ret = 1;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnVehicleRespray", &idx))
			{
				amx_Push(fsAMX[i], color2);
				amx_Push(fsAMX[i], color1);
				amx_Push(fsAMX[i], vehicleid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnVehicleMod(cell playerid, cell vehicleid, cell componentid)
{
	int idx;
	cell ret = 1;
	uint32_t retval = 1;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnVehicleMod", &idx))
			{
				amx_Push(fsAMX[i], componentid);
				amx_Push(fsAMX[i], vehicleid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
				if (!ret) retval = 0;
			}
		}
	}
	return retval;
}

uint32_t CFilterscriptsManager::OnEnterExitModShop(cell playerid, cell enterexit, cell uint32_teriorid)
{
	int idx;
	cell ret = 1;
	uint32_t retval = 1;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnEnterExitModShop", &idx))
			{
				amx_Push(fsAMX[i], uint32_teriorid);
				amx_Push(fsAMX[i], enterexit);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
				if (!ret) retval = 0;
			}
		}
	}
	return retval;
}

uint32_t CFilterscriptsManager::OnVehiclePaintjob(cell playerid, cell vehicleid, cell pauint32_tjobid)
{
	int idx;
	cell ret = 1;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{
			if (!amx_FindPublic(fsAMX[i], "OnVehiclePaintjob", &idx))
			{
				amx_Push(fsAMX[i], pauint32_tjobid);
				amx_Push(fsAMX[i], vehicleid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnRconLoginAttempt( unsigned char* szIP, unsigned char* szPassword, cell success )
{
	int idx;
	cell retval;

	for (uint32_t i=0; i < MAX_FS; i++)
	{
		if (fsAMX[i])
		{

			if ( !amx_FindPublic(fsAMX[i], "OnRconLoginAttempt", &idx ) )
			{
				cell amx_addr, amx_addr2, *phys_addr;

				amx_Push( fsAMX[i], success );
				amx_PushString(fsAMX[i], &amx_addr, &phys_addr, (char*)szPassword, 0, 0);
				amx_PushString(fsAMX[i], &amx_addr2, &phys_addr, (char*)szIP, 0, 0);

				amx_Exec( fsAMX[i], &retval, idx );

				amx_Release(fsAMX[i], amx_addr );
				amx_Release(fsAMX[i], amx_addr2 );
			}
		}
	}

	return 1;
}

uint32_t CFilterscriptsManager::OnPlayerUpdate(cell playerid)
{
	int idx;
	cell ret = 1;

	for (uint32_t i=0; i < MAX_FS; i++) {
		if (fsAMX[i]) 
		{
			if(!amx_FindPublic(fsAMX[i], "OnPlayerUpdate", &idx))
			{
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}

	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerStreamIn(cell playerid, cell forplayerid)
{
	int idx;
	cell ret = 1;

	for (uint32_t i=0; i < MAX_FS; i++) {
		if (fsAMX[i]) 
		{
			if(!amx_FindPublic(fsAMX[i], "OnPlayerStreamIn", &idx))
			{
				amx_Push(fsAMX[i], forplayerid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerStreamOut(cell playerid, cell forplayerid)
{
	int idx;
	cell ret = 1;

	for (uint32_t i=0; i < MAX_FS; i++) {
		if (fsAMX[i]) 
		{
			if(!amx_FindPublic(fsAMX[i], "OnPlayerStreamOut", &idx))
			{
				amx_Push(fsAMX[i], forplayerid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnVehicleStreamIn(cell vehicleid, cell forplayerid)
{
	int idx;
	cell ret = 1;

	for (uint32_t i=0; i < MAX_FS; i++) {
		if (fsAMX[i]) 
		{
			if(!amx_FindPublic(fsAMX[i], "OnVehicleStreamIn", &idx))
			{
				amx_Push(fsAMX[i], forplayerid);
				amx_Push(fsAMX[i], vehicleid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnVehicleStreamOut(cell vehicleid, cell forplayerid)
{
	int idx;
	cell ret = 1;

	for (uint32_t i=0; i < MAX_FS; i++) {
		if (fsAMX[i]) 
		{
			if(!amx_FindPublic(fsAMX[i], "OnVehicleStreamOut", &idx))
			{
				amx_Push(fsAMX[i], forplayerid);
				amx_Push(fsAMX[i], vehicleid);
				amx_Exec(fsAMX[i], &ret, idx);
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnDialogResponse(cell playerid, cell dialogid, cell response, cell listitem, unsigned char *szInputText)
{
	int idx;
	cell ret = 0;

	for(uint32_t i=0; i < MAX_FS; i++)
	{
		if(fsAMX[i])
		{
			if(!amx_FindPublic(fsAMX[i], "OnDialogResponse", &idx))
			{
				cell amx_addr, *phys_addr;
				amx_PushString(fsAMX[i], &amx_addr, &phys_addr, (char*)szInputText, 0, 0);
				amx_Push(fsAMX[i], listitem);
				amx_Push(fsAMX[i], response);
				amx_Push(fsAMX[i], dialogid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
				amx_Release(fsAMX[i], amx_addr);
				if (ret) return 1;
			}
		}
	}

	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerClickPlayer(cell playerid, cell clickedplayerid, cell source)
{
	int idx;
	cell ret = 0;

	for(uint32_t i=0; i < MAX_FS; i++)
	{
		if(fsAMX[i])
		{
			if(!amx_FindPublic(fsAMX[i], "OnPlayerClickPlayer", &idx))
			{
				amx_Push(fsAMX[i], source);
				amx_Push(fsAMX[i], clickedplayerid);
				amx_Push(fsAMX[i], playerid);
				amx_Exec(fsAMX[i], &ret, idx);
				if (ret) return 1;
			}
		}
	}

	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnVehicleDamageStatusUpdate(cell vehicleid, cell playerid)
{
	int idx;
	cell ret = 0;
	
	for(uint32_t i=0; i < MAX_FS; i++)
	{
		if(fsAMX[i])
		{
			if(!amx_FindPublic(fsAMX[i], "OnVehicleDamageStatusUpdate", &idx))
			{
				amx_Push(fsAMX[i], playerid);
				amx_Push(fsAMX[i], vehicleid);
				amx_Exec(fsAMX[i], &ret, idx);
				if (ret) return 1;
			}
		}
	}

	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerMoneyChange(cell playerid, cell old_value, cell new_value )
{
	int idx;
	cell ret = 0;
	
	for(uint32_t i=0; i < MAX_FS; i++)
	{
		if(fsAMX[i])
		{
			if(!amx_FindPublic(fsAMX[i], "OnPlayerMoneyChange", &idx))
			{
				// stack à l'envers
				amx_Push(fsAMX[i], new_value );
				amx_Push(fsAMX[i], old_value );
				amx_Push(fsAMX[i], playerid );
				amx_Exec(fsAMX[i], &ret, idx );
				if (ret) return 1;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnUnoccupiedVehicleUpdate(cell vehicleid, cell playerid, cell passenger_seat)
{
	int idx;
	cell ret = 0;
	
	for(uint32_t i=0; i < MAX_FS; i++)
	{
		if(fsAMX[i])
		{
			if(!amx_FindPublic(fsAMX[i], "OnUnoccupiedVehicleUpdate", &idx))
			{
				amx_Push(fsAMX[i], passenger_seat );
				amx_Push(fsAMX[i], playerid );
				amx_Push(fsAMX[i], vehicleid );
				amx_Exec(fsAMX[i], &ret, idx );
				if (ret) return 1;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerTakeDamage( cell playerID, cell attackerID, float damageAmount, cell weaponid, cell bodypart )
{
	int idx;
	cell ret = 0;
	
	for(uint32_t i=0; i < MAX_FS; i++)
	{
		if(fsAMX[i])
		{
			if(!amx_FindPublic(fsAMX[i], "OnPlayerTakeDamage", &idx))
			{
				amx_Push(fsAMX[i], bodypart );
				amx_Push(fsAMX[i], weaponid );
				amx_Push(fsAMX[i], amx_ftoc( damageAmount ) );
				amx_Push(fsAMX[i], attackerID );
				amx_Push(fsAMX[i], playerID);
				amx_Exec(fsAMX[i], &ret, idx);
				if (ret) return 1;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerTargetPlayer( cell playerID, cell targetID )
{
	int idx;
	cell ret = 0;
	
	for(uint32_t i=0; i < MAX_FS; i++)
	{
		if(fsAMX[i])
		{
			if(!amx_FindPublic(fsAMX[i], "OnPlayerTargetPlayer", &idx))
			{
				amx_Push(fsAMX[i], targetID );
				amx_Push(fsAMX[i], playerID);
				amx_Exec(fsAMX[i], &ret, idx);
				if (ret) return 1;
			}
		}
	}
	return (uint32_t)ret;
}

uint32_t CFilterscriptsManager::OnPlayerClickMap( cell playerID, float posX, float posY, float posZ )
{
	int idx;
	cell ret = 0;
	
	for(uint32_t i=0; i < MAX_FS; i++)
	{
		if(fsAMX[i])
		{
			if(!amx_FindPublic(fsAMX[i], "OnPlayerClickMap", &idx))
			{
				amx_Push(fsAMX[i], amx_ftoc( posZ ) );
				amx_Push(fsAMX[i], amx_ftoc( posY ) );
				amx_Push(fsAMX[i], amx_ftoc( posX ) );
				amx_Push(fsAMX[i], playerID);
				amx_Exec(fsAMX[i], &ret, idx);
				if (ret) return 1;
			}
		}
	}
	return (uint32_t)ret;
}