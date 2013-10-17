#include "../../main.h"

#ifndef _STANDALONE
#include "../../../SDK/amx/amx.h"
#endif

#include "../func_amx.h"
#include "func_amx_element.h"

cell AMX_NATIVE_CALL funcElementCreate ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementCreate()" );

	//elementtype, parent
	CHECK_PARAMS ( 2 );

	switch ( a_Params[ 1 ] )
	{
		case ELEMENT_TYPE_ROOT:
		{
			//logprintf ( "[Error] Root Element can't be created from Scripting Engine." );
			
			CElement* l_Element = ( CElement* )__ElementFactory->CreateFromFile ( "test.xml", 0, NULL );
			if ( l_Element )
			{
				uint32_t l_uint32_ElementIndex = l_Element->GetElementIndex();
				if ( l_uint32_ElementIndex == -1 )
					return -1;
				return l_uint32_ElementIndex;
			}
			break;
		}
		case ELEMENT_TYPE_VIRTUAL:
		{
			CElement* l_Element = ( CElement* )__ElementFactory->CreateVirtual ( 0, new tVector(), __ElementFactory->GetElementFromIndex ( a_Params[ 2 ] ) );
			if ( l_Element )
			{
				uint32_t l_uint32_ElementIndex = l_Element->GetElementIndex();
				if ( l_uint32_ElementIndex == -1 )
					return -1;
				return l_uint32_ElementIndex;
			}
			break;
		}
		case ELEMENT_TYPE_OBJECT:
		{
			CElement* l_Element = ( CElement* )__ElementFactory->CreateObject ( 0, 0, new tVector(), new tVector(), __ElementFactory->GetElementFromIndex ( a_Params[ 2 ] ) );
			if ( l_Element )
			{
				uint32_t l_uint32_ElementIndex = l_Element->GetElementIndex();
				if ( l_uint32_ElementIndex == -1 )
					return -1;
				return l_uint32_ElementIndex;
			}
			break;
		}
		case ELEMENT_TYPE_RADAR_ICON:
		{
			CElement* l_Element = ( CElement* )__ElementFactory->CreateRadarIcon ( 0, 0, RADAR_ICON_TYPE_LOCAL, new tVector(), 0xFFFFFFFF, __ElementFactory->GetElementFromIndex ( a_Params[ 2 ] ) );
			if ( l_Element )
			{
				uint32_t l_uint32_ElementIndex = l_Element->GetElementIndex();
				if ( l_uint32_ElementIndex == -1 )
					return -1;
				return l_uint32_ElementIndex;
			}
			break;
		}
		case ELEMENT_TYPE_RADAR_ZONE:
		{
			CElement* l_Element = ( CElement* )__ElementFactory->CreateRadarZone ( 0, new tVector(), new tVector(), 0xFFFFFFFF, __ElementFactory->GetElementFromIndex ( a_Params[ 2 ] ) );
			if ( l_Element )
			{
				uint32_t l_uint32_ElementIndex = l_Element->GetElementIndex();
				if ( l_uint32_ElementIndex == -1 )
					return -1;
				return l_uint32_ElementIndex;
			}

			break;
		}
		default:
		{
			return -1;
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcElementClone ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementClone()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() != ELEMENT_TYPE_ROOT ) )
	{
		CElement* l_ClonedElement = __ElementFactory->Clone ( l_Element );
		
		if ( l_ClonedElement )
			return l_ClonedElement->GetElementIndex();
	}
	return -1;
}

cell AMX_NATIVE_CALL funcElementDestroy ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementDestroy()" );

	CHECK_PARAMS ( 1 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element )
	{
		delete l_Element;
		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcElementSetModel ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementSetModel()" );

	//elementid, modelid
	CHECK_PARAMS ( 2 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() != ELEMENT_TYPE_ROOT ) && ( l_Element->GetElementType() != ELEMENT_TYPE_VIRTUAL ) )
	{
		return ( cell )l_Element->SetElementModel ( ( uint32_t )a_Params[ 2 ] );
	}
	return -1;
}

cell AMX_NATIVE_CALL funcElementGetModel ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementGetModel()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element && ( l_Element->GetElementType() != ELEMENT_TYPE_ROOT ) && ( l_Element->GetElementType() != ELEMENT_TYPE_VIRTUAL ) )
	{
		return ( cell )l_Element->GetElementModel();
	}
	return -1;
}

cell AMX_NATIVE_CALL funcElementIsValid ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementIsValid()" );

	CHECK_PARAMS ( 1 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element )
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL funcElementGetType ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementGetType()" );

	CHECK_PARAMS ( 1 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element )
	{
		return ( cell )l_Element->GetElementType();
	}
	return 0;
}

cell AMX_NATIVE_CALL funcElementSetParent ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementSetParent()" );

	//elementid, parentid
	CHECK_PARAMS ( 2 );

	CElement* l_ParentElement = __ElementFactory->GetElementFromIndex ( a_Params[ 2 ] );
	if ( l_ParentElement )
	{
		CElement* l_ChildElement = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
		if ( l_ChildElement )
		{
			l_ParentElement->AddChild ( l_ChildElement );
			return 1;
		}
	}
	return -1;
}

