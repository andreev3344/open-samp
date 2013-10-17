#include "../main.h"
#include "class_radaricon.h"

CRadarIcon::~CRadarIcon()
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarIconDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_RemovePlayerMapIcon, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
	}
}


TiXmlElement* CRadarIcon::SerializeAttribute ( void )
{
	TiXmlElement* l_XmlElement = new TiXmlElement ( XML_ELEMENT_RADARICON );
	if ( l_XmlElement )
	{
		l_XmlElement->SetAttribute ( "icon", this->m_uint32_ModelIndex );
		l_XmlElement->SetAttribute ( "type", this->m_uint8_RadarIconType );
		l_XmlElement->SetDoubleAttribute ( "x", this->m_Position.X );
		l_XmlElement->SetDoubleAttribute ( "y", this->m_Position.Y );
		l_XmlElement->SetDoubleAttribute ( "z", this->m_Position.Z );

		l_XmlElement->SetAttribute ( "r", this->m_Color.R );
		l_XmlElement->SetAttribute ( "g", this->m_Color.G );
		l_XmlElement->SetAttribute ( "b", this->m_Color.B );
		l_XmlElement->SetAttribute ( "a", this->m_Color.A );

		return l_XmlElement;
	}
	return NULL;
}
	
void CRadarIcon::UnSerializeAttribute ( TiXmlElement* a_XmlElement )
{
	a_XmlElement->QueryUnsignedAttribute ( "icon", ( unsigned int* )&this->m_uint32_ModelIndex );
	a_XmlElement->QueryUnsignedAttribute ( "type", ( unsigned int* )&this->m_uint8_RadarIconType );

	tVector* l_Position = new tVector();
	if ( l_Position )
	{
		a_XmlElement->QueryFloatAttribute ( "x", &l_Position->X );
		a_XmlElement->QueryFloatAttribute ( "y", &l_Position->Y );
		a_XmlElement->QueryFloatAttribute ( "z", &l_Position->Z );

		this->SetPosition ( l_Position );
	}

	/**
	 *	uint32_t for QueryUnsignedAttribute...
	 */
	uint32_t l_uint32_ColorR, l_uint32_ColorG, l_uint32_ColorB, l_uint32_ColorA = 0; 
	
	a_XmlElement->QueryUnsignedAttribute ( "r", ( unsigned int* )&l_uint32_ColorR );
	a_XmlElement->QueryUnsignedAttribute ( "g", ( unsigned int* )&l_uint32_ColorG );
	a_XmlElement->QueryUnsignedAttribute ( "b", ( unsigned int* )&l_uint32_ColorB );
	a_XmlElement->QueryUnsignedAttribute ( "a", ( unsigned int* )&l_uint32_ColorA );

	this->SetColor ( tColor ( l_uint32_ColorR, l_uint32_ColorG, l_uint32_ColorB, l_uint32_ColorA ) );
}

void CRadarIcon::SetElementOwner ( uint16_t a_uint16_ElementOwner )
{
	CElement::SetElementOwner ( a_uint16_ElementOwner );

	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarIconDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_RemovePlayerMapIcon, l_BitStream, 0xFFFF, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	if ( a_uint16_ElementOwner == 0 )
		this->InitializeForAll();
	else
		this->InitializeForPlayer ( a_uint16_ElementOwner );
}

bool CRadarIcon::SetElementModel ( uint32_t a_uint32_ModelIndex )
{
	bool l_Return = CElement::SetElementModel ( a_uint32_ModelIndex );

	RakNet::BitStream* l_BitStream = NULL;

	l_BitStream = ComputeBitStream_ElementRadarIconDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_RemovePlayerMapIcon, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
	}

	l_BitStream = ComputeBitStream_ElementRadarIconCreate();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_SetPlayerMapIcon, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;
	}
	return l_Return;
}

void CRadarIcon::SetPosition ( tVector* a_Position )
{
	CElement::SetPosition ( a_Position );

	RakNet::BitStream* l_BitStream = NULL;
	
	l_BitStream = ComputeBitStream_ElementRadarIconDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_RemovePlayerMapIcon, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;
	}

	l_BitStream = ComputeBitStream_ElementRadarIconCreate();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_SetPlayerMapIcon, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;
	}
}

void CRadarIcon::UpdatePosition ( void )
{
	CElement::UpdatePosition();

	RakNet::BitStream* l_BitStream = NULL;

	l_BitStream = ComputeBitStream_ElementRadarIconDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_RemovePlayerMapIcon, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;
	}

	l_BitStream = ComputeBitStream_ElementRadarIconCreate();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_SetPlayerMapIcon, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;
	}
}

void CRadarIcon::SetColor ( tColor& a_Color )
{
	this->m_Color = a_Color;

	RakNet::BitStream* l_BitStream = NULL;

	l_BitStream = ComputeBitStream_ElementRadarIconDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_RemovePlayerMapIcon, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;
	}

	l_BitStream = ComputeBitStream_ElementRadarIconCreate();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_SetPlayerMapIcon, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;
	}
}

tColor& CRadarIcon::GetColor ( void )
{
	return this->m_Color;
}

void CRadarIcon::SetRadarIconType ( uint8_t a_uint8_RadarIconType )
{
	this->m_uint8_RadarIconType = a_uint8_RadarIconType;

	RakNet::BitStream* l_BitStream = NULL;

	l_BitStream = ComputeBitStream_ElementRadarIconDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_RemovePlayerMapIcon, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;
	}

	l_BitStream = ComputeBitStream_ElementRadarIconCreate();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_SetPlayerMapIcon, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;
	}
}
	
uint8_t CRadarIcon::GetRadarIconType ( void )
{
	return this->m_uint8_RadarIconType;
}

void CRadarIcon::InitializeForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	if ( ( this->m_uint16_ElementOwner == 0 ) || ( this->m_uint16_ElementOwner == a_uint16_PlayerIndex ) )
	{
		RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarIconCreate();
		if ( l_BitStream )
		{
			__NetGame->PlayerRPC ( RPC_SetPlayerMapIcon, l_BitStream, a_uint16_PlayerIndex, 2 );
			delete l_BitStream;
			l_BitStream = NULL;
		}
	}
}

void CRadarIcon::InitializeForAll ( void )
{
	if ( this->m_uint16_ElementOwner == 0 )
	{
		RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarIconCreate();
		if ( l_BitStream )
		{
			__NetGame->GlobalRPC ( RPC_SetPlayerMapIcon, l_BitStream, 0xFFFF, 2 );
			delete l_BitStream;
			l_BitStream = NULL;
		}
	}
}


void CRadarIcon::ShowForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarIconCreate();
	if ( l_BitStream )
	{
		__NetGame->PlayerRPC ( RPC_SetPlayerMapIcon, l_BitStream, a_uint16_PlayerIndex, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = a_uint16_PlayerIndex;
	}
}

void CRadarIcon::ShowForAll ( void )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarIconCreate();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_SetPlayerMapIcon, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}

void CRadarIcon::HideForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarIconDestroy();
	if ( l_BitStream )
	{
		__NetGame->PlayerRPC ( RPC_RemovePlayerMapIcon, l_BitStream, a_uint16_PlayerIndex, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}

void CRadarIcon::HideForAll ( void )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarIconDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_RemovePlayerMapIcon, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}