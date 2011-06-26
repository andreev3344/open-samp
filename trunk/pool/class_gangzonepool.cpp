#include "../main.h"
#include "class_gangzonepool.h"


uint16_t CGangZonePool::New ( float a_float_MinX, float a_float_MinY, float a_float_MaxX, float a_float_MaxY )
{
	logprintf ( "[Call]-> CGangZonePool::New ( %f, %f, %f, %f )", a_float_MinX, a_float_MinY, a_float_MaxX, a_float_MaxY );

	uint16_t l_uint16_ZoneIndex = 0;
	while ( l_uint16_ZoneIndex < LIMIT_MAX_GANGZONE )
	{
		if ( this->m_bool_SlotState[ l_uint16_ZoneIndex ] == FALSE )
			break;

		l_uint16_ZoneIndex++;
	}

	if ( l_uint16_ZoneIndex == LIMIT_MAX_GANGZONE )
		return -1;

	this->m_GangZone[ l_uint16_ZoneIndex ].m_float_MinX = a_float_MinX;
	this->m_GangZone[ l_uint16_ZoneIndex ].m_float_MinY = a_float_MinY;
	this->m_GangZone[ l_uint16_ZoneIndex ].m_float_MaxX = a_float_MaxX;
	this->m_GangZone[ l_uint16_ZoneIndex ].m_float_MaxY = a_float_MaxY;
	this->m_bool_SlotState[ l_uint16_ZoneIndex ] = TRUE;

	return l_uint16_ZoneIndex;
}

void CGangZonePool::Delete ( uint16_t a_uint16_ZoneIndex )
{
	logprintf ( "[Call]-> CGangZonePool::Delete ( %d )", a_uint16_ZoneIndex );



	this->m_bool_SlotState[ a_uint16_ZoneIndex ] = FALSE;

	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );

	uint32_t l_RpcRemoveGangZone = 0x0000004B;
	CNetGame__RPC_SendToEveryPlayer ( (DWORD)__NetGame, &l_RpcRemoveGangZone, &l_BitStream, 0xFFFFu, 2 );
}

void CGangZonePool::ShowForPlayer ( uint16_t a_uint16_PlayerIndex, uint16_t a_uint16_ZoneIndex, uint32_t a_uint32_ZoneColor )
{
	logprintf ( "[Call]-> CGangZonePool::ShowForPlayer ( %d, %d, 0x%0.6X )", a_uint16_PlayerIndex, a_uint16_ZoneIndex, a_uint32_ZoneColor );



	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );
		l_BitStream.Write ( this->m_GangZone[ a_uint16_ZoneIndex ].m_float_MinX );
		l_BitStream.Write ( this->m_GangZone[ a_uint16_ZoneIndex ].m_float_MinY );
		l_BitStream.Write ( this->m_GangZone[ a_uint16_ZoneIndex ].m_float_MaxX );
		l_BitStream.Write ( this->m_GangZone[ a_uint16_ZoneIndex ].m_float_MaxY );

		a_uint32_ZoneColor = RGBA_ABGR ( a_uint32_ZoneColor );
		l_BitStream.Write ( a_uint32_ZoneColor );

	uint32_t l_RpcAddGangZone = 0x0000004A;
	CNetGame__RPC_SendToPlayer ( (DWORD)__NetGame, &l_RpcAddGangZone, &l_BitStream, a_uint16_PlayerIndex, 2 );
}

void CGangZonePool::ShowForAll ( uint16_t a_uint16_ZoneIndex, uint32_t a_uint32_ZoneColor )
{
	logprintf ( "[Call]-> CGangZonePool::ShowForAll ( %d, 0x%X )", a_uint16_ZoneIndex, a_uint32_ZoneColor );

	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );
		l_BitStream.Write ( this->m_GangZone[ a_uint16_ZoneIndex ].m_float_MinX );
		l_BitStream.Write ( this->m_GangZone[ a_uint16_ZoneIndex ].m_float_MinY );
		l_BitStream.Write ( this->m_GangZone[ a_uint16_ZoneIndex ].m_float_MaxX );
		l_BitStream.Write ( this->m_GangZone[ a_uint16_ZoneIndex ].m_float_MaxY );

		a_uint32_ZoneColor = RGBA_ABGR ( a_uint32_ZoneColor );
		l_BitStream.Write ( a_uint32_ZoneColor );

	uint32_t l_RpcAddGangZone = 0x0000004A;
	CNetGame__RPC_SendToEveryPlayer ( (DWORD)__NetGame, &l_RpcAddGangZone, &l_BitStream, 0xFFFFu, 2 );
}

