#ifndef __CNETGAME_H__
#define __CNETGAME_H__

#define FUNC_CNETGAME_SETMAPICON		0x84F0
#define FUNC_CNETGAME_REMOVEMAPICON		0x75E0


typedef struct _tNetGamePools 
{
	void*				m_pGangZonePool;		// + 0x0000
	void*				m_pMenuPool;			// + 0x0004
	CPlayerPool*		m_pPlayerPool;			// + 0x0008
	CVehiclePool*		m_pVehiclePool;			// + 0x000C
	void*				m_pTextDrawPool;		// + 0x0010
	CObjectPool*		m_pObjectPool;			// + 0x0014
	CText3DLabelsPool*	m_p3DTextPool;			// + 0x0018
	void*				m_pPickupPool;			// + 0x001C
 
} tNetGamePools;

typedef struct _tServerSettings
{
#pragma pack( 1 )
        uint8_t		disableInteriorEnterExit;	// 0x0
        uint32_t	spawnsNumber;				// 0x1			
        uint8_t		showPlayerMarkers;			// 0x5
        int			iUnknown1;					// 0x6
        uint8_t		bUnknown_10[3];				// 0xA
        bool		showNameTags;				// 0xD
        uint8_t		worldTime_Hour;				// 0xE
        uint8_t		worldTime_Minute;			// 0xF
        float		worldBounds[4];				// 0x10
        bool		enableZoneName;				// 0x20
        uint8_t		holdTime;					// 0x21
        uint8_t		unknown;					// 0x22
        uint8_t		setTime;					// 0x23
        uint8_t		unknown_2_2;				// 0x24
        bool		usePlayerPedAnims;			// 0x25
        int			deathDropAmount;			// 0x26
        float		nameTagDrawDistance;		// 0x2A
        uint8_t		unk;						// 0x2E
        uint8_t		friendlyFire;				// 0x2F
        uint8_t		weather;					// 0x30
        bool		disableNameTagLineOfSight;	// 0x31
        float		gravity;					// 0x32
} tServerSettings;

class CNetGame // 0.3d
{
#pragma pack( 1 )

private:
	tNetGamePools*			pPools;					// + 0x0000
	uint32_t				svrPort;				// + 0x0004
	char					svrHostOrIp[256+2];		// + 0x0008
	char					svrHostName[256+2];		// + 0x010A
	uint32_t				mapIcons[100];			// + 0x020C
	uint32_t				gameState;				// + 0x039C
	uint32_t				lastConnectAttempt;		// + 0x03A0
	BOOL					bLanMode;				// + 0x03A4
	RakClientInterface*		rakClientInterface;		// + 0x03A8
	tServerSettings*		svrSettings;			// + 0x03AC
	
public:		
	CNetGame();
	~CNetGame();

	tNetGamePools*		getPools();
	void*				getGangZonePool();
	void*				getMenuPool();
	CPlayerPool*		getPlayerPool();
	CVehiclePool*		getVehiclePool();
	void*				getTextDrawPool();
	CObjectPool*		getObjectPool();
	CText3DLabelsPool*	getText3DPool();
	void*				getPickupPool();

	uint32_t			getServerPort();
	char*				getServerHost();
	char*				getServerHostName();

	uint32_t			getGameState();
	BOOL				isLanMode();

	RakClientInterface*	getRakClientInterface();
	tServerSettings*	getServerSettings();

	uint32_t setMapIcon( uint8_t iconID, float posX, float posY, float posZ, uint8_t markerType, uint32_t color, uint32_t style ); // return GTA icon ID
	void removeMapIcon( uint8_t iconID );


	void registerRPCs( );
	void unRegisterRPCs( );
};
#endif