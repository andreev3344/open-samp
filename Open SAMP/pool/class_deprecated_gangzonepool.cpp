#include "../main.h"
#include "class_deprecated_gangzonepool.h"


uint16_t CDeprecatedGangZonePool::New ( float a_float_MinX, float a_float_MinY, float a_float_MaxX, float a_float_MaxY )
{
	uint16_t l_uint16_ZoneIndex = 0;
	while ( l_uint16_ZoneIndex < LIMIT_MAX_GANGZONE )
	{
		if ( this->m_GangZoneList[ l_uint16_ZoneIndex ] == NULL )
			break;

		l_uint16_ZoneIndex++;
	}

	if ( l_uint16_ZoneIndex == LIMIT_MAX_GANGZONE )
		return -1;

	this->m_GangZoneList[ l_uint16_ZoneIndex ] = new tGangZone();
	if ( this->m_GangZoneList[ l_uint16_ZoneIndex ] )
	{
		this->m_GangZoneList[ l_uint16_ZoneIndex ]->m_float_MinX = a_float_MinX;
		this->m_GangZoneList[ l_uint16_ZoneIndex ]->m_float_MinY = a_float_MinY;
		this->m_GangZoneList[ l_uint16_ZoneIndex ]->m_float_MaxX = a_float_MaxX;
		this->m_GangZoneList[ l_uint16_ZoneIndex ]->m_float_MaxY = a_float_MaxY;

		return l_uint16_ZoneIndex;
	}
	return -1;
}

void CDeprecatedGangZonePool::Delete ( uint16_t a_uint16_ZoneIndex )
{
	if ( this->m_GangZoneList[ a_uint16_ZoneIndex ] )
	{
		delete this->m_GangZoneList[ a_uint16_ZoneIndex ];
		this->m_GangZoneList[ a_uint16_ZoneIndex ] = NULL;

		RakNet::BitStream 
			l_BitStream;
			l_BitStream.Write ( a_uint16_ZoneIndex );

		__NetGame->GlobalRPC ( RPC_RemoveGangZone, &l_BitStream, 0xFFFF, 2 );
	}
}

void CDeprecatedGangZonePool::ShowForPlayer ( _PlayerID a_uint16_PlayerIndex, uint16_t a_uint16_ZoneIndex, uint32_t a_uint32_ZoneColor )
{
	if ( this->m_GangZoneList[ a_uint16_ZoneIndex ] )
	{
		RakNet::BitStream 
			l_BitStream;
			l_BitStream.Write ( a_uint16_ZoneIndex );
			l_BitStream.Write ( this->m_GangZoneList[ a_uint16_ZoneIndex ]->m_float_MinX );
			l_BitStream.Write ( this->m_GangZoneList[ a_uint16_ZoneIndex ]->m_float_MinY );
			l_BitStream.Write ( this->m_GangZoneList[ a_uint16_ZoneIndex ]->m_float_MaxX );
			l_BitStream.Write ( this->m_GangZoneList[ a_uint16_ZoneIndex ]->m_float_MaxY );

			a_uint32_ZoneColor = RGBA_ABGR ( a_uint32_ZoneColor );
			l_BitStream.Write ( a_uint32_ZoneColor );

	
		__NetGame->PlayerRPC( RPC_AddGangZone, &l_BitStream, a_uint16_PlayerIndex, 2 );
	}
}

void CDeprecatedGangZonePool::ShowForAll ( uint16_t a_uint16_ZoneIndex, uint32_t a_uint32_ZoneColor )
{
	if ( this->m_GangZoneList[ a_uint16_ZoneIndex ] )
	{
		RakNet::BitStream 
			l_BitStream;
			l_BitStream.Write ( a_uint16_ZoneIndex );
			l_BitStream.Write ( this->m_GangZoneList[ a_uint16_ZoneIndex ]->m_float_MinX );
			l_BitStream.Write ( this->m_GangZoneList[ a_uint16_ZoneIndex ]->m_float_MinY );
			l_BitStream.Write ( this->m_GangZoneList[ a_uint16_ZoneIndex ]->m_float_MaxX );
			l_BitStream.Write ( this->m_GangZoneList[ a_uint16_ZoneIndex ]->m_float_MaxY );

			a_uint32_ZoneColor = RGBA_ABGR ( a_uint32_ZoneColor );
			l_BitStream.Write ( a_uint32_ZoneColor );

		__NetGame->GlobalRPC( RPC_AddGangZone, &l_BitStream, 0xFFFF, 2 );
	}
}

void CDeprecatedGangZonePool::HideForPlayer ( _PlayerID a_uint16_PlayerIndex, uint16_t a_uint16_ZoneIndex )
{
	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );

	__NetGame->PlayerRPC( RPC_RemoveGangZone, &l_BitStream, a_uint16_PlayerIndex, 2 );
}

void CDeprecatedGangZonePool::HideForAll ( uint16_t a_uint16_ZoneIndex )
{
	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );

	__NetGame->GlobalRPC( RPC_RemoveGangZone, &l_BitStream, 0xFFFF, 2 );
}

void CDeprecatedGangZonePool::FlashForPlayer ( _PlayerID a_uint16_PlayerIndex, uint16_t a_uint16_ZoneIndex, uint32_t a_uint32_ZoneColor )
{
	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );

		a_uint32_ZoneColor = RGBA_ABGR ( a_uint32_ZoneColor );
		l_BitStream.Write ( a_uint32_ZoneColor );

	
	__NetGame->PlayerRPC ( RPC_FlashGangZone, &l_BitStream, a_uint16_PlayerIndex, 2 );
}

void CDeprecatedGangZonePool::FlashForAll ( uint16_t a_uint16_ZoneIndex, uint32_t a_uint32_ZoneColor )
{
	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );

		a_uint32_ZoneColor = RGBA_ABGR ( a_uint32_ZoneColor );
		l_BitStream.Write ( a_uint32_ZoneColor );

	__NetGame->GlobalRPC ( RPC_FlashGangZone, &l_BitStream, 0xFFFF, 2 );
}

void CDeprecatedGangZonePool::StopFlashForPlayer ( _PlayerID a_uint16_PlayerIndex, uint16_t a_uint16_ZoneIndex )
{
	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );

	__NetGame->PlayerRPC ( RPC_StopFlashGangZone, &l_BitStream, a_uint16_PlayerIndex, 2 );
}

void CDeprecatedGangZonePool::StopFlashForAll ( uint16_t a_uint16_ZoneIndex )
{
	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );

	__NetGame->GlobalRPC ( RPC_StopFlashGangZone, &l_BitStream, 0xFFFF, 2 );
}

bool CDeprecatedGangZonePool::GetSlotState ( uint16_t a_uint16_ZoneIndex )
{
	if ( a_uint16_ZoneIndex >= LIMIT_MAX_GANGZONE )
		return false;
	return ( this->m_GangZoneList[ a_uint16_ZoneIndex ] ? true : false );
}