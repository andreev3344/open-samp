#include "../main.h"
#include "class_radaricon.h"

CRadarZone::~CRadarZone()
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarZoneDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_RemoveGangZone, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}

void CRadarZone::SetElementOwner ( uint16_t a_uint16_ElementOwner )
{
	CElement::SetElementOwner ( a_uint16_ElementOwner );

	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarZoneDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_RemoveGangZone, l_BitStream, 0xFFFF, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	if ( a_uint16_ElementOwner == 0 )
		this->InitializeForAll();
	else
		this->InitializeForPlayer ( a_uint16_ElementOwner );
}

void CRadarZone::SetPosition ( tVector* a_Position )
{
	CElement::SetPosition ( a_Position );

	RakNet::BitStream* l_BitStream = NULL;
	
	l_BitStream = ComputeBitStream_ElementRadarZoneDestroy();
	if ( l_BitStream )
	{
		if ( this->m_uint16_ElementOwner == 0 )
			__NetGame->GlobalRPC ( RPC_RemoveGangZone, l_BitStream, 0xFFFF, 2 );
		else
			__NetGame->PlayerRPC ( RPC_RemoveGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	l_BitStream = ComputeBitStream_ElementRadarZoneCreate();
	if ( l_BitStream )
	{
		if ( this->m_uint16_ElementOwner == 0 )
			__NetGame->GlobalRPC ( RPC_AddGangZone, l_BitStream, 0xFFFF, 2 );
		else
			__NetGame->PlayerRPC ( RPC_AddGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	if ( this->m_bool_Flashing )
	{
		RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarZoneFlash();
		if ( l_BitStream )
		{
			if ( this->m_uint16_ElementOwner == 0 )
				__NetGame->GlobalRPC ( RPC_FlashGangZone, l_BitStream, 0xFFFF, 2 );
			else
				__NetGame->PlayerRPC ( RPC_FlashGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

			delete l_BitStream;
			l_BitStream = NULL;
		}
	}
}

void CRadarZone::UpdatePosition ( void )
{
	CElement::UpdatePosition();

	RakNet::BitStream* l_BitStream = NULL;

	l_BitStream = ComputeBitStream_ElementRadarZoneDestroy();
	if ( l_BitStream )
	{
		if ( this->m_uint16_ElementOwner == 0 )
			__NetGame->GlobalRPC ( RPC_RemoveGangZone, l_BitStream, 0xFFFF, 2 );
		else
			__NetGame->PlayerRPC ( RPC_RemoveGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	l_BitStream = ComputeBitStream_ElementRadarZoneCreate();
	if ( l_BitStream )
	{
		if ( this->m_uint16_ElementOwner == 0 )
			__NetGame->GlobalRPC ( RPC_AddGangZone, l_BitStream, 0xFFFF, 2 );
		else
			__NetGame->PlayerRPC ( RPC_AddGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	if ( this->m_bool_Flashing )
	{
		RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarZoneFlash();
		if ( l_BitStream )
		{
			if ( this->m_uint16_ElementOwner == 0 )
				__NetGame->GlobalRPC ( RPC_FlashGangZone, l_BitStream, 0xFFFF, 2 );
			else
				__NetGame->PlayerRPC ( RPC_FlashGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

			delete l_BitStream;
			l_BitStream = NULL;
		}
	}
}

void CRadarZone::SetSize ( tVector* a_Size )
{
	this->m_Size = *a_Size;

	RakNet::BitStream* l_BitStream = NULL;

	l_BitStream = ComputeBitStream_ElementRadarZoneDestroy();
	if ( l_BitStream )
	{
		if ( this->m_uint16_ElementOwner == 0 )
			__NetGame->GlobalRPC ( RPC_RemoveGangZone, l_BitStream, 0xFFFF, 2 );
		else
			__NetGame->PlayerRPC ( RPC_RemoveGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	l_BitStream = ComputeBitStream_ElementRadarZoneCreate();
	if ( l_BitStream )
	{
		if ( this->m_uint16_ElementOwner == 0 )
			__NetGame->GlobalRPC ( RPC_AddGangZone, l_BitStream, 0xFFFF, 2 );
		else
			__NetGame->PlayerRPC ( RPC_AddGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	if ( this->m_bool_Flashing )
	{
		RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarZoneFlash();
		if ( l_BitStream )
		{
			if ( this->m_uint16_ElementOwner == 0 )
				__NetGame->GlobalRPC ( RPC_FlashGangZone, l_BitStream, 0xFFFF, 2 );
			else
				__NetGame->PlayerRPC ( RPC_FlashGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

			delete l_BitStream;
			l_BitStream = NULL;
		}
	}
}

tVector* CRadarZone::GetSize ( void )
{
	return &( this->m_Size );
}

tVector* CRadarZone::GetCenter ( void )
{
	return new tVector ( ( ( this->m_Size.X - this->m_Position.X ) / 2 ), ( ( this->m_Size.Y - this->m_Position.Y ) / 2 ), 0.0f );
}

void CRadarZone::SetColor ( uint32_t a_uint32_Color )
{
	this->m_uint32_Color = a_uint32_Color;

	RakNet::BitStream* l_BitStream = NULL;

	l_BitStream = ComputeBitStream_ElementRadarZoneDestroy();
	if ( l_BitStream )
	{
		if ( this->m_uint16_ElementOwner == 0 )
			__NetGame->GlobalRPC ( RPC_RemoveGangZone, l_BitStream, 0xFFFF, 2 );
		else
			__NetGame->PlayerRPC ( RPC_RemoveGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	l_BitStream = ComputeBitStream_ElementRadarZoneCreate();
	if ( l_BitStream )
	{
		if ( this->m_uint16_ElementOwner == 0 )
			__NetGame->GlobalRPC ( RPC_AddGangZone, l_BitStream, 0xFFFF, 2 );
		else
			__NetGame->PlayerRPC ( RPC_AddGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

		delete l_BitStream;
		l_BitStream = NULL;
	}

	if ( this->m_bool_Flashing )
	{
		RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarZoneFlash();
		if ( l_BitStream )
		{
			if ( this->m_uint16_ElementOwner == 0 )
				__NetGame->GlobalRPC ( RPC_FlashGangZone, l_BitStream, 0xFFFF, 2 );
			else
				__NetGame->PlayerRPC ( RPC_FlashGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

			delete l_BitStream;
			l_BitStream = NULL;
		}
	}
}

uint32_t CRadarZone::GetColor ( void )
{
	return this->m_uint32_Color;
}

void CRadarZone::SetFlashingColor ( uint32_t a_uint32_FlashingColor )
{
	this->m_uint32_FlashingColor = a_uint32_FlashingColor;

	if ( this->m_bool_Flashing )
	{
		RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarZoneFlash();
		if ( l_BitStream )
		{
			if ( this->m_uint16_ElementOwner == 0 )
				__NetGame->GlobalRPC ( RPC_FlashGangZone, l_BitStream, 0xFFFF, 2 );
			else
				__NetGame->PlayerRPC ( RPC_FlashGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

			delete l_BitStream;
			l_BitStream = NULL;
		}
	}
}

uint32_t CRadarZone::GetFlashingColor ( void )
{
	return this->m_uint32_FlashingColor;
}

void CRadarZone::SetFlashing ( bool a_bool_Flashing )
{
	this->m_bool_Flashing = a_bool_Flashing;

	RakNet::BitStream* l_BitStream = NULL;

	if ( this->m_bool_Flashing )
	{
		l_BitStream = ComputeBitStream_ElementRadarZoneFlash();
		if ( l_BitStream )
		{
			if ( this->m_uint16_ElementOwner == 0 )
				__NetGame->GlobalRPC ( RPC_FlashGangZone, l_BitStream, 0xFFFF, 2 );
			else
				__NetGame->PlayerRPC ( RPC_FlashGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

			delete l_BitStream;
			l_BitStream = NULL;
		}
	}
	else
	{
		l_BitStream = ComputeBitStream_ElementRadarZoneStopFlash();
		if ( l_BitStream )
		{
			if ( this->m_uint16_ElementOwner == 0 )
				__NetGame->GlobalRPC ( RPC_StopFlashGangZone, l_BitStream, 0xFFFF, 2 );
			else
				__NetGame->PlayerRPC ( RPC_StopFlashGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

			delete l_BitStream;
			l_BitStream = NULL;
		}
	}
}

bool CRadarZone::IsFlashing ( void )
{
	return this->m_bool_Flashing;
}

void CRadarZone::InitializeForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	if ( ( this->m_uint16_ElementOwner == 0 ) || ( this->m_uint16_ElementOwner == a_uint16_PlayerIndex ) )
	{
		RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarZoneCreate();
		if ( l_BitStream )
		{
			__NetGame->PlayerRPC ( RPC_AddGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );
		}

		if ( this->m_bool_Flashing )
		{
			l_BitStream = ComputeBitStream_ElementRadarZoneFlash();
			if ( l_BitStream )
			{
				if ( this->m_uint16_ElementOwner == 0 )
					__NetGame->GlobalRPC ( RPC_FlashGangZone, l_BitStream, 0xFFFF, 2 );
				else
					__NetGame->PlayerRPC ( RPC_FlashGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

				delete l_BitStream;
				l_BitStream = NULL;
			}
		}
		else
		{
			l_BitStream = ComputeBitStream_ElementRadarZoneStopFlash();
			if ( l_BitStream )
			{
				if ( this->m_uint16_ElementOwner == 0 )
					__NetGame->GlobalRPC ( RPC_StopFlashGangZone, l_BitStream, 0xFFFF, 2 );
				else
					__NetGame->PlayerRPC ( RPC_StopFlashGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

				delete l_BitStream;
				l_BitStream = NULL;
			}
		}
	}
}

void CRadarZone::InitializeForAll ( void )
{
	if ( this->m_uint16_ElementOwner == 0 )
	{
		RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarZoneCreate();
		if ( l_BitStream )
		{
			__NetGame->GlobalRPC ( RPC_AddGangZone, l_BitStream, 0xFFFF, 2 );
		}

		if ( this->m_bool_Flashing )
		{
			l_BitStream = ComputeBitStream_ElementRadarZoneFlash();
			if ( l_BitStream )
			{
				if ( this->m_uint16_ElementOwner == 0 )
					__NetGame->GlobalRPC ( RPC_FlashGangZone, l_BitStream, 0xFFFF, 2 );
				else
					__NetGame->PlayerRPC ( RPC_FlashGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

				delete l_BitStream;
				l_BitStream = NULL;
			}
		}
		else
		{
			l_BitStream = ComputeBitStream_ElementRadarZoneStopFlash();
			if ( l_BitStream )
			{
				if ( this->m_uint16_ElementOwner == 0 )
					__NetGame->GlobalRPC ( RPC_StopFlashGangZone, l_BitStream, 0xFFFF, 2 );
				else
					__NetGame->PlayerRPC ( RPC_StopFlashGangZone, l_BitStream, this->m_uint16_ElementOwner, 2 );

				delete l_BitStream;
				l_BitStream = NULL;
			}
		}
	}
}

void CRadarZone::ShowForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarZoneCreate();
	if ( l_BitStream )
	{
		__NetGame->PlayerRPC ( RPC_AddGangZone, l_BitStream, a_uint16_PlayerIndex, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = a_uint16_PlayerIndex;
	}
}

void CRadarZone::ShowForAll ( void )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarZoneCreate();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_AddGangZone, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}

void CRadarZone::HideForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarZoneDestroy();
	if ( l_BitStream )
	{
		__NetGame->PlayerRPC ( RPC_RemoveGangZone, l_BitStream, a_uint16_PlayerIndex, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}

void CRadarZone::HideForAll ( void )
{
	RakNet::BitStream* l_BitStream = ComputeBitStream_ElementRadarZoneDestroy();
	if ( l_BitStream )
	{
		__NetGame->GlobalRPC ( RPC_RemoveGangZone, l_BitStream, 0xFFFF, 2 );
		delete l_BitStream;
		l_BitStream = NULL;

		this->m_uint16_ElementOwner = 0;
	}
}