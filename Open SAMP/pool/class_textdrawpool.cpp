#include "../main.h"



CTextDrawPool::CTextDrawPool( ) // Ref: 0x47D040
{
	memset( isCreated, 0x00, 4 * MAX_TEXTDRAW );
	memset( textDraw, 0x00, 4 * MAX_TEXTDRAW );
	memset( text, 0x00, 4 * MAX_TEXTDRAW );
	memset( textDrawOwner, 0x00, 1 * 500 * MAX_TEXTDRAW );

}

CTextDrawPool::~CTextDrawPool( )
{
}

int CTextDrawPool::Destroy( int textDrawID ) // Ref: 0x47D880
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;

	delete this->textDraw[textDrawID];
	this->textDraw[textDrawID] = 0;

	delete this->text[textDrawID];
	this->text[textDrawID] = 0;

	this->isCreated[ textDrawID ] = 0;

	return 1;
}

uint16_t CTextDrawPool::Create( float x, float y, char* text ) // Ref: 0x47D0C0
{
	uint16_t id = 0;

	while( id < MAX_TEXT_LABELS )
	{
//		logprintf ( "Checking textdraw %d, is it created: %s\n", id,  this->isCreated[id] ? "Yes" : "No" );
		if( this->isCreated[id] == 0 ) break;
		id ++;
	}
	if( id >= MAX_TEXT_LABELS ) return 0xFFFF;

//	logprintf ( "Creating TextDraw id %d\n", id );

	this->textDraw[id] = new tTextDraw;

	this->text[id] = new char[ MAX_TEXTDRAW_TEXT + 1 ];
	strncpy( this->text[id], text, MAX_TEXTDRAW_TEXT );
	
	this->textDraw[id]->posX = x;
	this->textDraw[id]->posY = y;

	this->textDraw[id]->SizeX =
		this->textDraw[id]->SizeY = 1280.0000f;

	this->textDraw[id]->letterWidth		= 0.47999999f; 
	this->textDraw[id]->letterHeight	= 1.1200000f; 
	this->textDraw[id]->color			= 0xFFE1E1E1;
	this->textDraw[id]->boxColor		= 0x80808080;
	this->textDraw[id]->backgroundColor = 0xFF000000;
	this->textDraw[id]->useShadow		= 0x02;
	this->textDraw[id]->useOutline		= 0x00;
	this->textDraw[id]->textFont		= 0x01;
	this->textDraw[id]->textdrawFlags	= this->textDraw[id]->textdrawFlags & 0xF0 | 0x10;
	this->isCreated[id]					= 1;

	return id;
}

int CTextDrawPool::setColor( uint16_t textDrawID, uint32_t color ) // Ref: 0x47D280
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;

	this->textDraw[textDrawID]->color = (((color << 16) | (uint16_t)(color & 0xFF00)) << 8) | (((color >> 16) | color & 0xFF0000) >> 8);
	return 1;
}

int CTextDrawPool::setBackgroundColor( uint16_t textDrawID, uint32_t color ) // Ref: 0x47D300
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;
	this->textDraw[textDrawID]->backgroundColor = (((color << 16) | (uint16_t)(color & 0xFF00)) << 8) | (((color >> 16) | color & 0xFF0000) >> 8);
	return 1;
}

int CTextDrawPool::setAlignement( uint16_t textDrawID, uint8_t value ) // Ref: 0x47D230
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;

	this->textDraw[textDrawID]->textdrawFlags &= 0xFD;
	this->textDraw[textDrawID]->textdrawFlags &= 0xF7;
	this->textDraw[textDrawID]->textdrawFlags &= 0xFB;

	
	if( value == 1 )
	{
		this->textDraw[textDrawID]->textdrawFlags |= 2;
	}
	else if( value == 2 )
	{
		this->textDraw[textDrawID]->textdrawFlags |= 8;
	}
	else if( value == 3 )
	{
		this->textDraw[textDrawID]->textdrawFlags |= 4;
	}
	return 1;
}

int CTextDrawPool::setFont( uint16_t textDrawID, uint8_t font )
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;
	this->textDraw[textDrawID]->textFont = font;
	return 1;
}

int CTextDrawPool::setLetterSize( uint16_t textDrawID, float letterWidth, float letterHeight )
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;
	this->textDraw[textDrawID]->letterWidth = letterWidth;
	this->textDraw[textDrawID]->letterHeight = letterHeight;
	return 1;
}

int CTextDrawPool::setTextSize( uint16_t textDrawID, float sizeX, float sizeY )
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;
	this->textDraw[textDrawID]->SizeX = sizeX;
	this->textDraw[textDrawID]->SizeY = sizeY;
	return 1;
}

int CTextDrawPool::setOutline( uint16_t textDrawID, uint8_t outline )
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;
	this->textDraw[textDrawID]->useOutline = outline;
	return 1;
}

int CTextDrawPool::setShadow( uint16_t textDrawID, uint8_t shadow )
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;
	this->textDraw[textDrawID]->useShadow = shadow;
	return 1;
}

