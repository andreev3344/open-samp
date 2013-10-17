#ifndef __CLASS_MARKER_H__
#define __CLASS_MARKER_H__

#define MAX_MARKERS	175


struct RadarMarker {
	uint32_t	dwColourID;           // 0
	uint32_t*	pEntity;             // 4
	tVector		vecPos;
	//float		fPosX;                // 8
	//float		fPosY;                // 12
	//float		fPosZ;                // 16
	uint16_t	wFlag;                // 20
	uint16_t	_wAlign;              // 22
	float		fUnknown;             // 24 (either 1.0 or 5.0)
	uint32_t	dwIconSize;           // 28
	uint32_t*	pEnterExit;          // 32
	uint8_t		byteIcon;              // 36
	uint8_t		byteFlags;             // 37
	uint8_t		byteType;              // 38
	uint8_t		_bAlign;               // 39
};

class CMarkers 
{
#pragma pack( 1 )
public:

	CMarkers();
	~CMarkers();

	
	uint32_t	Create( uint32_t unk, float posX, float posY, float posZ, uint32_t unk2, uint32_t unk3 );
	void		SetIcon( uint32_t markerID, uint8_t iconID );
	void		SetColour( uint32_t markerID, uint32_t colour );
	void		SetScaleMode( uint32_t markerID, uint16_t mode );
	void		Remove( uint32_t markerID );
	bool		IsActive( uint32_t markerID );

//0x583820 CMarker::Create
//0x5839A0 CMarker::SetAboveEntity
//0x583AB0 CMarker::SetColour
//0x583F00 CMarker::SetEnterExit
//0x583EB0 CMarker::SetFriendOrThreat
//0x583D70 CMarker::SetIcon
//0x583CC0 CMarker::SetIconSize
//0x583D20 CMarker::SetType 


private:

	RadarMarker*		radarMarkers; // @gta 0xBA86F0


};





#endif