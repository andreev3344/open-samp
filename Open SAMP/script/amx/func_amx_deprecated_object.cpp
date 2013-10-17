#include "../../main.h"

#ifndef _STANDALONE
#include "../../../SDK/amx/amx.h"
#endif

#include "../func_amx.h"
#include "func_amx_deprecated_object.h"

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
	if ( bScriptDebug ) logprintf ( "[Call]-> funcCreateObject()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: CreateObject(). Use ObjectCreate() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 8 );
	
	if ( !__NetGame->objectPool )
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

	uint16_t l_uint16_ObjectIndex = __NetGame->objectPool->New ( a_Params[ 1 ], l_VectorPosition, l_VectorRotation, amx_ctof ( a_Params[ 8 ] ) );

	if ( l_uint16_ObjectIndex == -1 )
		return -1;

	CDeprecatedObject* l_Object = NULL;
	if ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT )
	{
		l_Object = __NetGame->objectPool->Get ( l_uint16_ObjectIndex );
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
	if(bScriptDebug) logprintf ( "[Call]-> funcAttachObjectToVehicle()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: AttachObjectToVehicle(). Use Parent/Child Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 8 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CDeprecatedObject* l_Object = NULL;
	if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_ObjectIndex ) ) )
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
	if(bScriptDebug) logprintf ( "[Call]-> funcSetObjectPos()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: SetObjectPos(). Use ElementSetPosition() or ElementSetAbsolutePosition() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 4 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CDeprecatedObject* l_Object = NULL;
	if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_ObjectIndex ) ) )
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
			__NetGame->GlobalRPC( RPC_SetObjectPosition, l_BitStream, 0xFFFFu, 2 );

			return 1;
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcSetObjectRot ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetObjectRot()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: SetObjectRot(). Use ElementSetRotation() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 4 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CDeprecatedObject* l_Object = NULL;
	if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_ObjectIndex ) ) )
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
			__NetGame->GlobalRPC( RPC_SetObjectRotation, l_BitStream, 0xFFFFu, 2 );

			return 1;
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcGetObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetObjectPos()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GetObjectPos(). Use ElementGetPosition() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 4 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CDeprecatedObject* l_Object = NULL;
	if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_ObjectIndex ) ) )
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
	if ( bScriptDebug ) logprintf ( "[Call]-> funcGetObjectRot()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GetObjectRot(). Use ElementGetRotation() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 4 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CDeprecatedObject* l_Object = NULL;
	if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_ObjectIndex ) ) )
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
	if(bScriptDebug) logprintf ( "[Call]-> funcIsValidObject()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: IsValidObject(). Use ObjectIsValid() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 1 );

	if ( !__NetGame->objectPool )
		return -1;

    return ( ( a_Params[ 1 ] < LIMIT_MAX_OBJECT ) && ( __NetGame->objectPool->Get ( ( uint16_t )a_Params[ 1 ] ) ) );
}

cell AMX_NATIVE_CALL funcDestroyObject ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcDestroyObject()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: DestroyObject(). Use ObjectDestroy() or ElementDestroy() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 1 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CDeprecatedObject* l_Object = NULL;
	if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_ObjectIndex ) ) )
	{
		__NetGame->objectPool->Delete ( l_uint16_ObjectIndex );

		
		RakNet::BitStream 
			l_BitStream;
			l_BitStream.Write ( l_uint16_ObjectIndex );

			__NetGame->GlobalRPC( RPC_DestroyObject, &l_BitStream, 0xFFFFu, 2 );

		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcMoveObject ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcMoveObject()" );

	// DEPRECATED FUNCTION
	//logprintf ( "[Script]-> DEPRECATED FUNCTION: MoveObject(). Use ElementMove() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 5 );

	float l_Return = 0.0f;

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CDeprecatedObject* l_Object = NULL;
	if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_ObjectIndex ) ) )
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

		
			__NetGame->GlobalRPC( RPC_MoveObject, &l_BitStream, 0xFFFFu, 2 );

		l_Return = l_Object->Move ( l_VectorPosition, l_MoveSpeed );
	}
	return ( uint32_t )( l_Return * 1000.0f );
}

