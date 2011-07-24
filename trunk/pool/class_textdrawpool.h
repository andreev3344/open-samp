#ifndef __TEXTDRAWPOOL_H__
#define __TEXTDRAWPOOL_H__

#define MAX_TEXTDRAW		2048
#define MAX_TEXTDRAW_TEXT	1024



typedef struct TextDraw_t
{
	float letterWidth;		// + 0x00	// ref to 0x047D1E0, c'est pas sûr mais je pense que si
	float letterHeight;		// + 0x04	// ref to 0x047D1E0, idem
	uint32_t color;			// + 0x08
	float SizeX;			// + 0x0C
	float SizeY;			// + 0x10
	uint32_t boxColor;			// + 0x14
	uint8_t textdrawFlags;		// + 0x18 - utilisé pour l'alignement, usebox, setproportional
	uint8_t useShadow;			// + 0x19
	uint8_t useOutline;		// + 0x1A
	uint32_t backgroundColor;	// + 0x1B
	uint8_t textFont;			// + 0x1F
	float posX;				// + 0x20
	float posY;				// + 0x24

} tTextDraw;



class CTextDrawPool
{
#pragma pack( 1 )
public:
	BOOL			isCreated[MAX_TEXTDRAW];					// + 0x0000
	tTextDraw*		textDraw[MAX_TEXTDRAW];						// + 0x2000
	char*			text[MAX_TEXTDRAW];							// + 0x4000
	uint8_t			textDrawOwner[MAX_TEXTDRAW][MAX_PLAYERS];	// + 0x6000 /* MAX_PLAYERS sûrement pour savoir a qui appartient chaque TextDraw */
	
	int Destroy( int textDrawID ); // Ref: 0x47D880
	uint16_t Create( float x, float y, char* text ); // Ref: 0x47D0C0

	int setDrawBoxColor( uint16_t textDrawID, uint32_t color ); // Ref: 0x47D2C0
	int setColor( uint16_t textDrawID, uint32_t color );  // Ref: 0x47D280
	int setBackgroundColor( uint16_t textDrawID, uint32_t color ); // Ref: 0x47D300
	int setAlignement( uint16_t textDrawID, uint8_t value ); // Ref: 0x47D230
	int setFont( uint16_t textDrawID, uint8_t font ); // Ref: 0x488840
	int setLetterSize( uint16_t textDrawID, float letterWidth, float letterHeight ); // Ref: 0x47D1E0
	int setTextSize( uint16_t textDrawID, float sizeX, float sizeY ); // Ref: 0x47D200
	int setOutline( uint16_t textDrawID, uint8_t outline ); // Ref: 0x4887C0
	int setShadow( uint16_t textDrawID, uint8_t shadow ); // Ref: 0x488780
	int setProportional( uint16_t textDrawID, uint8_t value ); // Ref: 0x488880
	int setUseBox( uint16_t textDrawID, uint8_t value ); // Ref: 0x4886F0
	int setString( uint16_t textDrawID, char* text ); // Ref: 0x47D740

	
//	Besoin de RakNet
	int showForPlayer( _PlayerID playerid, uint16_t textDrawID ); //Ref: 0x47D340
	int hideForPlayer( _PlayerID playerid, uint16_t textDrawID );
	int showForAll( uint16_t textDrawID );
	int hideForAll( uint16_t textDrawID ); // Ref: 0x47D670

	

	CTextDrawPool( ); // Ref 0x47D040
	~CTextDrawPool( );

private:

	
};




#endif