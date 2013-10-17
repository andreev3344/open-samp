#include "../main.h"




CKeyBinder::CKeyBinder( _PlayerID p_ownerID )
{
	this->ownerID = p_ownerID;
	memset( m_KeyBinds, 0x00, 4 * MAX_KEYBIND );
}
CKeyBinder::~CKeyBinder( )
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


uint32_t CKeyBinder::BindKey( uint8_t keyCode, bool CallOnPush, uint32_t functionIndex, uint8_t fromScript ) // -1 pour le gamemode
{
	uint32_t keyIndex = 0;

	while( keyIndex <= MAX_KEYBIND )
	{
		if( IsSlotUsed( keyIndex ) == false ) break;
		keyIndex ++;
	}

	if( keyIndex >= MAX_KEYBIND ) return -1;

	m_KeyBinds[ keyIndex ] = new stKeyBind;
	printf( "Key 0x%X binded in script %d\n", keyCode, fromScript );
	m_KeyBinds[ keyIndex ]->funcIdx						= ( uint8_t )( functionIndex & 0x1F );
	m_KeyBinds[ keyIndex ]->scriptIdentifier			= fromScript;
	m_KeyBinds[ keyIndex ]->isCalledOnPushed			= ( uint8_t )( CallOnPush ? 1 : 0 );
	m_KeyBinds[ keyIndex ]->keyCode						= keyCode;
	
	RegisterKeyInClient( keyIndex );

	return keyIndex;
}

bool CKeyBinder::UnBindKey( uint32_t KeyIndex )
{
	if( IsSlotUsed( KeyIndex ) == false ) return false;

	if( m_KeyBinds[ KeyIndex ] )
		delete m_KeyBinds[ KeyIndex ];
	m_KeyBinds[ KeyIndex ] = 0;

	UnregisterKeyInClient( KeyIndex );
	return true;
}

void CKeyBinder::RegisterKeyInClient( uint32_t keyIndex )
{
	RakNet::BitStream bStream;

	bStream.Write( ( uint32_t )keyIndex ); // key index
	bStream.Write( ( uint8_t ) m_KeyBinds[ keyIndex ]->keyCode ); // Keycode
	bStream.Write( ( bool ) m_KeyBinds[ keyIndex ]->isCalledOnPushed ); // Call on push 

	__NetGame->PlayerRPC( RPC_RegisterBindKey, &bStream, this->ownerID );
 }

void CKeyBinder::UnregisterKeyInClient( uint32_t keyIndex )
{
	RakNet::BitStream bStream;
	bStream.Write( ( uint32_t )keyIndex ); // key index
	__NetGame->PlayerRPC( RPC_UnregisterBindKey, &bStream, this->ownerID );
}

void CKeyBinder::KeyPressed( uint32_t keyIndex )
{
	if( IsSlotUsed( keyIndex ) == false ) return;

	if( !__NetGame->gamemodeManager && !__NetGame->filterscriptsManager ) return;

	AMX* amx = 0;

	if( m_KeyBinds[ keyIndex ]->scriptIdentifier == GAMEMODE_KEYBIND_SCRIPT )
		amx = &__NetGame->gamemodeManager->gmAMX;
	else
		amx = __NetGame->filterscriptsManager->fsAMX[ m_KeyBinds[ keyIndex ]->scriptIdentifier ];


	cell ret = 0;
	amx_Push( amx, ( cell )( m_KeyBinds[ keyIndex ]->isCalledOnPushed > 0 ) );
	amx_Push( amx, m_KeyBinds[ keyIndex ]->keyCode );
	amx_Push( amx, this->ownerID );
	amx_Exec( amx, &ret, m_KeyBinds[ keyIndex ]->funcIdx );
}

void CKeyBinder::OnFilterScriptUnloaded( uint32_t scriptID )
{
	for( uint32_t i = 0; i < MAX_KEYBIND; i++ )
	{
		if( IsSlotUsed( i ) )
		{
			if( m_KeyBinds[ i ]->scriptIdentifier == scriptID )
				UnBindKey( i );
		}
	}
}

void CKeyBinder::OnGameModeUnloaded( )
{
	for( uint32_t i = 0; i < MAX_KEYBIND; i++ )
	{
		if( IsSlotUsed( i ) )
		{
			if( m_KeyBinds[ i ]->scriptIdentifier == GAMEMODE_KEYBIND_SCRIPT )
				UnBindKey( i );
		}
	}
}