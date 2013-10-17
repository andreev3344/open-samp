#ifndef __CNETGAME_H__
#define __CNETGAME_H__

#define PACKET_STREAM_SYSTEM			0
#define PACKET_STREAM_SYNC				1
#define PACKET_STREAM_RPC_DEFAULT		2
#define PACKET_STREAM_RPC_TEXT			3
#define PACKET_STREAM_RPC_STREAMING		4

#define NETMODE_IDLE_ONFOOT_SENDRATE	80
#define NETMODE_NORMAL_ONFOOT_SENDRATE	30
#define NETMODE_IDLE_INCAR_SENDRATE		80
#define NETMODE_NORMAL_INCAR_SENDRATE	30
#define NETMODE_HEADSYNC_SENDRATE		1000
#define NETMODE_AIM_SENDRATE			100
#define NETMODE_FIRING_SENDRATE			30
#define LANMODE_IDLE_ONFOOT_SENDRATE	20
#define LANMODE_NORMAL_ONFOOT_SENDRATE	15
#define LANMODE_IDLE_INCAR_SENDRATE		30
#define LANMODE_NORMAL_INCAR_SENDRATE	15
#define NETMODE_SEND_MULTIPLIER			2

#define STATS_UPDATE_TICKS				1000

#define PLAYER_MARKERS_MODE_OFF			0
#define PLAYER_MARKERS_MODE_GLOBAL		1
#define PLAYER_MARKERS_MODE_STREAMED	2
#define MARKER_UPDATE_TICKS	2500


#define WEAPON_BRASSKNUCKLE				1
#define WEAPON_GOLFCLUB					2
#define WEAPON_NITESTICK				3
#define WEAPON_KNIFE					4
#define WEAPON_BAT						5
#define WEAPON_SHOVEL					6
#define WEAPON_POOLSTICK				7
#define WEAPON_KATANA					8
#define WEAPON_CHAINSAW					9
#define WEAPON_DILDO					10
#define WEAPON_DILDO2					11
#define WEAPON_VIBRATOR					12
#define WEAPON_VIBRATOR2				13
#define WEAPON_FLOWER					14
#define WEAPON_CANE						15
#define WEAPON_GRENADE					16
#define WEAPON_TEARGAS					17
#define WEAPON_MOLTOV					18
#define WEAPON_COLT45					22
#define WEAPON_SILENCED					23
#define WEAPON_DEAGLE					24
#define WEAPON_SHOTGUN					25
#define WEAPON_SAWEDOFF					26
#define WEAPON_SHOTGSPA					27
#define WEAPON_UZI						28
#define WEAPON_MP5						29
#define WEAPON_AK47						30
#define WEAPON_M4						31
#define WEAPON_TEC9						32
#define WEAPON_RIFLE					33
#define WEAPON_SNIPER					34
#define WEAPON_ROCKETLAUNCHER			35
#define WEAPON_HEATSEEKER				36
#define WEAPON_FLAMETHROWER				37
#define WEAPON_MINIGUN					38
#define WEAPON_SATCHEL					39
#define WEAPON_BOMB						40
#define WEAPON_SPRAYCAN					41
#define WEAPON_FIREEXTINGUISHER			42
#define WEAPON_CAMERA					43
#define WEAPON_PARACHUTE				46
#define WEAPON_VEHICLE					49
#define WEAPON_DROWN					53
#define WEAPON_COLLISION				54

