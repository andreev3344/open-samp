#ifndef __CPLAYER_TEXT3DLABELS_H__
#define __CPLAYER_TEXT3DLABELS_H__



typedef struct PlayerText3DLabels_t // size 0x21 exactement la même que tText3DLabels
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
} tPlayerText3DLabels;


class CPlayerText3DLabels // size 0x9802
{
#pragma pack( 1 )
public:

	bool GetSlotState( _Text3DID labelID );
	void setOwnerID( _PlayerID ownerID );

	_Text3DID New( char* text, uint32_t color, float posX, float posY, float posZ, float drawDistance, _PlayerID attachedToPlayer, _VehicleID attachedToVehicle, bool testLOS  );
	void Delete( _Text3DID labelID );

	void UpdateText( _Text3DID labelID, uint32_t color, char* text );
	
	void hide( _Text3DID labelID );
	void show( _Text3DID labelID );

	

	CPlayerText3DLabels( );
	~CPlayerText3DLabels( );
private:
	tPlayerText3DLabels	TextLabels[ MAX_TEXT_LABELS ];	// + 0x0000
	BOOL				isCreated[ MAX_TEXT_LABELS ];	// + 0x8400
	uint8_t				unknown9800[1024];				// + 0x9400
	_PlayerID			ownerID;

};



#endif