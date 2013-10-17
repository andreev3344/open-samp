#ifndef __CLASS_TEXT3DLABELS_H__
#define __CLASS_TEXT3DLABELS_H__


//#define MAX_TEXT_LABELS 2048

#define FUNC_CTEXT3DLABELSPOOL_CreateTextLabel		0x11D0
#define FUNC_CTEXT3DLABELSPOOL_Delete				0x12C0

typedef struct Text3DLabels_t // size 0x1D
{
#pragma pack( 1 )

	char* text;					// + 0x00
	uint32_t color;				// + 0x04
	float posX;					// + 0x08
	float posY;					// + 0x0C
	float posZ;					// + 0x10
	float drawDistance;			// + 0x14
	bool useLineOfSight;		// + 0x18
	uint16_t attachedToPlayerID;	// + 0x19
	uint16_t attachedToVehicleID;	// + 0x1B
} tText3DLabels;

class CText3DLabelsPool
{
#pragma pack( 1 )

public:

	void CreateTextLabel( _Text3DID labelID, char* text, uint32_t color, float posX, float posY, float posZ, float drawDistance, bool useLOS, _PlayerID attachedToPlayerID, _VehicleID attachedToVehicleID ); // 0x11D0
	BOOL Delete( _Text3DID labelID ); // 0x12C0

private:
	tText3DLabels		textLabels[ MAX_TEXT_LABELS ];	// + 0x0000
	BOOL				isCreated[ MAX_TEXT_LABELS ];	// + 0xE800


};



#endif