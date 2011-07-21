#include "../main.h"


CVehicle::CVehicle(uint32_t model, tVector *pos, float rot, uint32_t color1, uint32_t color2, uint32_t respawnTime)
{

	customSpawn.vehType = model;
	customSpawn.vehRot = rot;
	customSpawn.vehPos.X = pos->X;
	customSpawn.vehPos.Y = pos->Y;
	customSpawn.vehPos.Z = pos->Z;
	customSpawn.vehColor1 = color1;
	customSpawn.vehColor2 = color2;
	customSpawn.vehRespawnTime = respawnTime;
	customSpawn.vehInterior = 0;

	vehPos.X = pos->X;
	vehPos.Y = pos->Y;
	vehPos.Z = pos->Z;

	vehOccupied = false;
	vehRespawnTick = __NetGame->GetTime(); // get time

	memset(&vehMatrix, 0, sizeof(MATRIX4X4));
	vehMatrix.pos.X = customSpawn.vehPos.X;
	vehMatrix.pos.Y = customSpawn.vehPos.Y;
	vehMatrix.pos.Z = customSpawn.vehPos.Z;

	memset(&vehMoveSpeed, 0, sizeof(tVector));
	memset(&vehTurnSpeed, 0, sizeof(tVector));

	memset(&vehModInfo, 0, sizeof(VEHMOD_INFO));
	vehModInfo.vehColor1 = -1;
	vehModInfo.vehColor2 = -1;

	memset(&vehNumberPlate[0], 0, sizeof(vehNumberPlate));

	vehActive = TRUE;
	vehWasted = FALSE;
	vehDriverID = 0xFFFF;
	vehHealth = 1000.0f;
	vehDoorStatus = 0;
	vehPanelStatus = 0;
	vehLightStatus = 0;
	vehTireStatus = 0;

	for(char i=0; i < 7; i++) unk[i] = -1;

	vehDeathNotification = false;
	vehTrailerID = 0;
	vehDead = false;	
}

CVehicle::~CVehicle()
{
	//if(__NetGame && __NetGame->playerPool) 
		//__NetGame->playerPool->RemoveVehicleForEveryone(vehID);
}


void CVehicle::Update(_PlayerID playerId, MATRIX4X4 * matrix, float health, _VehicleID trailerID, bool occupied)
{
	if(playerId != 0xFFFF)
	{ // Invalid
		CPlayer* pDriver = NULL;
		if(!__NetGame->playerPool) return;
		pDriver = __NetGame->playerPool->GetPlayer(playerId);
		if(!pDriver) return;
//        if(!pDriver->IsVehicleAdded(vehID)) return;
	}
	
	vehDriverID = playerId;
	memcpy(&vehMatrix, matrix, sizeof(MATRIX4X4));
	
	vehPos.X = vehMatrix.pos.X;
	vehPos.Y = vehMatrix.pos.Y;
	vehPos.Z = vehMatrix.pos.Z;

	if(occupied) 
	{
		vehHealth = health;
		vehOccupied = true;
		vehOccupiedTick = __NetGame->GetTime(); // get time
	}

	if(trailerID && trailerID != 0xFFFF && trailerID < MAX_VEHICLES)
		vehTrailerID = trailerID;
	else
		vehTrailerID = 0;

	if(vehHealth <= 0.0f) vehDead = true;
}

uint32_t CVehicle::IsOccupied()
{
	CPlayer* pPlayer;

	for( _PlayerID playerID = 0; playerID < MAX_PLAYERS; playerID ++ )
	{
		if(__NetGame->playerPool->GetSlotState(playerID))
		{
			pPlayer = __NetGame->playerPool->GetPlayer(playerID);
			if(pPlayer && pPlayer->currentVehicleID == vehID && (pPlayer->getState() == PLAYER_STATE_DRIVER ||
				pPlayer->getState() == PLAYER_STATE_PASSENGER))
					return 1;
		}
	}

	return FALSE;
}

bool CVehicle::IsATrainPart()
{
	int model = customSpawn.vehType;

	if(model == 538 || model == 570 || model == 537 || 
		model == 569 || model == 449) 
			return true;

	return false;
}

