#include "main.h"

char currentGamemodeFile[256];
float fRestartWaitTime = 0.0f;

extern int iServerSleepTimer;

CNetGame::CNetGame ( )
{
	fRestartWaitTime = 0.0f;
	this->allowAdminTeleport = FALSE;
	this->allowInteriorWeapons = FALSE;
	this->worldTime = 12;
	this->weather	= 1;
	this->enableBonusStuntForAll = true;
	this->gravity	= 0.008f;
	this->deathDropAmount = 0;
	this->enableZoneName = false;
	
	this->playerPool = NULL;
	this->vehiclePool = NULL;
	this->gamemodeManager = NULL;
	this->pickupPool = NULL;
	this->objectPool = NULL;
	this->menuPool = NULL;
	this->textDrawPool = NULL;
	this->disableNameTagLineOfSight = true;
	this->gangZonePool = NULL;
	this->text3DLabelsPool = NULL;
	this->bLanMode = FALSE;
	this->byteMod = 0x01;

	this->blimitGlobalChatRadius = false;
	this->dlimitGlobalChatRadius = 10000.0f;
	this->bLimitPlayerMarkerRadius = FALSE;
	this->dlimitPlayerMarkerRadius = 10000.0f;
	this->nameTagDrawDistance = 70.0f;
	this->disableInteriorEnterExit = false;

	this->currentGameModeIndex = 0;
	this->currentGameModeRepeat = 0;
	this->isFirstGameModeLoad = FALSE;
	this->scriptTimerManager = new CScriptTimers;
	this->scriptHttpManager = new CScriptHttp;

	#ifndef WIN32
		this->elapsedTime = 0.0;
	#endif

	if(__Console->GetIntVar("maxplayers") > MAX_PLAYERS)
		__Console->SetIntVar("maxplayers", MAX_PLAYERS);

	char* szBindAddress = __Console->GetStringVar("bind");
	if (szBindAddress && szBindAddress[0] == 0)
		szBindAddress = NULL;

	uint16_t Port = __Console->GetIntVar("port");
	uint16_t MaxPlayers = __Console->GetIntVar("maxplayers");
	BOOL useLanMode = __Console->GetBoolVar("lanmode");

	this->rakServerInterface = RakNetworkFactory::GetRakServerInterface();
	
	//NetGameStartTime = RakNet::GetTime();

	if (!this->rakServerInterface->Start(MaxPlayers, 0, iServerSleepTimer, Port, szBindAddress))
	{
		if (szBindAddress)
			logprintf("Unable to start server on %s:%d. Port in use?",szBindAddress, Port);
		else
			logprintf("Unable to start server on port: %d. Port in use?", Port);
		return;
	}
	
	LoadBanList();

	if(!this->setNextGamemodeFile(NULL)) 
	{
		logprintf("I couldn't load any gamemode scripts. Please verify your server.cfg");
		logprintf("It needs a gamemode0 line at the very least.");
		fcloseall();
		exit(1);
	}
		
	this->rakServerInterface->StartOccasionalPing();

	char* szPass = __Console->GetStringVar("password");
	if ((szPass) && (szPass[0] != 0)) { 
		this->rakServerInterface->SetPassword(szPass);
	}

	RegisterRPCs(this->rakServerInterface);

	char szTime[256];
	sprintf(szTime, "%02d:%02d", this->worldTime, 0);
	__Console->AddStringVar("worldtime", CONSOLE_VARFLAG_RULE, szTime);
	
	if(useLanMode)
		this->bLanMode = true;

	char szScriptFiles[512];
	int len;

	#ifdef WIN32
		GetCurrentDirectoryA(sizeof(szScriptFiles), szScriptFiles);
		len = strlen(szScriptFiles);
		if (szScriptFiles[len-1] != '\\')
		{
			szScriptFiles[len] = '\\';
			szScriptFiles[len+1] = '\0';
		}
		strcat(szScriptFiles, "scriptfiles\\");
		SetEnvironmentVariableA("AMXFILE", szScriptFiles);
	#else
		getcwd(szScriptFiles, sizeof(szScriptFiles));
		len = strlen(szScriptFiles);
		if (szScriptFiles[len-1] != '/')
		{
			szScriptFiles[len] = '/';
			szScriptFiles[len+1] = '\0';
		}
		strcat(szScriptFiles, "scriptfiles/");
		setenv("AMXFILE", szScriptFiles, 1);
	#endif

	this->filterscriptsManager = new CFilterscriptsManager();

	if (szBindAddress) 
	{
		printf( "\nStarted server on %s:%d, with maxplayers: %d lanmode is %s.\n\n",
			szBindAddress, Port, MaxPlayers, useLanMode?"ON":"OFF" );
	}
	else
	{
		printf( "\nStarted server on port: %d, with maxplayers: %d lanmode is %s.\n\n",
			Port, MaxPlayers, useLanMode?"ON":"OFF" );
	}

	this->gameState = 0;
}

CNetGame::~CNetGame( )
{
	logprintf("--- Server Shutting Down.");

	SAFE_DELETE(this->gamemodeManager);
	SAFE_DELETE(this->filterscriptsManager);
	SAFE_DELETE(this->scriptTimerManager);
	SAFE_DELETE(this->scriptHttpManager);
	SAFE_DELETE(this->text3DLabelsPool);

	SAFE_DELETE(this->vehiclePool);
	SAFE_DELETE(this->playerPool);	
	SAFE_DELETE(this->objectPool);
	SAFE_DELETE(this->pickupPool);
	SAFE_DELETE(this->menuPool);
	SAFE_DELETE(this->textDrawPool);
	SAFE_DELETE(this->gangZonePool);	

	this->rakServerInterface->Disconnect(100);
	UnRegisterRPCs(this->rakServerInterface);

	RakNetworkFactory::DestroyRakServerInterface(this->rakServerInterface);
}


uint32_t CNetGame::GetTime( )
{
	return RakNet::GetTime( );
}
uint32_t CNetGame::addSpawn( tSPAWNS spawn )
{
	if( this->spawnsNumber >= MAX_SPAWNS ) return MAX_SPAWNS;
	memcpy( &this->spawns[ this->spawnsNumber ], &spawn, sizeof( tSPAWNS ) );

	return this->spawnsNumber++;
}

void CNetGame::limitGlobalChatRadius( float distance )
{
	this->blimitGlobalChatRadius = true;
	this->dlimitGlobalChatRadius = distance;
}
void CNetGame::limitPlayerMarkerRadius( float distance )
{
	this->bLimitPlayerMarkerRadius = true;
	this->dlimitPlayerMarkerRadius = distance;
}

void CNetGame::setWeather( uint8_t weather )
{
	RakNet::BitStream* bStream = new RakNet::BitStream( );

	bStream->Write( (uint8_t)weather );
	this->weather = weather;

	if( this->playerPool > 0 )
	{
		__NetGame->GlobalRPC( RPC_ChangeWeather, bStream, 0xFFFF, 2 );
	}

	char str[ 128 ] = "";
	sprintf( str, "%d", weather );
	__Console->SetStringVar( "weather", str );
}

