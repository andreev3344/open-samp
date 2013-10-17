#ifndef __CMENU_H__
#define __CMENU_H__

#define MAX_MENU_TEXT_SIZE	32
#define MAX_ITEMS			12
#define MAX_COLUMNS			2

struct t_MenuInteraction
{
	BOOL	Menu;
	BOOL	Row[MAX_ITEMS];
	uint8_t	unknown[12];
};
	
class CMenu	// size 0xB84
{
#pragma pack( 1 )
public:

	uint8_t	menuID;														// + 0x0000
	char	title[ MAX_MENU_TEXT_SIZE ];								// + 0x0001
	char	items[ MAX_ITEMS ][ MAX_COLUMNS ][ MAX_MENU_TEXT_SIZE ];	// + 0x0021
	char	headers[MAX_COLUMNS][MAX_MENU_TEXT_SIZE];					// + 0x0321
	BOOL	isInitiedForPlayer[MAX_PLAYERS];							// + 0x0361
	t_MenuInteraction interaction;										// + 0x0B31
	float	posX;														// + 0x0B71
	float	posY;														// + 0x0B75
	float	column1Width;												// + 0x0B79
	float	column2Width;												// + 0x0B7D
	uint8_t	columnsNumber;												// + 0x0B81
	uint8_t	itemsCount[ MAX_COLUMNS ];									// + 0x0B82
	
	



	uint8_t AddMenuItem( uint8_t column, char* item );
	void SetColumnHeader( uint8_t column, char* title );

	void initForPlayer( _PlayerID playerID );

	int showForPlayer( _PlayerID playerID );
	int hideForPlayer( _PlayerID playerID );

	

	CMenu( char *title, int columns, float x, float y, float col1width, float col2width );
	~CMenu( );
private:
};



#endif
