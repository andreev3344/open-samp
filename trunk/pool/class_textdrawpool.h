#ifndef __TEXTDRAWPOOL_H__
#define __TEXTDRAWPOOL_H__

#define MAX_TEXTDRAW		2048
#define MAX_TEXTDRAW_TEXT	1024



typedef struct TextDraw_t
{
	float letterWidth;		// + 0x00	// ref to 0x047D1E0, c'est pas sûr mais je pense que si
	float letterHeight;		// + 0x04	// ref to 0x047D1E0, idem
	DWORD color;			// + 0x08
	float SizeX;			// + 0x0C
	float SizeY;			// + 0x10
	DWORD boxColor;			// + 0x14
	BYTE textdrawFlags;		// + 0x18 - utilisé pour l'alignement, usebox, setproportional
	BYTE useShadow;			// + 0x19
	BYTE useOutline;		// + 0x1A
	DWORD backgroundColor;	// + 0x1B
	BYTE textFont;			// + 0x1F
	float posX;				// + 0x20
	float posY;				// + 0x24

} tTextDraw;



class CTextDrawPool
{
#pragma pack( 1 )
public:
	BOOL			isCreated[MAX_TEXTDRAW];			// + 0x0000
	tTextDraw*		textDraw[MAX_TEXTDRAW];				// + 0x2000
	char*			text[MAX_TEXTDRAW];					// + 0x4000
	BYTE			textDrawOwner[MAX_TEXTDRAW][500];	// + 0x6000 /* MAX_PLAYERS sûrement pour savoir a qui appartient chaque TextDraw */
	
	int Destroy( int textDrawID ); // Ref: 0x47D880
	WORD Create( float x, float y, char* text ); // Ref: 0x47D0C0

	int setDrawBoxColor( WORD textDrawID, DWORD color ); // Ref: 0x47D2C0
	int setColor( WORD textDrawID, DWORD color );  // Ref: 0x47D280
	int setBackgroundColor( WORD textDrawID, DWORD color ); // Ref: 0x47D300
	int setAlignement( WORD textDrawID, BYTE value ); // Ref: 0x47D230
	int setFont( WORD textDrawID, BYTE font ); // Ref: 0x488840
	int setLetterSize( WORD textDrawID, float letterWidth, float letterHeight ); // Ref: 0x47D1E0
	int setTextSize( WORD textDrawID, float sizeX, float sizeY ); // Ref: 0x47D200
	int setOutline( WORD textDrawID, BYTE outline ); // Ref: 0x4887C0
	int setShadow( WORD textDrawID, BYTE shadow ); // Ref: 0x488780
	int setProportional( WORD textDrawID, BYTE value ); // Ref: 0x488880
	int setUseBox( WORD textDrawID, BYTE value ); // Ref: 0x4886F0
	int setString( WORD textDrawID, char* text ); // Ref: 0x47D740

	
//	Besoin de RakNet
	int showForPlayer( WORD playerid, WORD textDrawID ); //Ref: 0x47D340
	int hideForPlayer( WORD playerid, WORD textDrawID );
	int showForAll( WORD textDrawID );
	int hideForAll( WORD textDrawID ); // Ref: 0x47D670

	

	CTextDrawPool( ); // Ref 0x47D040
	~CTextDrawPool( );

private:

	
};




#endif