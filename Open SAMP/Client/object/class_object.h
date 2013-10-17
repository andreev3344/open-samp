#ifndef __CLASS_OBJECT_H__
#define __CLASS_OBJECT_H__

#define FUNC_COBJECT_MOVEOBJECT				0x074B0
#define FUNC_COBJECT_STOPOBJECT				0x06920
#define FUNC_COBJECT_ATTACHTOPLAYER			0x96A70
#define FUNC_COBJECT_ATTACHTOVEHICLE		0x969E0
#define FUNC_COBJECT_SETOBJECTROTATION		0x96990


class CObject // size 0x18E
{
public:
	CObject( );
	~CObject( );


	void attachToPlayer( _PlayerID playerID, float offsetX, float offsetY, float offsetZ );
	void attachToVehicle( _VehicleID vehicleID, float offsetX, float offsetY, float offsetZ );
	void moveObject( float toPosX, float toPosY, float toPosZ, float speed, float rotX, float rotY, float rotZ );
	void stopObject( );
	void setObjectRotation( float x, float y, float z );

private:
	

	uint32_t		gtaObjectID;				// + 0x0044


	_VehicleID		attachedToVehicleID;		// + 0x0171
	_PlayerID		attachedToPlayerID;			// + 0x0173
	tVector			attachedOffset;				// + 0x0175

};




#endif