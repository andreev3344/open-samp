#ifndef __CLASS_PICKUPPOOL_H_
#define __CLASS_PICKUPPOOL_H_



typedef struct Pickup_t
{
#pragma pack(1)
	uint32_t m_uint32_Model;	// - 0x0000 - 0000
	uint32_t m_uint32_Type;		// - 0x0004 - 0004
	float m_float_X;			// - 0x0008	- 0008
	float m_float_Y;			// - 0x000C - 0012
	float m_float_Z;			// - 0x0010 - 0016
} tPickup;						// - 0x0014 - 0020

typedef struct PickupPool_t
{
#pragma pack(1)
	tPickup m_Pickups[ LIMIT_MAX_PICKUPS ];			// - 0x0000 - 0000
	uint32_t m_uint32_PickupCount;					// - 0xA000 - 40960
	uint8_t m_uint8_Active[ LIMIT_MAX_PICKUPS ];	// - 0xA004 - 40964
} tPickupPool;


extern tPickupPool* __PickupPoolEx;


class CPickupPool
{
private:

	tPickup m_Pickups[ LIMIT_MAX_PICKUPS ];			// - 0x0000 - 0000
	uint32_t m_uint32_PickupCount;					// - 0xA000 - 40960
	uint8_t m_uint8_Active[ LIMIT_MAX_PICKUPS ];	// - 0xA004 - 40964
													// - 0xA804 - 43012
public:
	
	CPickupPool()
	{
		this->m_uint32_PickupCount = 0;
		for ( uint32_t i = 0; i < LIMIT_MAX_PICKUPS; i++ )
		{
			this->m_uint8_Active[ i ] = false;
		}
	};

	~CPickupPool()
	{
	
	};

	uint32_t New ( uint32_t a_uint32_Model, uint32_t a_uint32_Type, float a_float_X, float a_float_Y, float a_float_Z, uint8_t a_uint8_Static = 0 );
	uint8_t Destroy ( uint32_t a_uint32_PickupIndex );
	void InitForPlayer ( _PlayerID a_uint8_PlayerIndex );
};

// __CLASS_PICKUPPOOL_H_
#endif