bool CVehicle::IsATrainLoco()
{
	int model = customSpawn.vehType;

	if(model == 538 || model == 537) return true;

	return false;
}

void CVehicle::CheckForIdleRespawn()
{	
	if(IsATrainPart()) return;

	if( (__NetGame->GetTime() - vehRespawnTick) < 10000 ) // get time
		return;

	if(!IsOccupied()) 
	{
		if( vehOccupied &&
			(__NetGame->GetTime() - vehOccupiedTick) >= customSpawn.vehRespawnTime ) 
				Respawn();
	}
}

void CVehicle::Process(float fElapsedTime)
{
	CPlayerPool* pPlayerPool = __NetGame->playerPool;
	
	if(!vehDeathNotification && customSpawn.vehRespawnTime > 0 && ((rand() % 20) == 0)) {
		CheckForIdleRespawn();
		return;
	}

	if(vehDead)
	{
		if(!vehDeathNotification)
		{
			vehDeathNotification = true;

			if(__NetGame->gamemodeManager && __NetGame->filterscriptsManager) 
			{
				__NetGame->filterscriptsManager->OnVehicleDeath(vehID, 255);
				__NetGame->gamemodeManager->OnVehicleDeath(vehID, 255);
			}
			vehOccupiedTick = __NetGame->GetTime();
		}
		if(!(rand() % 20) && (__NetGame->GetTime() - vehOccupiedTick) > 10000)
		{
			Respawn();
		}
	}
}

void CVehicle::Respawn()
{
	memset(&vehMatrix, 0, sizeof(MATRIX4X4));
	memset(&vehMoveSpeed, 0, sizeof(tVector));
	memset(&vehTurnSpeed, 0, sizeof(tVector));

	memset(&vehModInfo, 0, sizeof(VEHMOD_INFO));
	vehModInfo.vehColor1 = -1;
	vehModInfo.vehColor2 = -1;

	vehMatrix.pos.X = customSpawn.vehPos.X;
	vehMatrix.pos.Y = customSpawn.vehPos.Y;
	vehMatrix.pos.Z = customSpawn.vehPos.Z;

	vehPos.X = customSpawn.vehPos.X;
	vehPos.Y = customSpawn.vehPos.Y;
	vehPos.Z = customSpawn.vehPos.Z;

	vehHealth = 1000.0f;
	vehDoorStatus = 0;
	vehPanelStatus = 0;
	vehLightStatus = 0;
	vehTireStatus = 0;

	vehDead = false;
	vehDeathNotification = false;
	vehOccupied = false;
	vehRespawnTick = __NetGame->GetTime();
	vehOccupiedTick = __NetGame->GetTime();

	if(__NetGame->playerPool) 
//		__NetGame->playerPool->RemoveVehicleForEveryone(vehID);

	if(__NetGame->filterscriptsManager && __NetGame->gamemodeManager) 
	{
		__NetGame->filterscriptsManager->OnVehicleSpawn(vehID);
		__NetGame->gamemodeManager->OnVehicleSpawn(vehID);
	}
}

void CVehicle::SetHealth(float health)
{
	uint32_t RPC_SetVehicleHealth = 0x2D;	

	RakNet::BitStream bStream;
	bStream.Write(vehID);
	bStream.Write(health);

	CNetGame__RPC_SendToPlayerVehicle( ( uint32_t )__NetGame, &RPC_SetVehicleHealth, &bStream, vehID, 0xFFFF, 2);

	vehHealth = health;
}

void CVehicle::SetNumberPlate(char* nbplate)
{
	if(!nbplate) 
	{
		memset(vehNumberPlate,0,32);
		return;
	}

	if(strlen(nbplate) <= 32) 
		strcpy(vehNumberPlate, nbplate);
}

float CVehicle::GetDistanceFromPoint(float X, float Y, float Z)
{

	return sqrt( (float) (vehPos.X - X) * (vehPos.X - X) +
		(vehPos.Y - Y) * (vehPos.Y - Y) +
		(vehPos.Z - Z) * (vehPos.Z - Z) );

}

