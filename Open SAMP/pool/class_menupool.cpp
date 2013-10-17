#include "../main.h"



CMenuPool::CMenuPool( )
{
	memset( menu, 0x00, 4 * MAX_MENUS );
	memset( isCreated, 0x00, 4 * MAX_MENUS );
}

CMenuPool::~CMenuPool( )
{
}

void CMenuPool::resetForPlayer( _PlayerID playerID )
{
	if( 0 > playerID || playerID >= MAX_PLAYERS ) return;

	for( uint8_t menuID = 0; menuID < MAX_MENUS; menuID ++ )
	{
		if(this->menu[menuID]) // fail
			this->menu[menuID]->isInitiedForPlayer[ playerID ] = 0;
	}

}

uint8_t CMenuPool::New( char* title, float x, float y, uint8_t column, float col1width, float col2width )
{
	uint8_t menuID = 1;

	while( menuID < MAX_MENUS )
	{
		if( this->isCreated[menuID] == 0 ) break;
		menuID ++;
	}

	if( menuID >= MAX_MENUS ) return -1;

	this->menu[ menuID ] = new CMenu( title, column, x, y, col1width, col2width );
	this->isCreated[ menuID ] = 1;

	this->menu[ menuID ]->menuID = menuID;

	return menuID;
}

int CMenuPool::Destroy( uint8_t menuID )
{
	if( 0 > menuID || menuID >= MAX_MENUS ) return 0;
	if( this->isCreated[ menuID ] != 0 && this->menu[ menuID ] > 0 )
	{
		delete this->menu[ menuID ];
		this->menu[ menuID ] = 0;
		this->isCreated[ menuID ] = 0;
		return 1;
	}

	return 0;
}