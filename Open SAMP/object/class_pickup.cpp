#include "../main.h"
#include "class_radaricon.h"

CPickup::~CPickup()
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementPickupDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_HidePickupForPlayer, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}

void CPickup::SetElementOwner ( uint16_t a_uint16_ElementOwner )
{
	CElement::SetElementOwner ( a_uint16_ElementOwner );

	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementPickupDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_HidePickupForPlayer, l_BitStream, 0xFFFF, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	if ( a_uint16_ElementOwner == 0 )
		this->InitializeForAll();
	else
		this->InitializeForPlayer ( a_uint16_ElementOwner );
}

void CPickup::SetPosition ( tVector* a_Position )
{
	CElement::SetPosition ( a_Position );

	RakNet::BitStream* l_BitStream = NULL;
	
	l_BitStream = ComputeBitStream_ElementPickupDestroy();
	if ( l_BitStream )
	{
		if ( this->m_uint16_ElementOwner == 0 )
			__NetGame->GlobalRPC ( RPC_HidePickupForPlayer, l_BitStream, 0xFFFF, 2 );
		else
			__NetGame->PlayerRPC ( RPC_HidePickupForPlayer, l_BitStream, this->m_uint16_ElementOwner, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	l_BitStream = ComputeBitStream_ElementPickupCreate();
	if ( l_BitStream )
	{
		if ( this->m_uint16_ElementOwner == 0 )
			__NetGame->GlobalRPC ( RPC_ShowPickupForPlayer, l_BitStream, 0xFFFF, 2 );
		else
			__NetGame->PlayerRPC ( RPC_ShowPickupForPlayer, l_BitStream, this->m_uint16_ElementOwner, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}
}

void CPickup::UpdatePosition ( void )
{
	CElement::UpdatePosition();

	RakNet::BitStream* l_BitStream = NULL;

	l_BitStream = ComputeBitStream_ElementPickupDestroy();
	if ( l_BitStream )
	{
		if ( this->m_uint16_ElementOwner == 0 )
			__NetGame->GlobalRPC ( RPC_HidePickupForPlayer, l_BitStream, 0xFFFF, 2 );
		else
			__NetGame->PlayerRPC ( RPC_HidePickupForPlayer, l_BitStream, this->m_uint16_ElementOwner, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	l_BitStream = ComputeBitStream_ElementPickupCreate();
	if ( l_BitStream )
	{
		if ( this->m_uint16_ElementOwner == 0 )
			__NetGame->GlobalRPC ( RPC_ShowPickupForPlayer, l_BitStream, 0xFFFF, 2 );
		else
			__NetGame->PlayerRPC ( RPC_ShowPickupForPlayer, l_BitStream, this->m_uint16_ElementOwner, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}
}

void CPickup::InitializeForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	if ( ( this->m_uint16_ElementOwner == 0 ) || ( this->m_uint16_ElementOwner == a_uint16_PlayerIndex ) )
	{
		RakNet::BitStream* l_BitStream = ComputeBitStream_ElementPickupCreate();
		if ( l_BitStream )
		{
			__NetGame->PlayerRPC ( RPC_ShowPickupForPlayer, l_BitStream, this->m_uint16_ElementOwner, 2 );
		}
	}
}

void CPickup::InitializeForAll ( void )
{
	if ( this->m_uint16_ElementOwner == 0 )
	{
		RakNet::BitStream* l_BitStream = ComputeBitStream_ElementPickupCreate();
		if ( l_BitStream )
		{
			__NetGame->GlobalRPC ( RPC_ShowPickupForPlayer, l_BitStream, 0xFFFF, 2 );
		}
	}
}

void CPickup::ShowForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementPickupCreate();
	if ( l_BitStream )
	{
		__NetGame->PlayerRPC ( RPC_ShowPickupForPlayer, l_BitStream, a_uint16_PlayerIndex, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = a_uint16_PlayerIndex;
	}
}

void CPickup::ShowForAll ( void )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementPickupCreate();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_ShowPickupForPlayer, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}

void CPickup::HideForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementPickupDestroy();
	if ( l_BitStream )
	{
		__NetGame->PlayerRPC ( RPC_HidePickupForPlayer, l_BitStream, a_uint16_PlayerIndex, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}

void CPickup::HideForAll ( void )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementPickupDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_HidePickupForPlayer, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}