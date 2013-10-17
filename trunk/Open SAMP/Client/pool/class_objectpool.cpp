#include "../main.h"


void CObjectPool::Delete( uint16_t objectID )
{
	__asm
	{
		pushad

		mov ecx, this
		mov ebx, FUNC_COBJECTPOOL_DELETE
		add ebx, sampBaseAddr

		push objectID
		call ebx

		popad
	}
}

uint16_t CObjectPool::New( uint16_t objectID, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float viewDistance )
{
	uint16_t retour = 0;

	__asm
	{
		pushad
		
		mov ecx, this
		mov ebx, FUNC_COBJECTPOOL_NEW
		add ebx, sampBaseAddr

		push viewDistance
		push rotZ
		push rotY
		push rotX
		push posZ
		push posY
		push posX
		push objectID

		call ebx
		mov retour, ax

		popad
	}

	return retour;
}

uint32_t CObjectPool::getObjectNumber( )
{
	uint32_t objectNumber = 0;
	for( uint32_t i = 0; i < MAX_OBJECTS; i++ )
	{
		if( this->isSlotUsed[ i ] && this->objects[ i ] > 0 )
		{
			objectNumber++;
		}
	}
	return objectNumber;
}