void CNetGame::SendClientMessage(_PlayerID playerId, uint32_t msgColor, char* msgStr, ...)
{
	char szBuffer[1024];
	memset(szBuffer, 0, 1024);

	va_list va;
	va_start(va, msgStr);
	vsprintf(szBuffer, msgStr, va);
	va_end(va);

	RakNet::BitStream bsParams;
	uint32_t strLen = strlen(szBuffer);

	bsParams.Write(msgColor);
	bsParams.Write(strLen);
	bsParams.Write(szBuffer, strLen);

	this->PlayerRPC(RPC_ClientMessage, &bsParams, playerId, PACKET_STREAM_RPC_TEXT);
}

void CNetGame::SendClientMessageToAll(uint32_t msgColor, char* msgStr, ...)
{
	char szBuffer[1024];
	memset(szBuffer, 0, 1024);

	va_list va;
	va_start(va, msgStr);
	vsprintf(szBuffer, msgStr, va);
	va_end(va);

	RakNet::BitStream bsParams;
	uint32_t dwStrLen = strlen(szBuffer);

	bsParams.Write(msgColor);
	bsParams.Write(dwStrLen);
	bsParams.Write(szBuffer, dwStrLen);

	this->GlobalRPC(RPC_ClientMessage, &bsParams, INVALID_PLAYER_ID, PACKET_STREAM_RPC_TEXT);
}

char* CNetGame::getNextGamemodeFile()
{
	char* szTemp;
	char szCurGameModeConsoleVar[64];
	this->currentGameModeIndex++;

	sprintf(szCurGameModeConsoleVar, "gamemode%u", this->currentGameModeIndex);
	szTemp = strtok(__Console->GetStringVar(szCurGameModeConsoleVar), " ");

	if(!szTemp || !strlen(szTemp)) 
	{
		this->currentGameModeIndex = 0;				
		sprintf(szCurGameModeConsoleVar,"gamemode%u", this->currentGameModeIndex);
		szTemp = strtok(__Console->GetStringVar(szCurGameModeConsoleVar), " ");
	}

	if(!szTemp || !strlen(szTemp)) return NULL;
	return szTemp;

}

int CanFileBeOpenedForReading(char* filename)
{
	FILE *f;
	if(f=fopen(filename,"r")) 
	{
		fclose(f);
		return 1;
	}
	return 0;
}

BOOL CNetGame::setNextGamemodeFile(char* gamemodeStr)
{
	char szConfigFileName[64];
	char* szTemp;
	int  iConfigRepeatCount=0;

	if(gamemodeStr == NULL) 
	{ 
		if(this->currentGameModeRepeat || !this->isFirstGameModeLoad) 
		{ 
			this->currentGameModeIndex--;
		}
		
		szTemp = this->getNextGamemodeFile();
		if (szTemp == NULL) return false;

		sscanf(szTemp, "%s%d", szConfigFileName, &iConfigRepeatCount);

		sprintf(currentGamemodeFile, "gamemodes/%s.amx", szConfigFileName);

		if(!CanFileBeOpenedForReading(currentGamemodeFile))
			return FALSE;

		if(!this->currentGameModeRepeat)
			this->currentGameModeRepeat = iConfigRepeatCount;

		this->currentGameModeRepeat--;

		this->isFirstGameModeLoad = TRUE;

		return TRUE;

	} 
	else
	{
		
		sprintf(currentGamemodeFile, "gamemodes/%s.amx", gamemodeStr);

		if(!CanFileBeOpenedForReading(currentGamemodeFile))
			return FALSE;

		this->currentGameModeRepeat = 0;

		return TRUE;
	}
}

void CNetGame::LoadBanList()
{
	this->rakServerInterface->ClearBanList();

	FILE* fileBanList = fopen("samp.ban","r");

	if(!fileBanList)
		return;

	char tmpban_ip[256];

	while(!feof(fileBanList)) 
	{
		if (fgets(tmpban_ip,256,fileBanList)) 
		{
			int len = strlen(tmpban_ip);
			if (len > 0 && tmpban_ip[len - 1] == '\n')
				tmpban_ip[len - 1] = 0;
			len = strlen(tmpban_ip);
			if (len > 0 && tmpban_ip[len - 1] == '\r')
				tmpban_ip[len - 2] = 0;
			if (tmpban_ip[0] != 0 && tmpban_ip[0] != '#') 
			{
				char *ban_ip = strtok(tmpban_ip, " \t");
				this->rakServerInterface->AddToBanList(ban_ip);
			}
		}
	}

	logprintf("");
	logprintf("Ban list");
	logprintf("--------");
	logprintf(" Loaded: samp.ban");
	logprintf("");

	fclose(fileBanList);
}

void CNetGame::AddBan(char* nick, char* ip_mask, char* reason)
{
	const struct tm *tm;
	time_t now;
	now = time(NULL);
	tm = localtime(&now);
	char *s;
	s = new char[256];
	strftime(s, 256, "[%d/%m/%y | %H:%M:%S]", tm);

	this->rakServerInterface->AddToBanList(ip_mask);
	
	FILE* fileBanList = fopen("samp.ban","a");
	if(!fileBanList) return;
	
	fprintf(fileBanList,"%s %s %s - %s\n", ip_mask, s, nick, reason);
	fclose(fileBanList);

	delete [] s;
}

void CNetGame::RemoveBan(char* ip_mask)
{
	this->rakServerInterface->RemoveFromBanList(ip_mask);
	
	FILE* fileBanList = fopen("samp.ban", "r");
	FILE* fileWriteList = fopen("samp.ban.temp", "w");
	if(!fileBanList || !fileWriteList) return;
	
	char line[256];
	char line2[256];
	char* ip;
	
	while(!feof(fileBanList))
	{
		if (fgets(line, 256, fileBanList))
		{
			strcpy(line2, line);
			ip = strtok(line, " \t");
			if (strcmp(ip_mask, ip) != 0)
			{
				fprintf(fileWriteList, "%s", line2);
			}
		}
	}

	fclose(fileBanList);
	fclose(fileWriteList);
	remove("samp.ban");
	rename("samp.ban.temp", "samp.ban");
}

void CNetGame::MasterServerAnnounce(float fElapsedTime)
{
	static float fRemainingTime = 0.0f;
	fRemainingTime -= fElapsedTime;
	char szPort[32];

	if(fRemainingTime <= 0.0f)
	{
		fRemainingTime = 300.0f;
		sprintf(szPort,"%d", __Console->GetIntVar("port"));

		char *szBindAddress = __Console->GetStringVar("bind");
		if(szBindAddress && szBindAddress[0] == 0) szBindAddress = NULL;

#ifdef WIN32
		ShellExecuteA(0, "open", "announce.exe", szPort, NULL, SW_HIDE);
#else
		char szCurrentDir[256];
		char szAnnounceCmd[256];
		getcwd(szCurrentDir,256);

		if(szBindAddress) {
			sprintf(szAnnounceCmd,"%s/announce %s %s &",szCurrentDir,szPort,szBindAddress);
		} else {
			sprintf(szAnnounceCmd,"%s/announce %s &",szCurrentDir,szPort);
		}

		system(szAnnounceCmd);
#endif

	}
}

