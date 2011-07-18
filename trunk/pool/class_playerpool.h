#ifndef __CPLAYER_POOL_H__
#define __CPLAYER_POOL_H__


class CPlayerPool
{
#pragma pack( 1 )
public:

	BOOL		isCreated[ MAX_PLAYERS ];				// + 0x0000 - 0000
	CPlayer*	player[ MAX_PLAYERS ];					// + 0x07D0	- 2000
	char		nickNames[ MAX_PLAYERS ][ 0x19 ];		// + 0x0FA0 - 4000
	BOOL		isPlayerAdmin[ MAX_PLAYERS ];			// + 0x4074 - 16500
	uint32_t	playersVirtualWorlds[MAX_PLAYERS];		// + 0x4844 - 18500
	BOOL		isPlayerNPC[ MAX_PLAYERS ];				// + 0x5014	- 20500			// Ouais je sais IsPlayerNPC c'est un peu contradictoire comme nom, mais si vous avez mieux ... gardez le pour vous :p
	uint8_t		unk[0xC];								// + 0x57EE - 22510
	uint32_t	playersScore[ MAX_PLAYERS ];			// + 0x57F0 - 22512
	uint32_t	playersMoney[ MAX_PLAYERS ];			// + 0x5FC0 - 24512
	uint32_t	drunkLevel[ MAX_PLAYERS ];				// + 0x6790 - 26512

	int HidePlayerForPlayer( _PlayerID playerID, _PlayerID forPlayerID );
	int	ShowPlayerForPlayer( _PlayerID forPlayerID, _PlayerID playerID  );

	bool GetSlotState( _PlayerID playerID );
	CPlayer* GetPlayer( _PlayerID playerID );

	CPlayerPool( );
	~CPlayerPool( );
private:

};

#endif