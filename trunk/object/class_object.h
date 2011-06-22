#ifndef __CLASS_OBJECT_H_
#define __CLASS_OBJECT_H_

class CObject
{
private:

	uint16_t m_uint16_ObjectIndex;		// - 0x0000 - 0000
	uint32_t m_uint32_ModelIndex;		// - 0x0002 - 0002

	uint8_t m_Pad01[ 52 ];				// - 0x0006 - 0006

	tVector m_Position;					// - 0x003A - 0058

	uint8_t m_Pad02[ 4 ];				// - 0x0046 - 0070

	tVector m_Rotation;					// - 0x004A - 0074

public:
	
	CObject()
	{
	};

	~CObject()
	{
	
	};

	void SpawnForPlayer ( uint16_t a_PlayerIndex );

	void SetRotation ( tVector* a_Rotation );
};

// __CLASS_OBJECT_H_
#endif