#ifndef __CLASS_PICKUP_H_
#define __CLASS_PICKUP_H_

#define PICKUP_TYPE_NULL		0

class CPickup : public CElement
{
public:

	uint32_t m_uint32_PickupType;

public:
	
	CPickup ( uint32_t a_uint32_ModelIndex = -1, uint32_t a_uint32_PickupType = PICKUP_TYPE_NULL ) : CElement()
	{
		this->m_uint8_ElementType = ELEMENT_TYPE_PICKUP;

		this->m_uint32_ModelIndex = a_uint32_ModelIndex;
		this->m_uint32_PickupType = a_uint32_PickupType;
	};

	~CPickup();

	void SetElementOwner ( uint16_t a_uint16_ElementOwner );

	void SetPosition ( tVector* a_Position );
	void UpdatePosition ( void );

	void InitializeForPlayer ( uint16_t a_uint16_PlayerIndex );
	void InitializeForAll ( void );

	void ShowForPlayer ( uint16_t a_uint16_PlayerIndex );
	void ShowForAll ( void );

	void HideForPlayer ( uint16_t a_uint16_PlayerIndex );
	void HideForAll ( void );

	inline RakNet::BitStream* ComputeBitStream_ElementPickupCreate ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint32_t )( ( ( uint32_t )( this ) ) % 2048 ) ); // object index for client
			l_BitStream->Write ( ( uint32_t )this->m_uint32_ModelIndex );
			l_BitStream->Write ( ( uint32_t )this->m_uint32_PickupType );
			l_BitStream->Write ( this->m_Position.X );
			l_BitStream->Write ( this->m_Position.Y );
			l_BitStream->Write ( this->m_Position.Z );

		return l_BitStream;
	}

	inline RakNet::BitStream* ComputeBitStream_ElementPickupDestroy ( void )
	{
		RakNet::BitStream*
			l_BitStream = new RakNet::BitStream();
			l_BitStream->Write ( ( uint32_t )( ( ( uint32_t )( this ) ) % 2048 ) );

		return l_BitStream;
	}
};

// __CLASS_PICKUP_H_
#endif