void CNetGame::LoadAllFilterscripts()
{
	logprintf("");
	logprintf("Filter Scripts");
	logprintf("---------------");
	int iScriptCount = 0;
	char* szFilterScript = strtok(__Console->GetStringVar("filterscripts"), " ");
	while (szFilterScript)
	{
		logprintf("  Loading filter script '%s.amx'...", szFilterScript);

		if (this->filterscriptsManager->LoadFilterScript(szFilterScript))
			iScriptCount++;
		else
			logprintf("  Unable to load filter script '%s.amx'.", szFilterScript);

		szFilterScript = strtok(NULL, " ");
	}
	logprintf("  Loaded %d filter scripts.\n", iScriptCount);
}

void CNetGame::Init(BOOL bFirst)
{
	this->spawnsNumber = 0;

	if(!this->playerPool)
		this->playerPool = new CPlayerPool();
	else
		this->playerPool->ResetPlayerScoresAndMoney();

	if(!this->vehiclePool)
		this->vehiclePool = new CVehiclePool();

	if(!this->pickupPool)
		this->pickupPool = new CPickupPool();

	if(!this->objectPool)
		this->objectPool = new CDeprecatedObjectPool();

	if(!this->menuPool)
		this->menuPool = new CMenuPool();
	
	if(!this->textDrawPool)
		this->textDrawPool = new CTextDrawPool();
	
	if(!this->gangZonePool)
		this->gangZonePool = new CDeprecatedGangZonePool();
	
	if(!this->text3DLabelsPool)
		this->text3DLabelsPool = new CText3DLabels();

	if(!this->gamemodeManager)
		this->gamemodeManager = new CGamemodeManager();

	this->showNameTags = true;
	this->showPlayerMarkers = PLAYER_MARKERS_MODE_GLOBAL;
	this->disableNameTagLineOfSight = true;
	this->usePlayerPedAnims = FALSE;

	this->worldTime = 12;
	this->weather   = 1;

	this->blimitGlobalChatRadius = FALSE;
	this->dlimitGlobalChatRadius = 10000.0f;
	this->bLimitPlayerMarkerRadius = FALSE;
	this->dlimitPlayerMarkerRadius = 10000.0f;

	this->nameTagDrawDistance = 70.0f;
	this->disableInteriorEnterExit = false;
	this->useManualVehicleEngineAndLight = false;

	if (bFirst) this->LoadAllFilterscripts();

	this->gamemodeManager->Load(currentGamemodeFile);

	logprintf("Number of vehicle models: %d", this->vehiclePool->GetUsedModelsCount());

	this->gameState = 1;

	srand(0);
}

void CNetGame::ShutdownForGameModeRestart()
{
	RakNet::BitStream bsParams;
	this->GlobalRPC(RPC_GameModeRestart, &bsParams);

	this->playerPool->DeactivateAll();
	
	SAFE_DELETE(this->gamemodeManager);
	SAFE_DELETE(this->vehiclePool);
	SAFE_DELETE(this->pickupPool);
	SAFE_DELETE(this->objectPool);
	SAFE_DELETE(this->menuPool);
	SAFE_DELETE(this->textDrawPool);
	SAFE_DELETE(this->gangZonePool);
	SAFE_DELETE(this->text3DLabelsPool);

	fRestartWaitTime = 0.0f;
	this->allowAdminTeleport = false;
	this->allowInteriorWeapons = FALSE;
	this->worldTime = 12;
	this->weather	= 1;
	this->gravity	= 0.008f;
	this->deathDropAmount = 0;
	this->enableZoneName = FALSE;
	this->gameState = 2;
}

extern int iNetModeNormalOnfootSendRate;
extern int iNetModeNormalIncarSendRate;
extern int iNetModeFiringSendRate;
extern int iNetModeSendMultiplier;

void CNetGame::InitGameForPlayer(_PlayerID playerId)
{
	CPlayer* player = __NetGame->playerPool->GetPlayer( playerId );
	if( player ) player->setColor( ( rand()*rand() ) | 0x000000FF ); // fix fucking color problem

	RakNet::BitStream bsInitGame;

	bsInitGame.Write(this->enableZoneName);
	bsInitGame.Write(this->usePlayerPedAnims);
	bsInitGame.Write(this->allowInteriorWeapons);
	bsInitGame.Write(this->blimitGlobalChatRadius);
	bsInitGame.Write(this->dlimitGlobalChatRadius);
	bsInitGame.Write(this->enableBonusStuntForAll);
	bsInitGame.Write(this->nameTagDrawDistance);
	bsInitGame.Write(this->disableInteriorEnterExit);
	bsInitGame.Write(this->disableNameTagLineOfSight);
	bsInitGame.Write(this->useManualVehicleEngineAndLight);
	bsInitGame.Write(this->spawnsNumber);
	bsInitGame.Write(playerId);
	bsInitGame.Write(this->showNameTags);
	bsInitGame.Write(this->showPlayerMarkers);
	bsInitGame.Write(this->worldTime);
	bsInitGame.Write(this->weather);
	bsInitGame.Write(this->gravity);

	if(this->bLanMode)
		bsInitGame.Write(true);
	else
		//bsInitGame.Write0();
		bsInitGame.Write(false);

	bsInitGame.Write(this->deathDropAmount);
	bsInitGame.Write(false); // instagib

	bsInitGame.Write(iNetModeNormalOnfootSendRate);
	bsInitGame.Write(iNetModeNormalIncarSendRate);
	bsInitGame.Write(iNetModeFiringSendRate);
	bsInitGame.Write(iNetModeSendMultiplier);

	char* szHostName = __Console->GetStringVar("hostname");
	if(szHostName) 
	{
		uint8_t byteStrLen = strlen(szHostName);
		bsInitGame.Write(byteStrLen);
		bsInitGame.Write(szHostName, byteStrLen);
	} 
	else
		bsInitGame.Write((uint8_t)0);

	BYTE byteUsedVehicleModels[NUM_VEHICLE_MODELS];
	memset(byteUsedVehicleModels, 0, NUM_VEHICLE_MODELS);

	if(this->vehiclePool)
		memcpy(byteUsedVehicleModels, &(this->vehiclePool->modelsUsed[0]), NUM_VEHICLE_MODELS);
	
	bsInitGame.Write((char *)byteUsedVehicleModels, NUM_VEHICLE_MODELS);

	this->PlayerRPC(RPC_InitGame, &bsInitGame, playerId);
}

void CNetGame::ReInitWhenRestarting()
{
	this->Init();

	_PlayerID playerId = 0;

	for(_PlayerID playerId = 0; playerId < MAX_PLAYERS; playerId++)
	{
		if(this->playerPool->GetSlotState(playerId)) 
		{
			/* Open SA:MP */
			__ElementFactory->InitializeForPlayer ( playerId );

			this->objectPool->InitForPlayer(playerId);
			this->InitGameForPlayer(playerId);
			this->filterscriptsManager->OnPlayerConnect(playerId);
			if(this->gamemodeManager) this->gamemodeManager->OnPlayerConnect(playerId);
		}
	}

}

