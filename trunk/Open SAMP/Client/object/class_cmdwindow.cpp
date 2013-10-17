#include "../main.h"




CCmdWindow::CCmdWindow( ) // pas utile vu qu'on l'appelera jamais
{
	numberOfCommands = 0;
	defaultCommand = 0;
	for( int i = 0; i < CMDWINDOW_MAX_COMMANDS; i++ )
	{
		commandFunction[ i ] = 0;
		commandName[ i ][ 0 ] = 0;
	}
//	dxutDialogBox = new stInputBox;

}

CCmdWindow::~CCmdWindow( ) // idem inutile
{
	if( dxutDialogBox )
		delete dxutDialogBox;
}

void CCmdWindow::setDefaultCommand( void (*func)( char* ) )
{
	defaultCommand = func;
}

bool CCmdWindow::addCommand( char* command_name, void (*func)( char* ) )
{

	if( numberOfCommands < CMDWINDOW_MAX_COMMANDS )
	{
		if( strlen( command_name ) < CMDWINDOW_MAX_LEN )
		{
			commandFunction[ numberOfCommands ] = func;
			strcpy( commandName[ numberOfCommands ], command_name );
			numberOfCommands++;
			return true;
		}
	}
	return false;
}

void CCmdWindow::pageUp()
{

	if( currentOldTextIndex < totalOfOldText - 1 )
	{
		if( currentOldTextIndex == -1 )
		{
			strncpy( currentBuffer, (char*)dxutDialogBox->GetText(), CHATBOX_MAX_TEXTLEN );
			currentBuffer[ CHATBOX_MAX_TEXTLEN ] = 0;
		}
		currentOldTextIndex++;
		dxutDialogBox->SetText( oldText[ currentOldTextIndex ], false );
		
		// sub_1007BE80( oldText[ currentOldTextIndex ], 0 );
	}

}

void CCmdWindow::pageDown()
{
	currentOldTextIndex--;

	if( currentOldTextIndex < 0 )
	{
		if( currentOldTextIndex== -1 )
			dxutDialogBox->SetText( currentBuffer );
			// sub_1007BE80( currentText, 0 );
		currentOldTextIndex = -1;
	}
	else
	{
		dxutDialogBox->SetText( oldText[ currentOldTextIndex ], false );
		// sub_1007BE80( oldText[ unknown1AF0 ], 0 ):
	}
}

void CCmdWindow::HideInputBox( )
{
	if( this->showInputBox )
	{
		dxutDialogBox->SetVisible( false );
		dxutDialogBox->SetEnabled( false );
	}


	uint32_t pGame	= *( uint32_t*)( sampBaseAddr + Addr_pGame );
	uint32_t function = sampBaseAddr + 0x8E410; // disable GTA key input call process 

	_asm pushad
	_asm mov ecx, pGame
	_asm push 1
	_asm push 0
	_asm call function
	_asm popad

	this->showInputBox = FALSE;
}

CDXUTEditBox* CCmdWindow::GetEditBox( )
{
	return dxutDialogBox;
}

bool CCmdWindow::IsInputBoxVisible()
{
	return ( this->showInputBox == 0 ? false : true );
}