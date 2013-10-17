#include "../main.h"
#include "class_deprecated_object.h"

void CDeprecatedObject::SetObjectIndex ( uint16_t a_uint16_Index )
{
	this->m_uint16_ObjectIndex = a_uint16_Index;
}

void CDeprecatedObject::SetRotation ( tVector* a_Rotation )
{
	this->m_Rotation = *a_Rotation;
}
	
tVector* CDeprecatedObject::GetRotation ( void )
{
	return &( this->m_Rotation );
}
	
void CDeprecatedObject::SetPosition ( tVector* a_Position )
{
	this->m_Position = *a_Position;
}

tVector* CDeprecatedObject::GetPosition ( void )
{
	return &( this->m_Position );
}

void CDeprecatedObject::SpawnForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_Spawn();
	if ( l_BitStream )
	{
		
		__NetGame->PlayerRPC( RPC_SpawnObject, l_BitStream, a_uint16_PlayerIndex, 2 );

		delete l_BitStream;
	}
}

void CDeprecatedObject::SpawnForAll ( void )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_Spawn();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC( RPC_SpawnObject, l_BitStream, 0xFFFF, 2 );

		delete l_BitStream;
	}
}


void CDeprecatedObject::AttachToVehicle ( uint16_t a_uint16_VehicleIndex, tVector* a_Offset, tVector* a_Rotation )
{
	if ( a_uint16_VehicleIndex == -1 )
	{
		this->m_uint16_AttachedVehicleIndex = -1;
		this->m_AttachedOffset.X = 0.0f;
		this->m_AttachedOffset.Y = 0.0f;
		this->m_AttachedOffset.Z = 0.0f;
		this->m_AttachedRotation.X = 0.0f;
		this->m_AttachedRotation.Y = 0.0f;
		this->m_AttachedRotation.Z = 0.0f;
	}
	else
	{
		this->m_uint16_AttachedVehicleIndex = a_uint16_VehicleIndex;
		this->m_AttachedOffset.X = a_Offset->X;
		this->m_AttachedOffset.Y = a_Offset->Y;
		this->m_AttachedOffset.Z = a_Offset->Z;
		this->m_AttachedRotation.X = a_Rotation->X;
		this->m_AttachedRotation.Y = a_Rotation->Y;
		this->m_AttachedRotation.Z = a_Rotation->Z;
	}

	this->SpawnForAll();
}

float CDeprecatedObject::Move ( float a_float_X, float a_float_Y, float a_float_Z, float a_float_Speed )
{
	this->m_Position.X = a_float_X;
	this->m_Position.Y = a_float_Y;
	this->m_Position.Z = a_float_Z;

	this->m_float_MoveSpeed = a_float_Speed;
	this->m_uint8_IsMoving |= 1;
	
	float l_float_X = ( ( a_float_X - this->m_Position.X ) * ( a_float_X - this->m_Position.X ) );
	float l_float_Y = ( ( a_float_Y - this->m_Position.Y ) * ( a_float_Y - this->m_Position.Y ) );
	float l_float_Z = ( ( a_float_Z - this->m_Position.Z ) * ( a_float_Z - this->m_Position.Z ) );
	
	return ( sqrt ( l_float_X + l_float_Y + l_float_Z ) / a_float_Speed );
}

float CDeprecatedObject::Move ( tVector* a_Position, float a_float_Speed )
{
	this->m_Position.X = a_Position->X;
	this->m_Position.Y = a_Position->Y;
	this->m_Position.Z = a_Position->Z;

	this->m_float_MoveSpeed = a_float_Speed;
	this->m_uint8_IsMoving |= 1;
	
	float l_float_X = ( ( a_Position->X - this->m_Position.X ) * ( a_Position->X - this->m_Position.X ) );
	float l_float_Y = ( ( a_Position->Y - this->m_Position.Y ) * ( a_Position->Y - this->m_Position.Y ) );
	float l_float_Z = ( ( a_Position->Z - this->m_Position.Z ) * ( a_Position->Z - this->m_Position.Z ) );
	
	return ( sqrt ( l_float_X + l_float_Y + l_float_Z ) / a_float_Speed );
}

void CDeprecatedObject::Stop ( void )
{
	this->m_uint8_IsMoving &= 0xFEu;
}

float CDeprecatedObject::DistanceRemaining()
{
	float fSX, fSY, fSZ;
	fSX = (this->m_Position.X - this->m_targetMatrix.pos.X) * (this->m_Position.X - this->m_targetMatrix.pos.X);
	fSY = (this->m_Position.Y - this->m_targetMatrix.pos.Y) * (this->m_Position.Y - this->m_targetMatrix.pos.Y);
	fSZ = (this->m_Position.Z - this->m_targetMatrix.pos.Z) * (this->m_Position.Z - this->m_targetMatrix.pos.Z);
	return (float)sqrt(fSX + fSY + fSZ);
}

int CDeprecatedObject::Process(float time)
{
	int ret = 0;

	if (this->m_uint8_IsMoving & 1)
	{
		float distance = time * this->m_float_MoveSpeed;
		float remaining = this->DistanceRemaining();
		if (distance >= remaining)
		{
			ret |= 1;
			this->m_uint8_IsMoving &= ~1;
			this->m_Position.X = this->m_targetMatrix.pos.X;
			this->m_Position.Y = this->m_targetMatrix.pos.Y;
			this->m_Position.Z = this->m_targetMatrix.pos.Z;
		}
		else
		{
			remaining /= distance;
			this->m_Position.X += (this->m_targetMatrix.pos.X - this->m_Position.X) / remaining;
			this->m_Position.Y += (this->m_targetMatrix.pos.Y - this->m_Position.Y) / remaining;
			this->m_Position.Z += (this->m_targetMatrix.pos.Z - this->m_Position.Z) / remaining;
		}
	}
	return ret;
}