void CNetGame::setWorldTime(uint8_t hour)
{
	RakNet::BitStream bStream;

	this->worldTime = hour;
	bStream.Write(hour);

	__NetGame->GlobalRPC( RPC_WorldTime, &bStream );

	char szTime[256];
	sprintf(szTime, "%02d:%02d", hour, 0);
	__Console->SetStringVar("worldtime", szTime);
}

void CNetGame::setGravity(float fValue)
{
	this->gravity = fValue;
	RakNet::BitStream bStream;
	bStream.Write(fValue);
		
	char szGravity[128];
	sprintf(szGravity, "%f", fValue);

	__Console->SetStringVar("gravity", szGravity);
//	__NetGame->GlobalRPC( RPC_SetGravity, &bStream );

	for( _PlayerID i = 0; i < MAX_PLAYERS; i++ )
	{
		CPlayer* player = this->playerPool->GetPlayer( i );
		if( player )
		{
			player->setGravity( fValue );
		}
	}


}

const char* CNetGame::getWeaponName(int weaponID)
{
	switch(weaponID)
	{ 
      case WEAPON_BRASSKNUCKLE: 
         return "Brass Knuckles"; 
      case WEAPON_GOLFCLUB: 
         return "Golf Club"; 
      case WEAPON_NITESTICK: 
         return "Nite Stick"; 
      case WEAPON_KNIFE: 
         return "Knife"; 
      case WEAPON_BAT: 
         return "Baseball Bat"; 
      case WEAPON_SHOVEL: 
         return "Shovel"; 
      case WEAPON_POOLSTICK: 
         return "Pool Cue"; 
      case WEAPON_KATANA: 
         return "Katana"; 
      case WEAPON_CHAINSAW: 
         return "Chainsaw"; 
      case WEAPON_DILDO: 
         return "Dildo"; 
      case WEAPON_DILDO2: 
         return "Dildo"; 
      case WEAPON_VIBRATOR: 
         return "Vibrator"; 
      case WEAPON_VIBRATOR2: 
         return "Vibrator"; 
      case WEAPON_FLOWER: 
         return "Flowers"; 
      case WEAPON_CANE: 
         return "Cane"; 
      case WEAPON_GRENADE: 
         return "Grenade"; 
      case WEAPON_TEARGAS: 
         return "Teargas"; 
      case WEAPON_COLT45: 
         return "Colt 45"; 
      case WEAPON_SILENCED: 
         return "Silenced Pistol"; 
      case WEAPON_DEAGLE: 
         return "Desert Eagle"; 
      case WEAPON_SHOTGUN: 
         return "Shotgun"; 
      case WEAPON_SAWEDOFF: 
         return "Sawn-off Shotgun"; 
      case WEAPON_SHOTGSPA:
         return "Combat Shotgun"; 
      case WEAPON_UZI: 
         return "UZI"; 
      case WEAPON_MP5: 
         return "MP5"; 
      case WEAPON_AK47: 
         return "AK47"; 
      case WEAPON_M4: 
         return "M4"; 
      case WEAPON_TEC9: 
         return "TEC9"; 
      case WEAPON_RIFLE: 
         return "Rifle"; 
      case WEAPON_SNIPER: 
         return "Sniper Rifle"; 
      case WEAPON_ROCKETLAUNCHER: 
         return "Rocket Launcher"; 
      case WEAPON_HEATSEEKER: 
         return "Heat Seaker"; 
      case WEAPON_FLAMETHROWER: 
         return "Flamethrower"; 
      case WEAPON_MINIGUN: 
         return "Minigun"; 
      case WEAPON_SATCHEL: 
         return "Satchel Explosives"; 
      case WEAPON_BOMB: 
         return "Bomb"; 
      case WEAPON_SPRAYCAN: 
         return "Spray Can"; 
      case WEAPON_FIREEXTINGUISHER: 
         return "Fire Extinguisher"; 
      case WEAPON_CAMERA: 
         return "Camera"; 
      case WEAPON_PARACHUTE: 
         return "Parachute"; 
      case WEAPON_VEHICLE: 
         return "Vehicle"; 
      case WEAPON_DROWN: 
         return "Drowned"; 
      case WEAPON_COLLISION: 
         return "Splat";
	}

	return "";
}

void CNetGame::ProcessClientJoin(_PlayerID playerID)
{
	if(this->gameState == 1)
	{
		/* Open SA:MP */
		__ElementFactory->InitializeForPlayer ( playerID );

		this->objectPool->InitForPlayer(playerID);
		this->menuPool->resetForPlayer(playerID);
		this->InitGameForPlayer(playerID);
		this->playerPool->InitPlayersForPlayer(playerID);
	} 
	else if(this->gameState == 2)
	{
		this->InitGameForPlayer(playerID);
		this->playerPool->InitPlayersForPlayer(playerID);
		
		RakNet::BitStream bsParams;
		PlayerID sender = this->rakServerInterface->GetPlayerIDFromIndex(playerID);
		this->rakServerInterface->RPC(RPC_GameModeRestart, &bsParams, HIGH_PRIORITY, RELIABLE, 0, sender, false, false);
	}
}

void CNetGame::Process()
{
	float fElapsedTime = GetElapsedTime();

	UpdateNetwork();

	if(this->gameState == 1) 
	{	
		if(this->playerPool) this->playerPool->Process(fElapsedTime);
		if(this->vehiclePool) this->vehiclePool->Process(fElapsedTime);
		if(this->objectPool) this->objectPool->Process(fElapsedTime);
		if(this->gamemodeManager) this->gamemodeManager->Frame(fElapsedTime);
		if(this->scriptTimerManager) this->scriptTimerManager->Process((uint32_t)(fElapsedTime * 1000.0f));
		if(this->scriptHttpManager) this->scriptHttpManager->Process();

		if ( __ElementFactory ) __ElementFactory->Process ( fElapsedTime );
	} 
	else if(this->gameState == 2) 
	{
		fRestartWaitTime += fElapsedTime;
		if(fRestartWaitTime > 12.0f)
		{
			ReInitWhenRestarting();
		}
	}

	if (__Console->GetBoolVar("announce"))
		MasterServerAnnounce(fElapsedTime);

	__Plugins->DoProcessTick();

	#ifndef WIN32
		this->elapsedTime += (double)fElapsedTime;
	#endif
}

// RPC Interface

void CNetGame::GlobalRPC(char *szUniqueID, RakNet::BitStream *bitStream, _PlayerID ExcludePlayer, char PacketStream)
{
	if(!this->playerPool) return;

	PacketReliability reliable = RELIABLE_ORDERED;
	if(PacketStream == PACKET_STREAM_RPC_TEXT) reliable = RELIABLE;

	if(ExcludePlayer == INVALID_PLAYER_ID) 
		this->rakServerInterface->RPC(szUniqueID, bitStream, HIGH_PRIORITY, reliable, PacketStream, UNASSIGNED_PLAYER_ID, true, false);
	else
		this->rakServerInterface->RPC(szUniqueID, bitStream, HIGH_PRIORITY, reliable, PacketStream, this->rakServerInterface->GetPlayerIDFromIndex(ExcludePlayer), true, false);
}

