#ifndef __CLASS_RADAR_ICON_H_
#define __CLASS_RADAR_ICON_H_

#define RADAR_ICON_TYPE_LOCAL					0
#define RADAR_ICON_TYPE_GLOBAL					1
#define RADAR_ICON_TYPE_LOCAL_CHECKPOINT		2
#define RADAR_ICON_TYPE_GLOBAL_CHECKPOINT		3

class CRadarIcon : public CElement
{
public:
	
	tColor m_Color;
	uint8_t m_uint8_RadarIconType;

public:
	
	CRadarIcon ( uint32_t a_uint32_ModelIndex = -1, uint32_t a_uint32_Color = 0xFFFFFFFF, uint8_t a_uint8_RadarIconType = RADAR_ICON_TYPE_LOCAL ) : CElement()
	{
		this->m_uint8_ElementType = ELEMENT_TYPE_RADAR_ICON;

		this->m_uint32_ModelIndex = a_uint32_ModelIndex;
		this->m_Color = tColor ( a_uint32_Color );
		this->m_uint8_RadarIconType = a_uint8_RadarIconType;
	};

	~CRadarIcon();

	TiXmlElement* SerializeAttribute ( void );
	void UnSerializeAttribute ( TiXmlElement* a_XmlElement );

	void SetElementOwner ( uint16_t a_uint16_ElementOwner );

	bool SetElementModel ( uint32_t a_uint32_ModelIndex );

	void SetPosition ( tVector* a_Position );
	void UpdatePosition ( void );

	void SetColor ( tColor& a_Color );
	tColor& GetColor ( void );

	void SetRadarIconType ( uint8_t a_uint8_RadarIconType );
	uint8_t GetRadarIconType ( void );

	void InitializeForPlayer ( uint16_t a_uint16_PlayerIndex );
	void InitializeForAll ( void );

	void ShowForPlayer ( uint16_t a_uint16_PlayerIndex );
	void ShowForAll ( void );

	void HideForPlayer ( uint16_t a_uint16_PlayerIndex );
	void HideForAll ( void );

	inline RakNet::BitStream* ComputeBitStream_ElementRadarIconCreate ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint8_t )( ( ( uint32_t )( this ) ) % 100 ) ); // object index for client
			l_BitStream->Write ( this->m_Position.X );
			l_BitStream->Write ( this->m_Position.Y );
			l_BitStream->Write ( this->m_Position.Z );
			l_BitStream->Write ( ( uint8_t )this->m_uint32_ModelIndex );
			l_BitStream->Write ( this->m_Color.RGBA );
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

// __CLASS_RADAR_ICON_H_
#endif