float CVehicle::GetSquaredDistanceFromPoint( float X, float Y, float Z )
{
	return (float) ((vehPos.X - X) * (vehPos.X - X) +
		(vehPos.Y - Y) * (vehPos.Y - Y) +
		(vehPos.Z - Z) * (vehPos.Z - Z) );
}

float CVehicle::GetSquaredDistance2D_FromPoint( float X, float Y )
{
	return (float) ((vehPos.X - X) * (vehPos.X - X) +
		(vehPos.Y - Y) * (vehPos.Y - Y) );
}

void CVehicle::UpdatePositionForPlayer(_PlayerID playerId, float X, float Y, float Z)
{
	uint32_t RPC_SetVehiclePos = 0x19;	

	RakNet::BitStream bStream;
	bStream.Write(vehID);
	bStream.Write(X);
	bStream.Write(Y);
	bStream.Write(Z);

	CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_SetVehiclePos, &bStream, playerId, 2);
}

void CVehicle::Repair()
{
    SetHealth(1000.0f);
	UpdateDamage(0xFFFF, 0, 0, 0, 0);
}

void CVehicle::UpdateDamage(_PlayerID attackerId, uint32_t panelDamage, uint32_t doorDamage, uint8_t lightDamage, uint8_t tireStatus)
{
    vehDoorStatus = doorDamage;
	vehPanelStatus = panelDamage;
	vehLightStatus = lightDamage;
	vehTireStatus = tireStatus;
	
	RakNet::BitStream bStream;
	bStream.Write(vehID);
	bStream.Write(vehPanelStatus);
	bStream.Write(vehDoorStatus);
	bStream.Write(vehLightStatus);
    bStream.Write(vehTireStatus);

	if(attackerId != 0xFFFF) 
	{
		if(__NetGame->gamemodeManager && __NetGame->filterscriptsManager) 
		{
			__NetGame->filterscriptsManager->OnVehicleDamageStatusUpdate((cell)vehID,(cell)attackerId);
			__NetGame->gamemodeManager->OnVehicleDamageStatusUpdate((cell)vehID,(cell)attackerId);
		}
	}

	uint32_t RPC_DamageVehicle = 0x6C;	

	CNetGame__RPC_SendToPlayerVehicle( ( uint32_t )__NetGame, &RPC_DamageVehicle, &bStream, vehID, attackerId, 2);
}

bool CVehicle::AddVehicleComponent(_PlayerID playerId, uint16_t component)
{
	uint8_t ucVehicleModIdLookup;
	uint8_t ucVehicleModelLookup;
	uint8_t ucModSlotId;

	if(component < 1000 || component > (1000 + (194 - 1)) ) 
		return false;

	ucVehicleModIdLookup = component - 1000;
	ucVehicleModelLookup = customSpawn.vehType - 400;

	if( vehicleTypeComponent[ucVehicleModIdLookup] != 0xFF &&
		vehicleTypeComponent[ucVehicleModIdLookup] != ucVehicleModelLookup ) {
		return false;
	}

	if(playerId != 0xFFFF) 
	{

		if(!__NetGame->gamemodeManager || !__NetGame->filterscriptsManager) 
			return false;

		if( !__NetGame->gamemodeManager->OnVehicleMod(playerId, vehID, component) ||
			!__NetGame->filterscriptsManager->OnVehicleMod(playerId, vehID, component) ) 
		{
			uint32_t RPC_RemoveComponent = 0x3F;
				
			RakNet::BitStream bStream;
			bStream.Write(vehID);
			bStream.Write(component);
			CNetGame__RPC_SendToPlayer( ( uint32_t )__NetGame, &RPC_RemoveComponent, &bStream, playerId, 2);
			return false;
		}
	
	}

	ucModSlotId = vehicleComponentTypes[ucVehicleModIdLookup];
    if(ucModSlotId == 8) return false;
    vehModInfo.vehModSlots[ucModSlotId] = ucVehicleModIdLookup + 1;

	uint32_t RPC_ScmEvent = 0xE4;
  	 
	RakNet::BitStream bStream;
	int	iEvent = 2;

	bStream.Write(playerId);
    bStream.Write(iEvent);
	bStream.Write(vehID);
	bStream.Write((uint32_t)component);
	bStream.Write((uint32_t)0);

	CNetGame__RPC_SendToPlayerVehicle( ( uint32_t )__NetGame, &RPC_ScmEvent, &bStream, vehID, playerId, 2);

	return true;
}

