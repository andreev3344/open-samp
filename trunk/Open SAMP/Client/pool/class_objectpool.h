#ifndef __CLASS_OBJECTPOOL_H__
#define __CLASS_OBJECTPOOL_H__

#define FUNC_COBJECTPOOL_DELETE		0x0CDD0
#define FUNC_COBJECTPOOL_NEW		0x0CE20


class CObjectPool
{
#pragma pack( 1 )

public:
	CObjectPool( );
	~CObjectPool( );
		
	void Delete( uint16_t objectID );
	uint16_t New( uint16_t objectID, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float viewDistance );

	uint32_t getObjectNumber( );	


private:

	void*			objects[ MAX_OBJECTS ];			// + 0x0000
	BOOL			isSlotUsed[ MAX_OBJECTS ];		// + 0x0FA0


};




#endif