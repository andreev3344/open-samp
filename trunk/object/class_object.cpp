#include "../main.h"
#include "class_object.h"

void CObject::SetIndex ( uint16_t a_uint16_ObjectIndex )
{
	this->m_uint16_ObjectIndex = a_uint16_ObjectIndex;
}

void CObject::SpawnForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( this->m_uint16_ObjectIndex );
		l_BitStream.Write ( this->m_uint32_ModelIndex );
		l_BitStream.Write ( this->m_Position.X );
		l_BitStream.Write ( this->m_Position.Y );
		l_BitStream.Write ( this->m_Position.Z );
		l_BitStream.Write ( this->m_Rotation.X );
		l_BitStream.Write ( this->m_Rotation.Y );
		l_BitStream.Write ( this->m_Rotation.Z );
		l_BitStream.Write ( this->m_float_DrawDistance );
		l_BitStream.Write ( this->m_uint16_AttachedVehicleIndex );

	if ( this->m_uint16_AttachedVehicleIndex != -1 )
	{
		l_BitStream.Write ( this->m_AttachedOffset.X );
		l_BitStream.Write ( this->m_AttachedOffset.Y );
		l_BitStream.Write ( this->m_AttachedOffset.Z );
		l_BitStream.Write ( this->m_AttachedRotation.X );
		l_BitStream.Write ( this->m_AttachedRotation.Y );
		l_BitStream.Write ( this->m_AttachedRotation.Z );
	}

	//// TODO: Remove that Shitty !
	__NetGame = *( uint32_t* )( 0x004F6270 );

	uint32_t l_RpcSpawnObject = 0x00000030;
	CNetGame__RPC_SendToPlayer ( __NetGame, &l_RpcSpawnObject, &l_BitStream, a_uint16_PlayerIndex, 2 );
}


void CObject::AttachToVehicle ( uint16_t a_uint16_VehicleIndex, tVector* a_Offset, tVector* a_Rotation )
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

	
		//// TODO: Remove that Shitty !
	__NetGame = *( uint32_t* )( 0x004F6270 );
	
	uint32_t __PlayerPoolEx = *( uint32_t* )( *( uint32_t* )( __NetGame + 0x04 ) );
	if ( __PlayerPoolEx )
	{
		for ( uint16_t l_PlayerIndex = 0; l_PlayerIndex < 500; l_PlayerIndex++ )
		{
			if ( ( *( uint32_t* )( *( uint32_t* )( __NetGame + 4 ) + 4 * l_PlayerIndex ) ) )
			{
				SpawnForPlayer ( l_PlayerIndex );
			}
		}
	}
}

void CObject::SetRotation ( tVector* a_Rotation )
{
	this->m_Rotation.X = a_Rotation->X;
	this->m_Rotation.Y = a_Rotation->Y;
	this->m_Rotation.Z = a_Rotation->Z;
}
	
tVector* CObject::GetRotation ( void )
{
	return &( this->m_Rotation );
}
	
void CObject::SetPosition ( tVector* a_Position )
{
	this->m_Position.X = a_Position->X;
	this->m_Position.Y = a_Position->Y;
	this->m_Position.Z = a_Position->Z;
}

tVector* CObject::GetPosition ( void )
{
	return &( this->m_Position );
}

void CObject::Move ( float a_float_X, float a_float_Y, float a_float_Z, float a_float_Speed )
{
/*
 long double v6; // fst7@1
  long double v7; // fst6@1
  long double v8; // fst5@1
  char v9; // al@1

  v6 = a_float_X - *(float *)(this + 58);
  *(_DWORD *)(this + 134) = LODWORD(a_float_X);
  v7 = a_float_Y - *(float *)(this + 62);
  *(_DWORD *)(this + 142) = LODWORD(a_float_Z);
  v8 = a_float_Z - *(float *)(this + 66);
  v9 = *(_BYTE *)(this + 150);
  *(_DWORD *)(this + 138) = LODWORD(a_float_Y);
  *(_DWORD *)(this + 151) = LODWORD(a_float_Speed);
  *(_BYTE *)(this + 150) = v9 | 1;
  return sqrt(v8 * v8 + v7 * v7 + v6 * v6) / a_float_Speed;
  */
}