#ifndef __CNETGAME_H__
#define __CNETGAME_H__

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
	void*				rakServerInterface;					// + 0x0000	0
	CPlayerPool*		playerPool;							// + 0x0004 4
	CVehiclePool*		vehiclePool;						// + 0x0008 8
	CText3DLabels*		text3DLabelsPool;					// + 0x000C 12
	CPickupPool*		pickupPool;							// + 0x0010 16
	CObjectPool*		objectPool;							// + 0x0014 20
	CGamemodeManager*	gamemodeManager;					// + 0x0018 24
	CFilterscriptsManager* filterscriptsManager;			// + 0x001C 28
	CMenuPool*			menuPool;							// + 0x0020 32
	CTextDrawPool*		textDrawPool;						// + 0x0024 36
	CGangZonePool*		gangZonePool;						// + 0x0028 40
	uint32_t				currentGameModeIndex;				// + 0x002C 44
	uint32_t				unknown_GameMode;					// + 0x0030 48
	bool				isFirstGameModeLoad;				// + 0x0034 52
	bool				useLanMode;							// + 0x0035 53
	uint16_t				unknown001;							// + 0x0036 54
	void*				scriptTimerManager;					// + 0x0038 56
	uint8_t				unknown002[8];						// + 0x003C 60
	uint32_t				showPlayerMarkers;					// + 0x0044 68
	bool				showNameTags;						// + 0x0048 72
	uint8_t				worldTime;							// + 0x0049	73
	bool				allowInteriorWeapons;				// + 0x004A	74
	bool				enableBonusStuntForAll;				// + 0x004B	75
	uint8_t				weather;							// + 0x004C	76
	uint32_t				gameState;							// + 0x004D	77
	float				gravity;							// + 0x0051	81
	uint32_t				deathDropAmount;					// + 0x0055	85
	uint32_t				allowAdminTeleport;					// + 0x0059	89
	bool				enableZoneName;						// + 0x005D	93
	uint8_t				fuckingUnknownuint8_t;					// + 0x005E 94
	bool				blimitGlobalChatRadius;				// + 0x005F	95
	bool				usePlayerPedAnims;					// + 0x0060	96
	float				dlimitGlobalChatRadius;				// + 0x0061	97
	float				nameTagDrawDistance;				// + 0x0065	101
	bool				disableInteriorEnterExit;			// + 0x0069	105
	bool				disableNameTagLineOfSight;			// + 0x006A	106
	bool				useManualVehicleEngineAndLight;		// + 0x006B	107
	bool				bLimitPlayerMarkerRadius;			// + 0x006C	108
	float				dlimitPlayerMarkerRadius;			// + 0x006D	109
	uint32_t				spawnsNumber;						// + 0x0071	113
	tSPAWNS				spawns[ MAX_SPAWNS ];				// + 0x0075	117

	uint32_t GetTime( );


	uint32_t			addSpawn( tSPAWNS spawn );
	void				limitGlobalChatRadius( float distance );
	void				limitPlayerMarkerRadius( float distance );
	void				setWeather( uint8_t weather );

	CNetGame ( );
	~CNetGame( );
private:
	

};



#endif