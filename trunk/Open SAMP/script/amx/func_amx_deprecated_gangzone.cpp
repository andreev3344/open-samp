#include "../../main.h"

#ifndef _STANDALONE
#include "../../../SDK/amx/amx.h"
#endif

#include "../func_amx.h"
#include "func_amx_deprecated_gangzone.h"

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
	if ( bScriptDebug ) logprintf ( "[Call]-> funcGangZoneCreate()" );

	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GangZoneCreate(). Use RadarZone Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 4 );

	
	if ( !__NetGame->gangZonePool )
		return -1;

	uint16_t l_Return = __NetGame->gangZonePool->New ( amx_ctof ( a_Params[ 1 ] ), amx_ctof ( a_Params[ 2 ] ), amx_ctof ( a_Params[ 3 ] ), amx_ctof ( a_Params[ 4 ] ) );
	if ( l_Return == 0xFFFF )
		return -1;
	return l_Return;
	//*/
/*
	tVector* 
		l_VectorPosition = new tVector();
		l_VectorPosition->X = amx_ctof ( a_Params[ 1 ] );
		l_VectorPosition->Y = amx_ctof ( a_Params[ 2 ] );

	tVector* 
		l_VectorSize = new tVector();
		l_VectorSize->X = ( amx_ctof ( a_Params[ 3 ] ) - l_VectorPosition->X );
		l_VectorSize->Y = ( amx_ctof ( a_Params[ 4 ] ) - l_VectorPosition->Y );

	CRadarZone* l_RadarZone = __ElementFactory->CreateRadarZone ( 0, l_VectorPosition, l_VectorSize, 0x00000000 );
	if ( l_RadarZone )
	{
		uint32_t l_uint32_ElementIndex = l_RadarZone->GetElementIndex();
		if ( l_uint32_ElementIndex == -1 )
			return -1;
		return l_uint32_ElementIndex;
	}
	return -1;
*/
}

cell AMX_NATIVE_CALL funcGangZoneDestroy ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcGangZoneDestroy()" );
	
	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GangZoneDestroy(). Use RadarZone Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 1 );

	
	if ( !__NetGame->gangZonePool || !__NetGame->gangZonePool->GetSlotState ( (uint16_t)a_Params[ 1 ] ) )
		return -1;

	__NetGame->gangZonePool->Delete ( (uint16_t)a_Params[ 1 ] );

	return 1;
	//*/
/*
	CElement* l_Element = __ElementFactory->GetElementFromIndex ( ( uint32_t )a_Params[ 1 ] );
	if ( l_Element )
	{
		delete l_Element;
		l_Element = NULL;

		return 1;
	}
	return -1;
*/
}

cell AMX_NATIVE_CALL funcGangZoneShowForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcGangZoneShowForPlayer()" );
	
	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GangZoneShowForPlayer(). Use RadarZone Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 3 );

	if ( !( a_Params[ 1 ] < 500 ) && !( __NetGame->playerPool->isCreated[ a_Params[ 1 ] ]  ) )
		return -1;


	if ( !__NetGame->gangZonePool || !__NetGame->gangZonePool->GetSlotState ( (uint16_t)a_Params[ 2 ] ) )
		return -1;

	__NetGame->gangZonePool->ShowForPlayer ( (_PlayerID)a_Params[ 1 ], (uint16_t)a_Params[ 2 ], a_Params[ 3 ] );

	return 1;
	//*/

	/*
	CElement* l_Element = __ElementFactory->GetElementFromIndex ( ( uint32_t )a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ZONE ) )
	{


		return 1;
	}
	//*/
}