void CNetGame::AddedPlayersRPC(char *szUniqueID, RakNet::BitStream *bitStream, _PlayerID Player, char PacketStream)
{
	if(!this->playerPool) return;
	CPlayer* player;

	for(_PlayerID i = 0; i < MAX_PLAYERS; i++)
	{
		if(this->playerPool->GetSlotState(i) && i != Player) 
		{
			player = this->playerPool->GetPlayer(i);
			if(player && player->isPlayerStreamedIn(Player))
				this->rakServerInterface->RPC(szUniqueID, bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, PacketStream, this->rakServerInterface->GetPlayerIDFromIndex(i), false, false);

		}
	}
}

void CNetGame::AddedVehicleRPC(char *szUniqueID, RakNet::BitStream *bitStream, _VehicleID Vehicle, _PlayerID ExcludePlayer, char PacketStream)
{
	if(!this->playerPool || !this->vehiclePool) return;
	CPlayer* player;

	for(_PlayerID i = 0; i < MAX_PLAYERS; i++)
	{
		if(this->playerPool->GetSlotState(i) && (i != ExcludePlayer)) 
		{
			player = this->playerPool->GetPlayer(i);
			if(player && player->isVehicleStreamedIn(Vehicle))
				this->rakServerInterface->RPC(szUniqueID, bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, PacketStream, this->rakServerInterface->GetPlayerIDFromIndex(i), false, false);
		
		}
	}
}

void CNetGame::PlayerRPC(char *szUniqueID, RakNet::BitStream *bitStream, _PlayerID Player, char PacketStream)
{
	if(!this->playerPool) return;

	PacketReliability reliable = RELIABLE_ORDERED;
	if(PacketStream == PACKET_STREAM_RPC_TEXT) reliable = RELIABLE;

	//if(this->playerPool->GetSlotState(Player))
	this->rakServerInterface->RPC(szUniqueID, bitStream, HIGH_PRIORITY, reliable, PacketStream, this->rakServerInterface->GetPlayerIDFromIndex(Player), false, false);

}

// Packet Interface

void CNetGame::GlobalPacket(RakNet::BitStream* bStream)
{
	this->rakServerInterface->Send(bStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, PACKET_STREAM_SYNC, UNASSIGNED_PLAYER_ID, true);
}

void CNetGame::PlayerPacket(RakNet::BitStream* bStream, _PlayerID remotePlayer)
{
	this->rakServerInterface->Send(bStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, PACKET_STREAM_SYNC, this->rakServerInterface->GetPlayerIDFromIndex(remotePlayer), false);
}

BOOL CNetGame::DecimatePacket(float distance)
{
	int iSendRate = 0;
	int iWillDecimate = 0;

    if	    (distance < 150.0f) iSendRate = 0;
	else if (distance < 250.0f) iSendRate = 1;
	else						 iSendRate = 2;

	if(iSendRate > 0) iWillDecimate = (int)(rand() % iSendRate);
    if(iWillDecimate) return TRUE;
	
	return FALSE;
}

void CNetGame::AddedPlayersPacket(RakNet::BitStream* bStream, _PlayerID remotePlayer)
{
	if(!this->playerPool) return;
	CPlayer* player = NULL;

	for(_PlayerID i = 0; i < MAX_PLAYERS; i++)
	{
		if(this->playerPool->GetSlotState(i) && (i != remotePlayer))
		{
			player = this->playerPool->GetPlayer(i);
			if(player->isPlayerStreamedIn(remotePlayer)) 
			{
				float distance = this->playerPool->GetDistanceBetweenPlayers(remotePlayer, i);
				if(!this->DecimatePacket(distance)) 
				{
					this->rakServerInterface->Send(bStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, PACKET_STREAM_SYNC,
						this->rakServerInterface->GetPlayerIDFromIndex(i), false);
				}
			}
		}
	}
}

void CNetGame::AddedVehiclePacket(RakNet::BitStream* bStream, _VehicleID vehicleID, _PlayerID remotePlayer)
{
	if(!this->playerPool || !this->vehiclePool) return;

	CPlayer* player = NULL;
	CVehicle* vehicle = NULL;

	vehicle = this->vehiclePool->GetVehicle(vehicleID);
	if(!this->vehiclePool->GetSlotState(vehicleID) || !vehicle) return;

	for(_PlayerID i = 0; i < MAX_PLAYERS; i++)
	{
		if(this->playerPool->GetSlotState(i) && (i != remotePlayer))
		{
			player = this->playerPool->GetPlayer(i);
			if(player && player->isVehicleStreamedIn(vehicleID)) 
			{
				this->rakServerInterface->Send(bStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, PACKET_STREAM_SYNC, 
					this->rakServerInterface->GetPlayerIDFromIndex(i), false);
			}
		}
	}
}

// Network Handling

void CNetGame::UpdateNetwork()
{
	Packet* p;
	unsigned char packetId;

	while(p = this->rakServerInterface->Receive())
	{
		packetId = p->data[0];
		
		switch(packetId) 
		{

		case ID_NEW_INCOMING_CONNECTION:
			Packet_NewIncomingConnection(p);
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			Packet_DisconnectionNotification(p);
			break;
		case ID_CONNECTION_LOST:
			Packet_ConnectionLost(p);
			break;
		case ID_MODIFIED_PACKET:
			Packet_ModifiedPacket(p);
			break;
		case ID_PLAYER_SYNC:
			Packet_PlayerSync(p);
			break;
		case ID_VEHICLE_SYNC:
			Packet_VehicleSync(p);
			break;
		case ID_PASSENGER_SYNC:
			Packet_PassengerSync(p);
			break;
		case ID_SPECTATOR_SYNC:
			Packet_SpectatorSync(p);
			break;
		case ID_AIM_SYNC:
			Packet_AimSync(p);
			break;
		case ID_RCON_COMMAND:
			Packet_InGameRcon(p);
			break;
		case ID_STATS_UPDATE:
			Packet_StatsUpdate(p);
			break;
		case ID_WEAPONS_UPDATE:
			Packet_WeaponsUpdate(p);
			break;
		case ID_TRAILER_SYNC:
			Packet_TrailerSync(p);
			break;
		case ID_UNOCCUPIED_SYNC:
			Packet_UnoccupiedSync(p);
			break;
		}

		this->rakServerInterface->DeallocatePacket(p);		
	}
}

void CNetGame::KickPlayer(_PlayerID playerId)
{
	PlayerID player = this->rakServerInterface->GetPlayerIDFromIndex(playerId);

	if(playerId < MAX_PLAYERS) 
	{
		if(this->playerPool->GetSlotState(playerId)) 
		{
			this->playerPool->Delete(playerId, 2);
			this->rakServerInterface->Kick(player);
		}
	}
}


