#include "../main.h"



CMenuPool::CMenuPool( )
{
	memset( menu, 0x00, 4 * MAX_MENUS );
	memset( isCreated, 0x00, 4 * MAX_MENUS );
}

CMenuPool::~CMenuPool( )
{
}


BYTE CMenuPool::New( char* title, float x, float y, BYTE column, float col1width, float col2width )
{
	BYTE menuID = 1;

	while( menuID < MAX_MENUS )
	{
		logprintf( "IsMenuCreated[ %d ] = %d", menuID, this->isCreated[menuID]  );
		if( this->isCreated[menuID] == 0 ) break;
		menuID ++;
	}

	if( menuID >= MAX_MENUS ) return -1;

	this->menu[ menuID ] = new CMenu( title, column, x, y, col1width, col2width );
	this->isCreated[ menuID ] = 1;

	this->menu[ menuID ]->menuID = menuID;

	return menuID;
}

int CMenuPool::Destroy( BYTE menuID )
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