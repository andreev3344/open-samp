#include "../main.h"




CPlayer::CPlayer( char* nickName, BOOL isNPC ) // euh j'ai fais n'importe quoi ? apparemment oui !
{
	VTBL_textHandler[ 0 ]	= 0;
	VTBL_textHandler[ 4 ]	= 0;
	VTBL_textHandler[ 6 ]	= 15;

	setNickName( nickName, strlen( nickName ) );
	//sub_100098F0( nickName, strlen( nickName ) );

	this->bIsNPC			= isNPC;
	this->ping				= 0;
	this->score				= 0;
	remotePlayerData		= new CPlayerData();

}

CPlayer::~CPlayer( )
{

}


uint32_t CPlayer::getPing( )
{
	return this->ping;
}

uint32_t CPlayer::getScore( )
{
	return this->score;
}

char* CPlayer::getNickName( )
{
	return (char*)this->playerName;
}

uint32_t CPlayer::getNickNameLenght( )
{
	return this->playerNameLen;
}

bool CPlayer::isNPC( )
{
	return ( bool )( this->bIsNPC ? true: false );
}

CPlayerData* CPlayer::getRemoteData( )
{
	return this->remotePlayerData;
}



void CPlayer::setScore( uint32_t value )
{
	this->score = value;
}

void CPlayer::setNickName( char* nick, uint32_t len )
{
/*	if( strlen( nick ) <= 16 )
	{
		strcpy( this->playerName, nick );
		this->playerNameLen = strlen( nick );
	}
*/





}

void CPlayer::setPlayerNPC( BOOL value )
{
	this->bIsNPC = value;
}
