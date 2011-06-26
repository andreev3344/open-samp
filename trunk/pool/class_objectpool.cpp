#include "../main.h"
#include "class_objectpool.h"

tObjectPool* __ObjectPoolEx = NULL;

uint16_t CObjectPool::New ( uint32_t a_uint32_ModelIndex, tVector* a_Position, tVector* a_Rotation, float a_float_DrawDistance )
{
	//// TODO: Remove that Shitty !
	__NetGame = *( uint32_t* )( 0x004F6270 );
	__ObjectPoolEx = ( tObjectPool* )( *( uint32_t* )( __NetGame + 0x14 ) );

	uint16_t l_uint16_ObjectIndex;

	for ( l_uint16_ObjectIndex = 1; l_uint16_ObjectIndex != LIMIT_MAX_OBJECT; l_uint16_ObjectIndex++ )
	{
		if ( ( __ObjectPoolEx->m_bool_ObjectSlotState[ l_uint16_ObjectIndex ] == FALSE ) && ( __ObjectPoolEx->m_bool_PlayerObject[ l_uint16_ObjectIndex ] == FALSE ) )
			break;
	}

	if ( l_uint16_ObjectIndex == LIMIT_MAX_OBJECT )
		return -1;

	__ObjectPoolEx->m_Object[ l_uint16_ObjectIndex ] = new CObject ( a_uint32_ModelIndex, a_Position, a_Rotation, a_float_DrawDistance );

	if ( __ObjectPoolEx->m_Object[ l_uint16_ObjectIndex ] )
	{
		__ObjectPoolEx->m_Object[ l_uint16_ObjectIndex ]->SetIndex ( l_uint16_ObjectIndex );
		__ObjectPoolEx->m_bool_ObjectSlotState[ l_uint16_ObjectIndex ] = TRUE;
		__ObjectPoolEx->m_bool_PlayerObject[ l_uint16_ObjectIndex ] = FALSE;

		return l_uint16_ObjectIndex;
	}
	return -1;
}

void CObjectPool::Delete ( uint16_t a_uint16_ObjectIndex )
{

		//// TODO: Remove that Shitty !
	__NetGame = *( uint32_t* )( 0x004F6270 );
	__ObjectPoolEx = ( tObjectPool* )( *( uint32_t* )( __NetGame + 0x14 ) );

	if ( ( a_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( __ObjectPoolEx->m_Object[ a_uint16_ObjectIndex ] ) )
	{
		__ObjectPoolEx->m_bool_ObjectSlotState[ a_uint16_ObjectIndex ] = FALSE;
		//delete __ObjectPoolEx->m_pObjects[ a_uint16_ObjectIndex ];  ///// CRASH ?!? FUITE MEMOIRE MOUAHAH
		//__ObjectPoolEx->m_pObjects[ a_uint16_ObjectIndex ] = NULL;
	}
}