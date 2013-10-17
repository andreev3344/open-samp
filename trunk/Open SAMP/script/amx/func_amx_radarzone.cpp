#include "../../main.h"

#ifndef _STANDALONE
#include "../../../SDK/amx/amx.h"
#endif

#include "../func_amx.h"
#include "func_amx_radarzone.h"

cell AMX_NATIVE_CALL funcRadarZoneCreate ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarZoneCreate()" );

	//playerid, x, y, sx, sy, color, flashingcolor, flashing, elementid
	CHECK_PARAMS ( 9 );

	tVector* 
		l_VectorPosition = new tVector();
		l_VectorPosition->X = amx_ctof ( a_Params[ 2 ] );
		l_VectorPosition->Y = amx_ctof ( a_Params[ 3 ] );

	tVector* 
		l_VectorSize = new tVector();
		l_VectorSize->X = amx_ctof ( a_Params[ 4 ] );
		l_VectorSize->Y = amx_ctof ( a_Params[ 5 ] );

	CRadarZone* l_RadarZone = __ElementFactory->CreateRadarZone ( a_Params[ 1 ], l_VectorPosition, l_VectorSize, a_Params[ 6 ], __ElementFactory->GetElementFromIndex ( a_Params[ 9 ] ) );
	if ( l_RadarZone )
	{
		l_RadarZone->SetFlashingColor ( a_Params[ 7 ] );

		
		if ( a_Params[ 8 ] == 0 )
			l_RadarZone->SetFlashing ( false );
		else
			l_RadarZone->SetFlashing ( true );

		uint32_t l_uint32_ElementIndex = l_RadarZone->GetElementIndex();
		if ( l_uint32_ElementIndex == -1 )
			return -1;
		return l_uint32_ElementIndex;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarZoneDestroy ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarZoneDestroy()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( ( uint32_t )a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ZONE ) )
	{
		delete l_Element;
		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarZoneIsValid ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarZoneIsValid()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( ( uint32_t )a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ZONE ) )
	{
		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarZoneSetSize ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarZoneSetSize()" );

	//elementid, x, y
	CHECK_PARAMS ( 3 );

	tVector* 
		l_VectorSize = new tVector();
		l_VectorSize->X = amx_ctof ( a_Params[ 2 ] );
		l_VectorSize->Y = amx_ctof ( a_Params[ 3 ] );

	CRadarZone* l_Element = ( CRadarZone* )__ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ZONE ) )
	{
		l_Element->SetSize ( l_VectorSize );
		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarZoneGetSize ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarZoneGetSize()" );

	//elementid, x, y
	CHECK_PARAMS ( 3 );

	CRadarZone* l_Element = ( CRadarZone* )__ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ZONE ) )
	{
		tVector* l_VectorSize = l_Element->GetSize();

		cell* cptr;
		amx_GetAddr ( a_AmxInterface, a_Params[ 2 ], &cptr );
		*cptr = amx_ftoc ( l_VectorSize->X );

		amx_GetAddr ( a_AmxInterface, a_Params[ 3 ], &cptr );
		*cptr = amx_ftoc ( l_VectorSize->Y );

		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarZoneGetCenter ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarZoneGetCenter()" );

	//elementid, x, y
	CHECK_PARAMS ( 3 );

	CRadarZone* l_Element = ( CRadarZone* )__ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ZONE ) )
	{
		tVector* l_VectorCenter = l_Element->GetCenter();
		if ( l_VectorCenter )
		{
			cell* cptr;
			amx_GetAddr ( a_AmxInterface, a_Params[ 2 ], &cptr );
			*cptr = amx_ftoc ( l_VectorCenter->X );

			amx_GetAddr ( a_AmxInterface, a_Params[ 3 ], &cptr );
			*cptr = amx_ftoc ( l_VectorCenter->Y );

			delete l_VectorCenter;
		}
		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarZoneSetColor ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarZoneSetColor()" );

	//elementid, color
	CHECK_PARAMS ( 2 );

	CRadarZone* l_Element = ( CRadarZone* )__ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ZONE ) )
	{
		l_Element->SetColor ( ( uint32_t )a_Params[ 2 ] );
		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarZoneGetColor ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarZoneGetColor()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CRadarZone* l_Element = ( CRadarZone* )__ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ZONE ) )
	{
		return ( cell )( l_Element->GetColor() );
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarZoneSetFlashingColor ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarZoneSetFlashingColor()" );

	//elementid, color
	CHECK_PARAMS ( 2 );

	CRadarZone* l_Element = ( CRadarZone* )__ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ZONE ) )
	{
		l_Element->SetFlashingColor ( ( uint32_t )a_Params[ 2 ] );
		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarZoneGetFlashingColor ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarZoneGetFlashingColor()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CRadarZone* l_Element = ( CRadarZone* )__ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ZONE ) )
	{
		return ( cell )( l_Element->GetFlashingColor() );
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarZoneSetFlashing ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarZoneSetFlashing()" );

	//elementid, flashing
	CHECK_PARAMS ( 2 );

	CRadarZone* l_Element = ( CRadarZone* )__ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ZONE ) )
	{
		if ( a_Params[ 2 ] == 0 )
			l_Element->SetFlashing ( false );
		else
			l_Element->SetFlashing ( true );
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarZoneIsFlashing ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarZoneSetFlashing()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CRadarZone* l_Element = ( CRadarZone* )__ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ZONE ) )
	{
		if ( l_Element->IsFlashing() )
			return 1;
	}
	return 0;
}