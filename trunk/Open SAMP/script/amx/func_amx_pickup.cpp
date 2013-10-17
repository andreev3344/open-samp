#include "../../main.h"

#ifndef _STANDALONE
#include "../../../SDK/amx/amx.h"
#endif

#include "../func_amx.h"
#include "func_amx_pickup.h"

cell AMX_NATIVE_CALL funcPickupCreate ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcPickupCreate()" );

	//playerid, modelid, type, x, y, z, elementid
	CHECK_PARAMS ( 7 );
	
	tVector* 
		l_VectorPosition = new tVector();
		l_VectorPosition->X = amx_ctof ( a_Params[ 4 ] );
		l_VectorPosition->Y = amx_ctof ( a_Params[ 5 ] );
		l_VectorPosition->Z = amx_ctof ( a_Params[ 6 ] );

	CPickup* l_Pickup = __ElementFactory->CreatePickup ( ( uint16_t )a_Params[ 1 ], ( uint32_t )a_Params[ 2 ], ( uint32_t )a_Params[ 3 ], l_VectorPosition, __ElementFactory->GetElementFromIndex ( a_Params[ 7 ] ) );
	if ( l_Pickup )
	{
		uint32_t l_uint32_ElementIndex = l_Pickup->GetElementIndex();
		if ( l_uint32_ElementIndex == -1 )
			return -1;
		return l_uint32_ElementIndex;
	}
	return -1;
}
