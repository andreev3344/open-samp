#include "../main.h"



CKeyBinder::CKeyBinder( )
{
	memset( m_KeyBinds, 0x00, 4 * MAX_KEYBIND );

}

CKeyBinder::~CKeyBinder( )
{
	Clear( );
}

void CKeyBinder::Clear( )
{
	for( uint32_t i = 0; i < MAX_KEYBIND; i++ )
	{
		if( m_KeyBinds[ i ] )
			delete m_KeyBinds[ i ];
		m_KeyBinds[ i ] = 0;
	}
}

bool CKeyBinder::IsValidSlot( uint32_t keyIndex )
{
	if( 0 > keyIndex || keyIndex >= MAX_KEYBIND ) return false;
	return true;
}

bool CKeyBinder::IsSlotUsed( uint32_t keyIndex )
{
	if( !IsValidSlot( keyIndex ) ) return true;
	return (bool)( m_KeyBinds[ keyIndex ] == 0 ? false : true );
}

bool CKeyBinder::BindKey( uint32_t keyIndex, uint8_t keyCode, bool CallOnPush )
{
	if( IsSlotUsed( keyIndex ) ) return false;

	m_KeyBinds[ keyIndex ] = new stKeyBind;
	memset( m_KeyBinds[ keyIndex ], 0x00, sizeof( stKeyBind ) );

	m_KeyBinds[ keyIndex ]->callOnPushed = CallOnPush;
	m_KeyBinds[ keyIndex ]->keyCode = keyCode;
	m_KeyBinds[ keyIndex ]->hasBeenPressed = false;

	return true;
}

bool CKeyBinder::UnBindKey( uint32_t KeyIndex )
{
	if( IsSlotUsed( KeyIndex ) == false || IsValidSlot( KeyIndex ) == false ) return false;

	if( m_KeyBinds[ KeyIndex ] ) 
		delete m_KeyBinds[ KeyIndex ];
	m_KeyBinds[ KeyIndex ] = 0;

	return true;
}

void CKeyBinder::KeyProcessing( uint32_t keycode, uint32_t key_flags )
{
	if( __CmdWindow )
		if( __CmdWindow->IsInputBoxVisible() ) return; // Si le gars tape du texte sur la chatbox alors on check pas les touches bindées


	for( uint32_t i = 0; i < MAX_KEYBIND; i++ )
	{
		if( IsSlotUsed( i ) && IsValidSlot( i ) )
		{
			if( m_KeyBinds[ i ]->keyCode == keycode ) // quand une touche a été trouvée, on arrête pas la boucle car elle a pu être enregistré pour plusieurs fonctions
			{
				if( ( ( key_flags & 0x40000000 ) == KEY_STATE_PRESSED ) )
					m_KeyBinds[ i ]->hasBeenPressed = true;

				if( ( ( key_flags & 0x40000000 ) == KEY_STATE_PRESSED ) && m_KeyBinds[ i ]->callOnPushed )
				{
					KeyPressed( i );
				}
				else if( ( ( key_flags & 0x40000000 ) == KEY_STATE_RELEASED ) && m_KeyBinds[ i ]->callOnPushed == false )
				{
					if( m_KeyBinds[ i ]->hasBeenPressed )
					{
						KeyPressed( i );
						m_KeyBinds[ i ]->hasBeenPressed = false;
					}
				}
			}
		}
	}
}

void CKeyBinder::KeyPressed( uint32_t keyIndex )
{
	if( !( IsSlotUsed( keyIndex ) && IsValidSlot( keyIndex ) ) ) return;
	RakNet::BitStream bStream;

	bStream.Write( keyIndex );
	__NetGame->getRakClientInterface()->RPC( RPC_PlayerPressKeyBinded, &bStream, HIGH_PRIORITY, RELIABLE, 2, false );
}