cell AMX_NATIVE_CALL funcElementGetParent ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementGetParent()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 2 ] );
	if ( l_Element )
	{
		return l_Element->GetParent()->GetElementIndex();
	}
	return -1;
}

cell AMX_NATIVE_CALL funcElementSetOwner ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementSetOwner()" );

	//elementid, parentid
	CHECK_PARAMS ( 2 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element )
	{
		l_Element->SetElementOwner ( ( uint16_t )a_Params[ 2 ] );

		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcElementGetOwner ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementGetOwner()" );

	//elementid
	CHECK_PARAMS ( 1 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 2 ] );
	if ( l_Element )
	{
		return l_Element->GetElementOwner();
	}
	return -1;
}

cell AMX_NATIVE_CALL funcElementSetPosition ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementSetPosition()" );

	//elementid, x, y, z
	CHECK_PARAMS ( 4 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element )
	{
		l_Element->SetPosition ( new tVector ( amx_ctof ( a_Params[ 2 ] ), amx_ctof ( a_Params[ 3 ] ), amx_ctof ( a_Params[ 4 ] ) ) );
		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcElementGetPosition ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementGetPosition()" );

	// elementid, x, y, z
	CHECK_PARAMS ( 4 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element )
	{
		tVector* l_VectorPosition = l_Element->GetPosition();

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

cell AMX_NATIVE_CALL funcElementSetAbsolutePosition ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementSetAbsolutePosition()" );

	//elementid, x, y, z
	CHECK_PARAMS ( 4 );

	tVector* 
		l_VectorAbsolutePosition = new tVector();
		l_VectorAbsolutePosition->X = amx_ctof ( a_Params[ 2 ] );
		l_VectorAbsolutePosition->Y = amx_ctof ( a_Params[ 3 ] );
		l_VectorAbsolutePosition->Z = amx_ctof ( a_Params[ 4 ] );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element )
	{
		l_Element->SetAbsolutePosition ( l_VectorAbsolutePosition );
		return 1;
	}
	return -1;
}

cell AMX_NATIVE_CALL funcElementGetAbsolutePosition ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementGetAbsolutePosition()" );

	// elementid, x, y, z
	CHECK_PARAMS ( 4 );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element )
	{
		tVector* l_VectorRelativePosition = l_Element->GetAbsolutePosition();

		cell* cptr;
		amx_GetAddr ( a_AmxInterface, a_Params[ 2 ], &cptr );
		*cptr = amx_ftoc ( l_VectorRelativePosition->X );

		amx_GetAddr ( a_AmxInterface, a_Params[ 3 ], &cptr );
		*cptr = amx_ftoc ( l_VectorRelativePosition->Y );

		amx_GetAddr ( a_AmxInterface, a_Params[ 4 ], &cptr );
		*cptr = amx_ftoc ( l_VectorRelativePosition->Z );

		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL funcElementGetDistanceFromPoint ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementGetDistanceFromPoint()" );

	//elementid, x, y, z
	CHECK_PARAMS ( 4 );

	tVector* 
		l_VectorPosition = new tVector();
		l_VectorPosition->X = amx_ctof ( a_Params[ 2 ] );
		l_VectorPosition->Y = amx_ctof ( a_Params[ 3 ] );
		l_VectorPosition->Z = amx_ctof ( a_Params[ 4 ] );

	CElement* l_Element = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element )
	{
		float l_Distance = l_Element->GetDistanceFrom ( l_VectorPosition );
		return amx_ftoc ( l_Distance );
	}
	return -1;
}

cell AMX_NATIVE_CALL funcElementGetDistanceFromElement ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementGetDistanceFromElement()" );

	//elementid, elementid
	CHECK_PARAMS ( 2 );

	CElement* l_Element1 = __ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	CElement* l_Element2 = __ElementFactory->GetElementFromIndex ( a_Params[ 2 ] );
	if ( l_Element1 && l_Element2 )
	{
		float l_Distance = l_Element1->GetDistanceFrom ( l_Element2 );
		return amx_ftoc ( l_Distance );
	}
	return -1;
}

cell AMX_NATIVE_CALL funcElementMove ( AMX* a_AmxInterface, cell* a_Params )
{
	if ( bScriptDebug ) logprintf ( "[Call]-> funcElementMove()" );

	//elementid, x, y, z, speed
	CHECK_PARAMS ( 5 );

	tVector* 
		l_VectorPosition = new tVector();
		l_VectorPosition->X = amx_ctof ( a_Params[ 2 ] );
		l_VectorPosition->Y = amx_ctof ( a_Params[ 3 ] );
		l_VectorPosition->Z = amx_ctof ( a_Params[ 4 ] );

	CObject* l_Element = ( CObject* )__ElementFactory->GetElementFromIndex ( a_Params[ 1 ] );
	if ( l_Element )
	{
		l_Element->Move ( l_VectorPosition, amx_ctof ( a_Params[ 5 ] ) );
		return 1;
	}
	return -1;
}
