#include "../../main.h"

#ifndef _STANDALONE
#include "../../../SDK/amx/amx.h"
#endif

#include "../func_amx.h"
#include "func_amx_radaricon.h"

cell AMX_NATIVE_CALL funcRadarIconCreate ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarIconCreate()" );

	//playerid, icon, type, color, x, y, z, elementid
	CHECK_PARAMS ( 8 );

	tVector* 
		l_VectorPosition = new tVector();
		l_VectorPosition->X = amx_ctof ( a_Params[ 5 ] );
		l_VectorPosition->Y = amx_ctof ( a_Params[ 6 ] );
		l_VectorPosition->Z = amx_ctof ( a_Params[ 7 ] );

	CRadarIcon* l_RadarIcon = __ElementFactory->CreateRadarIcon ( ( uint32_t )a_Params[ 1 ], ( uint32_t )a_Params[ 2 ], ( uint8_t )a_Params[ 3 ], l_VectorPosition, ( uint32_t )a_Params[ 4 ], __ElementFactory->GetElementFromIndex ( a_Params[ 8 ] ) );
	if ( l_RadarIcon )
	{
		uint32_t l_uint32_ElementIndex = l_RadarIcon->GetElementIndex();
		if ( l_uint32_ElementIndex == -1 )
			return -1;
		return l_uint32_ElementIndex;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarIconDestroy ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarIconDestroy()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( ( uint32_t )a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ICON ) )
	{
		delete l_Element;
		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarIconIsValid ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarIconIsValid()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( ( uint32_t )a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ICON ) )
	{
		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarIconSetColor ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarIconSetColor()" );

	//elementid, color
	CHECK_PARAMS ( 2 );

	CRadarIcon* l_Element = ( CRadarIcon* )__ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ICON ) )
	{
		l_Element->SetColor ( tColor ( ( uint32_t )a_Params[ 2 ] ) );
		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcRadarIconGetColor ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcRadarIconGetColor()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CRadarIcon* l_Element = ( CRadarIcon* )__ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_RADAR_ICON ) )
	{
		return ( cell )( l_Element->GetColor().RGBA );
	}
	return -1;
}