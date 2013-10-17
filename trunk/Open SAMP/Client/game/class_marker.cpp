#include "../main.h"



CMarkers::CMarkers( )
{
//	radarMarkers = *( RadarMarker** )( 0xBA86F0 );
}

CMarkers::~CMarkers()
{


}

void CMarkers::Remove( uint32_t markerID )
{
	uint32_t CMarker_Remove = 0x587CE0;
	_asm
	{
		pushad
		push markerID
		call CMarker_Remove
		popad
	}
}

uint32_t CMarkers::Create( uint32_t unk, float posX, float posY, float posZ, uint32_t unk2, uint32_t unk3 )
{
	uint32_t CMarker_Create = 0x583820;
	uint32_t functionReturn = 0;

	_asm
	{
		pushad
		push unk3
		push unk2
		push posZ
		push posY
		push posX
		push unk
		call CMarker_Create
		mov functionReturn, eax
		popad
	}
	return functionReturn;
}

void CMarkers::SetIcon( uint32_t markerID, uint8_t iconID )
{
	if( 0 > markerID || markerID >= MAX_MARKERS ) return;

	if( ( markerID >> 16 ) ==  this->radarMarkers[ markerID ].wFlag )
	{
		if( IsActive( markerID ) )
		{
			this->radarMarkers[ markerID ].byteIcon = iconID;
		}
	}
}

void CMarkers::SetColour( uint32_t markerID, uint32_t colour )
{
	if( 0 > markerID || markerID >= MAX_MARKERS ) return;

	if( ( markerID >> 16 ) ==  this->radarMarkers[ markerID ].wFlag )
	{
		if( IsActive( markerID ) )
		{
			this->radarMarkers[ markerID ].dwColourID = colour;
		}
	}

}

void CMarkers::SetScaleMode( uint32_t markerID, uint16_t mode )
{
	if( 0 > markerID || markerID >= MAX_MARKERS ) return;
	if( ( markerID >> 16 ) ==  this->radarMarkers[ markerID ].wFlag )
	{
		if( IsActive( markerID ) )
		{
			if ( *(bool*)( 0xBA6748 + 0x59 ) ) // menu.drawRadarOrMap
				mode = 1;
			this->radarMarkers[ markerID ].dwIconSize = mode;
		}
	}
}

bool CMarkers::IsActive( uint32_t markerID )
{
	if( 0 > markerID || markerID >= MAX_MARKERS ) return false;
	return ( bool )( ( this->radarMarkers[ markerID ].byteFlags & 2 ) == 2 );
}