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

	int	Create3DTextLabel( char* text, uint32_t color, float x, float y, float z, float drawDistance, uint32_t virtualWorld, bool useLOS );
	int Delete3DTextLabel( int labelID );
	int Update3DTextLabelText( int labelID, uint32_t color, char* text );
	int Attach3DTextLabelToVehicle( int labelID, uint16_t vehicleID, float offsetX, float offsetY, float offsetZ );
	int Attach3DTextLabelPlayer( int labelID, _PlayerID playerID, float offsetX, float offsetY, float offsetZ );

	void showForPlayer( uint16_t labelID, _PlayerID playerID );

	void hideForPlayer( uint16_t labelID, _PlayerID playerID );
	void hideForAll( uint16_t labelID, bool to_update = false );

	CText3DLabels( );
	~CText3DLabels( );
private:


};

#endif