#ifndef __CMENUPOOL_H__
#define __CMENUPOOL_H__


#define MAX_MENUS	128


class CMenuPool
{
#pragma pack( 1 )
public:
	
	CMenu*		menu[ MAX_MENUS ];			//	+ 0x0000
	BOOL		isCreated[ MAX_MENUS ];		//	+ 0x0200
	BOOL		playerMenu[MAX_PLAYERS];	//	+ 0x0400



	uint8_t New( char* title, float x, float y, uint8_t column, float col1width, float col2width );
	int Destroy( uint8_t menuID );

	void resetForPlayer( _PlayerID playerID );


	CMenuPool( );
	~CMenuPool( );
private:
};



#endif