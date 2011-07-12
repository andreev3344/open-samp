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
//cell ( __cdecl* _funcMoveObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_MoveObject;
//cell ( __cdecl* _funcStopObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_StopObject;
//cell ( __cdecl* _funcCreatePlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_CreatePlayerObject;
//cell ( __cdecl* _funcSetPlayerObjectPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerObjectPos;
//cell ( __cdecl* _funcSetPlayerObjectRot )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerObjectRot;
//cell ( __cdecl* _funcGetPlayerObjectPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerObjectPos;
//cell ( __cdecl* _funcGetPlayerObjectRot )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerObjectRot;
//cell ( __cdecl* _funcIsValidPlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsValidPlayerObject;
//cell ( __cdecl* _funcDestroyPlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DestroyPlayerObject;
//cell ( __cdecl* _funcMovePlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_MovePlayerObject;
//cell ( __cdecl* _funcStopPlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_StopPlayerObject;
//cell ( __cdecl* _funcAttachObjectToPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AttachObjectToPlayer;


cell AMX_NATIVE_CALL funcCreateObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCreateObject()" );

	CHECK_PARAMS ( 8 );

	if ( !__ObjectPool )
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

	uint16_t l_uint16_ObjectIndex = __ObjectPool->New ( a_Params[ 1 ], l_VectorPosition, l_VectorRotation, amx_ctof ( a_Params[ 8 ] ) );

	if ( l_uint16_ObjectIndex == -1 )
		return -1;

	CObject* l_Object = NULL;
	if ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT )
	{
		l_Object = __ObjectPool->Get ( l_uint16_ObjectIndex );
	}
	else
	{
		l_Object = NULL;
	}

	if ( l_Object && __NetGame->playerPool > 0 )
	{
		for ( _PlayerID playerid = 0; playerid < MAX_PLAYERS; playerid++ )
		{
			if ( __NetGame->playerPool->isCreated[ playerid ] != 0 )
			{
				l_Object->SpawnForPlayer( playerid );
			}
		}
		return l_uint16_ObjectIndex;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcAttachObjectToVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAttachObjectToVehicle()" );

	CHECK_PARAMS ( 8 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CObject* l_Object = NULL;
	if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_ObjectIndex ) ) )
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

		l_Object->AttachToVehicle ( ( uint16_t )a_Params[ 2 ], l_AttachedOffset, l_AttachedRotation );

		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcSetObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetObjectPos()" );

	CHECK_PARAMS ( 4 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CObject* l_Object = NULL;
	if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_ObjectIndex ) ) )
	{
		tVector* 
			l_VectorPosition = new tVector();
			l_VectorPosition->X = amx_ctof ( a_Params[ 2 ] );
			l_VectorPosition->Y = amx_ctof ( a_Params[ 3 ] );
			l_VectorPosition->Z = amx_ctof ( a_Params[ 4 ] );

		l_Object->SetPosition ( l_VectorPosition );
		
		RakNet::BitStream* l_BitStream = l_Object->ComputeBitStream_SetPosition();
		if ( l_BitStream )
		{
			uint32_t l_RpcSetObjectPosition = 0x00000031;
			CNetGame__RPC_SendToEveryPlayer ( ( uint32_t )__NetGame, &l_RpcSetObjectPosition, l_BitStream, 0xFFFFu, 2 );

			return 1;
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcSetObjectRot ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetObjectRot()" );

	CHECK_PARAMS ( 4 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CObject* l_Object = NULL;
	if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_ObjectIndex ) ) )
	{
		tVector* 
			l_VectorRotation = new tVector();
			l_VectorRotation->X = amx_ctof ( a_Params[ 2 ] );
			l_VectorRotation->Y = amx_ctof ( a_Params[ 3 ] );
			l_VectorRotation->Z = amx_ctof ( a_Params[ 4 ] );

		l_Object->SetRotation ( l_VectorRotation );

		RakNet::BitStream* l_BitStream = l_Object->ComputeBitStream_SetRotation();
		if ( l_BitStream )
		{
			uint32_t l_RpcSetObjectRotation = 0x00000032;
			CNetGame__RPC_SendToEveryPlayer ( ( uint32_t )__NetGame, &l_RpcSetObjectRotation, l_BitStream, 0xFFFFu, 2 );

			return 1;
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcGetObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetObjectPos()" );

	CHECK_PARAMS ( 4 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CObject* l_Object = NULL;
	if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_ObjectIndex ) ) )
	{
		tVector* l_VectorPosition = l_Object->GetPosition();

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

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CObject* l_Object = NULL;
	if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_ObjectIndex ) ) )
	{
		tVector* l_VectorRotation = l_Object->GetRotation();

		cell* cptr;
		amx_GetAddr ( a_AmxInterface, a_Params[ 2 ], &cptr);
		*cptr = amx_ftoc ( l_VectorRotation->X );

		amx_GetAddr ( a_AmxInterface, a_Params[ 3 ], &cptr);
		*cptr = amx_ftoc ( l_VectorRotation->Y );

		amx_GetAddr ( a_AmxInterface, a_Params[ 4 ], &cptr);
		*cptr = amx_ftoc ( l_VectorRotation->Z );

		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL funcIsValidObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsValidObject()" );

	CHECK_PARAMS ( 1 );

	if ( !__ObjectPool )
		return -1;

    return ( ( a_Params[ 1 ] < LIMIT_MAX_OBJECT ) && ( __ObjectPool->Get ( ( uint16_t )a_Params[ 1 ] ) ) );
}

