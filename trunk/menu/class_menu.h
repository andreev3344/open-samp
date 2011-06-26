#ifndef __CMENU_H__
#define __CMENU_H__

#define MAX_MENU_TEXT_SIZE	32
#define MAX_ITEMS			12
#define MAX_COLUMNS			2



class CMenu
{
#pragma pack( 1 )


	BYTE	menuID;														// + 0x0000
	char	title[ MAX_MENU_TEXT_SIZE ];								// + 0x0001
	char	items[ MAX_ITEMS ][ MAX_COLUMNS ][ MAX_MENU_TEXT_SIZE ];	// + 0x0021
	char	headers[MAX_COLUMNS][MAX_MENU_TEXT_SIZE];					// + 0x0321
	BOOL	isInitiedForPlayer[500];									// + 0x0361
	BYTE	unk[12];													// + 0x0B31
	float	posX;														// + 0x0B3D
	float	posY;														// + 0x0B41
	float	column1Width;												// + 0x0B45
	float	column2Width;												// + 0x0B49
	DWORD	columnsNumber;												// + 0x0B4D
	BYTE	itemsCount[ MAX_COLUMNS ];									// + 0x0B51
	
	

public:
	CMenu( );
	~CMenu( );
private:
};



#endif