int CTextDrawPool::setProportional( uint16_t textDrawID, uint8_t value ) // Ref: 0x488880
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;

	value = ( ( value ? 1 : 0 ) );
	this->textDraw[textDrawID]->textdrawFlags ^= this->textDraw[textDrawID]->textdrawFlags ^ 0x10 * value & 0x10;
	return 1;
}

int CTextDrawPool::setUseBox( uint16_t textDrawID, uint8_t value ) // Ref: 0x4886F0
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;
	
	uint8_t Flags = this->textDraw[textDrawID]->textdrawFlags;

	value = ( ( value ? 1 : 0 ) );

	this->textDraw[textDrawID]->textdrawFlags ^= this->textDraw[textDrawID]->textdrawFlags ^ value;

	return 1;
}

int CTextDrawPool::setDrawBoxColor( uint16_t textDrawID, uint32_t color ) // Ref: 0x47D2C0
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;
	this->textDraw[textDrawID]->boxColor = (((color << 16) | (uint16_t)(color & 0xFF00)) << 8) | (((color >> 16) | color & 0xFF0000) >> 8);
	return 1;
}

int CTextDrawPool::setString( uint16_t textDrawID, char* text ) // Ref: 0x47D740
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;

	strncpy( this->text[textDrawID], text, MAX_TEXTDRAW_TEXT );
	
	RakNet::BitStream bStream;
	bStream.Write( (uint16_t)textDrawID );
	bStream.Write( text, MAX_TEXTDRAW_TEXT );

	for( uint16_t i = 0; i < 500; i++ )
	{
		if( this->textDrawOwner[textDrawID][ i ] != 0 )
		{
			__NetGame->PlayerRPC( RPC_TextDraw_SetString, &bStream, i, 2 );
		}

	}

	return 1;
}

int CTextDrawPool::showForPlayer( _PlayerID playerid, uint16_t textDrawID ) //Ref: 0x47D340
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;
	

	if( 0 > playerid || playerid >= MAX_PLAYERS ) return 0;
	if( __NetGame->playerPool->isCreated[ playerid ] == 0 ) return 0;

	uint16_t textLen = (uint16_t)( strlen( this->text[ textDrawID ] ) +1 );

	RakNet::BitStream bStream;
	bStream.Write( (uint16_t)textDrawID );
	bStream.Write( (char*)this->textDraw[ textDrawID ], sizeof( tTextDraw ) );
	bStream.Write( (uint16_t)textLen );
	bStream.Write( this->text[ textDrawID ], textLen );

	this->textDrawOwner[ textDrawID ][ playerid ] = 1;
	__NetGame->PlayerRPC( RPC_ShowTextDraw, &bStream, playerid, 2 );
	return 1;

}

int CTextDrawPool::hideForPlayer( _PlayerID playerid, uint16_t textDrawID )
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;

	if( 0 > playerid || playerid >= MAX_PLAYERS ) return 0;
	if( __NetGame->playerPool->isCreated[ playerid ] == 0 ) return 0;

	if( this->textDrawOwner[textDrawID][playerid] == 0 ) return 0;

	RakNet::BitStream bStream;
	bStream.Write( (uint16_t)textDrawID );
	
	__NetGame->PlayerRPC( RPC_HideTextDraw, &bStream, playerid, 2 );
	this->textDrawOwner[textDrawID][playerid] = 0;

	return 1;
}

int CTextDrawPool::showForAll( uint16_t textDrawID )
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;

	uint16_t textLen = (uint16_t)( strlen( this->text[textDrawID] ) + 1 );

	RakNet::BitStream bStream;
	bStream.Write( (uint16_t)textDrawID );
	bStream.Write( (char*)this->textDraw[ textDrawID ], sizeof( tTextDraw ) );
	bStream.Write( (uint16_t)textLen );
	bStream.Write( this->text[ textDrawID ], textLen );

	for( int i = 0; i < 500; i++ )
	{
		if( __NetGame->playerPool->GetSlotState( i ) )
		{
			this->textDrawOwner[ textDrawID ][ i ] = 1;
			__NetGame->PlayerRPC( RPC_ShowTextDraw, &bStream, i, 2 );
		}
	}


	return 1;
}

int CTextDrawPool::hideForAll( uint16_t textDrawID ) // Ref: 0x47D670
{
	if( 0 > textDrawID || textDrawID >= MAX_TEXTDRAW ) return 0;
	if( this->isCreated[textDrawID ] == 0 ) return 0;

	RakNet::BitStream bStream;
	bStream.Write( (uint16_t)textDrawID );

	for( uint16_t i = 0; i < 500; i++ )
	{
		if( __NetGame->playerPool->GetSlotState( i ) && this->textDrawOwner[textDrawID][i] != 0 )
		{
			__NetGame->PlayerRPC( RPC_HideTextDraw, &bStream, i, 2 );
			this->textDrawOwner[textDrawID][i] = 0;
		}
	}

	return 1;
}