void CNetGame::Packet_PlayerSync(Packet* p)
{
	CPlayer* pPlayer = this->playerPool->GetPlayer((_PlayerID)p->playerIndex);
	RakNet::BitStream bsPlayerSync((char*)p->data, p->length, false);

	if(this->gameState != 1) return;

	uint8_t				bytePacketID = 0;
	ON_FOOT_SYNC		ofSync;
	
	bsPlayerSync.Read(bytePacketID);
#ifdef _BIG_ENDIAN_SYSTEM
	bsPlayerSync.Read(ofSync.leftRightKeysOnfoot);
	bsPlayerSync.Read(ofSync.updownKeysOnfoot);
	bsPlayerSync.Read(ofSync.keysOnfoot);
	bsPlayerSync.Read(ofSync.position.X), bsPlayerSync.Read(ofSync.position.Y), bsPlayerSync.Read(ofSync.position.Z);
	bsPlayerSync.Read(ofSync.quaterRotation.W), bsPlayerSync.Read(ofSync.quaterRotation.X), bsPlayerSync.Read(ofSync.quaterRotation.Y), bsPlayerSync.Read(ofSync.quaterRotation.Z);
	bsPlayerSync.Read(ofSync.health);
	bsPlayerSync.Read(ofSync.armour);
	bsPlayerSync.Read(ofSync.weapon);
	bsPlayerSync.Read(ofSync.specialAction);
	bsPlayerSync.Read(ofSync.velocity.X), bsPlayerSync.Read(ofSync.velocity.Y), bsPlayerSync.Read(ofSync.velocity.Z);
	bsPlayerSync.Read(ofSync.surfingOffsets.X), bsPlayerSync.Read(ofSync.surfingOffsets.Y), bsPlayerSync.Read(ofSync.surfingOffsets.Z);
	bsPlayerSync.Read(ofSync.surfingVehicleID);
	bsPlayerSync.Read(ofSync.animationIndex);
#else
	bsPlayerSync.Read((char*)&ofSync, sizeof(ON_FOOT_SYNC));
#endif

	if(pPlayer)	
	{		
		if( ofSync.velocity.X < 100.0f && ofSync.velocity.X > -100.0f &&
			ofSync.velocity.Y < 100.0f && ofSync.velocity.Y > -100.0f &&
			ofSync.velocity.Z < 100.0f && ofSync.velocity.Z > -100.0f )
		{
			pPlayer->ProcessOnFootSyncData(&ofSync);

			if( this->gamemodeManager && this->filterscriptsManager )
			{
				if( this->gamemodeManager->OnPlayerUpdate( ( cell )p->playerIndex ) == 0 || this->filterscriptsManager->OnPlayerUpdate( ( cell )p->playerIndex ) == 0 )
					pPlayer->setSyncingType( SYNCING_TYPE_NONE );
			}

		}		
	}
}

void CNetGame::Packet_AimSync(Packet* p)
{
	CPlayer* pPlayer = this->playerPool->GetPlayer((_PlayerID)p->playerIndex);
	RakNet::BitStream bsAimSync((char*)p->data, p->length, false);

	if(this->gameState != 1) return;

	uint8_t			bytePacketID=0;
	AIM_SYNC		aimSync;
	
	bsAimSync.Read(bytePacketID);
#ifdef _BIG_ENDIAN_SYSTEM
	bsAimSync.Read(aimSync.cameraMode);
	bsAimSync.Read(aimSync.cameraFrontVector.X), bsAimSync.Read(aimSync.cameraFrontVector.Y), bsAimSync.Read(aimSync.cameraFrontVector.Z);
	bsAimSync.Read(aimSync.cameraPosition.X), bsAimSync.Read(aimSync.cameraPosition.Y), bsAimSync.Read(aimSync.cameraPosition.Z);
	bsAimSync.Read(aimSync.aimZaxis);
	bsAimSync.Read(aimSync.weaponState);
	bsAimSync.Read(aimSync.unknown001E);
#else
	bsAimSync.Read((char*)&aimSync,sizeof(AIM_SYNC));
#endif
		
	if(pPlayer)
		pPlayer->ProcessAimingSyncData(&aimSync);
}

void CNetGame::Packet_VehicleSync(Packet* p)
{
	CPlayer* pPlayer = this->playerPool->GetPlayer((_PlayerID)p->playerIndex);
	RakNet::BitStream bsVehicleSync((char*)p->data, p->length, false);

	if(this->gameState != 1) return;

	uint8_t			bytePacketID=0;
	IN_VEHICLE_SYNC icSync;
	
	bsVehicleSync.Read(bytePacketID);
#ifdef _BIG_ENDIAN_SYSTEM
	bsVehicleSync.Read(icSync.vehicleID);
	bsVehicleSync.Read(icSync.leftRightKeysOnVehicle);
	bsVehicleSync.Read(icSync.updownKeysOnVehicle);
	bsVehicleSync.Read(icSync.keysOnVehicle);
	bsVehicleSync.Read(icSync.rotation.W), bsVehicleSync.Read(icSync.rotation.X), bsVehicleSync.Read(icSync.rotation.Y), bsVehicleSync.Read(icSync.rotation.Z);
	bsVehicleSync.Read(icSync.position.X), bsVehicleSync.Read(icSync.position.Y), bsVehicleSync.Read(icSync.position.Z);
	bsVehicleSync.Read(icSync.velocity.X), bsVehicleSync.Read(icSync.velocity.Y), bsVehicleSync.Read(icSync.velocity.Z);
	bsVehicleSync.Read(icSync.health);
	bsVehicleSync.Read(icSync.playerHealth);
	bsVehicleSync.Read(icSync.playerArmor);
	bsVehicleSync.Read(icSync.playerWeapon);
	bsVehicleSync.Read(icSync.sirenType);
	bsVehicleSync.Read(icSync.gearState);
	bsVehicleSync.Read(icSync.trailerID);
	bsVehicleSync.Read(icSync.hydraReactorAngle[0]), bsVehicleSync.Read(icSync.hydraReactorAngle[1]);
	icSync.trainSpeed = ((icSync.hydraReactorAngle[0] << 16) | ((icSync.hydraReactorAngle[1]) & 0xFFFF));
#else
	bsVehicleSync.Read((char*)&icSync,sizeof(IN_VEHICLE_SYNC));
#endif

	if(pPlayer)	
	{
		if(icSync.vehicleID == INVALID_VEHICLE_ID) 
		{
			this->KickPlayer((_PlayerID)p->playerIndex);
			return;
		}

		if( icSync.velocity.X < 100.0f && icSync.velocity.X > -100.0f &&
			icSync.velocity.Y < 100.0f && icSync.velocity.Y > -100.0f &&
			icSync.velocity.Z < 100.0f && icSync.velocity.Z > -100.0f )
		{
			pPlayer->ProcessOnVehicleSyncData(&icSync);
			if( this->gamemodeManager && this->filterscriptsManager )
			{
				if( this->gamemodeManager->OnPlayerUpdate( ( cell )p->playerIndex ) == 0 || this->filterscriptsManager->OnPlayerUpdate( ( cell )p->playerIndex ) == 0 )
					pPlayer->setSyncingType( SYNCING_TYPE_NONE );
			}
		}
	}
}

