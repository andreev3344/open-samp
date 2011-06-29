#ifndef __CLASS_OBJECTPOOL_H_
#define __CLASS_OBJECTPOOL_H_

#define LIMIT_MAX_OBJECT			400
#define LIMIT_MAX_PLAYER_OBJECT		400

struct tObjectPool
{
#pragma pack(1)
	BOOL m_bool_ObjectSlotState[ LIMIT_MAX_OBJECT ];						// - 0x000000 - 000000
	CObject* m_Object[ LIMIT_MAX_OBJECT ];									// - 0x000640 - 001600
												
	BOOL m_bool_PlayerObjectSlotState[ MAX_PLAYERS ][ LIMIT_MAX_PLAYER_OBJECT ];	// - 0x000C80 - 003200
	BOOL m_bool_PlayerObject[ LIMIT_MAX_PLAYER_OBJECT ];					// - 0x0C4180 - 803200
	CObject* m_PlayerObject[ MAX_PLAYERS ][ LIMIT_MAX_PLAYER_OBJECT	];				// - 0x0C4C70 - 804800

};


//extern tObjectPool* __ObjectPoolEx;



class CObjectPool
{
public:

	BOOL m_bool_ObjectSlotState[ LIMIT_MAX_OBJECT ];						// - 0x000000 - 000000
	CObject* m_Object[ LIMIT_MAX_OBJECT ];									// - 0x000640 - 001600
												
	BOOL m_bool_PlayerObjectSlotState[ MAX_PLAYERS ][ LIMIT_MAX_PLAYER_OBJECT ];	// - 0x000C80 - 003200
	BOOL m_bool_PlayerObject[ LIMIT_MAX_PLAYER_OBJECT ];					// - 0x0C4180 - 803200
	CObject* m_PlayerObject[ MAX_PLAYERS ][ LIMIT_MAX_PLAYER_OBJECT	];				// - 0x0C4C70 - 804800

public:

	CObjectPool()
	{
		for ( uint16_t l_uint16_ObjectIndex = 0; l_uint16_ObjectIndex != LIMIT_MAX_OBJECT; l_uint16_ObjectIndex++ )
		{
			this->m_bool_ObjectSlotState[ l_uint16_ObjectIndex ] = FALSE;
			this->m_Object[ l_uint16_ObjectIndex ] = NULL;
			this->m_bool_PlayerObject[ l_uint16_ObjectIndex ] = FALSE;

			for ( uint16_t l_uint16_PlayerIndex = 0; l_uint16_PlayerIndex < 500; l_uint16_PlayerIndex++ )
			{
				this->m_bool_PlayerObjectSlotState[ l_uint16_PlayerIndex ][ l_uint16_ObjectIndex ] = FALSE;
				this->m_PlayerObject[ l_uint16_PlayerIndex ][ l_uint16_ObjectIndex ] = NULL;
			}
		}
	};

	~CObjectPool()
	{
	
	};

	uint16_t New ( uint32_t a_uint32_ModelIndex, tVector* a_Position, tVector* a_Rotation, float a_float_DrawDistance );
	void Delete ( uint16_t a_uint16_ObjectIndex );
};

// __CLASS_OBJECTPOOL_H_
#endif