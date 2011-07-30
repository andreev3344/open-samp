#include "../main.h"

CFilterscriptsManager::CFilterscriptsManager ( )
{

}

CFilterscriptsManager::~CFilterscriptsManager( )
{

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
				if (!ret) return ret;
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
				amx_Push(fsAMX[i], playerid );
				amx_Push(fsAMX[i], old_value );
				amx_Push(fsAMX[i], new_value );
				amx_Exec(fsAMX[i], &ret, idx );
				if (ret) return 1;
			}
		}
	}
	return (uint32_t)ret;
}