void CGangZonePool::HideForPlayer ( uint16_t a_uint16_PlayerIndex, uint16_t a_uint16_ZoneIndex )
{
	logprintf ( "[Call]-> CGangZonePool::HideForPlayer ( %d, %d )", a_uint16_PlayerIndex, a_uint16_ZoneIndex );



	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );

	uint32_t l_RpcRemoveGangZone = 0x0000004B;
	CNetGame__RPC_SendToPlayer ( (DWORD)__NetGame, &l_RpcRemoveGangZone, &l_BitStream, a_uint16_PlayerIndex, 2 );
}

void CGangZonePool::HideForAll ( uint16_t a_uint16_ZoneIndex )
{
	logprintf ( "[Call]-> CGangZonePool::HideForAll ( %d )", a_uint16_ZoneIndex );


	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );

	uint32_t l_RpcRemoveGangZone = 0x0000004B;
	CNetGame__RPC_SendToEveryPlayer ( (DWORD)__NetGame, &l_RpcRemoveGangZone, &l_BitStream, 0xFFFFu, 2 );
}

void CGangZonePool::FlashForPlayer ( uint16_t a_uint16_PlayerIndex, uint16_t a_uint16_ZoneIndex, uint32_t a_uint32_ZoneColor )
{
	logprintf ( "[Call]-> CGangZonePool::FlashForPlayer ( %d, %d, 0x%X )", a_uint16_PlayerIndex, a_uint16_ZoneIndex, a_uint32_ZoneColor );



	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );

		a_uint32_ZoneColor = RGBA_ABGR ( a_uint32_ZoneColor );
		l_BitStream.Write ( a_uint32_ZoneColor );

	uint32_t l_RpcFlashGangZone = 0x0000004C;
	CNetGame__RPC_SendToPlayer ( (DWORD)__NetGame, &l_RpcFlashGangZone, &l_BitStream, a_uint16_PlayerIndex, 2 );
}

void CGangZonePool::FlashForAll ( uint16_t a_uint16_ZoneIndex, uint32_t a_uint32_ZoneColor )
{
	logprintf ( "[Call]-> CGangZonePool::FlashForAll ( %d, 0x%X )", a_uint16_ZoneIndex, a_uint32_ZoneColor );


	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );

		a_uint32_ZoneColor = RGBA_ABGR ( a_uint32_ZoneColor );
		l_BitStream.Write ( a_uint32_ZoneColor );

	uint32_t l_RpcFlashGangZone = 0x0000004C;
	CNetGame__RPC_SendToEveryPlayer ( (DWORD)__NetGame, &l_RpcFlashGangZone, &l_BitStream, 0xFFFFu, 2 );
}

void CGangZonePool::StopFlashForPlayer ( uint16_t a_uint16_PlayerIndex, uint16_t a_uint16_ZoneIndex )
{
	logprintf ( "[Call]-> CGangZonePool::FlashForPlayer ( %d, %d )", a_uint16_PlayerIndex, a_uint16_ZoneIndex );


	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );

	uint32_t l_RpcStopFlashGangZone = 0x0000004D;
	CNetGame__RPC_SendToPlayer ( (DWORD)__NetGame, &l_RpcStopFlashGangZone, &l_BitStream, a_uint16_PlayerIndex, 2 );
}

void CGangZonePool::StopFlashForAll ( uint16_t a_uint16_ZoneIndex )
{
	logprintf ( "[Call]-> CGangZonePool::StopFlashForAll ( %d )", a_uint16_ZoneIndex );



	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( a_uint16_ZoneIndex );

	uint32_t l_RpcStopFlashGangZone = 0x0000004D;
	CNetGame__RPC_SendToEveryPlayer ( (DWORD)__NetGame, &l_RpcStopFlashGangZone, &l_BitStream, 0xFFFFu, 2 );
}

BOOL CGangZonePool::GetSlotState ( uint16_t a_uint16_ZoneIndex )
{
	if ( a_uint16_ZoneIndex >= LIMIT_MAX_GANGZONE )
		return FALSE;
	return this->m_bool_SlotState[ a_uint16_ZoneIndex ];
}