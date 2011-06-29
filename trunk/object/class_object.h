#ifndef __CLASS_OBJECT_H_
#define __CLASS_OBJECT_H_

class CObject // Size: 189
{
public:

	uint16_t m_uint16_ObjectIndex;				// - 0x0000 - 0000
	uint32_t m_uint32_ModelIndex;				// - 0x0002 - 0002

	BOOL m_bool_Active;							// - 0x0006 - 0006

	uint8_t m_Pad01[ 48 ];						// - 0x000A - 0010

	tVector m_Position;							// - 0x003A - 0058

	uint8_t m_Pad02[ 4 ];						// - 0x0046 - 0070

	tVector m_Rotation;							// - 0x004A - 0074

	uint8_t m_Pad03[ 64 ];						// - 0x0056 - 0086

	uint8_t m_uint8_IsMoving;					// - 0x0096 - 0150

	float m_float_MoveSpeed;					// - 0x0097 - 0151

	uint8_t m_Pad04[ 4 ];						// - 0x009B - 0155

	float m_float_DrawDistance;					// - 0x009F - 0159

	uint16_t m_uint16_AttachedVehicleIndex;		// - 0x00A3 - 0163

	tVector m_AttachedOffset;					// - 0x00A5 - 0165

	tVector m_AttachedRotation;					// - 0x00B1 - 0177

public:
	
	CObject()
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
	
	CObject ( uint32_t a_uint32_ModelIndex, tVector* a_Position, tVector* a_Rotation, float a_float_DrawDistance = 299.0f )
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

	~CObject()
	{
	
	};

	void SetIndex ( uint16_t a_uint16_ObjectIndex );

	void SpawnForPlayer ( uint16_t a_uint16_PlayerIndex );

	void AttachToVehicle ( uint16_t a_uint16_VehicleIndex, tVector* a_Offset, tVector* a_Rotation );

	void SetRotation ( tVector* a_Rotation );
	tVector* GetRotation ( void );
	
	void SetPosition ( tVector* a_Position );
	tVector* GetPosition ( void );

	float Move ( float a_float_X, float a_float_Y, float a_float_Z, float a_float_Speed );
};

// __CLASS_OBJECT_H_
#endif