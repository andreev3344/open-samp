#include "../main.h"
#include "class_objectpool.h"

uint16_t CObjectPool::New ( uint32_t a_uint32_ModelIndex, tVector* a_Position, tVector* a_Rotation, float a_float_DrawDistance )
{
	uint16_t l_uint16_ObjectIndex;

	for ( l_uint16_ObjectIndex = 1; l_uint16_ObjectIndex != LIMIT_MAX_OBJECT; l_uint16_ObjectIndex++ )
	{
		if ( ( this->m_bool_ObjectSlotState[ l_uint16_ObjectIndex ] == FALSE ) && ( this->m_bool_PlayerObject[ l_uint16_ObjectIndex ] == FALSE ) )
			break;
	}

	if ( l_uint16_ObjectIndex == LIMIT_MAX_OBJECT )
		return -1;

	this->m_Object[ l_uint16_ObjectIndex ] = new CObject ( a_uint32_ModelIndex, a_Position, a_Rotation, a_float_DrawDistance );

	if ( this->m_Object[ l_uint16_ObjectIndex ] )
	{
		this->m_Object[ l_uint16_ObjectIndex ]->SetIndex ( l_uint16_ObjectIndex );
		this->m_bool_ObjectSlotState[ l_uint16_ObjectIndex ] = TRUE;
		this->m_bool_PlayerObject[ l_uint16_ObjectIndex ] = FALSE;

		return l_uint16_ObjectIndex;
	}
	return -1;
}

uint16_t CObjectPool::New ( uint32_t a_uint32_ModelIndex, uint16_t a_uint16_PlayerIndex, tVector* a_Position, tVector* a_Rotation, float a_float_DrawDistance )
{
	uint16_t l_uint16_ObjectIndex;

	for ( l_uint16_ObjectIndex = 1; l_uint16_ObjectIndex != LIMIT_MAX_OBJECT; l_uint16_ObjectIndex++ )
	{
		if ( ( this->m_bool_ObjectSlotState[ l_uint16_ObjectIndex ] == FALSE ) && ( this->m_bool_PlayerObjectSlotState[ a_uint16_PlayerIndex ][ l_uint16_ObjectIndex ] == FALSE ) )
			break;
	}

	if ( l_uint16_ObjectIndex == LIMIT_MAX_OBJECT )
		return -1;

	this->m_PlayerObject[ a_uint16_PlayerIndex ][ l_uint16_ObjectIndex ] = new CObject ( a_uint32_ModelIndex, a_Position, a_Rotation, a_float_DrawDistance );

	if ( this->m_PlayerObject[ a_uint16_PlayerIndex ][ l_uint16_ObjectIndex ] )
	{
		this->m_PlayerObject[ a_uint16_PlayerIndex ][ l_uint16_ObjectIndex ]->SetIndex ( l_uint16_ObjectIndex );
		this->m_bool_PlayerObjectSlotState[ a_uint16_PlayerIndex ][ l_uint16_ObjectIndex ] = TRUE;
		this->m_bool_PlayerObject[ l_uint16_ObjectIndex ] = TRUE;

		return l_uint16_ObjectIndex;
	}
	return -1;
}

CObject* CObjectPool::Get ( uint16_t a_uint16_ObjectIndex )
{
	if ( a_uint16_ObjectIndex < LIMIT_MAX_OBJECT )
	{
		return this->m_Object[ a_uint16_ObjectIndex ];
	}
	return NULL;
}

CObject* CObjectPool::Get ( uint16_t a_uint16_PlayerIndex, uint16_t a_uint16_ObjectIndex )
{
	if ( ( a_uint16_PlayerIndex < 500 ) && ( a_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) )
	{
		return this->m_PlayerObject[ a_uint16_PlayerIndex ][ a_uint16_ObjectIndex ];
	}
	return NULL;
}

BOOL CObjectPool::GetSlotState ( uint16_t a_uint16_ObjectIndex )
{
	if ( a_uint16_ObjectIndex < LIMIT_MAX_OBJECT )
	{
		return this->m_bool_ObjectSlotState[ a_uint16_ObjectIndex ];
	}
	return FALSE;
}

BOOL CObjectPool::GetSlotState ( uint16_t a_uint16_PlayerIndex, uint16_t a_uint16_ObjectIndex )
{
	if ( ( a_uint16_PlayerIndex < 400 ) && ( a_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) )
	{
		if ( this->m_bool_PlayerObject[ a_uint16_ObjectIndex ] )
		{
			return this->m_bool_PlayerObjectSlotState[ a_uint16_PlayerIndex ][ a_uint16_ObjectIndex ];
		}
	}
	return FALSE;
}


void CObjectPool::Delete ( uint16_t a_uint16_ObjectIndex )
{
	if ( ( a_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( this->m_Object[ a_uint16_ObjectIndex ] ) )
	{
		this->m_bool_ObjectSlotState[ a_uint16_ObjectIndex ] = FALSE;
		delete this->m_Object[ a_uint16_ObjectIndex ];
		this->m_Object[ a_uint16_ObjectIndex ] = NULL;
	}
}

void CObjectPool::Delete ( uint16_t a_uint16_PlayerIndex, uint16_t a_uint16_ObjectIndex )
{
	if ( ( a_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( a_uint16_PlayerIndex < 500 ) && ( this->m_PlayerObject[ a_uint16_PlayerIndex ][ a_uint16_ObjectIndex ] ) )
	{
		this->m_bool_PlayerObjectSlotState[ a_uint16_PlayerIndex ][ a_uint16_ObjectIndex ] = FALSE;
		delete this->m_PlayerObject[ a_uint16_PlayerIndex ][ a_uint16_ObjectIndex ];
		this->m_PlayerObject[ a_uint16_PlayerIndex ][ a_uint16_ObjectIndex ] = NULL;
	}

	for ( uint32_t l_uint32_Index = 0; l_uint32_Index < 500; l_uint32_Index++ )
	{	
		if ( this->m_bool_PlayerObjectSlotState[ l_uint32_Index ][ a_uint16_ObjectIndex ] )
			return;
	}
	this->m_bool_PlayerObject[ a_uint16_ObjectIndex ] = FALSE;
}