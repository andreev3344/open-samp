#ifndef __CLASS_GANGZONE_H_
#define __CLASS_GANGZONE_H_

#define LIMIT_MAX_GANGZONE		1024

#define RGBA_ABGR(n) (((n >> 24) & 0x000000FF) | ((n >> 8) & 0x0000FF00) | ((n << 8) & 0x00FF0000) | ((n << 24) & 0xFF000000))

typedef struct GangZone_t
{
#pragma pack(1)
	float m_float_MinX;		// - 0x0000 - 0000
	float m_float_MinY;		// - 0x0004 - 0004
	float m_float_MaxX;		// - 0x0008	- 0008
	float m_float_MaxY;		// - 0x000C - 0012
} tGangZone;				// - 0x0014 - 0020

class CGangZonePool
{
public:

	tGangZone m_GangZone[ LIMIT_MAX_GANGZONE ];
	BOOL m_bool_SlotState[ LIMIT_MAX_GANGZONE ];

public:

	CGangZonePool()
	{
		for ( uint16_t l_uint16_ZoneIndex = 0; l_uint16_ZoneIndex < LIMIT_MAX_GANGZONE; l_uint16_ZoneIndex++ )
		{
			this->m_bool_SlotState[ l_uint16_ZoneIndex ] = 0;
		}
	};

	~CGangZonePool()
	{
	
	};

	uint16_t New ( float a_float_MinX, float a_float_MinY, float a_float_MaxX, float a_float_MaxY );
	void Delete ( uint16_t a_uint16_ZoneIndex );
	
	void ShowForPlayer ( uint16_t a_uint16_PlayerIndex, uint16_t a_uint16_ZoneIndex, uint32_t a_uint32_ZoneColor );
	void ShowForAll ( uint16_t a_uint16_ZoneIndex, uint32_t a_uint32_ZoneColor );

	void HideForPlayer ( uint16_t a_uint8_PlayerIndex, uint16_t a_uint16_ZoneIndex );
	void HideForAll ( uint16_t a_uint16_ZoneIndex );

	void FlashForPlayer ( uint16_t a_uint16_PlayerIndex, uint16_t a_uint16_ZoneIndex, uint32_t a_uint32_ZoneColor );
	void FlashForAll ( uint16_t a_uint16_ZoneIndex, uint32_t a_uint32_ZoneColor );

	void StopFlashForPlayer ( uint16_t a_uint16_PlayerIndex, uint16_t a_uint16_ZoneIndex );
	void StopFlashForAll ( uint16_t a_uint16_ZoneIndex );

	BOOL GetSlotState ( uint16_t a_uint16_ZoneIndex );
};

// __CLASS_GANGZONE_H_
#endif