#ifndef __CLASS_CMDWINDOW_H__
#define __CLASS_CMDWINDOW_H__


#define CMDWINDOW_MAX_COMMANDS	144
#define CMDWINDOW_MAX_LEN		32


struct stInputBox	// Thanks to s0beit m0d sa
{
#pragma pack( 1 )
	void			*pUnknown;					// + 0x0000
	uint8_t			bIsChatboxOpen;				// + 0x0004
	uint8_t			bIsMouseInChatbox;			// + 0x0005
	uint8_t			bMouseClick_related;		// + 0x0006
	uint8_t			bUnknown;					// + 0x0007
	uint32_t		dwPosChatInput[2];			// + 0x0008
	uint8_t			unknown[263];				// + 0x0010
	int             iCursorPosition;			// + 0x0117
	uint8_t			unknown_2;					// + 0x011B
	int             iMarkedText_startPos;		// + 0x011C
	uint8_t			unknown_3[20];				// + 0x0120
	int             iMouseLeftButton;			// + 0x0134
};




class CCmdWindow
{
#pragma pack( 1 )

public:
	CCmdWindow( );
	~CCmdWindow( );

	bool addCommand( char* command_name,  void (*func)( char* ) );
	void setDefaultCommand( void (*func)( char* ) );

	void HideInputBox( );

	void pageUp();
	void pageDown();

	CDXUTEditBox* GetEditBox( );
	
	bool IsInputBoxVisible();

private:


	IDirect3DDevice9			*d3dDevice;												// + 0x0000
	CDXUTDialog					*dxutDialog;											// + 0x0004
	CDXUTEditBox				*dxutDialogBox;											// + 0x0008
	void (*commandFunction[CMDWINDOW_MAX_COMMANDS])( char* );							// + 0x000C
	char commandName[ CMDWINDOW_MAX_COMMANDS ][ CMDWINDOW_MAX_LEN+1 ];					// + 0x024C
	uint32_t					numberOfCommands;										// + 0x14DC
	BOOL						showInputBox;											// + 0x14E0
	char						inputBuffer[ CHATBOX_MAX_TEXTLEN + 1 ];					// + 0x14E4
	char						oldText[10][ CHATBOX_MAX_TEXTLEN + 1 ];					// + 0x1565
	char						currentBuffer[ CHATBOX_MAX_TEXTLEN + 1 ];				// + 0x1A6F
	uint32_t					currentOldTextIndex;									// + 0x1AF0
	uint32_t					totalOfOldText;											// + 0x1AF4
	void (*defaultCommand)( char* );													// + 0x1AF8

};





#endif