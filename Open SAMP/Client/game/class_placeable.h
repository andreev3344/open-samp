#ifndef __CLASS_PLACEABLE_H__
#define __CLASS_PLACEABLE_H__


class CPlaceableSA		 // size 0x18
{
#pragma pack( 1 )

public: // TODO Toufik : Faire des setter et getter pour plus de propreté

	void*		___vmt;							// + 0x0000
	tVector		placeable_Translation;			// + 0x0004
	float		placeable_Heading;				// + 0x0010
	MATRIX4X4*	placeable_coords;				// + 0x0014
};


#endif