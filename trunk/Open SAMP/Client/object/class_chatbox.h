#ifndef __CLASS_CHATBOX_H__
#define __CLASS_CHATBOX_H__

#define CHATBOX_DRAW_MODE_FULL	2
#define CHATBOX_DRAW_MODE_LIGHT	1
#define CHATBOX_DRAW_MODE_NONE	0

#define CHATBOX_MAX_LINES	100
#define CHATBOX_MAX_TEXTLEN	128

#define CHATBOX_MESSAGETYPE_PREFIXED	10
#define CHATBOX_MESSAGETYPE_INFO		11
#define CHATBOX_MESSAGETYPE_DEBUG		12

typedef struct ChatBoxLine_t // size 0xFC
{
#pragma pack( 1 )

	uint32_t	messageType;			// + 0x0000
	uint32_t	textColor;				// + 0x0004
	uint32_t	prefixColor;			// + 0x0008
	uint32_t	addedTime;				// + 0x000C quand le message a été ajouté
	char		messagePrefix[ 28 ];	// + 0x0010
	char		messageText[ 144 ];		// + 0x002C
	uint8_t		unknown[0xFC-0xBC];		// + 0x00BC
} tChatBoxLine;

class CChatBox
{
#pragma pack( 1 )
public:

	CChatBox( uint32_t aChatLinesHeight, void* d3dFont, char* aChatlogFilePath );
	~CChatBox( );

	void ChangeDrawMode( );

	void FilterBadCaracters( char* buffer );

	void log( uint32_t type, char* text, char* prefix );

	void addToChatBuffer( uint32_t type, char* text, char* prefix, uint32_t textColor, uint32_t prefixColor );

	void addInfoMessage( char* text, ... );
	void addDebugMessage( char* text, ... );
	void addClientMessage( uint32_t color, char* text );
	void addChatMessage( char* nick, uint32_t nickColor, char* text );


	void setPageSize( uint32_t size );
	void enableTimestamp( bool enable );

private:

	uint32_t		drawMode;					// + 0x0000
	bool			useTimeStamp;				// + 0x0004
	BOOL			logText;					// + 0x0005
	char			chatlogFilePath[ 261 ];		// + 0x0009
	tChatBoxLine	chatLines[100];				// + 0x010E -> 0x6282
	uint32_t		textColor;					// + 0x637E	
	uint32_t		debugTextColor;				// + 0x6382
	uint32_t		informationTextColor;		// + 0x6386
	uint32_t		chatBoxOffset;				// + 0x638A // from s0beit m0d sa
	uint32_t		pageSize;					// + 0x638E

	void*			unknown6392;				// + 0x6392
	CDXUTDialog*	sampDialog;					// + 0x6396
	void*			unknown639A;				// + 0x639A
	
	CDXUTScrollBar*	scrollBar;					// + 0x639E

	void*			unknown63A2[2];				// + 0x63A2 // from s0beit m0d sa
	uint8_t			unknown63AA[4];				// + 0x63AA // from s0beit m0d sa
	uint32_t		chatLinesHeight;			// + 0x63AE // from s0beit m0d sa
	uint32_t		distanceTextToTimestamp;	// + 0x63B2 // from s0beit m0d sa
//	uint8_t			unknown63B6[0x63DE-0x63B6];	// + 0x63B6
	uint32_t		unknown63B6;				// + 0x63B6
	uint32_t		unknown63BA;				// + 0x63BA
	uint32_t		unknown63BE;				// + 0x63BE
	uint32_t		unknown63C2;				// + 0x63C2
	uint32_t		unknown63C6;				// + 0x63C6
	uint32_t		unknown63CA;				// + 0x63CA
	uint32_t		unknown63CE;				// + 0x63CE
	uint32_t		unknown63D2;				// + 0x63D2
	BOOL			needToBeUpdated;			// + 0x63D6 // IsChatBoxUpdated ? un truc de ce genre pour que le code sache s'il faut update la gui du chat
	uint32_t		unknown63DA;				// + 0x63DA
	uint32_t		fontSizeY;					// + 0x63DE
	uint32_t		fontSizeX;					// + 0x63E2
};



#endif