cell AMX_NATIVE_CALL funcDestroyObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDestroyObject()" );

	CHECK_PARAMS ( 1 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CObject* l_Object = NULL;
	if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_ObjectIndex ) ) )
	{
		__ObjectPool->Delete ( l_uint16_ObjectIndex );
		
		RakNet::BitStream 
			l_BitStream;
			l_BitStream.Write ( l_uint16_ObjectIndex );

		uint32_t l_RpcDestroyObject = 0x00000033;
		CNetGame__RPC_SendToEveryPlayer ( ( uint32_t )__NetGame, &l_RpcDestroyObject, &l_BitStream, 0xFFFFu, 2 );

		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcMoveObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcMoveObject()" );

	CHECK_PARAMS ( 5 );

	float l_Return = 0.0f;

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CObject* l_Object = NULL;
	if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_ObjectIndex ) ) )
	{
		tVector* 
			l_VectorPosition = new tVector();
			l_VectorPosition->X = amx_ctof ( a_Params[ 2 ] );
			l_VectorPosition->Y = amx_ctof ( a_Params[ 3 ] );
			l_VectorPosition->Z = amx_ctof ( a_Params[ 4 ] );

		float l_MoveSpeed = amx_ctof ( a_Params[ 5 ] );

		RakNet::BitStream 
			l_BitStream;
			l_BitStream.Write ( l_uint16_ObjectIndex );
			l_BitStream.Write ( l_Object->GetPosition()->X );
			l_BitStream.Write ( l_Object->GetPosition()->Y );
			l_BitStream.Write ( l_Object->GetPosition()->Z );
			l_BitStream.Write ( l_VectorPosition->X );
			l_BitStream.Write ( l_VectorPosition->Y );
			l_BitStream.Write ( l_VectorPosition->Z );
			l_BitStream.Write ( l_MoveSpeed );

		uint32_t l_RpcMoveObject = 0x00000038;
		CNetGame__RPC_SendToEveryPlayer ( ( uint32_t )__NetGame, &l_RpcMoveObject, &l_BitStream, 0xFFFFu, 2 );

		l_Return = l_Object->Move ( l_VectorPosition, l_MoveSpeed );
	}
	return ( uint32_t )( l_Return * 1000.0f );
}

