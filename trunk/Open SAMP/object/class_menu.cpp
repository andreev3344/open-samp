#include "../main.h"


CMenu::CMenu( char *title, int columns, float x, float y, float col1width, float col2width )
{
	memset( this->isInitiedForPlayer, 0x00, MAX_PLAYERS * 4 );

	for( int i = 0; i < MAX_ITEMS; i++ )
	{
		strcpy( this->items[0][i], "" );
		strcpy( this->items[1][i], "" );
		this->interaction.Row[ i ] = 1;
	}

	this->interaction.Menu = 1;
	memset( this->headers, 0x00, MAX_COLUMNS * MAX_MENU_TEXT_SIZE );

	if( strlen( title ) >= MAX_MENU_TEXT_SIZE ) title[MAX_MENU_TEXT_SIZE - 1] = 0;
	strcpy( this->title, title );

	this->posX = x;
	this->posY = y;
	this->column1Width = col1width;
	this->column2Width = col2width;
	this->columnsNumber = ( columns == 2 ) + 1;
	this->itemsCount[0] = this->itemsCount[1]
		= 0;

}

CMenu::~CMenu( )
{
}



uint8_t CMenu::AddMenuItem( uint8_t column, char* item )
{

	if( column < 2 )
	{
		if( this->itemsCount[ column ] < MAX_ITEMS ) // .text:004984DD                 cmp     bl, 20h ; Wtf ? c'est 0x0C pas 0x20
		{
			if( strlen( item ) >= MAX_MENU_TEXT_SIZE ) item[ MAX_MENU_TEXT_SIZE - 1 ] = 0;
			memset( this->isInitiedForPlayer, 0x00, MAX_PLAYERS * 4 );

			strcpy( this->items[ this->itemsCount[ column ] ][column], item );
			this->itemsCount[ column ]++;
			return this->itemsCount[ column ];
		}

	}

	return -1;
}

void CMenu::SetColumnHeader( uint8_t column, char* title )
{
	if( column < 2 )
	{
		if( strlen( title ) >= MAX_MENU_TEXT_SIZE ) title[ MAX_MENU_TEXT_SIZE - 1 ] = 0;
		memset( this->isInitiedForPlayer, 0x00, MAX_PLAYERS * 4 );
		strcpy( this->headers[column], title );
		// Normalement ça retourne quelque choses mais bon, pas besoin vu que sur le wiki ils disent que ça ne retourne rien :p http://wiki.sa-mp.com/wiki/SetMenuColumnHeader
	}
}

void CMenu::initForPlayer( _PlayerID playerID ) // ref: 0x498670
{
	int id  = 0;
	if( playerID < MAX_PLAYERS )
	{
		this->isInitiedForPlayer[playerID] = 1;

		RakNet::BitStream bStream;

		bStream.Write( this->menuID );
		bStream.Write( (BOOL)(this->columnsNumber == 2 ) );
		bStream.Write( (char*)this->title, MAX_MENU_TEXT_SIZE );
		bStream.Write( (float)this->posX );
		bStream.Write( (float)this->posY );
		bStream.Write( (float)this->column1Width );
		if( this->columnsNumber == 2 )
		{
			bStream.Write( (float)this->column2Width );
		}
		bStream.Write( (uint32_t)this->interaction.Menu );
		for( int i = 0; i < MAX_ITEMS; i++ )
		{
			bStream.Write( (uint32_t)this->interaction.Row[i] );
		}
		bStream.Write( (char*)this->headers[0], MAX_MENU_TEXT_SIZE );
		bStream.Write( this->itemsCount[0] );

		for( int i = 0; i < this->itemsCount[0]; i++ )
		{
			bStream.Write( (char*)this->items[i][0], MAX_MENU_TEXT_SIZE );
		}
		if( this->columnsNumber == 2 )
		{
			bStream.Write( (char*)this->headers[1], MAX_MENU_TEXT_SIZE );

			bStream.Write( this->itemsCount[1] );
		
			for( int i = 0; i < this->itemsCount[1]; i++ )
			{
				bStream.Write( (char*)this->items[i][1], MAX_MENU_TEXT_SIZE );
			}
		}
		
		__NetGame->PlayerRPC( RPC_Menu_InitForPlayer, &bStream, playerID, 2 );
	}
	
}

int CMenu::showForPlayer( _PlayerID playerID )
{

	if( playerID < MAX_PLAYERS )
	{
		if( this->isInitiedForPlayer[ playerID ] == 0 )
		{
			this->initForPlayer( playerID );
		}
		
		RakNet::BitStream bStream;
		bStream.Write( this->menuID );

		__NetGame->PlayerRPC( RPC_Menu_ShowForPlayer, &bStream, playerID, 2 );

	}
	return -1;
}

int CMenu::hideForPlayer( _PlayerID playerID )
{

	if( playerID < MAX_PLAYERS )
	{
		RakNet::BitStream bStream;
		bStream.Write( this->menuID );
		__NetGame->PlayerRPC( RPC_Menu_HideForPlayer, &bStream, playerID, 2 );
	}



	return -1;
}
