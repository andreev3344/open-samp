#include "../../main.h"
#include "../../../SDK/amx/amx.h"

#include "../func_amx.h"
#include "func_amx_gangzone.h"

//cell ( __cdecl* _funcGangZoneCreate )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GangZoneCreate;
//cell ( __cdecl* _funcGangZoneDestroy )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GangZoneDestroy;
//cell ( __cdecl* _funcGangZoneShowForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GangZoneShowForPlayer;
//cell ( __cdecl* _funcGangZoneShowForAll )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GangZoneShowForAll;
//cell ( __cdecl* _funcGangZoneHideForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GangZoneHideForPlayer;
//cell ( __cdecl* _funcGangZoneHideForAll )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GangZoneHideForAll;
//cell ( __cdecl* _funcGangZoneFlashForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GangZoneFlashForPlayer;
//cell ( __cdecl* _funcGangZoneFlashForAll )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GangZoneFlashForAll;
//cell ( __cdecl* _funcGangZoneStopFlashForPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GangZoneStopFlashForPlayer;
//cell ( __cdecl* _funcGangZoneStopFlashForAll )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GangZoneStopFlashForAll;


cell AMX_NATIVE_CALL funcGangZoneCreate ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGangZoneCreate()" );

	CHECK_PARAMS ( 4 );

	if ( !__GangZonePool )
		return -1;

	uint16_t l_Return = __GangZonePool->New ( amx_ctof ( a_Params[ 1 ] ), amx_ctof ( a_Params[ 2 ] ), amx_ctof ( a_Params[ 3 ] ), amx_ctof ( a_Params[ 4 ] ) );
	if ( l_Return == 0xFFFF )
		return -1;
	return l_Return;
}

cell AMX_NATIVE_CALL funcGangZoneDestroy ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGangZoneDestroy()" );

	CHECK_PARAMS ( 1 );

	if ( !__GangZonePool || !__GangZonePool->GetSlotState ( (uint16_t)a_Params[ 1 ] ) )
		return -1;

	__GangZonePool->Delete ( (uint16_t)a_Params[ 1 ] );

	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneShowForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGangZoneShowForPlayer()" );

	CHECK_PARAMS ( 3 );



	if ( !( a_Params[ 1 ] < 500 ) && !( __NetGame->playerPool->isCreated[ a_Params[ 1 ] ]  ) )
		return -1;

	//if ( __PlayerPool->GetSlotState ( a_Params[ 1 ] ) )
	//	return -1;

	if ( !__GangZonePool || !__GangZonePool->GetSlotState ( (uint16_t)a_Params[ 2 ] ) )
		return -1;

	__GangZonePool->ShowForPlayer ( (_PlayerID)a_Params[ 1 ], (uint16_t)a_Params[ 2 ], a_Params[ 3 ] );

	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneShowForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGangZoneShowForAll()" );

	CHECK_PARAMS ( 2 );
		
	if ( !__GangZonePool || !__GangZonePool->GetSlotState ( (uint16_t)a_Params[ 1 ] ) )
		return -1;

	__GangZonePool->ShowForAll ( (uint16_t)a_Params[ 1 ], a_Params[ 2 ] );

	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneHideForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGangZoneHideForPlayer()" );

	CHECK_PARAMS ( 2 );


	
	if ( !( a_Params[ 1 ] < 500 ) && !( __NetGame->playerPool->isCreated[ a_Params[ 1 ] ] ) )
		return -1;

	//if ( __PlayerPool->GetSlotState ( a_Params[ 1 ] ) )
	//	return -1;

	if ( !__GangZonePool || !__GangZonePool->GetSlotState ( (uint16_t)a_Params[ 2 ] ) )
		return -1;

	__GangZonePool->HideForPlayer ( (_PlayerID)a_Params[ 1 ], (uint16_t)a_Params[ 2 ] );
	
	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneHideForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGangZoneHideForAll()" );

	CHECK_PARAMS ( 1 );

	if ( !__GangZonePool || !__GangZonePool->GetSlotState ( (uint16_t)a_Params[ 1 ] ) )
		return -1;

	__GangZonePool->HideForAll ((uint16_t) a_Params[ 1 ] );

	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneFlashForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGangZoneFlashForPlayer()" );

	CHECK_PARAMS ( 3 );



	if ( !( a_Params[ 1 ] < 500 ) && !( __NetGame->playerPool->isCreated[ a_Params[ 1 ] ] ) )
		return -1;

	//if ( __PlayerPool->GetSlotState ( a_Params[ 1 ] ) )
	//	return -1;

	if ( !__GangZonePool || !__GangZonePool->GetSlotState ( (uint16_t)a_Params[ 2 ] ) )
		return -1;

	__GangZonePool->FlashForPlayer ((_PlayerID) a_Params[ 1 ], (uint16_t) a_Params[ 2 ], a_Params[ 3 ] );
	
	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneFlashForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGangZoneFlashForAll()" );

	CHECK_PARAMS ( 2 );

	if ( !__GangZonePool || !__GangZonePool->GetSlotState ( (uint16_t)a_Params[ 1 ] ) )
		return -1;

	__GangZonePool->FlashForAll ((uint16_t) a_Params[ 1 ], a_Params[ 2 ] );
	
	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneStopFlashForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGangZoneStopFlashForPlayer()" );

	CHECK_PARAMS ( 2 );



	if ( !( a_Params[ 1 ] < 500 ) && !( __NetGame->playerPool->isCreated[ a_Params[ 1 ] ] ) )
		return -1;

	//if ( __PlayerPool->GetSlotState ( a_Params[ 1 ] ) )
	//	return -1;

	if ( !__GangZonePool || !__GangZonePool->GetSlotState ( (uint16_t)a_Params[ 2 ] ) )
		return -1;

	__GangZonePool->StopFlashForPlayer ( (_PlayerID)a_Params[ 1 ], (uint16_t)a_Params[ 2 ] );
	
	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneStopFlashForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGangZoneStopFlashForAll()" );

	CHECK_PARAMS ( 1 );

	if ( !__GangZonePool || !__GangZonePool->GetSlotState ( (uint16_t)a_Params[ 1 ] ) )
		return -1;

	__GangZonePool->StopFlashForAll ( (uint16_t)a_Params[ 1 ] );
	
	return 1;
}