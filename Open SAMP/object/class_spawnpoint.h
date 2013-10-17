#ifdef __CLASS_SPAWN_POINT_H_
#define __CLASS_SPAWN_POINT_H_

class CSpawnPoint : public CElement
{
public:
	
	uint8_t m_uint8_Team;
	uint32_t m_uint32_Weapons[ 3 ];
	uint32_t m_uint32_Ammo[ 3 ];

public:
	
	CSpawnPoint ( uint32_t a_uint32_ModelIndex = -1, uint8_t a_uint8_Team = -1, uint32_t a_uint32_Weapons[ 3 ] = { -1, -1, -1 }, uint32_t* a_uint32_Ammo = NULL ) : CElement()
	{
		this->m_uint8_ElementType = ELEMENT_TYPE_RADAR_ICON;

		this->m_uint32_ModelIndex = a_uint32_ModelIndex;
		this->m_uint8_Team = a_uint8_Team;
		memcpy ( this->m_uint32_Weapons, a_uint32_Weapons, ( size_t )( sizeof ( uint32_t ) * 3 ) );
		memcpy ( this->m_uint32_Ammo, a_uint32_Ammo, ( size_t )( sizeof ( uint32_t ) * 3 ) );

	};

	~CSpawnPoint();

	bool SetElementModel ( uint32_t a_uint32_ModelIndex );

	void SetRotation ( tVector* a_Rotation );

	void SetPosition ( tVector* a_Position );
	void UpdatePosition ( void );

	void SetTeam ( uint8_t a_uint8_Team );
	uint8_t GetTeam ( void );

	void SetWeapons ( uint32_t a_uint32_Weapons[ 3 ] );
	uint32_t* GetWeapons ( void );

	void SetAmmo ( uint32_t a_uint32_Ammo[ 3 ] );
	uint32_t* GetAmmo ( void );

	void InitializeForAll ( void );

	inline RakNet::BitStream* ComputeBitStream_ElementRadarIconCreate ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint8_t )( ( ( uint32_t )( this ) ) % 100 ) ); // object index for client
			l_BitStream->Write ( this->m_Position.X );
			l_BitStream->Write ( this->m_Position.Y );
			l_BitStream->Write ( this->m_Position.Z );
			l_BitStream->Write ( ( uint8_t )this->m_uint32_ModelIndex );
			l_BitStream->Write ( this->m_uint32_Color );
			l_BitStream->Write ( this->m_uint8_RadarIconType );

		return l_BitStream;
	}

	inline RakNet::BitStream* ComputeBitStream_ElementRadarIconDestroy ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint8_t )( ( ( uint32_t )( this ) ) % 100 ) );

		return l_BitStream;
	}
};

// __CLASS_SPAWN_POINT_H_
#endif