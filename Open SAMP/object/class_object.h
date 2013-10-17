#ifndef __CLASS_OBJECT_H_
#define __CLASS_OBJECT_H_

class CObject : public CElement
{
public:

	tVector* m_TargetPosition;
	uint8_t m_uint8_IsMoving;
	float m_float_MoveSpeed;

public:
	
	CObject()
	{
		this->m_uint8_ElementType = ELEMENT_TYPE_OBJECT;

		this->m_uint32_ModelIndex = -1;

		this->m_TargetPosition = NULL;
		this->m_uint8_IsMoving = 0;
		this->m_float_MoveSpeed = 0.0f;
	};
	
	CObject ( uint32_t a_uint32_ModelIndex )
	{
		this->m_uint8_ElementType = ELEMENT_TYPE_OBJECT;

		this->m_uint32_ModelIndex = a_uint32_ModelIndex;

		this->m_TargetPosition = NULL;
		this->m_uint8_IsMoving = 0;
		this->m_float_MoveSpeed = 0.0f;
	};

	~CObject();

	TiXmlElement* SerializeAttribute ( void );
	void UnSerializeAttribute ( TiXmlElement* a_XmlElement );

	void SetElementOwner ( uint16_t a_uint16_ElementOwner );

	bool SetElementModel ( uint32_t a_uint32_ModelIndex );

	void SetRotation ( tVector* a_Rotation );

	void SetPosition ( tVector* a_Position );
	void UpdatePosition ( void );

	float Move ( float a_float_X, float a_float_Y, float a_float_Z, float a_float_Speed );
	float Move ( tVector* a_Position, float a_float_Speed );
	void Stop ( void );

	void InitializeForPlayer ( uint16_t a_uint16_PlayerIndex );
	void InitializeForAll ( void );

	void ShowForPlayer ( uint16_t a_uint16_PlayerIndex );
	void ShowForAll ( void );

	void HideForPlayer ( uint16_t a_uint16_PlayerIndex );
	void HideForAll ( void );

	uint8_t Process ( float a_float_Time );

	inline RakNet::BitStream* ComputeBitStream_ElementObjectSetPosition ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint16_t )( ( ( uint32_t )( this ) ) % 400 ) ); // object index for client
			l_BitStream->Write ( this->m_Position.X );
			l_BitStream->Write ( this->m_Position.Y );
			l_BitStream->Write ( this->m_Position.Z );

		return l_BitStream;
	}

	inline RakNet::BitStream* ComputeBitStream_ElementObjectSetRotation ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint16_t )( ( ( uint32_t )( this ) ) % 400 ) );
			l_BitStream->Write ( this->m_Rotation.X );
			l_BitStream->Write ( this->m_Rotation.Y );
			l_BitStream->Write ( this->m_Rotation.Z );

		return l_BitStream;
	}

	inline RakNet::BitStream* ComputeBitStream_ElementObjectSpawn ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint16_t )( ( ( uint32_t )( this ) ) % 400 ) ); // object index for client
			l_BitStream->Write ( this->m_uint32_ModelIndex );
			l_BitStream->Write ( this->m_Position.X );
			l_BitStream->Write ( this->m_Position.Y );
			l_BitStream->Write ( this->m_Position.Z );
			l_BitStream->Write ( this->m_Rotation.X );
			l_BitStream->Write ( this->m_Rotation.Y );
			l_BitStream->Write ( this->m_Rotation.Z );
			l_BitStream->Write ( ( float )299.0f );
			l_BitStream->Write ( ( uint16_t )-1 ); // attached player
			l_BitStream->Write ( ( uint16_t )-1 ); // attached vehicle

		return l_BitStream;
	}

	inline RakNet::BitStream* ComputeBitStream_ElementObjectMove ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint16_t )( ( ( uint32_t )( this ) ) % 400 ) ); // object index for client
			l_BitStream->Write ( this->m_Position.X );
			l_BitStream->Write ( this->m_Position.Y );
			l_BitStream->Write ( this->m_Position.Z );
			l_BitStream->Write ( this->m_TargetPosition->X );
			l_BitStream->Write ( this->m_TargetPosition->Y );
			l_BitStream->Write ( this->m_TargetPosition->Z );
			l_BitStream->Write ( this->m_float_MoveSpeed );

			//l_BitStream->Write ( this->m_float_MoveSpeed ); // rotX
			//l_BitStream->Write ( this->m_float_MoveSpeed ); // rotY
			//l_BitStream->Write ( this->m_float_MoveSpeed ); // rotZ
		return l_BitStream;
	}

	inline RakNet::BitStream* ComputeBitStream_ElementObjectDestroy ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint16_t )( ( ( uint32_t )( this ) ) % 400 ) ); // object index for client

		return l_BitStream;
	}
};

// __CLASS_OBJECT_H_
#endif