#include "../../main.h"

#ifndef _STANDALONE
#include "../../../SDK/amx/amx.h"
#endif

#include "../func_amx.h"
#include "func_amx_object.h"

cell AMX_NATIVE_CALL funcObjectCreate ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcObjectCreate()" );

	//playerid, model, x, y, z, rx, ry, rz, elementid
	CHECK_PARAMS ( 9 );
	
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

	CObject* l_Object = __ElementFactory->CreateObject ( ( uint16_t )a_Params[ 1 ], ( uint32_t )a_Params[ 2 ], l_VectorPosition, l_VectorRotation, __ElementFactory->GetElementFromIndex ( a_Params[ 9 ] ) );
	if ( l_Object )
	{
		uint32_t l_uint32_ElementIndex = l_Object->GetElementIndex();
		if ( l_uint32_ElementIndex == -1 )
			return -1;
		return l_uint32_ElementIndex;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcObjectDestroy ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcObjectDestroy()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( ( uint32_t )a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_OBJECT ) )
	{
		delete l_Element;
		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcObjectIsValid ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcObjectIsValid()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( ( uint32_t )a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() == ELEMENT_TYPE_OBJECT ) )
	{
		return 1;
	}
	return -1;
}
