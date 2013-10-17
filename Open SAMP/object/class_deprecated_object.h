#ifndef __CLASS_DEPRECATED_OBJECT_H_
#define __CLASS_DEPRECATED_OBJECT_H_

class CDeprecatedObject
{
private:

	uint16_t m_uint16_ObjectIndex;				// - 0x0000 - 0000

	uint32_t m_uint32_ModelIndex;				// - 0x0002 - 0002

	BOOL m_bool_Active;							// - 0x0006 - 0006

	MATRIX4X4 m_targetMatrix;

	tVector m_Position;
	tVector m_Rotation;

	uint8_t m_uint8_IsMoving;					// - 0x0096 - 0150

	float m_float_MoveSpeed;					// - 0x0097 - 0151

	uint8_t m_Pad04[ 4 ];						// - 0x009B - 0155

	float m_float_DrawDistance;					// - 0x009F - 0159

	uint16_t m_uint16_AttachedVehicleIndex;		// - 0x00A3 - 0163

	tVector m_AttachedOffset;					// - 0x00A5 - 0165

	tVector m_AttachedRotation;					// - 0x00B1 - 0177

public:
	
	CDeprecatedObject()
	{
		this->m_uint32_ModelIndex = -1;

		this->m_bool_Active = FALSE;

		this->m_Position.X = 0.0f;
		this->m_Position.Y = 0.0f;
		this->m_Position.Z = 0.0f;
		this->m_Rotation.X = 0.0f;
		this->m_Rotation.Y = 0.0f;
		this->m_Rotation.Z = 0.0f;

		this->m_uint8_IsMoving = 0;
		this->m_float_MoveSpeed = 0.0f;

		this->m_float_DrawDistance = 299.0f;

		this->m_uint16_AttachedVehicleIndex = -1;

		this->m_AttachedOffset.X = 0.0f;
		this->m_AttachedOffset.Y = 0.0f;
		this->m_AttachedOffset.Z = 0.0f;
		this->m_AttachedRotation.X = 0.0f;
		this->m_AttachedRotation.Y = 0.0f;
		this->m_AttachedRotation.Z = 0.0f;
	};
	
	CDeprecatedObject ( uint32_t a_uint32_ModelIndex, tVector* a_Position, tVector* a_Rotation, float a_float_DrawDistance = 299.0f )
	{
		this->m_uint32_ModelIndex = a_uint32_ModelIndex;

		this->m_bool_Active = TRUE;

		this->m_Position.X = a_Position->X;
		this->m_Position.Y = a_Position->Y;
		this->m_Position.Z = a_Position->Z;
		this->m_Rotation.X = a_Rotation->X;
		this->m_Rotation.Y = a_Rotation->Y;
		this->m_Rotation.Z = a_Rotation->Z;

		this->m_uint8_IsMoving = 0;
		this->m_float_MoveSpeed = 0.0f;

		this->m_float_DrawDistance = a_float_DrawDistance;

		this->m_uint16_AttachedVehicleIndex = -1;

		this->m_AttachedOffset.X = 0.0f;
		this->m_AttachedOffset.Y = 0.0f;
		this->m_AttachedOffset.Z = 0.0f;
		this->m_AttachedRotation.X = 0.0f;
		this->m_AttachedRotation.Y = 0.0f;
		this->m_AttachedRotation.Z = 0.0f;
	};

	~CDeprecatedObject()
	{
	
	};

	BOOL IsActive() { return this->m_bool_Active; };

	void SetObjectIndex ( uint16_t a_uint16_Index );

	void SetRotation ( tVector* a_Rotation );
	tVector* GetRotation ( void );
	
	void SetPosition ( tVector* a_Position );
	tVector* GetPosition ( void );
	
	void SpawnForPlayer ( uint16_t a_uint16_PlayerIndex );
	void SpawnForAll ( void );

	void AttachToVehicle ( uint16_t a_uint16_VehicleIndex, tVector* a_Offset, tVector* a_Rotation );

	float Move ( float a_float_X, float a_float_Y, float a_float_Z, float a_float_Speed );
	float Move ( tVector* a_Position, float a_float_Speed );
	void Stop ( void );

	float DistanceRemaining();
	int Process(float time);

	inline RakNet::BitStream* ComputeBitStream_Spawn ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( this->m_uint16_ObjectIndex );
			l_BitStream->Write ( this->m_uint32_ModelIndex );
			l_BitStream->Write ( this->m_Position.X );
			l_BitStream->Write ( this->m_Position.Y );
			l_BitStream->Write ( this->m_Position.Z );
			l_BitStream->Write ( this->m_Rotation.X );
			l_BitStream->Write ( this->m_Rotation.Y );
			l_BitStream->Write ( this->m_Rotation.Z );
			l_BitStream->Write ( this->m_float_DrawDistance );
			l_BitStream->Write ( this->m_uint16_AttachedVehicleIndex );

		if ( this->m_uint16_AttachedVehicleIndex != -1 )
		{
			l_BitStream->Write ( this->m_AttachedOffset.X );
			l_BitStream->Write ( this->m_AttachedOffset.Y );
			l_BitStream->Write ( this->m_AttachedOffset.Z );
			l_BitStream->Write ( this->m_AttachedRotation.X );
			l_BitStream->Write ( this->m_AttachedRotation.Y );
			l_BitStream->Write ( this->m_AttachedRotation.Z );
		}
		return l_BitStream;
	}

	inline RakNet::BitStream* ComputeBitStream_SetPosition ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( this->m_uint16_ObjectIndex );
			l_BitStream->Write ( this->m_Position.X );
			l_BitStream->Write ( this->m_Position.Y );
			l_BitStream->Write ( this->m_Position.Z );

		return l_BitStream;
	}

	inline RakNet::BitStream* ComputeBitStream_SetRotation ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( this->m_uint16_ObjectIndex );
			l_BitStream->Write ( this->m_Rotation.X );
			l_BitStream->Write ( this->m_Rotation.Y );
			l_BitStream->Write ( this->m_Rotation.Z );

		return l_BitStream;
	}
};

// __CLASS_DEPRECATED_OBJECT_H_
#endif