/*
	content of CNetGame.txt


Class CNetGame size 0x0365D


11 class, reversed 4/11


[CLASS]	CNETGAME_WIN32 + 0x00 - RakPeerInterface		
[CLASS]	CNETGAME_WIN32 + 0x04 - PlayerPool size 0x0132B4
[CLASS]	CNETGAME_WIN32 + 0x08 - VehiclePool size 0x5E94
[CLASS]	CNETGAME_WIN32 + 0x0C - Text3DLabels size 0x9400
[CLASS]	CNETGAME_WIN32 + 0x10 - PickupPool size 0x0E004
[CLASS]	CNETGAME_WIN32 + 0x14 - ObjectPool size 0x187CC0
[CLASS]	CNETGAME_WIN32 + 0x18 - GameMode size 0x6E
[CLASS]	CNETGAME_WIN32 + 0x1C - FilterScripts
[CLASS]	CNETGAME_WIN32 + 0x20 - MenuPool size 0x5F4
[CLASS]	CNETGAME_WIN32 + 0x24 - TextDrawPool size 0x100000
[CLASS]	CNETGAME_WIN32 + 0x28 - GangZonePool size 0x5000
[uint32_t]	CNETGAME_WIN32 + 0x2C - CurrentGameMode
[uint32_t] CNETGAME_WIN32 + 0x30 - Qque chose qui touche au GameMode, mais je peut pas le nommer
[uint8_t]  CNETGAME_WIN32 + 0x34 - IsGameModeLoaded
[uint8_t]	CNETGAME_WIN32 + 0x35 - useLanMode;
[uint8_t]	CNETGAME_WIN32 + 0x36 - Unknown
[CLASS]	CNETGAME_WIN32 + 0x38 - TimerManager
		
[uint32_t] CNETGAME_WIN32 + 0x44 - ShowPlayerMarkers
[uint8_t]	CNETGAME_WIN32 + 0x48 - bShowNameTags
[uint8_t]	CNETGAME_WIN32 + 0x49 - WorldTime
[uint8_t] 	CNETGAME_WIN32 + 0x4A - bAllowInteriorWeapons
[uint8_t]	CNETGAME_WIN32 + 0x4B - bEnableBonusStuntForAll
[uint8_t]	CNETGAME_WIN32 + 0x4C - Weather
[float] CNETGAME_WIN32 + 0x51 - Gravity
[uint32_t] CNETGAME_WIN32 + 0x55 - DeathDropAmount
[uint32_t] CNETGAME_WIN32 + 0x59 - AllowAdminTeleport
[uint8_t] 	CNETGAME_WIN32 + 0x5D - EnableZoneName
[uint8_t] 	CNETGAME_WIN32 + 0x5F - bLimiteGlobalChatRadius
[uint8_t]  CNETGAME_WIN32 + 0x60 - bUsePlayerPedAnims
[float] CNETGAME_WIN32 + 0x61 - LimitGlobalChatRadius
[float] CNETGAME_WIN32 + 0x65 - NameTagDrawDistance
[uint8_t]	CNETGAME_WIN32 + 0x69 - bDisableInteriorEnterExits
[uint8_t]	CNETGAME_WIN32 + 0x6A - bDisableNameTagLineOfSight
[uint8_t]	CNETGAME_WIN32 + 0x6B - bUseManualVehicleEngineAndLight
[uint8_t]	CNETGAME_WIN32 + 0x6C - bLimitPlayerMarkerRadius
[float] CNETGAME_WIN32 + 0x6D - LimitPlayerMarkerRadius





*/

#define MAX_SPAWNS	300

class CNetGame // size 0x0365D
{
#pragma pack( 1 )
public:
	RakServerInterface*	rakServerInterface;					// + 0x0000	0
	CPlayerPool*		playerPool;							// + 0x0004 4
	CVehiclePool*		vehiclePool;						// + 0x0008 8
	CText3DLabels*		text3DLabelsPool;					// + 0x000C 12
	CPickupPool*		pickupPool;							// + 0x0010 16
	CDeprecatedObjectPool*		objectPool;							// + 0x0014 20 // DEPRECATED
	CGamemodeManager*	gamemodeManager;					// + 0x0018 24
	CFilterscriptsManager* filterscriptsManager;			// + 0x001C 28
	CMenuPool*			menuPool;							// + 0x0020 32
	CTextDrawPool*		textDrawPool;						// + 0x0024 36
	CDeprecatedGangZonePool*		gangZonePool;						// + 0x0028 40 // DEPRECATED
	uint32_t			currentGameModeIndex;				// + 0x002C 44
	uint32_t			currentGameModeRepeat;				// + 0x0030 48
	BOOL				isFirstGameModeLoad;				// + 0x0034 52
	CScriptTimers*		scriptTimerManager;					// + 0x0038 56
	CScriptHttp*		scriptHttpManager;					// + 0x003C 60
	uint32_t			bLanMode;							// + 0x0040 64
	uint32_t			showPlayerMarkers;					// + 0x0044 68
	bool				showNameTags;						// + 0x0048 72
	uint8_t				worldTime;							// + 0x0049	73
	bool				allowInteriorWeapons;				// + 0x004A	74
	bool				enableBonusStuntForAll;				// + 0x004B	75
	uint8_t				weather;							// + 0x004C	76
	uint32_t			gameState;							// + 0x004D	77
	float				gravity;							// + 0x0051	81
	uint32_t			deathDropAmount;					// + 0x0055	85
	uint32_t			allowAdminTeleport;					// + 0x0059	89
	bool				enableZoneName;						// + 0x005D	93
	uint8_t				byteMod;							// + 0x005E 94
	bool				blimitGlobalChatRadius;				// + 0x005F	95
	bool				usePlayerPedAnims;					// + 0x0060	96
	float				dlimitGlobalChatRadius;				// + 0x0061	97
	float				nameTagDrawDistance;				// + 0x0065	101
	bool				disableInteriorEnterExit;			// + 0x0069	105
	bool				disableNameTagLineOfSight;			// + 0x006A	106
	bool				useManualVehicleEngineAndLight;		// + 0x006B	107
	bool				bLimitPlayerMarkerRadius;			// + 0x006C	108
	float				dlimitPlayerMarkerRadius;			// + 0x006D	109
	uint32_t			spawnsNumber;						// + 0x0071	113
	tSPAWNS				spawns[ MAX_SPAWNS ];				// + 0x0075	117

