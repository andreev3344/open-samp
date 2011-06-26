#ifndef __CLASS_OBJECT_H_
#define __CLASS_OBJECT_H_

class CObject;

struct CObjectPool
{
#pragma pack(1)
	BOOL m_bObjectSlotState[400];
	CObject* m_pObjects[400];
};


extern CObjectPool* __ObjectPoolEx;

class CObject
{
public:

	uint16_t m_uint16_ObjectIndex;				// - 0x0000 - 0000
	uint32_t m_uint32_ModelIndex;				// - 0x0002 - 0002

	uint8_t m_Pad01[ 52 ];						// - 0x0006 - 0006

	tVector m_Position;							// - 0x003A - 0058

	uint8_t m_Pad02[ 4 ];						// - 0x0046 - 0070

	tVector m_Rotation;							// - 0x004A - 0074

	uint8_t m_Pad03[ 73 ];						// - 0x0056 - 0086

	float m_Unknown01;							// - 0x009F - 0159 (DrawDistance)

	uint16_t m_uint16_AttachedVehicleIndex;		// - 0x00A3 - 0163

	tVector m_AttachedOffset;					// - 0x00A5 - 0165

	tVector m_AttachedRotation;					// - 0x00B1 - 0177

public:
	
	CObject()
	{
	};

	~CObject()
	{
	
	};

	void SpawnForPlayer ( uint16_t a_uint16_PlayerIndex );

	void AttachToVehicle ( uint16_t a_uint16_VehicleIndex, tVector* a_Offset, tVector* a_Rotation );

	void SetRotation ( tVector* a_Rotation );
	tVector* GetRotation ( void );
	
	void SetPosition ( tVector* a_Position );
	tVector* GetPosition ( void );
};

// __CLASS_OBJECT_H_
#endif