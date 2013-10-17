#include "../main.h"



CPlayerText3DLabels::CPlayerText3DLabels( )
{
	this->ownerID = -1;
	memset( this->TextLabels, 0x00, sizeof( tPlayerText3DLabels ) * MAX_TEXT_LABELS );
	memset( this->isCreated, FALSE, sizeof( BOOL ) * MAX_TEXT_LABELS );
}

CPlayerText3DLabels::~CPlayerText3DLabels( )
{
	for(_Text3DID i = 0; i < MAX_TEXT_LABELS; i++) 
	{
		if(this->GetSlotState(i)) 
            this->Delete(i);
	}
}


bool CPlayerText3DLabels::GetSlotState( _Text3DID labelID )
{
	if( 0 > labelID || labelID >= MAX_TEXT_LABELS ) return false;
	return ( this->isCreated[ labelID ] ? true : false );
}

_Text3DID CPlayerText3DLabels::New( char* text, uint32_t color, float posX, float posY, float posZ, float drawDistance, _PlayerID attachedToPlayer, _VehicleID attachedToVehicle, bool testLOS  )
{
	_Text3DID labelID = 0;
	
	while( labelID <= MAX_TEXT_LABELS  )
	{
		if( this->GetSlotState( labelID ) == false ) break;
		labelID ++;
	}

	if( labelID >= MAX_TEXT_LABELS ) return 0xFFFF;

	if( this->TextLabels[ labelID ].text )
		delete this->TextLabels[ labelID ].text;

	this->TextLabels[ labelID ].text = new char[ strlen( text ) + 1 ];
	strcpy( this->TextLabels[ labelID ].text, text );

	this->TextLabels[ labelID ].color				= color;
	this->TextLabels[ labelID ].posX				= posX;
	this->TextLabels[ labelID ].posY				= posY;
	this->TextLabels[ labelID ].posZ				= posZ;
	this->TextLabels[ labelID ].useLineOfSight		= testLOS;
	this->TextLabels[ labelID ].virtualWorld		= -1;
	this->TextLabels[ labelID ].drawDistance		= drawDistance;
	this->TextLabels[ labelID ].attachedToPlayerID	= attachedToPlayer;
	this->TextLabels[ labelID ].attachedToVehicleID	= attachedToVehicle;
	this->isCreated[ labelID ]						= TRUE;

	show( labelID );

	return labelID;
}

void CPlayerText3DLabels::Delete( _Text3DID labelID )
{
	if( GetSlotState( labelID ) )
	{
		hide( labelID );
		if( this->TextLabels[ labelID ].text )
			delete this->TextLabels[ labelID ].text;
		memset( &this->TextLabels[ labelID ], 0x00, sizeof( tPlayerText3DLabels ) );
		this->isCreated[ labelID ] = FALSE;
	}
}

void CPlayerText3DLabels::UpdateText( _Text3DID labelID, uint32_t color, char* text )
{
	if( GetSlotState( labelID ) )
	{

		if( this->TextLabels[ labelID ].text )
			delete this->TextLabels[ labelID ].text;

		this->TextLabels[ labelID ].text = new char[ strlen( text ) + 1 ];
		strcpy( this->TextLabels[ labelID ].text, text );
		this->TextLabels[ labelID ].color = color;

		hide( labelID );
		show( labelID );

	}
}

void CPlayerText3DLabels::hide( _Text3DID labelID )
{
	if( GetSlotState( labelID ) )
	{
		RakNet::BitStream bStream;
		bStream.Write( ( _Text3DID ) labelID + MAX_TEXT_LABELS );
		__NetGame->PlayerRPC( RPC_HideText3DLabel, &bStream, this->ownerID, 2 );
	}
}

void CPlayerText3DLabels::show( _Text3DID labelID )
{
	if( GetSlotState( labelID ) )
	{
		RakNet::BitStream bStream;
		bStream.Write( ( _Text3DID ) labelID + MAX_TEXT_LABELS  );
		bStream.Write( ( float ) this->TextLabels[ labelID ].posX );
		bStream.Write( ( float ) this->TextLabels[ labelID ].posY );
		bStream.Write( ( float ) this->TextLabels[ labelID ].posZ );
		bStream.Write( ( float ) this->TextLabels[ labelID ].drawDistance );
		bStream.Write( ( bool ) this->TextLabels[ labelID ].useLineOfSight );
		bStream.Write( ( _PlayerID ) this->TextLabels[ labelID ].attachedToPlayerID );
		bStream.Write( ( _VehicleID ) this->TextLabels[ labelID ].attachedToVehicleID );
		stringCompressor->EncodeString( this->TextLabels[ labelID ].text, strlen( this->TextLabels[ labelID ].text ) + 1, &bStream, 0);

		__NetGame->PlayerRPC( RPC_ShowText3DLabels, &bStream, this->ownerID, 2 );
	}
}


void CPlayerText3DLabels::setOwnerID( _PlayerID ownerID )
{
	this->ownerID = ownerID;
}