	#ifndef WIN32
		double			elapsedTime;
	#endif

	uint32_t GetTime( );


	uint32_t			addSpawn( tSPAWNS spawn );
	void				limitGlobalChatRadius( float distance );
	void				limitPlayerMarkerRadius( float distance );
	void				setWeather( uint8_t weather );

	BOOL				setNextGamemodeFile(char* gamemodeStr);
	char*				getNextGamemodeFile();


	void				ShutdownForGameModeRestart();
	void				LoadBanList();
	void				AddBan(char* nick, char* ip_mask, char* reason);
	void				RemoveBan(char* ip_mask);
	void				InitGameForPlayer(_PlayerID playerId);
	void				LoadAllFilterscripts();
	void				Init(BOOL bFirst = false);
	void				ReInitWhenRestarting();
	void				UpdateNetwork();
	void				MasterServerAnnounce(float fElapsedTime);
	void				Process();
	void				ProcessClientJoin(_PlayerID playerID);

	void				KickPlayer(_PlayerID playerId);

	void				SendClientMessage(_PlayerID playerId, uint32_t msgColor, char* msgStr, ...);
	void				SendClientMessageToAll(uint32_t msgColor, char* msgStr, ...);
	void				setWorldTime(uint8_t hour);
	void				setGravity(float fValue);
	const char*			getWeaponName(int weaponID);

	void				GlobalRPC(char *szUniqueID, RakNet::BitStream *bitStream, _PlayerID ExcludePlayer = INVALID_PLAYER_ID, char PacketStream = PACKET_STREAM_RPC_DEFAULT);
	void				AddedPlayersRPC(char *szUniqueID, RakNet::BitStream *bitStream, _PlayerID Player, char PacketStream = PACKET_STREAM_RPC_DEFAULT);
	void				AddedVehicleRPC(char *szUniqueID, RakNet::BitStream *bitStream, _VehicleID Vehicle, _PlayerID ExcludePlayer = INVALID_PLAYER_ID, char PacketStream = PACKET_STREAM_RPC_DEFAULT);
	void				PlayerRPC(char *szUniqueID, RakNet::BitStream *bitStream, _PlayerID Player, char PacketStream = PACKET_STREAM_RPC_DEFAULT);

	void				GlobalPacket(RakNet::BitStream* bStream);
	void				PlayerPacket(RakNet::BitStream* bStream, _PlayerID remotePlayer);
	BOOL				DecimatePacket(float distance);
	void				AddedPlayersPacket(RakNet::BitStream* bStream, _PlayerID remotePlayer);
	void				AddedVehiclePacket(RakNet::BitStream* bStream, _VehicleID vehicleID, _PlayerID remotePlayer);

	// Packet handlers

	void				Packet_PlayerSync(Packet* p);
	void				Packet_VehicleSync(Packet* p);
	void				Packet_PassengerSync(Packet* p);
	void				Packet_AimSync(Packet* p);
	void				Packet_SpectatorSync(Packet* p);
	void				Packet_TrailerSync(Packet* p);
	void				Packet_UnoccupiedSync(Packet* p);

	void				Packet_StatsUpdate(Packet* p);
	void				Packet_WeaponsUpdate(Packet* p);
	
	void				Packet_NewIncomingConnection(Packet* p);
	void				Packet_DisconnectionNotification(Packet* p);
	void				Packet_ConnectionLost(Packet* p);
	void				Packet_ModifiedPacket(Packet* p);
	void				Packet_RemotePortRefused(Packet* p);

	void				Packet_InGameRcon(Packet* p);

	RakServerInterface*	getRakInterface( ) { return rakServerInterface; }
	//

	CNetGame ( );
	~CNetGame( );
private:
	

};



#endif