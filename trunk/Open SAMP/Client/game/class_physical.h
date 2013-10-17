#ifndef __CLASS_PHYSICAL_H__
#define __CLASS_PHYSICAL_H__


// Thanks to the MTA Project 
// http://code.google.com/p/mtasa-blue/

class CPhysicalSA : public CEntitySA
{
#pragma pack( 1 )
public:
    tVector*	physical_Velocity;		// + 0x44
    tVector*	physical_Spin;			// + 0x48
    tVector*	vecUnk3;				// + 0x4C
    tVector*	vecUnk4;				// + 0x50
    tVector*	vecUnk5;				// + 0x54
    tVector*	vecUnk6;				// + 0x58
    float		pad [12];				// + 0x5C
    float		physical_Mass;			// + 0x8C
    float		physical_TurnMass;		// + 0x90

    uint32_t	dwUnk;					// + 0x94
    uint32_t	dwPhysUnk1;				// + 0x98

    float		fElasticity;			// + 0x9C
    float		fBuoyancyConstant;		// + 0xA0
    tVector*	vecCenterOfMass;		// + 0xA4

    uint32_t	dwUnk2;					// + 0xA8
    uint32_t*	unkCPtrNodeDoubleLink;	// + 0xAC
	
    uint8_t		byUnk: 8;				// + 0xB0
    uint8_t		byCollisionRecords: 8;	// + 0xB1
    uint8_t		byUnk2: 8;				// + 0xB2
    uint8_t		byUnk3: 8;				// + 0xB3

    float		pad4 [8];				// + 0xB4

    float		fDistanceTravelled;		// + 0xD4
    float		fDamageImpulseMagnitude;// + 0xD8
    CEntitySA*	damageEntity;			// + 0xDC
	
    uint8_t		pad2[28];				// + 0xE0
    CEntitySA*	pAttachedEntity;		// + 0xFC
    tVector		vecAttachedPosition;    // + 0x100
    tVector		vecAttachedRotation;    // + 0x10C
    uint8_t		pad3[20];				// + 0x118
    float		fLighting;				// + 0x12C col lighting? CPhysical::GetLightingFromCol
    float		fLighting_2;			// + 0x130 added to col lighting in CPhysical::GetTotalLighting
    uint8_t		pad3a[4];				// + 0x134
};

#endif