void CNetGame::Packet_PassengerSync(Packet* p)
{
	CPlayer* pPlayer = this->playerPool->GetPlayer((_PlayerID)p->playerIndex);
	RakNet::BitStream bsPassengerSync((char*)p->data, p->length, false);

	if(this->gameState != 1) return;

	uint8_t			bytePacketID=0;
	PASSENGER_SYNC	psSync;
	
	bsPassengerSync.Read(bytePacketID);
#ifdef _BIG_ENDIAN_SYSTEM
	bsPassengerSync.Read(psSync.vehicleID);
	bsPassengerSync.Read(psSync.seatID);
	bsPassengerSync.Read(psSync.playerWeapon);
	bsPassengerSync.Read(psSync.playerHealth);
	bsPassengerSync.Read(psSync.playerArmour);
	bsPassengerSync.Read(psSync.leftRightKeysPassenger);
	bsPassengerSync.Read(psSync.updownKeysPassenger);
	bsPassengerSync.Read(psSync.passengersKeys);
	bsPassengerSync.Read(psSync.position.X), bsPassengerSync.Read(psSync.position.Y), bsPassengerSync.Read(psSync.position.Z);
#else
	bsPassengerSync.Read((char*)&psSync,sizeof(PASSENGER_SYNC));
#endif

	if(pPlayer)	
	{
		if(psSync.vehicleID == INVALID_VEHICLE_ID)
		{
			this->KickPlayer((uint8_t)p->playerIndex);
			return;
		}
	    pPlayer->ProcessPassengerSyncData(&psSync);
		if( this->gamemodeManager && this->filterscriptsManager )
		{
			if( this->gamemodeManager->OnPlayerUpdate( ( cell )p->playerIndex ) == 0 || this->filterscriptsManager->OnPlayerUpdate( ( cell )p->playerIndex ) == 0 )
				pPlayer->setSyncingType( SYNCING_TYPE_NONE );
		}
	}
}

void CNetGame::Packet_SpectatorSync(Packet* p)
{
	CPlayer* pPlayer = this->playerPool->GetPlayer((_PlayerID)p->playerIndex);
	RakNet::BitStream bsSpectatorSync((char*)p->data, p->length, false);

	if(this->gameState != 1) return;

	uint8_t			bytePacketID=0;
	SPECTATING_SYNC	spSync;
	
	bsSpectatorSync.Read(bytePacketID);
#ifdef _BIG_ENDIAN_SYSTEM
	bsSpectatorSync.Read(spSync.leftRightKeysOnSpectating);
	bsSpectatorSync.Read(spSync.updownKeysOnSpectating);
	bsSpectatorSync.Read(spSync.keysOnSpectating);
	bsSpectatorSync.Read(spSync.position.X), bsSpectatorSync.Read(spSync.position.Y), bsSpectatorSync.Read(spSync.position.Z);
#else
	bsSpectatorSync.Read((char*)&spSync,sizeof(SPECTATING_SYNC));
#endif

	if(pPlayer)
	{
		pPlayer->ProcessSpectatingSyncData(&spSync);
		if( this->gamemodeManager && this->filterscriptsManager )
		{
			if( this->gamemodeManager->OnPlayerUpdate( ( cell )p->playerIndex ) == 0 || this->filterscriptsManager->OnPlayerUpdate( ( cell )p->playerIndex ) == 0 )
				pPlayer->setSyncingType( SYNCING_TYPE_NONE );
		}
	}
}

void CNetGame::Packet_TrailerSync(Packet* p)
{
	CPlayer* pPlayer = this->playerPool->GetPlayer((_PlayerID)p->playerIndex);
	RakNet::BitStream bsTrailerSync((char*)p->data, p->length, false);

	if(this->gameState != 1) return;

	uint8_t bytePacketID=0;
	TRAILER_SYNC trSync;
	
	bsTrailerSync.Read(bytePacketID);
#ifdef _BIG_ENDIAN_SYSTEM
	bsTrailerSync.Read(trSync.trailerID);
	bsTrailerSync.Read(trSync.roll.X), bsTrailerSync.Read(trSync.roll.Y), bsTrailerSync.Read(trSync.roll.Z);
	bsTrailerSync.Read(trSync.direction.X), bsTrailerSync.Read(trSync.direction.Y), bsTrailerSync.Read(trSync.direction.Z);
	bsTrailerSync.Read(trSync.position.X), bsTrailerSync.Read(trSync.position.Y), bsTrailerSync.Read(trSync.position.Z);
	bsTrailerSync.Read(trSync.velocity.X), bsTrailerSync.Read(trSync.velocity.Y), bsTrailerSync.Read(trSync.velocity.Z);
#else
	bsTrailerSync.Read((char*)&trSync, sizeof(TRAILER_SYNC));
#endif

	if(pPlayer)
		pPlayer->ProcessTrailerSyncData(&trSync);
}

void CNetGame::Packet_UnoccupiedSync(Packet* p)
{
	CPlayer* pPlayer = this->playerPool->GetPlayer((_PlayerID)p->playerIndex);
	RakNet::BitStream bsUnoccupiedSync((char*)p->data, p->length, false);
	
	if(this->gameState != 1) return;

	uint8_t bytePacketID=0;
	UNOCCUPIED_SYNC unSync;
	
	bsUnoccupiedSync.Read(bytePacketID);
#ifdef _BIG_ENDIAN_SYSTEM
	bsUnoccupiedSync.Read(unSync.vehicleID);
	bsUnoccupiedSync.Read(unSync.passengerSlot);
	bsUnoccupiedSync.Read(unSync.roll.X), bsUnoccupiedSync.Read(unSync.roll.Y), bsUnoccupiedSync.Read(unSync.roll.Z);
	bsUnoccupiedSync.Read(unSync.direction.X), bsUnoccupiedSync.Read(unSync.direction.Y), bsUnoccupiedSync.Read(unSync.direction.Z);
	bsUnoccupiedSync.Read(unSync.position.X), bsUnoccupiedSync.Read(unSync.position.Y), bsUnoccupiedSync.Read(unSync.position.Z);
	bsUnoccupiedSync.Read(unSync.velocity.X), bsUnoccupiedSync.Read(unSync.velocity.Y), bsUnoccupiedSync.Read(unSync.velocity.Z);
	bsUnoccupiedSync.Read(unSync.turnVelocity.X), bsUnoccupiedSync.Read(unSync.turnVelocity.Y), bsUnoccupiedSync.Read(unSync.turnVelocity.Z);
	bsUnoccupiedSync.Read(unSync.health);
#else
	bsUnoccupiedSync.Read((char*)&unSync,sizeof(UNOCCUPIED_SYNC));
#endif

	if(pPlayer)
		pPlayer->ProcessUnoccupiedSyncData(&unSync);
}