cell AMX_NATIVE_CALL funcStopObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcStopObject()" );

	CHECK_PARAMS ( 1 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CObject* l_Object = NULL;
	if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_ObjectIndex ) ) )
	{
		l_Object->Stop();

		RakNet::BitStream 
			l_BitStream;
			l_BitStream.Write ( l_uint16_ObjectIndex );
			l_BitStream.Write ( l_Object->GetPosition()->X );
			l_BitStream.Write ( l_Object->GetPosition()->Y );
			l_BitStream.Write ( l_Object->GetPosition()->Z );

		uint32_t l_RpcStopObject = 0x00000039;
		CNetGame__RPC_SendToEveryPlayer ( ( uint32_t )__NetGame, &l_RpcStopObject, &l_BitStream, 0xFFFFu, 2 );

		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcCreatePlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCreatePlayerObject()" );

	CHECK_PARAMS ( 9 );

	if ( !__ObjectPool )
		return -1;

	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( l_uint16_PlayerIndex < 500 ) && __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] != 0 )
	{
		tVector* 
			l_VectorPosition = new tVector();
			l_VectorPosition->X = amx_ctof ( a_Params[ 3 ] );
			l_VectorPosition->Y = amx_ctof ( a_Params[ 4 ] );
			l_VectorPosition->Z = amx_ctof ( a_Params[ 5 ] );

		tVector* 
			l_VectorRotation = new tVector();
			l_VectorRotation->X = amx_ctof ( a_Params[ 6 ] );
			l_VectorRotation->Y = amx_ctof ( a_Params[ 7 ] );
			l_VectorRotation->Z = amx_ctof ( a_Params[ 8 ] );

		uint16_t l_ObjectIndex = __ObjectPool->New ( ( uint32_t )a_Params[ 2 ], l_uint16_PlayerIndex, l_VectorPosition, l_VectorRotation, amx_ctof ( a_Params[ 9 ] ) );

		if ( l_ObjectIndex == -1 )
			return -1;

		CObject* l_Object = NULL;
		if ( l_Object = __ObjectPool->Get ( l_uint16_PlayerIndex, l_ObjectIndex ) )
		{
			l_Object->SpawnForPlayer( l_uint16_PlayerIndex );

			return l_ObjectIndex;
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcDestroyPlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDestroyPlayerObject()" );

	CHECK_PARAMS ( 2 );

	if ( ( __NetGame->playerPool > 0 ) && ( a_Params[ 1 ] < 500 ) && ( __NetGame->playerPool->isCreated[ a_Params[ 1 ] ] ) )
	{
		if ( __ObjectPool && ( a_Params[ 2 ] < LIMIT_MAX_OBJECT ) && ( __ObjectPool->Get ( ( uint16_t )a_Params[ 1 ], ( uint16_t )a_Params[ 2 ] ) ) )
		{
			__ObjectPool->Delete ( ( uint16_t )a_Params[ 1 ], ( uint16_t )a_Params[ 2 ] );

			RakNet::BitStream 
				l_BitStream;
				l_BitStream.Write ( ( uint16_t )a_Params[ 2 ] );

			uint32_t l_RpcDestroyObject = 0x00000033;
			CNetGame__RPC_SendToPlayer ( ( uint32_t )__NetGame, &l_RpcDestroyObject, &l_BitStream, ( uint16_t )a_Params[ 1 ], 2 );

			return 1;
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcSetPlayerObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerObjectPos()" );

	CHECK_PARAMS ( 5 );
	
	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];

		CObject* l_Object = NULL;
		if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
		{
			tVector* 
				l_VectorPosition = new tVector();
				l_VectorPosition->X = amx_ctof ( a_Params[ 3 ] );
				l_VectorPosition->Y = amx_ctof ( a_Params[ 4 ] );
				l_VectorPosition->Z = amx_ctof ( a_Params[ 5 ] );

			l_Object->SetPosition ( l_VectorPosition );
		
			RakNet::BitStream* l_BitStream = l_Object->ComputeBitStream_SetPosition();
			if ( l_BitStream )
			{
				uint32_t l_RpcSetObjectPosition = 0x00000031;
				CNetGame__RPC_SendToPlayer ( ( uint32_t )__NetGame, &l_RpcSetObjectPosition, l_BitStream, l_uint16_PlayerIndex, 2 );
				
				return 1;
			}
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcSetPlayerObjectRot ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerObjectRot()" );

	CHECK_PARAMS ( 5 );
	
	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];

		CObject* l_Object = NULL;
		if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
		{
			tVector* 
				l_VectorRotation = new tVector();
				l_VectorRotation->X = amx_ctof ( a_Params[ 3 ] );
				l_VectorRotation->Y = amx_ctof ( a_Params[ 4 ] );
				l_VectorRotation->Z = amx_ctof ( a_Params[ 5 ] );
			
			l_Object->SetPosition ( l_VectorRotation );

			RakNet::BitStream* l_BitStream = l_Object->ComputeBitStream_SetRotation();
			if ( l_BitStream )
			{
				uint32_t l_RpcSetObjectRotation = 0x00000032;
				CNetGame__RPC_SendToPlayer ( ( uint32_t )__NetGame, &l_RpcSetObjectRotation, l_BitStream, l_uint16_PlayerIndex, 2 );
				
				return 1;
			}
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcGetPlayerObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerObjectPos()" );

	CHECK_PARAMS ( 5 );

	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];

		CObject* l_Object = NULL;
		if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
		{
			tVector* l_VectorPosition = l_Object->GetPosition();

			cell* cptr;
			amx_GetAddr ( a_AmxInterface, a_Params[ 3 ], &cptr);
			*cptr = amx_ftoc ( l_VectorPosition->X );

			amx_GetAddr ( a_AmxInterface, a_Params[ 4 ], &cptr);
			*cptr = amx_ftoc ( l_VectorPosition->Y );

			amx_GetAddr ( a_AmxInterface, a_Params[ 5 ], &cptr);
			*cptr = amx_ftoc ( l_VectorPosition->Z );

			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL funcGetPlayerObjectRot ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerObjectRot()" );

	CHECK_PARAMS ( 5 );

	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];

		CObject* l_Object = NULL;
		if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
		{
			tVector* l_VectorRotation = l_Object->GetRotation();

			cell* cptr;
			amx_GetAddr ( a_AmxInterface, a_Params[ 3 ], &cptr);
			*cptr = amx_ftoc ( l_VectorRotation->X );

			amx_GetAddr ( a_AmxInterface, a_Params[ 4 ], &cptr);
			*cptr = amx_ftoc ( l_VectorRotation->Y );

			amx_GetAddr ( a_AmxInterface, a_Params[ 5 ], &cptr);
			*cptr = amx_ftoc ( l_VectorRotation->Z );

			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL funcIsValidPlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsValidPlayerObject()" );

	CHECK_PARAMS ( 2 );

	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];
		if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( __ObjectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL funcMovePlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcMovePlayerObject()" );

	CHECK_PARAMS ( 6 );

	float l_Return = 0.0f;

	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];

		CObject* l_Object = NULL;
		if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
		{
			tVector* 
				l_VectorPosition = new tVector();
				l_VectorPosition->X = amx_ctof ( a_Params[ 3 ] );
				l_VectorPosition->Y = amx_ctof ( a_Params[ 4 ] );
				l_VectorPosition->Z = amx_ctof ( a_Params[ 5 ] );

			float l_MoveSpeed = amx_ctof ( a_Params[ 6 ] );

			RakNet::BitStream 
				l_BitStream;
				l_BitStream.Write ( l_uint16_ObjectIndex );
				l_BitStream.Write ( l_Object->GetPosition()->X );
				l_BitStream.Write ( l_Object->GetPosition()->Y );
				l_BitStream.Write ( l_Object->GetPosition()->Z );
				l_BitStream.Write ( l_VectorPosition->X );
				l_BitStream.Write ( l_VectorPosition->Y );
				l_BitStream.Write ( l_VectorPosition->Z );
				l_BitStream.Write ( l_MoveSpeed );

			uint32_t l_RpcMoveObject = 0x00000038;
			CNetGame__RPC_SendToPlayer ( ( uint32_t )__NetGame, &l_RpcMoveObject, &l_BitStream, l_uint16_PlayerIndex, 2 );

			l_Return = l_Object->Move ( l_VectorPosition, l_MoveSpeed );
		}
	}
	return ( uint32_t )( l_Return * 1000.0f );
}

cell AMX_NATIVE_CALL funcStopPlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcStopPlayerObject()" );

	CHECK_PARAMS ( 2 );

	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];

		CObject* l_Object = NULL;
		if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __ObjectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
		{
			l_Object->Stop();

			RakNet::BitStream 
				l_BitStream;
				l_BitStream.Write ( l_uint16_ObjectIndex );
				l_BitStream.Write ( l_Object->GetPosition()->X );
				l_BitStream.Write ( l_Object->GetPosition()->Y );
				l_BitStream.Write ( l_Object->GetPosition()->Z );

			uint32_t l_RpcStopObject = 0x00000039;
			CNetGame__RPC_SendToPlayer ( ( uint32_t )__NetGame, &l_RpcStopObject, &l_BitStream, l_uint16_PlayerIndex, 2 );

			return 1;
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcAttachObjectToPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAttachObjectToPlayer()" );

	CHECK_PARAMS ( 8 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];
	if ( __ObjectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( __ObjectPool->Get ( l_uint16_ObjectIndex ) ) )
	{
		uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 2 ];
		if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
		{
			RakNet::BitStream 
				l_BitStream;
				l_BitStream.Write ( l_uint16_ObjectIndex );
				l_BitStream.Write ( l_uint16_PlayerIndex );
				l_BitStream.Write ( amx_ctof ( a_Params[ 3 ] ) );
				l_BitStream.Write ( amx_ctof ( a_Params[ 4 ] ) );
				l_BitStream.Write ( amx_ctof ( a_Params[ 5 ] ) );
				l_BitStream.Write ( amx_ctof ( a_Params[ 6 ] ) );
				l_BitStream.Write ( amx_ctof ( a_Params[ 7 ] ) );
				l_BitStream.Write ( amx_ctof ( a_Params[ 8 ] ) );

				
			uint32_t l_RpcAttachObjectToPlayer = 0x00000041;
			CNetGame__RPC_SendToUnknown ( ( uint32_t )__NetGame, &l_RpcAttachObjectToPlayer, &l_BitStream, l_uint16_PlayerIndex, 2 );
			CNetGame__RPC_SendToPlayer ( ( uint32_t )__NetGame, &l_RpcAttachObjectToPlayer, &l_BitStream, l_uint16_PlayerIndex, 2 );
			return 1;
		}
	}
	return -1;
}