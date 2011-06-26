#include "../../main.h"
#include "../../../SDK/amx/amx.h"

#include "../func_amx.h"
#include "func_amx_object.h"

//cell ( __cdecl* _funcCreateObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_CreateObject;
//cell ( __cdecl* _funcAttachObjectToVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AttachObjectToVehicle;
//cell ( __cdecl* _funcSetObjectPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetObjectPos;
//cell ( __cdecl* _funcSetObjectRot )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetObjectRot;
//cell ( __cdecl* _funcGetObjectPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetObjectPos;
//cell ( __cdecl* _funcGetObjectRot )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetObjectRot;
//cell ( __cdecl* _funcIsValidObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsValidObject;
//cell ( __cdecl* _funcDestroyObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DestroyObject;
cell ( __cdecl* _funcMoveObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_MoveObject;
cell ( __cdecl* _funcStopObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_StopObject;
cell ( __cdecl* _funcCreatePlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_CreatePlayerObject;
cell ( __cdecl* _funcSetPlayerObjectPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerObjectPos;
cell ( __cdecl* _funcSetPlayerObjectRot )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerObjectRot;
cell ( __cdecl* _funcGetPlayerObjectPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerObjectPos;
cell ( __cdecl* _funcGetPlayerObjectRot )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerObjectRot;
cell ( __cdecl* _funcIsValidPlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsValidPlayerObject;
cell ( __cdecl* _funcDestroyPlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DestroyPlayerObject;
cell ( __cdecl* _funcMovePlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_MovePlayerObject;
cell ( __cdecl* _funcStopPlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_StopPlayerObject;
cell ( __cdecl* _funcAttachObjectToPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AttachObjectToPlayer;
cell ( __cdecl* _funcAttachPlayerObjectToPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AttachPlayerObjectToPlayer;


cell AMX_NATIVE_CALL funcCreateObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCreateObject()" );

	CHECK_PARAMS ( 8 );

		//// TODO: Remove that Shitty !
	__NetGame = *( uint32_t* )( 0x004F6270 );
	__ObjectPoolEx = ( tObjectPool* )( *( uint32_t* )( __NetGame + 0x14 ) );

	
	if ( !__ObjectPoolEx )
		return -1;

	tVector* 
		l_VectorPosition = new tVector();
		l_VectorPosition->X = amx_ctof ( a_Params[ 2 ] );
		l_VectorPosition->Y = amx_ctof ( a_Params[ 3 ] );
		l_VectorPosition->Z = amx_ctof ( a_Params[ 4 ] );

	tVector* 
		l_VectorRotation = new tVector();
		l_VectorRotation->X = amx_ctof ( a_Params[ 5 ] );
		l_VectorRotation->Y = amx_ctof ( a_Params[ 6 ] );
		l_VectorRotation->Z = amx_ctof ( a_Params[ 7 ] );

	uint16_t l_ObjectIndex = __ObjectPool->New ( a_Params[ 1 ], l_VectorPosition, l_VectorRotation, amx_ctof ( a_Params[ 8 ] ) );
	
	if ( l_ObjectIndex == -1 )
		return -1;

	CObject* l_Object = NULL;
	if ( l_ObjectIndex < 400 )
	{
		l_Object = __ObjectPoolEx->m_pObjects[ l_ObjectIndex ];
	}
	else
	{
		l_Object = NULL;
	}
	
	uint32_t __PlayerPoolEx = *( uint32_t* )( *( uint32_t* )( __NetGame + 0x04 ) );
	if ( l_Object && __PlayerPoolEx )
	{
		for ( uint16_t l_PlayerIndex = 0; l_PlayerIndex < 500; l_PlayerIndex++ )
		{
			if ( ( *( uint32_t* )( *( uint32_t* )( __NetGame + 4 ) + 4 * l_PlayerIndex ) ) )
			{
				l_Object->SpawnForPlayer ( l_PlayerIndex );
			}
		}
		return l_ObjectIndex;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcAttachObjectToVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAttachObjectToVehicle()" );

	CHECK_PARAMS ( 8 );

		//// TODO: Remove that Shitty !
	__NetGame = *( uint32_t* )( 0x004F6270 );
	__ObjectPoolEx = ( tObjectPool* )( *( uint32_t* )( __NetGame + 0x14 ) );

	if ( !__ObjectPoolEx )
		return -1;

	uint16_t l_ObjectIndex = a_Params[ 1 ];
	if ( ( a_Params[ 1 ] < 400 ) && __ObjectPoolEx->m_pObjects[ a_Params[ 1 ] ] )
	{
		tVector* 
			l_AttachedOffset = new tVector();
			l_AttachedOffset->X = amx_ctof ( a_Params[ 3 ] );
			l_AttachedOffset->Y = amx_ctof ( a_Params[ 4 ] );
			l_AttachedOffset->Z = amx_ctof ( a_Params[ 5 ] );

		tVector* 
			l_AttachedRotation = new tVector();
			l_AttachedRotation->X = amx_ctof ( a_Params[ 6 ] );
			l_AttachedRotation->Y = amx_ctof ( a_Params[ 7 ] );
			l_AttachedRotation->Z = amx_ctof ( a_Params[ 8 ] );

		__ObjectPoolEx->m_pObjects[ a_Params[ 1 ] ]->AttachToVehicle ( a_Params[ 2 ], l_AttachedOffset, l_AttachedRotation );

		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcSetObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetObjectPos()" );

	CHECK_PARAMS ( 4 );

		//// TODO: Remove that Shitty !
	__NetGame = *( uint32_t* )( 0x004F6270 );
	__ObjectPoolEx = ( tObjectPool* )( *( uint32_t* )( __NetGame + 0x14 ) );

	if ( !__ObjectPoolEx )
		return -1;

	uint16_t l_ObjectIndex = a_Params[ 1 ];
	if ( ( l_ObjectIndex < 400 ) && __ObjectPoolEx->m_pObjects[ l_ObjectIndex ] )
	{
		tVector* 
			l_VectorPosition = new tVector();
			l_VectorPosition->X = amx_ctof ( a_Params[ 2 ] );
			l_VectorPosition->Y = amx_ctof ( a_Params[ 3 ] );
			l_VectorPosition->Z = amx_ctof ( a_Params[ 4 ] );

		__ObjectPoolEx->m_pObjects[ l_ObjectIndex ]->SetPosition ( l_VectorPosition );

		
		RakNet::BitStream 
			l_BitStream;
			l_BitStream.Write ( l_ObjectIndex );
			l_BitStream.Write ( l_VectorPosition->X );
			l_BitStream.Write ( l_VectorPosition->Y );
			l_BitStream.Write ( l_VectorPosition->Z );

		uint32_t l_RpcSetObjectPosition = 0x00000031;
		CNetGame__RPC_SendToEveryPlayer ( __NetGame, &l_RpcSetObjectPosition, &l_BitStream, 0xFFFFu, 2 );

		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcSetObjectRot ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetObjectRot()" );

	CHECK_PARAMS ( 4 );

		//// TODO: Remove that Shitty !
	__NetGame = *( uint32_t* )( 0x004F6270 );
	__ObjectPoolEx = ( tObjectPool* )( *( uint32_t* )( __NetGame + 0x14 ) );

	if ( !__ObjectPoolEx )
		return -1;

	uint16_t l_ObjectIndex = a_Params[ 1 ];
	if ( ( l_ObjectIndex < 400 ) && __ObjectPoolEx->m_pObjects[ l_ObjectIndex ] )
	{
		tVector* 
			l_VectorRotation = new tVector();
			l_VectorRotation->X = amx_ctof ( a_Params[ 2 ] );
			l_VectorRotation->Y = amx_ctof ( a_Params[ 3 ] );
			l_VectorRotation->Z = amx_ctof ( a_Params[ 4 ] );

		__ObjectPoolEx->m_pObjects[ l_ObjectIndex ]->SetRotation ( l_VectorRotation );

		
		RakNet::BitStream 
			l_BitStream;
			l_BitStream.Write ( l_ObjectIndex );
			l_BitStream.Write ( l_VectorRotation->X );
			l_BitStream.Write ( l_VectorRotation->Y );
			l_BitStream.Write ( l_VectorRotation->Z );

		uint32_t l_RpcSetObjectRotation = 0x00000032;
		CNetGame__RPC_SendToEveryPlayer ( __NetGame, &l_RpcSetObjectRotation, &l_BitStream, 0xFFFFu, 2 );

		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcGetObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetObjectPos()" );

	CHECK_PARAMS ( 4 );

		//// TODO: Remove that Shitty !
	__NetGame = *( uint32_t* )( 0x004F6270 );
	__ObjectPoolEx = ( tObjectPool* )( *( uint32_t* )( __NetGame + 0x14 ) );

	if ( !__ObjectPoolEx )
		return -1;

    if ( ( a_Params[ 1 ] < 400 ) && __ObjectPoolEx->m_pObjects[ a_Params[ 1 ] ] )
    {
		tVector* l_VectorPosition = __ObjectPoolEx->m_pObjects[ a_Params[ 1 ] ]->GetPosition();

		cell* cptr;
		amx_GetAddr ( a_AmxInterface, a_Params[ 2 ], &cptr);
		*cptr = amx_ftoc ( l_VectorPosition->X );

		amx_GetAddr ( a_AmxInterface, a_Params[ 3 ], &cptr);
		*cptr = amx_ftoc ( l_VectorPosition->Y );

		amx_GetAddr ( a_AmxInterface, a_Params[ 4 ], &cptr);
		*cptr = amx_ftoc ( l_VectorPosition->Z );

		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL funcGetObjectRot ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetObjectRot()" );

	CHECK_PARAMS ( 4 );

		//// TODO: Remove that Shitty !
	__NetGame = *( uint32_t* )( 0x004F6270 );
	__ObjectPoolEx = ( tObjectPool* )( *( uint32_t* )( __NetGame + 0x14 ) );

	if ( !__ObjectPoolEx )
		return -1;

    if ( ( a_Params[ 1 ] < 400 ) && __ObjectPoolEx->m_pObjects[ a_Params[ 1 ] ] )
    {
		tVector* l_VectorRotation = __ObjectPoolEx->m_pObjects[ a_Params[ 1 ] ]->GetRotation();

		cell* cptr;
		amx_GetAddr ( a_AmxInterface, a_Params[ 2 ], &cptr);
		*cptr = amx_ftoc(l_VectorRotation->X);

		amx_GetAddr ( a_AmxInterface, a_Params[ 3 ], &cptr);
		*cptr = amx_ftoc(l_VectorRotation->Y);

		amx_GetAddr ( a_AmxInterface, a_Params[ 4 ], &cptr);
		*cptr = amx_ftoc(l_VectorRotation->Z);

		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL funcIsValidObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsValidObject()" );

	CHECK_PARAMS ( 1 );

		//// TODO: Remove that Shitty !
	__NetGame = *( uint32_t* )( 0x004F6270 );
	__ObjectPoolEx = ( tObjectPool* )( *( uint32_t* )( __NetGame + 0x14 ) );

	if ( !__ObjectPoolEx )
		return -1;

    return ( ( a_Params[ 1 ] < 400 ) && ( __ObjectPoolEx->m_pObjects[ a_Params[ 1 ] ] ) );
}

cell AMX_NATIVE_CALL funcDestroyObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDestroyObject()" );

	CHECK_PARAMS ( 1 );

		//// TODO: Remove that Shitty !
	__NetGame = *( uint32_t* )( 0x004F6270 );
	__ObjectPoolEx = ( tObjectPool* )( *( uint32_t* )( __NetGame + 0x14 ) );

	if ( !__ObjectPoolEx )
		return -1;

    if ( ( a_Params[ 1 ] < 400 ) && ( __ObjectPoolEx->m_pObjects[ a_Params[ 1 ] ] ) )
	{
		__ObjectPool->Delete ( a_Params[ 1 ] );

		
		RakNet::BitStream 
			l_BitStream;
			l_BitStream.Write ( ( uint16_t )a_Params[ 1 ] );

		uint32_t l_RpcDestroyObject = 0x00000033;
		CNetGame__RPC_SendToEveryPlayer ( __NetGame, &l_RpcDestroyObject, &l_BitStream, 0xFFFFu, 2 );

		return 1;
	}
	return -1;
}
cell AMX_NATIVE_CALL funcMoveObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcMoveObject()" );
	return _funcMoveObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcStopObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcStopObject()" );
	return _funcStopObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcCreatePlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCreatePlayerObject()" );
	return _funcCreatePlayerObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerObjectPos()" );
	return _funcSetPlayerObjectPos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerObjectRot ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerObjectRot()" );
	return _funcSetPlayerObjectRot ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerObjectPos()" );
	return _funcGetPlayerObjectPos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerObjectRot ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerObjectRot()" );
	return _funcGetPlayerObjectRot ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsValidPlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsValidPlayerObject()" );
	return _funcIsValidPlayerObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcDestroyPlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDestroyPlayerObject()" );
	return _funcDestroyPlayerObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcMovePlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcMovePlayerObject()" );
	return _funcMovePlayerObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcStopPlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcStopPlayerObject()" );
	return _funcStopPlayerObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcAttachObjectToPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAttachObjectToPlayer()" );
	return _funcAttachObjectToPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcAttachPlayerObjectToPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAttachPlayerObjectToPlayer()" );
	return _funcAttachPlayerObjectToPlayer ( a_AmxInterface, a_Params );
}