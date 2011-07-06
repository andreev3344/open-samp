#ifndef __CPLAYER_POOL_H__
#define __CPLAYER_POOL_H__


class CPlayerPool
{
#pragma pack( 1 )
public:

	BOOL		isCreated[ MAX_PLAYERS ];	// + 0x0000 - 0000
	CPlayer*	player[ MAX_PLAYERS ];		// + 0x07D0	- 2000

	char		nickNames[ MAX_PLAYERS ][ 0x19 ]; // + 0x0FA0

	uint32_t	playersScore[ MAX_PLAYERS ]; // + 0x57F0
	uint32_t	playersMoney[ MAX_PLAYERS ]; // + 0x5FC0
	uint32_t	drunkLevel[ MAX_PLAYERS ];	// + 0x6790

	CPlayerPool( );
	~CPlayerPool( );
private:

};

#endif