void CNetGame::Packet_StatsUpdate(Packet* p)
{
	RakNet::BitStream bsStats((char*)p->data, p->length, false);

	_PlayerID playerId = (_PlayerID)p->playerIndex;

	int iMoney;
	int iDrunkLevel;
	uint8_t bytePacketID;
	uint8_t moneySource = 0;

	bsStats.Read(bytePacketID);
	bsStats.Read(iMoney);
	bsStats.Read(iDrunkLevel);

	if(this->playerPool)
	{
		if(this->playerPool->GetSlotState(playerId))
		{
			if( playerPool->GetPlayer( playerId )->isAnOpenUser( ) )
			{
				bsStats.Read( moneySource ); // CASINO, STUNT, Blahblah ....
			}

			this->playerPool->setPlayerMoney(playerId,iMoney/*, moneySource*/);
			this->playerPool->setPlayerDrunkLevel(playerId, iDrunkLevel);
		}
	}	
}

void CNetGame::Packet_WeaponsUpdate(Packet* p)
{
	RakNet::BitStream bsData((char*)p->data, p->length, false);

	_PlayerID playerId = (_PlayerID)p->playerIndex;

	if(this->gameState != 1) return;

	uint8_t byteLength = (p->length - 1) / 4;
	
	uint8_t byteIndex;
	uint8_t byteWeapon;
	uint16_t wordAmmo;
	
	if(this->playerPool)
	{
		if (this->playerPool->GetSlotState(playerId))
		{
			CPlayer* player = this->playerPool->GetPlayer(playerId);
			bsData.Read(byteIndex);
			_PlayerID targettedPlayerID = 0;
			bsData.Read( targettedPlayerID );

			player->SetTargettedPlayerID( targettedPlayerID );

			while (byteLength)
			{
				bsData.Read(byteIndex);
				bsData.Read(byteWeapon);
				bsData.Read(wordAmmo);
				
				if (byteIndex < (uint8_t)13)
				{
					player->SetAmmoInSlot(byteIndex, wordAmmo);
					player->SetWeaponInSlot(byteIndex, byteWeapon);
				}
				byteLength--;
			}
		}
	}
}

void CNetGame::Packet_NewIncomingConnection(Packet* p)
{
/*
	in_addr in;
	in.s_addr = p->playerId.binaryAddress;
	logprintf("Incoming connection: %s:%u", inet_ntoa(in), p->playerId.port);
*/
}

void CNetGame::Packet_DisconnectionNotification(Packet* p)
{
	this->playerPool->Delete((_PlayerID)p->playerIndex, 1);
}

void CNetGame::Packet_ConnectionLost(Packet* p)
{
	this->playerPool->Delete((_PlayerID)p->playerIndex, 0);	
}

void CNetGame::Packet_ModifiedPacket(Packet* p)
{
	static char str[22];

	in_addr in;
	in.s_addr = p->playerId.binaryAddress;

	strcpy(str, inet_ntoa( in ));
	strcat(str, ":");
	itoa(p->playerId.port, str+strlen(str), 10);

	logprintf("Packet was modified, sent by id: %d, ip: %s", (unsigned int)p->playerIndex, str);
}

void CNetGame::Packet_RemotePortRefused(Packet* p)
{
	// o samp
	// logprintf("Remote Port Refused for Player: %u\n", p->playerIndex);
}

void CNetGame::Packet_InGameRcon(Packet* p)
{
	if(!this->playerPool) return;

	CPlayer* player = this->playerPool->GetPlayer((_PlayerID)p->playerIndex);

	if(player)
	{
		uint32_t dwCmdLen;
		char  cmd[1024];
		memset(cmd, 0, 1024);
#ifdef _BIG_ENDIAN_SYSTEM
		RakNet::BitStream bs((char*)p->data, p->length, false);
		uint8_t packetId;
		bs.Read(packetId);
		bs.Read(dwCmdLen);
#else
		memcpy(&dwCmdLen, &p->data[1], 4);
#endif

		if(dwCmdLen == 0 || dwCmdLen > 512) 
		{
			static char str[22];

			in_addr in;
			in.s_addr = p->playerId.binaryAddress;

			strcpy(str, inet_ntoa( in ));
			strcat(str, ":");
			itoa(p->playerId.port, str+strlen(str), 10);

			logprintf("Warning: /rcon command exploit from: %d:%s", p->playerIndex, str);
			return;
		}
#ifdef _BIG_ENDIAN_SYSTEM
		bs.Read(cmd, dwCmdLen);
#else
		memcpy(cmd, &p->data[5], dwCmdLen);
#endif
		cmd[dwCmdLen] = 0;

		if(this->playerPool->isPlayerAdmin[(_PlayerID)p->playerIndex])
		{
			if(strlen(cmd) == 0)
			{
				this->SendClientMessage((_PlayerID)p->playerIndex, 0xFFFFFFFF, "You forgot the RCON command!");
				return;
			}
			logprintf("RCON (In-Game): Player [%s] sent command: %s", this->playerPool->getPlayerNick(p->playerIndex), cmd);
			RconUser = (_PlayerID)p->playerIndex;
			__Console->Execute(cmd);
			RconUser = INVALID_PLAYER_ID;
		} 
		else 
		{
			char* szTemp = strtok(cmd, " ");
			if (szTemp)
			{
				if (stricmp(szTemp, "login") == 0)
				{
					szTemp = strtok(NULL, " ");
					if (szTemp)
					{
						in_addr in;
						in.s_addr = p->playerId.binaryAddress;
						char* szIP = inet_ntoa( in );

						if(!strcmp(szTemp, __Console->GetStringVar("rcon_password")))
						{
							if(__NetGame->filterscriptsManager) __NetGame->filterscriptsManager->OnRconLoginAttempt( (unsigned char*)szIP, (unsigned char*)szTemp, 1 );
							if(__NetGame->gamemodeManager) __NetGame->gamemodeManager->OnRconLoginAttempt( (unsigned char*)szIP, (unsigned char*)szTemp, 1 );

							this->playerPool->setPlayerAdmin((_PlayerID)p->playerIndex);						
							logprintf("RCON (In-Game): Player #%d (%s) has logged in.", p->playerIndex, this->playerPool->getPlayerNick((_PlayerID)p->playerIndex));
							this->SendClientMessage((_PlayerID)p->playerIndex, 0xFFFFFFFF, "SERVER: You are logged in as admin.");

						} else 
						{
							if(__NetGame->filterscriptsManager) __NetGame->filterscriptsManager->OnRconLoginAttempt( (unsigned char*)szIP, (unsigned char*)szTemp, 0 );
							if(__NetGame->gamemodeManager) __NetGame->gamemodeManager->OnRconLoginAttempt( (unsigned char*)szIP, (unsigned char*)szTemp, 0 );
							logprintf("RCON (In-Game): Player #%d (%s) <%s> failed login.", p->playerIndex, this->playerPool->getPlayerNick((_PlayerID)p->playerIndex), szTemp, __Console->GetStringVar("rcon_password"));
							this->SendClientMessage((_PlayerID)p->playerIndex, 0xFFFFFFFF,"SERVER: Bad admin password. Repeated attempts will get you banned.");
						}
					}
				}
			}
		}
	}
}
