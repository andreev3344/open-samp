#include "../main.h"


CChatBox::CChatBox( uint32_t aChatLinesHeight, void* d3dFont, char* aChatlogFilePath )
{
	strcpy( chatlogFilePath, "chatlog.txt" );
	memset( chatLines, 0x00, CHATBOX_MAX_LINES * sizeof( tChatBoxLine ) );

	chatLinesHeight			= aChatLinesHeight;
	unknown63A2[ 0 ]		= d3dFont;

	drawMode				= CHATBOX_DRAW_MODE_FULL;
	useTimeStamp			= false;
	//unknown;
	textColor				= 0xFFFFFFFF;
	debugTextColor			= 0xFF88AA62;
	informationTextColor	= 0xFFA9C4E4;
	pageSize				= 10; // CHATBOX_MAX_LINES / 10

	// d3dFont + 0x38
	// d3dFont->DrawText( 0, "Y", -1, &rect, 0x420, 0xFF000000 );
	// fontSizeY = rect.bottom - rect.top;

	// d3dFont->DrawText( 0, "[19:58:34]", -1, &rect, 0x420, 0xFF000000 );
	// fontSizeX = rect.right - rect.left;

	//this->sub_1009DD12( aChatLinesHeight, unknown639E[ 2 ] );
	//this->sub_1009DD12( aChatLinesHeight, unknown63AA[ 0 ] );

	memset( this->chatlogFilePath, 0, 261 );
	strncpy( this->chatlogFilePath, aChatlogFilePath, 260 );

	FILE* fichier = fopen( this->chatlogFilePath, "w" );
	if( fichier )
	{
		logText = TRUE;
	}

	distanceTextToTimestamp		= 0;
	unknown63B6					= 0;
	unknown63BA					= 0;
	//unknown63CE					= dword_100BB220( v5, v4 );
	unknown63DA					= 1;

	//this->sub_1005D760( );

}

CChatBox::~CChatBox( )
{
}

void CChatBox::enableTimestamp( bool enable )
{
	this->useTimeStamp = enable;
	this->needToBeUpdated = TRUE;
}

void CChatBox::setPageSize( uint32_t size )
{
	if( size >= 10 && size <= 100 )
	{
		this->pageSize = size;
		// sub_1005D870(); // Un truc avec la GUI, mais je connais pas DXUT >.<
		this->needToBeUpdated = TRUE;
	}
}

void CChatBox::ChangeDrawMode( )
{
	this->needToBeUpdated = TRUE;

	if( drawMode == CHATBOX_DRAW_MODE_NONE )
	{
		drawMode = CHATBOX_DRAW_MODE_FULL;
	}
	else if( drawMode == CHATBOX_DRAW_MODE_FULL )
	{
		drawMode = CHATBOX_DRAW_MODE_LIGHT;
	}
	else if( drawMode == CHATBOX_DRAW_MODE_LIGHT )
	{
		drawMode = CHATBOX_DRAW_MODE_NONE;
	}
}

void CChatBox::log( uint32_t type, char* text, char* prefix )
{
	time_t now;
	now = time( 0 );

	if( logText == TRUE )
	{
		FILE* fichier = fopen( chatlogFilePath, "a" );
		if( fichier )
		{
			tm *tm;
			tm = localtime( &now );
			char timeBuffer[ 64 ] = "";
			strftime( timeBuffer, 64, "[%H:%M:%S]", tm );

			if( type == CHATBOX_MESSAGETYPE_PREFIXED )
			{
				fprintf(fichier, "%s <%s> %s\r\n", timeBuffer, prefix, text );
			}
			else if( type > CHATBOX_MESSAGETYPE_PREFIXED && type <= CHATBOX_MESSAGETYPE_DEBUG )
			{
				fprintf(fichier, "%s %s\r\n", timeBuffer, text );
			}
			fclose( fichier );
		}
	}
}


void CChatBox::addClientMessage( uint32_t color, char* text )
{
	if( strlen( text ) <= CHATBOX_MAX_TEXTLEN )
	{
		FilterBadCaracters( text );
		addToChatBuffer( CHATBOX_MESSAGETYPE_INFO, text, 0, (color >> 8) | 0xFF000000, 0 );
	}
}

void CChatBox::addChatMessage( char* nick, uint32_t nickColor, char* text )
{
	FilterBadCaracters( text );
	addToChatBuffer( CHATBOX_MESSAGETYPE_PREFIXED, text, 0, this->textColor, nickColor );
}