cell AMX_NATIVE_CALL funcGangZoneShowForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGangZoneShowForAll()" );
	
	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GangZoneShowForAll(). Use RadarZone Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 2 );
		
	if ( !__NetGame->gangZonePool || !__NetGame->gangZonePool->GetSlotState ( (uint16_t)a_Params[ 1 ] ) )
		return -1;

	__NetGame->gangZonePool->ShowForAll ( (uint16_t)a_Params[ 1 ], a_Params[ 2 ] );

	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneHideForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGangZoneHideForPlayer()" );
	
	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GangZoneHideForPlayer(). Use RadarZone Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 2 );


	
	if ( !( a_Params[ 1 ] < 500 ) && !( __NetGame->playerPool->isCreated[ a_Params[ 1 ] ] ) )
		return -1;

	//if ( __PlayerPool->GetSlotState ( a_Params[ 1 ] ) )
	//	return -1;

	if ( !__NetGame->gangZonePool || !__NetGame->gangZonePool->GetSlotState ( (uint16_t)a_Params[ 2 ] ) )
		return -1;

	__NetGame->gangZonePool->HideForPlayer ( (_PlayerID)a_Params[ 1 ], (uint16_t)a_Params[ 2 ] );
	
	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneHideForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGangZoneHideForAll()" );
	
	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GangZoneHideForAll(). Use RadarZone Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 1 );

	if ( !__NetGame->gangZonePool || !__NetGame->gangZonePool->GetSlotState ( (uint16_t)a_Params[ 1 ] ) )
		return -1;

	__NetGame->gangZonePool->HideForAll ((uint16_t) a_Params[ 1 ] );

	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneFlashForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGangZoneFlashForPlayer()" );
	
	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GangZoneFlashForPlayer(). Use RadarZone Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 3 );



	if ( !( a_Params[ 1 ] < 500 ) && !( __NetGame->playerPool->isCreated[ a_Params[ 1 ] ] ) )
		return -1;

	//if ( __PlayerPool->GetSlotState ( a_Params[ 1 ] ) )
	//	return -1;

	if ( !__NetGame->gangZonePool || !__NetGame->gangZonePool->GetSlotState ( (uint16_t)a_Params[ 2 ] ) )
		return -1;

	__NetGame->gangZonePool->FlashForPlayer ((_PlayerID) a_Params[ 1 ], (uint16_t) a_Params[ 2 ], a_Params[ 3 ] );
	
	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneFlashForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGangZoneFlashForAll()" );
	
	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GangZoneFlashForAll(). Use RadarZone Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 2 );

	if ( !__NetGame->gangZonePool || !__NetGame->gangZonePool->GetSlotState ( (uint16_t)a_Params[ 1 ] ) )
		return -1;

	__NetGame->gangZonePool->FlashForAll ((uint16_t) a_Params[ 1 ], a_Params[ 2 ] );
	
	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneStopFlashForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGangZoneStopFlashForPlayer()" );
	
	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GangZoneStopFlashForPlayer(). Use RadarZone Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 2 );



	if ( !( a_Params[ 1 ] < 500 ) && !( __NetGame->playerPool->isCreated[ a_Params[ 1 ] ] ) )
		return -1;

	//if ( __PlayerPool->GetSlotState ( a_Params[ 1 ] ) )
	//	return -1;

	if ( !__NetGame->gangZonePool || !__NetGame->gangZonePool->GetSlotState ( (uint16_t)a_Params[ 2 ] ) )
		return -1;

	__NetGame->gangZonePool->StopFlashForPlayer ( (_PlayerID)a_Params[ 1 ], (uint16_t)a_Params[ 2 ] );
	
	return 1;
}

cell AMX_NATIVE_CALL funcGangZoneStopFlashForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	if(bScriptDebug) logprintf ( "[Call]-> funcGangZoneStopFlashForAll()" );
	
	// DEPRECATED FUNCTION
	logprintf ( "[Script]-> DEPRECATED FUNCTION: GangZoneStopFlashForAll(). Use RadarZone Concept Instead (Read Open SA-MP Docs)." );

	CHECK_PARAMS ( 1 );

	if ( !__NetGame->gangZonePool || !__NetGame->gangZonePool->GetSlotState ( (uint16_t)a_Params[ 1 ] ) )
		return -1;

	__NetGame->gangZonePool->StopFlashForAll ( (uint16_t)a_Params[ 1 ] );
	
	return 1;
}