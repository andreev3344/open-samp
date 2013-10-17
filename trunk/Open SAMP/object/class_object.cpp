/**
 *	Open SA-MP
 *
 *		SutraPlex Software
 *
 */

/**
 *	Include(s)
 */
#include "../main.h"
#include "class_object.h"

/**
 *	Constructor #1
 */
CObject::~CObject()
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementObjectDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_DestroyObject, l_BitStream, 0xFFFFu, 2 );
		delete l_BitStream;
	}
}

TiXmlElement* CObject::SerializeAttribute ( void )
{
	TiXmlElement* l_XmlElement = new TiXmlElement ( "object" );
	if ( l_XmlElement )
	{
		l_XmlElement->SetAttribute ( "model", this->m_uint32_ModelIndex );
		l_XmlElement->SetDoubleAttribute ( "x", this->m_Position.X );
		l_XmlElement->SetDoubleAttribute ( "y", this->m_Position.Y );
		l_XmlElement->SetDoubleAttribute ( "z", this->m_Position.Z );
		l_XmlElement->SetDoubleAttribute ( "rx", this->m_Rotation.X );
		l_XmlElement->SetDoubleAttribute ( "ry", this->m_Rotation.Y );
		l_XmlElement->SetDoubleAttribute ( "rz", this->m_Rotation.Z );

		return l_XmlElement;
	}
	return NULL;
}
	
void CObject::UnSerializeAttribute ( TiXmlElement* a_XmlElement )
{
	a_XmlElement->QueryUnsignedAttribute ( "model", ( unsigned int* )&this->m_uint32_ModelIndex );

	tVector* l_Position = new tVector();
	if ( l_Position )
	{
		a_XmlElement->QueryFloatAttribute ( "x", &l_Position->X );
		a_XmlElement->QueryFloatAttribute ( "y", &l_Position->Y );
		a_XmlElement->QueryFloatAttribute ( "z", &l_Position->Z );

		this->SetPosition ( l_Position );
	}

	tVector* l_Rotation = new tVector();
	if ( l_Rotation )
	{
		a_XmlElement->QueryFloatAttribute ( "rx", &l_Rotation->X );
		a_XmlElement->QueryFloatAttribute ( "ry", &l_Rotation->Y );
		a_XmlElement->QueryFloatAttribute ( "rz", &l_Rotation->Z );

		this->SetRotation ( l_Rotation );
	}
}

/**
 *	CObject::SetElementOwner()
 *		Set the owner of the element. The Owner is the element who can see the object.
 *	@a_uint16_ElementOwner: The New Element's Owner.
 */
void CObject::SetElementOwner ( uint16_t a_uint16_ElementOwner )
{
	CElement::SetElementOwner ( a_uint16_ElementOwner );

	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementObjectDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_DestroyObject, l_BitStream, 0xFFFF, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	if ( a_uint16_ElementOwner == 0 )
		this->InitializeForAll();
	else
		this->InitializeForPlayer ( a_uint16_ElementOwner );
}

/**
 *	CObject::SetElementModel()
 *		Change the element model.
 *	@a_uint32_ModelIndex: The New Element's Model.
 *	@return: True if Model Exist. Else, False.
 */
bool CObject::SetElementModel ( uint32_t a_uint32_ModelIndex )
{
	bool l_Return = CElement::SetElementModel ( a_uint32_ModelIndex );

	RakNet::BitStream* l_BitStream = NULL;

	l_BitStream = ComputeBitStream_ElementObjectDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_DestroyObject, l_BitStream, 0xFFFFu, 2 );
		delete l_BitStream;
		l_BitStream = NULL;
	}

	l_BitStream = ComputeBitStream_ElementObjectSpawn();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_SpawnObject, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;
	}
	return l_Return;
}

/**
 *	CObject::SetRotation()
 *		Set the rotation of the object.
 *	@a_Rotation: Pointer to a new Rotation Vector.
 */
void CObject::SetRotation ( tVector* a_Rotation )
{
	CElement::SetRotation ( a_Rotation );

	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementObjectSetRotation();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_SetObjectRotation, l_BitStream, 0xFFFFu, 2 );
		delete l_BitStream;
	}
}

/**
 *	CObject::SetPosition()
 *		Set the position of the object.
 *	@a_Position: Pointer to a new Position Vector.
 */
void CObject::SetPosition ( tVector* a_Position )
{
	CElement::SetPosition ( a_Position );

	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementObjectSetPosition();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_SetObjectPosition, l_BitStream, 0xFFFFu, 2 );
		delete l_BitStream;
	}
}

/**
 *	CObject::SetPosition()
 *		Update the position of the object and its children on the network.
 */
void CObject::UpdatePosition ( void )
{
	CElement::UpdatePosition();

	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementObjectSetPosition();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_SetObjectPosition, l_BitStream, 0xFFFFu, 2 );
		delete l_BitStream;
	}
}

float CObject::Move ( float a_float_X, float a_float_Y, float a_float_Z, float a_float_Speed )
{
	this->m_TargetPosition = new tVector ( a_float_X, a_float_Y, a_float_Z );

	this->m_float_MoveSpeed = a_float_Speed;
	this->m_uint8_IsMoving |= 1;
	
	float l_float_X = ( ( this->m_TargetPosition->X - this->m_Position.X ) * ( this->m_TargetPosition->X - this->m_Position.X ) );
	float l_float_Y = ( ( this->m_TargetPosition->Y - this->m_Position.Y ) * ( this->m_TargetPosition->Y - this->m_Position.Y ) );
	float l_float_Z = ( ( this->m_TargetPosition->Z - this->m_Position.Z ) * ( this->m_TargetPosition->Z - this->m_Position.Z ) );

	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementObjectMove();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_MoveObject, l_BitStream, 0xFFFFu, 2 );
		delete l_BitStream;
	}
	
	return ( sqrt ( l_float_X + l_float_Y + l_float_Z ) / a_float_Speed );
}
	
