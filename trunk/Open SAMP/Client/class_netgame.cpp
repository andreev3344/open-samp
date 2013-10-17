#include "main.h"



CNetGame::CNetGame()
{
}

CNetGame::~CNetGame()
{
}

void CNetGame::registerRPCs( )
{
	REGISTER_STATIC_RPC( __NetGame->getRakClientInterface(), RegisterBindKey );
	REGISTER_STATIC_RPC( __NetGame->getRakClientInterface(), UnregisterBindKey );
	REGISTER_STATIC_RPC( __NetGame->getRakClientInterface(), ToggleVehicleCollision );
	REGISTER_STATIC_RPC( __NetGame->getRakClientInterface(), ShowCheckpoint );
	REGISTER_STATIC_RPC( __NetGame->getRakClientInterface(), ShowRaceCheckpoint );
}


void CNetGame::unRegisterRPCs( )
{

	
	UNREGISTER_STATIC_RPC( __NetGame->getRakClientInterface(), RegisterBindKey );
	UNREGISTER_STATIC_RPC( __NetGame->getRakClientInterface(), UnregisterBindKey );
	UNREGISTER_STATIC_RPC( __NetGame->getRakClientInterface(), ToggleVehicleCollision );
	UNREGISTER_STATIC_RPC( __NetGame->getRakClientInterface(), ShowCheckpoint );
	UNREGISTER_STATIC_RPC( __NetGame->getRakClientInterface(), ShowRaceCheckpoint );
}


tNetGamePools* CNetGame::getPools()
{
	return this->pPools;
}

void* CNetGame::getGangZonePool()
{
	if( this->pPools )
		return this->pPools->m_pGangZonePool;
	return 0;
}

void* CNetGame::getMenuPool()
{
	if( this->pPools )
		return this->pPools->m_pMenuPool;
	return 0;
}

CPlayerPool* CNetGame::getPlayerPool()
{
	if( this->pPools )
		return this->pPools->m_pPlayerPool;
	return 0;
}

CVehiclePool* CNetGame::getVehiclePool()
{
	if( this->pPools )
		return this->pPools->m_pVehiclePool;
	return 0;
}

void* CNetGame::getTextDrawPool()
{
	if( this->pPools )
		return this->pPools->m_pTextDrawPool;
	return 0;
}

CObjectPool* CNetGame::getObjectPool()
{
	if( this->pPools )
		return this->pPools->m_pObjectPool;
	return 0;
}

CText3DLabelsPool* CNetGame::getText3DPool()
{
	if( this->pPools )
		return this->pPools->m_p3DTextPool;
}

void* CNetGame::getPickupPool()
{
	if( this->pPools )
		return this->pPools->m_pPickupPool;
}


uint32_t CNetGame::getServerPort()
{
	return this->svrPort;
}

char* CNetGame::getServerHost()
{
	return (char*)this->svrHostOrIp;
}

char* CNetGame::getServerHostName()
{
	return (char*)this->svrHostName;
}


uint32_t CNetGame::getGameState()
{
	return this->gameState;
}

BOOL CNetGame::isLanMode()
{
	return this->bLanMode;
}


RakClientInterface* CNetGame::getRakClientInterface()
{
	return this->rakClientInterface;
}

tServerSettings* CNetGame::getServerSettings()
{
	return this->svrSettings;
}

uint32_t CNetGame::setMapIcon( uint8_t iconID, float posX, float posY, float posZ, uint8_t markerType, uint32_t color, uint32_t style )
{
	uint32_t GTA_Icon_ID = 0;

	_asm
	{
		pushad

		mov ecx, this
		mov ebx, FUNC_CNETGAME_SETMAPICON
		add ebx, sampBaseAddr

		push style
		push color
		push markerType
		push posZ
		push posY
		push posX
		push iconID
		call ebx
		mov GTA_Icon_ID, eax

		popad
	}


	return GTA_Icon_ID;
}

void CNetGame::removeMapIcon( uint8_t iconID )
{
	/* scriptCommand( ....., &mapIcons[ iconID ] ); */

	_asm
	{
		pushad

		mov ecx, this
		mov ebx, FUNC_CNETGAME_REMOVEMAPICON
		add ebx, sampBaseAddr
		push iconID
		call ebx	

		popad
	}

}