cell AMX_NATIVE_CALL funcStopObject ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcStopObject()" );

	// DEPRECATED FUNCTION
	//logprintf ( "[Script]-> DEPRECATED FUNCTION: StopObject(). Use ElementStop() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 1 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];

	CDeprecatedObject* l_Object = NULL;
	if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_ObjectIndex ) ) )
	{
		l_Object->Stop();

		RakNet::BitStream 
			l_BitStream;
			l_BitStream.Write ( l_uint16_ObjectIndex );
			l_BitStream.Write ( l_Object->GetPosition()->X );
			l_BitStream.Write ( l_Object->GetPosition()->Y );
			l_BitStream.Write ( l_Object->GetPosition()->Z );

		
			__NetGame->GlobalRPC( RPC_StopObject, &l_BitStream, 0xFFFFu, 2 );

		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcCreatePlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcCreatePlayerObject()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: CreatePlayerObject(). Use ObjectCreate() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 9 );

	if ( !__NetGame->objectPool )
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

		uint16_t l_ObjectIndex = __NetGame->objectPool->New ( ( uint32_t )a_Params[ 2 ], l_uint16_PlayerIndex, l_VectorPosition, l_VectorRotation, amx_ctof ( a_Params[ 9 ] ) );

		if ( l_ObjectIndex == -1 )
			return -1;

		CDeprecatedObject* l_Object = NULL;
		if ( l_Object = __NetGame->objectPool->Get ( l_uint16_PlayerIndex, l_ObjectIndex ) )
		{
			l_Object->SpawnForPlayer( l_uint16_PlayerIndex );

			return l_ObjectIndex;
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcDestroyPlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcDestroyPlayerObject()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: DestroyPlayerObject(). Use ObjectDestroy() or ElementDestroy() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 2 );

	if ( ( __NetGame->playerPool > 0 ) && ( a_Params[ 1 ] < 500 ) && ( __NetGame->playerPool->isCreated[ a_Params[ 1 ] ] ) )
	{
		if ( __NetGame->objectPool && ( a_Params[ 2 ] < LIMIT_MAX_OBJECT ) && ( __NetGame->objectPool->Get ( ( uint16_t )a_Params[ 1 ], ( uint16_t )a_Params[ 2 ] ) ) )
		{
			__NetGame->objectPool->Delete ( ( uint16_t )a_Params[ 1 ], ( uint16_t )a_Params[ 2 ] );

			RakNet::BitStream 
				l_BitStream;
				l_BitStream.Write ( ( uint16_t )a_Params[ 2 ] );

			
			__NetGame->PlayerRPC( RPC_DestroyObject, &l_BitStream, ( uint16_t )a_Params[ 1 ], 2 );

			return 1;
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcSetPlayerObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerObjectPos()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: SetPlayerObjectPos(). Use ElementSetPosition() or ElementSetAbsolutePosition() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 5 );
	
	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];

		CDeprecatedObject* l_Object = NULL;
		if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
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
				
				__NetGame->PlayerRPC( RPC_SetObjectPosition, l_BitStream, l_uint16_PlayerIndex, 2 );
				
				return 1;
			}
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcSetPlayerObjectRot ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcSetPlayerObjectRot()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: SetPlayerObjectRot(). Use ElementSetRotation() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 5 );
	
	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];

		CDeprecatedObject* l_Object = NULL;
		if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
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
				
				__NetGame->PlayerRPC( RPC_SetObjectRotation, l_BitStream, l_uint16_PlayerIndex, 2 );
				
				return 1;
			}
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcGetPlayerObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerObjectPos()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GetPlayerObjectPos(). Use ElementGetPosition() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 5 );

	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];

		CDeprecatedObject* l_Object = NULL;
		if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
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
	if(bScriptDebug) logprintf ( "[Call]-> funcGetPlayerObjectRot()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GetPlayerObjectRot(). Use ElementGetRotation() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 5 );

	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];

		CDeprecatedObject* l_Object = NULL;
		if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
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
	if(bScriptDebug) logprintf ( "[Call]-> funcIsValidPlayerObject()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: IsValidPlayerObject(). Use ObjectIsValid() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 2 );

	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];
		if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( __NetGame->objectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL funcMovePlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcMovePlayerObject()" );

	// DEPRECATED FUNCTION
	//logprintf ( "[Script]-> DEPRECATED FUNCTION: MovePlayerObject(). Use ElementMove() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 6 );

	float l_Return = 0.0f;

	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];

		CDeprecatedObject* l_Object = NULL;
		if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
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

			__NetGame->PlayerRPC( RPC_MoveObject, &l_BitStream, l_uint16_PlayerIndex, 2 );

			l_Return = l_Object->Move ( l_VectorPosition, l_MoveSpeed );
		}
	}
	return ( uint32_t )( l_Return * 1000.0f );
}

cell AMX_NATIVE_CALL funcStopPlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcStopPlayerObject()" );

	// DEPRECATED FUNCTION
	//logprintf ( "[Script]-> DEPRECATED FUNCTION: StopPlayerObject(). Use ElementStop() Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 2 );

	uint16_t l_uint16_PlayerIndex = ( uint16_t )a_Params[ 1 ];
	if ( ( __NetGame->playerPool > 0 ) && ( l_uint16_PlayerIndex < 500 ) && ( __NetGame->playerPool->isCreated[ l_uint16_PlayerIndex ] ) )
	{
		uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 2 ];

		CDeprecatedObject* l_Object = NULL;
		if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( l_Object = __NetGame->objectPool->Get ( l_uint16_PlayerIndex, l_uint16_ObjectIndex ) ) )
		{
			l_Object->Stop();

			RakNet::BitStream 
				l_BitStream;
				l_BitStream.Write ( l_uint16_ObjectIndex );
				l_BitStream.Write ( l_Object->GetPosition()->X );
				l_BitStream.Write ( l_Object->GetPosition()->Y );
				l_BitStream.Write ( l_Object->GetPosition()->Z );

			
			__NetGame->PlayerRPC( RPC_StopObject, &l_BitStream, l_uint16_PlayerIndex, 2 );

			return 1;
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcAttachObjectToPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcAttachObjectToPlayer()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: AttachObjectToPlayer(). Use Parent/Child Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 8 );

	uint16_t l_uint16_ObjectIndex = ( uint16_t )a_Params[ 1 ];
	if ( __NetGame->objectPool && ( l_uint16_ObjectIndex < LIMIT_MAX_OBJECT ) && ( __NetGame->objectPool->Get ( l_uint16_ObjectIndex ) ) )
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

				
			
			__NetGame->AddedPlayersRPC( RPC_AttachObjectToPlayer, &l_BitStream, l_uint16_PlayerIndex, 2 );
			__NetGame->PlayerRPC( RPC_AttachObjectToPlayer, &l_BitStream, l_uint16_PlayerIndex, 2 );
			return 1;
		}
	}
	return -1;
}