float CObject::Move ( tVector* a_Position, float a_float_Speed )
{
	this->m_TargetPosition = a_Position;

	this->m_float_MoveSpeed = a_float_Speed;
	this->m_uint8_IsMoving |= 1;
	
	float l_float_X = ( ( this->m_TargetPosition->X - this->m_Position.X ) * ( this->m_TargetPosition->X - this->m_Position.X ) );
	float l_float_Y = ( ( this->m_TargetPosition->Y - this->m_Position.Y ) * ( this->m_TargetPosition->Y - this->m_Position.Y ) );
	float l_float_Z = ( ( this->m_TargetPosition->Z - this->m_Position.Z ) * ( this->m_TargetPosition->Z - this->m_Position.Z ) );

	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementObjectMove();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_MoveObject, l_BitStream, 0xFFFFu, 2 );
		delete l_BitStream;
	}
	
	return ( sqrt ( l_float_X + l_float_Y + l_float_Z ) / a_float_Speed );
}

void CObject::Stop ( void )
{
	this->m_uint8_IsMoving &= 0xFEu;

	if ( this->m_TargetPosition )
		delete this->m_TargetPosition;
}

/**
 *	CObject::InitializeForPlayer()
 *		Initialize the object for the specified player.
 *	@a_uint16_PlayerIndex: Player's Index
 */
void CObject::InitializeForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	if ( ( this->m_uint16_ElementOwner == 0 ) || ( this->m_uint16_ElementOwner == a_uint16_PlayerIndex ) )
	{
		RakNet::BitStream* l_BitStream = ComputeBitStream_ElementObjectSpawn();
		if ( l_BitStream )
		{
			__NetGame->PlayerRPC ( RPC_SpawnObject, l_BitStream, a_uint16_PlayerIndex, 2 );
			delete l_BitStream;
		}
	}
}

/**
 *	CObject::InitializeForAll()
 *		Initialize the object for everyone.
 */
void CObject::InitializeForAll ( void )
{
	if ( this->m_uint16_ElementOwner == 0 )
	{
		RakNet::BitStream* l_BitStream = ComputeBitStream_ElementObjectSpawn();
		if ( l_BitStream )
		{
			__NetGame->GlobalRPC ( RPC_SpawnObject, l_BitStream, 0xFFFF, 2 );
			delete l_BitStream;
		}
	}
}

/**
 *	CObject::ShowForPlayer()
 *		Update the network and show the object for the specified player and only. Object's Owner flag is modified.
 *	@a_uint16_PlayerIndex: The Player's Index.
 */
void CObject::ShowForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementObjectSpawn();
	if ( l_BitStream )
	{
		__NetGame->PlayerRPC ( RPC_SpawnObject, l_BitStream, a_uint16_PlayerIndex, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = a_uint16_PlayerIndex;
	}
}

/**
 *	CObject::ShowForAll()
 *		Update the network and show the object for everyone. Reset the Object's Owner flag.
 */
void CObject::ShowForAll ( void )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementObjectSpawn();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_SpawnObject, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}

/**
 *	CObject::HideForPlayer()
 *		Update the network and hide the object for the specified player. Reset the Object's Owner flag.
 *	@a_uint16_PlayerIndex: Player's Index.
 */
void CObject::HideForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementObjectDestroy();
	if ( l_BitStream )
	{
		__NetGame->PlayerRPC ( RPC_DestroyObject, l_BitStream, a_uint16_PlayerIndex, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}

/**
 *	CObject::HideForAll()
 *		Update the network and hide the object for everyone. Reset the Object's Owner flag.
 */
void CObject::HideForAll ( void )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementObjectDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_DestroyObject, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}

/**
 *	CObject::Process()
 *		Process the object, Moving and things..
 *	@a_float_Time: Network Sync Time
 */
uint8_t CObject::Process ( float a_float_Time )
{
	uint8_t l_Return = 0;

	if ( this->m_uint8_IsMoving & 1 )
	{
		float l_float_Distance = a_float_Time * this->m_float_MoveSpeed;
		float l_float_Remaining = this->GetDistanceFrom ( this->m_TargetPosition );
		if ( l_float_Distance >= l_float_Remaining )
		{
			l_Return |= 1;
			this->m_uint8_IsMoving &= ~1;
			
			if ( this->m_Parent )
			{
				this->m_Position = ( *( this->m_Parent->GetPosition() ) ) + *this->m_TargetPosition;
			}
			else
			{
				this->m_Position = *this->m_TargetPosition;
			}
		}
		else
		{
			l_float_Remaining /= l_float_Distance;
			
			if ( this->m_Parent )
			{
				this->m_Position += ( *( this->m_Parent->GetPosition() ) ) + ( *this->m_TargetPosition - this->m_Position ) / l_float_Remaining;
				//__NetGame->SendClientMessageToAll ( 0xFFFFFFFF, "Update: %f %f %f", this->m_Position.X, this->m_Position.Y, this->m_Position.Z );
			}
			else
			{
				this->m_Position += ( *this->m_TargetPosition - this->m_Position ) / l_float_Remaining;
				//__NetGame->SendClientMessageToAll ( 0xFFFFFFFF, "Update: %f %f %f", this->m_Position.X, this->m_Position.Y, this->m_Position.Z );
			}
		}
	}
	return l_Return;
}