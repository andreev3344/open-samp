#ifndef __CLASS_PLAYERPOOL_H__
#define __CLASS_PLAYERPOOL_H__


#define FUNC_CPLAYERPOOL_GETPLAYERCOLOR	0x9E640

class CPlayerPool
{
#pragma pack( 1 )
public:

	CPlayerPool( );
	~CPlayerPool( );

	bool New( _PlayerID playerID, char* nickName, BOOL isNPC );
	bool Delete( _PlayerID playerID, uint32_t reason );
	bool GetSlotState( _PlayerID playerID );

	char* GetLocalPlayerName();
	void SetLocalPlayerID( _PlayerID id );
	_PlayerID getLocalPlayerID();

	CLocalPlayer*  GetLocalPlayer( );
	CPlayer* GetPlayer( _PlayerID playerID );
	
	uint32_t getPlayerColor( _PlayerID playerID );

private:

	void*			VTBL_textHandler;				// + 0x0000
	union
	{
		char			localPlayerNickName[ 16 ];	// + 0x0004
		char*			ptrLocalPlayerNickName;		// + 0x0004 pour un pseudo ayant plus de 16 caractères
	};
	uint32_t		scoreBoard_something;			// + 0x0014
	uint32_t		localPlayerNameLen;				// + 0x0018	
	CLocalPlayer*	localPlayer;					// + 0x001C
	BOOL			isCreated[ MAX_PLAYERS ];		// + 0x0020
	CPlayer*		players[ MAX_PLAYERS ];			// + 0x0FC4
	uint32_t		localPlayerScore;				// + 0x1F68
	uint32_t		localPlayerPing;				// + 0x1F6C
	_PlayerID		localPlayerID;					// + 0x1F70
};



#endif