void CVehicle::RemoveVehicleComponent(_PlayerID playerId, uint16_t component)
{
	unsigned char ucVehicleModIdLookup;
	unsigned char ucModSlotId;

	if( component < 1000 || component > (1000 + (194 - 1)) )
		return;

	ucVehicleModIdLookup = component - 1000;
	ucModSlotId = vehicleComponentTypes[ucVehicleModIdLookup];

	if( vehModInfo.vehModSlots[ucModSlotId] != 0 &&
		(vehModInfo.vehModSlots[ucModSlotId] - 1) == ucVehicleModIdLookup ) 
	{
		uint32_t RPC_RemoveComponent = 0x3F;

		RakNet::BitStream bStream;
		bStream.Write(vehID);
		bStream.Write(component);
		CNetGame__RPC_SendToPlayerVehicle( ( uint32_t )__NetGame, &RPC_RemoveComponent, &bStream, vehID, playerId, 2);
		vehModInfo.vehModSlots[ucModSlotId] = 0;
	}
}

void CVehicle::SetPaintjob(_PlayerID playerId, uint8_t paintjob)
{
	if(playerId != 0xFFFF) 
	{
		if(!__NetGame->gamemodeManager || !__NetGame->filterscriptsManager) return;

		if( !__NetGame->gamemodeManager->OnVehiclePaintjob(playerId, vehID, paintjob) ||
			!__NetGame->filterscriptsManager->OnVehiclePaintjob(playerId, vehID, paintjob) )
				return;
	}

	vehModInfo.vehPaintJob = paintjob + 1;

	uint32_t RPC_ScmEvent = 0xE4;

	RakNet::BitStream bStream;
	int	iEvent = 1;
	DWORD dwVehicleID = vehID;
	DWORD dwPaint = paintjob;
	DWORD dwUnused = 0;

	bStream.Write(playerId);
    bStream.Write(iEvent);
	bStream.Write(dwVehicleID);
	bStream.Write(dwPaint);
	bStream.Write(dwUnused);

	CNetGame__RPC_SendToPlayerVehicle( ( uint32_t )__NetGame, &RPC_ScmEvent, &bStream, vehID, playerId, 2);       
}

void CVehicle::ChangeColor(_PlayerID playerId, uint32_t color1, uint32_t color2)
{
	if(playerId != 0xFFFF) 
	{
		if(!__NetGame->gamemodeManager || !__NetGame->filterscriptsManager) return;

		if( !__NetGame->gamemodeManager->OnVehicleRespray(playerId, vehID, color1, color2) ||
			!__NetGame->filterscriptsManager->OnVehicleRespray(playerId, vehID, color1, color2) ) 
				return;
	}

	vehModInfo.vehColor1 = color1;
	vehModInfo.vehColor2 = color2;

	uint32_t RPC_ScmEvent = 0xE4;

	RakNet::BitStream bStream;
	int	iEvent = 3;
	DWORD dwVehicleID = vehID;
	DWORD dwvehColor1 = color1;
	DWORD dwColor2 = color2;

	bStream.Write(playerId);
    bStream.Write(iEvent);
	bStream.Write(dwVehicleID);
	bStream.Write(dwvehColor1);
	bStream.Write(dwColor2);

	CNetGame__RPC_SendToPlayerVehicle( ( uint32_t )__NetGame, &RPC_ScmEvent, &bStream, vehID, playerId, 2);       
}

bool CVehicle::HasVehicleMods()
{	
    for(int i=0; i < 14; i++)
		if(vehModInfo.vehModSlots[i] != 0) return true;
    if(vehModInfo.vehPaintJob != 0) return true;
	if(vehModInfo.vehColor1 >= 0 && vehModInfo.vehColor1 != customSpawn.vehColor1) return true;
	if(vehModInfo.vehColor2 >= 0 && vehModInfo.vehColor2 != customSpawn.vehColor2) return true;

	return false;
}