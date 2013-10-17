#ifndef __CLASS_RADAR_ZONE_H_
#define __CLASS_RADAR_ZONE_H_

#define RGBA_ABGR(n) (((n >> 24) & 0x000000FF) | ((n >> 8) & 0x0000FF00) | ((n << 8) & 0x00FF0000) | ((n << 24) & 0xFF000000))

class CRadarZone : public CElement
{
public:

	tVector m_Size;
	uint32_t m_uint32_Color;
	uint32_t m_uint32_FlashingColor;

	bool m_bool_Flashing;

public:
	
	CRadarZone ( tVector* a_Position, tVector* a_Size, uint32_t a_uint32_Color = 0xFF0000FF ) : CElement()
	{
		this->m_uint8_ElementType = ELEMENT_TYPE_RADAR_ZONE;

		this->m_Position = *a_Position;
		this->m_Size = *a_Size;
		this->m_uint32_Color = a_uint32_Color;

		this->m_uint32_FlashingColor = a_uint32_Color;
		this->m_bool_Flashing = false;
	};

	~CRadarZone();

	void SetElementOwner ( uint16_t a_uint16_ElementOwner );

	void SetPosition ( tVector* a_Position );
	void UpdatePosition ( void );

	void SetSize ( tVector* a_Size );
	tVector* GetSize ( void );

	tVector* GetCenter ( void );

	void SetColor ( uint32_t a_uint32_Color );
	uint32_t GetColor ( void );

	void SetFlashingColor ( uint32_t a_uint32_FlashColor );
	uint32_t GetFlashingColor ( void );

	void SetFlashing ( bool a_bool_Flash );
	bool IsFlashing ( void );

	void InitializeForPlayer ( uint16_t a_uint16_PlayerIndex );
	void InitializeForAll ( void );

	void ShowForPlayer ( uint16_t a_uint16_PlayerIndex );
	void ShowForAll ( void );

	void HideForPlayer ( uint16_t a_uint16_PlayerIndex );
	void HideForAll ( void );

	inline RakNet::BitStream* ComputeBitStream_ElementRadarZoneCreate ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint16_t )( ( ( uint32_t )( this ) ) % 1024 ) ); // object index for client
			l_BitStream->Write ( this->m_Position.X );
			l_BitStream->Write ( this->m_Position.Y );
			l_BitStream->Write ( ( float )( this->m_Position.X + this->m_Size.X ) );
			l_BitStream->Write ( ( float )( this->m_Position.Y + this->m_Size.Y ) );

			uint32_t l_uint32_Color = RGBA_ABGR ( this->m_uint32_Color );
			l_BitStream->Write ( ( uint32_t )l_uint32_Color );

		return l_BitStream;
	}

	inline RakNet::BitStream* ComputeBitStream_ElementRadarZoneDestroy ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint16_t )( ( ( uint32_t )( this ) ) % 1024 ) );

		return l_BitStream;
	}

	inline RakNet::BitStream* ComputeBitStream_ElementRadarZoneFlash ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint16_t )( ( ( uint32_t )( this ) ) % 1024 ) );

			uint32_t l_uint32_FlashingColor = RGBA_ABGR ( this->m_uint32_FlashingColor );
			l_BitStream->Write ( ( uint32_t )l_uint32_FlashingColor );

		return l_BitStream;
	}
	
	inline RakNet::BitStream* ComputeBitStream_ElementRadarZoneStopFlash ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint16_t )( ( ( uint32_t )( this ) ) % 1024 ) );

		return l_BitStream;
	}
};

// __CLASS_RADAR_ZONE_H_
#endif