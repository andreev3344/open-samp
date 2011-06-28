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
[DWORD]	CNETGAME_WIN32 + 0x2C - CurrentGameMode
[DWORD] CNETGAME_WIN32 + 0x30 - Qque chose qui touche au GameMode, mais je peut pas le nommer
[BYTE]  CNETGAME_WIN32 + 0x34 - IsGameModeLoaded
[BYTE]	CNETGAME_WIN32 + 0x35 - useLanMode;
[BYTE]	CNETGAME_WIN32 + 0x36 - Unknown
[CLASS]	CNETGAME_WIN32 + 0x38 - TimerManager
		
[DWORD] CNETGAME_WIN32 + 0x44 - ShowPlayerMarkers
[BYTE]	CNETGAME_WIN32 + 0x48 - bShowNameTags
[BYTE]	CNETGAME_WIN32 + 0x49 - WorldTime
[BYTE] 	CNETGAME_WIN32 + 0x4A - bAllowInteriorWeapons
[BYTE]	CNETGAME_WIN32 + 0x4B - bEnableBonusStuntForAll
[BYTE]	CNETGAME_WIN32 + 0x4C - Weather
[float] CNETGAME_WIN32 + 0x51 - Gravity
[DWORD] CNETGAME_WIN32 + 0x55 - DeathDropAmount
[DWORD] CNETGAME_WIN32 + 0x59 - AllowAdminTeleport
[BYTE] 	CNETGAME_WIN32 + 0x5D - EnableZoneName
[BYTE] 	CNETGAME_WIN32 + 0x5F - bLimiteGlobalChatRadius
[BYTE]  CNETGAME_WIN32 + 0x60 - bUsePlayerPedAnims
[float] CNETGAME_WIN32 + 0x61 - LimitGlobalChatRadius
[float] CNETGAME_WIN32 + 0x65 - NameTagDrawDistance
[BYTE]	CNETGAME_WIN32 + 0x69 - bDisableInteriorEnterExits
[BYTE]	CNETGAME_WIN32 + 0x6A - bDisableNameTagLineOfSight
[BYTE]	CNETGAME_WIN32 + 0x6B - bUseManualVehicleEngineAndLight
[BYTE]	CNETGAME_WIN32 + 0x6C - bLimitPlayerMarkerRadius
[float] CNETGAME_WIN32 + 0x6D - LimitPlayerMarkerRadius





*/

#define MAX_SPAWNS	300



typedef struct SPAWNS_t // size 0x2E
{
	BYTE	Team;
	int		Skin;
	float	posX;
	float	posY;
	float	posZ;
	float	zAngle;
	int		weapons[ 3 ];
	int		ammo[ 3 ];

} tSPAWNS;

class CNetGame // size 0x0365D
{
#pragma pack( 1 )
public:
	void*				rakServerInterface;					// + 0x0000
	CPlayerPool*		playerPool;							// + 0x0004
	void*				vehiclePool;						// + 0x0008
	CText3DLabels*		text3DLabelsPool;					// + 0x000C
	CPickupPool*		pickupPool;							// + 0x0010
	CObjectPool*		objectPool;							// + 0x0014
	void*				gamemodeManager;					// + 0x0018
	void*				filterscriptsManager;				// + 0x001C
	CMenuPool*			menuPool;							// + 0x0020
	CTextDrawPool*		textDrawPool;						// + 0x0024
	CGangZonePool*		gangZonePool;						// + 0x0028
	DWORD				currentGameModeIndex;				// + 0x002C
	DWORD				unknown_GameMode;					// + 0x0030
	bool				isFirstGameModeLoad;				// + 0x0034
	bool				useLanMode;							// + 0x0035
	WORD				unknown001;							// + 0x0036
	void*				scriptTimerManager;					// + 0x0038
	BYTE				unknown002[8];						// + 0x003C
	DWORD				showPlayerMarkers;					// + 0x0044
	bool				showNameTags;						// + 0x0048
	BYTE				worldTime;							// + 0x0049
	bool				allowInteriorWeapons;				// + 0x004A
	bool				enableBonusStuntForAll;				// + 0x004B
	BYTE				weather;							// + 0x004C
	DWORD				gameState;							// + 0x004D
	float				gravity;							// + 0x0051
	DWORD				deathDropAmount;					// + 0x0055
	DWORD				allowAdminTeleport;					// + 0x0059
	bool				enableZoneName;						// + 0x005D
	bool				blimitGlobalChatRadius;				// + 0x005F
	bool				usePlayerPedAnims;					// + 0x0060
	float				limitGlobalChatRadius;				// + 0x0061
	float				nameTagDrawDistance;				// + 0x0065
	bool				disableInteriorEnterExit;			// + 0x0069
	bool				disableNameTagLineOfSight;			// + 0x006A
	bool				useManualVehicleEngineAndLight;		// + 0x006B
	bool				bLimitPlayerMarkerRadius;			// + 0x006C
	float				limitPlayerMarkerRadius;			// + 0x006D
	DWORD				spawnsNumber;						// + 0x0071
	tSPAWNS				spawns[ MAX_SPAWNS];				// + 0x0075




	CNetGame ( ) {};
	~CNetGame( ) {};
private:
	

};



#endif