void CChatBox::FilterBadCaracters( char* buffer )
{
	char* ptr = (char*)buffer;
	if( ptr )
	{
		do
		{
			if( *ptr > 0 && *ptr < ' ' )
				*ptr = ' ';
			ptr++;
		}
		while( *ptr );
	}
}

void CChatBox::addInfoMessage( char* text, ... )
{
	char buffer[ 512 ] = "";

	va_list listArg;
	va_start( listArg, text );
	vsnprintf( buffer, 512, text, listArg );
	va_end( listArg );

	FilterBadCaracters( buffer );

	addToChatBuffer( CHATBOX_MESSAGETYPE_INFO, buffer, "", this->informationTextColor, 0 );
}

void CChatBox::addDebugMessage( char* text, ... )
{
	char buffer[ 512 ] = "";

	va_list listArg;
	va_start( listArg, text );
	vsnprintf( buffer, 512, text, listArg );
	va_end( listArg );

	FilterBadCaracters( buffer );

	addToChatBuffer( CHATBOX_MESSAGETYPE_DEBUG, buffer, "", this->debugTextColor, 0 );
}

void CChatBox::addToChatBuffer( uint32_t type, char* text, char* prefix, uint32_t textColor, uint32_t prefixColor )
{

	memcpy( chatLines, &chatLines[ 1 ], CHATBOX_MAX_LINES * sizeof( tChatBoxLine ) );

	if( prefix != 0 || strlen( prefix ) <= 0x18 )
	{

		chatLines[ CHATBOX_MAX_LINES - 1 ].messageType	= type;
		chatLines[ CHATBOX_MAX_LINES - 1 ].textColor	= textColor;
		chatLines[ CHATBOX_MAX_LINES - 1 ].prefixColor	= prefixColor;
		chatLines[ CHATBOX_MAX_LINES - 1 ].addedTime	= (uint32_t)time( 0 );

		if( prefix )
		{
			strcpy( chatLines[ CHATBOX_MAX_LINES - 1 ].messagePrefix, prefix );
			strcat( chatLines[ CHATBOX_MAX_LINES - 1 ].messagePrefix, ":" );
		}
		else
		{
			chatLines[ CHATBOX_MAX_LINES - 1 ].messagePrefix[0] = 0;
		}

		log( type, text, prefix );


		if( chatLines[ CHATBOX_MAX_LINES - 1 ].messageType != CHATBOX_MESSAGETYPE_PREFIXED || strlen( text ) <= 72 )
		{
			strncpy( chatLines[ CHATBOX_MAX_LINES - 1 ].messageText, text, sizeof( chatLines[ CHATBOX_MAX_LINES - 1 ].messageText ) );
			chatLines[ CHATBOX_MAX_LINES - 1 ].unknown[0] = 0;
			this->needToBeUpdated = TRUE;
		}
		else
		{
			uint32_t lenght = 72;

			do
			{
				lenght--;
			} while( text[ lenght ] != ' ' && lenght );

			if( 72 - lenght <= 12 )
			{
				strncpy( chatLines[ CHATBOX_MAX_LINES - 1 ].messageText, text, lenght );
				chatLines[ CHATBOX_MAX_LINES - 1 ].messageText[ lenght ] = 0;
				memcpy( chatLines, &chatLines[ 1 ], CHATBOX_MAX_LINES * sizeof( tChatBoxLine ) );
				chatLines[ CHATBOX_MAX_LINES - 1 ].messageType = type;
				chatLines[ CHATBOX_MAX_LINES - 1 ].prefixColor = prefixColor;
				chatLines[ CHATBOX_MAX_LINES - 1 ].textColor = textColor;
				chatLines[ CHATBOX_MAX_LINES - 1 ].messagePrefix[0] = 0;
				this->needToBeUpdated = TRUE;
			}
			else
			{
				strncpy( chatLines[ CHATBOX_MAX_LINES - 1 ].messageText, text, 72 );
				chatLines[ CHATBOX_MAX_LINES - 1 ].messageText[ 72 ] = 0;
				memcpy( chatLines, &chatLines[ 1 ], CHATBOX_MAX_LINES * sizeof( tChatBoxLine ) );
				chatLines[ CHATBOX_MAX_LINES - 1 ].messageType = type;
				chatLines[ CHATBOX_MAX_LINES - 1 ].prefixColor = prefixColor;
				chatLines[ CHATBOX_MAX_LINES - 1 ].textColor = textColor;
				chatLines[ CHATBOX_MAX_LINES - 1 ].messagePrefix[0] = 0;
				this->needToBeUpdated = TRUE;							
			}

		}
	}
}