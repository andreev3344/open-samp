#ifndef __TEXT3DLABELS_H__
#define __TEXT3DLABELS_H__




/*
		Class CText3DLabels size 0x9400
*/

typedef struct Text3DLabels_t // size 0x21
{
#pragma pack( 1 )

	char* text;					// + 0x00
	uint32_t color;				// + 0x04
	float posX;					// + 0x08
	float posY;					// + 0x0C
	float posZ;					// + 0x10
	float drawDistance;			// + 0x14
	bool useLineOfSight;		// + 0x18
	uint32_t virtualWorld;			// + 0x19
	uint16_t attachedToPlayerID;	// + 0x1D
	uint16_t attachedToVehicleID;	// + 0x1F
} tText3DLabels;



class CText3DLabels
{
#pragma pack( 1 )
public:

	tText3DLabels		TextLabels[ MAX_TEXT_LABELS ];	// + 0x0000
	BOOL				isCreated[ MAX_TEXT_LABELS ];	// + 0x8400

	_Text3DID	Create3DTextLabel( char* text, uint32_t color, float x, float y, float z, float drawDistance, uint32_t virtualWorld, bool useLOS );
	int Delete3DTextLabel( _Text3DID labelID );
	int Update3DTextLabelText( _Text3DID labelID, uint32_t color, char* text );
	int Attach3DTextLabelToVehicle( _Text3DID labelID, uint16_t vehicleID, float offsetX, float offsetY, float offsetZ );
	int Attach3DTextLabelPlayer( _Text3DID labelID, _PlayerID playerID, float offsetX, float offsetY, float offsetZ );

	void showForPlayer( _Text3DID labelID, _PlayerID playerID );

	void hideForPlayer( _Text3DID labelID, _PlayerID playerID );
	void hideForAll( _Text3DID labelID );
	void updateForAll( _Text3DID labelID );

	bool GetSlotState( _Text3DID labelID );

	CText3DLabels( );
	~CText3DLabels( );
private:


};

#endif