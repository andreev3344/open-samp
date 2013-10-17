#ifndef __CLASS_PLAYER_H__
#define __CLASS_PLAYER_H__

typedef struct sampPed_t
{
#pragma pack( 1 )

	void*		VTBL_sampPed;			// + 0x0000
	CPlayerPed*	gtaPed;					// + 0x0004
	uint32_t	gtaPedID;				// + 0x0008
	BOOL		isUsingCellPhone;		// + 0x000C
	void*		gtaPedPtr2;				// + 0x0010
	uint8_t		padding[285];			// + 0x0014
	uint32_t	drinkingOrSmoking;		// + 0x0131
	uint32_t	objectInHand;			// + 0x0135
	uint32_t	drunkLevel;				// + 0x0139
	BOOL		isUrinating;			// + 0x013D
	uint32_t	gtaUrinateParticleID;	// + 0x0141
	uint8_t		unknown0145[ 5 ];		// + 0x0145
	BOOL		isDancing;				// + 0x014A
	uint32_t	danceStyle;				// + 0x014E
	uint32_t	danceMove;				// + 0x0152

} tsampPed;

class CPlayerData		// size 0x01B5
{

#pragma pack( 1 )

public:
	CPlayerData( )
	{
	}
	~CPlayerData()
	{
	}


	uint8_t		teamID;					// + 0x0000
	uint8_t		state;					// + 0x0001
	_VehicleID	vehicleID;				// + 0x0002
	uint8_t		seatID;					// + 0x0004
	BOOL		isDoingDriveBy;			// + 0x0005
	uint8_t		unknown0009;			// + 0x0009
	uint32_t	tick;					// + 0x000A
	uint32_t	lastStreamedIntick;		// + 0x000E
	uint32_t	unknown0012;			// + 0x0012
	BOOL		showNameTag;			// + 0x0016
	BOOL		hasJetPack;				// + 0x001A
	uint8_t		specialAction;			// + 0x001E
	float		health;					// + 0x001F
	float		armour;					// + 0x0023
	uint32_t	unknown0027;			// + 0x0027
	tsampPed*	sampActor;				// + 0x002B
	void*		sampVehicle;			// + 0x002F
	BOOL		isNPC;					// + 0x0033
	_PlayerID	playerID;				// + 0x0037


};


class CPlayer // size 0x2c
{
#pragma pack( 1 )

public:
	CPlayer( char* nickName, BOOL isNPC );
	~CPlayer( );

	uint32_t getPing( );
	uint32_t getScore( );
	char* getNickName( );
	uint32_t getNickNameLenght( );
	bool isNPC( );
	CPlayerData* getRemoteData( );


	void setScore( uint32_t value );
	void setNickName( char* nick, uint32_t len );
	void setPlayerNPC( BOOL value );

private:
	uint32_t		ping;					// + 0x0000
	uint32_t		score;					// + 0x0004
	uint32_t*		VTBL_textHandler;		// + 0x0008
	char			playerName[ 16 ];		// + 0x000C
	uint32_t		playerNameLen;			// + 0x001C
	uint32_t		scoreboardSomething;	// + 0x0020
	CPlayerData*	remotePlayerData;		// + 0x0024
	BOOL			bIsNPC;					// + 0x0028
};



#endif