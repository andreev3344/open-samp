#include "../main.h"


CObject::CObject( )
{
}

CObject::~CObject( )
{
}

void CObject::attachToPlayer( _PlayerID playerID, float offsetX, float offsetY, float offsetZ )
{
	__asm
	{
		pushad

		mov ecx, this
		mov ebx, FUNC_COBJECT_ATTACHTOPLAYER
		add ebx, sampBaseAddr

		push offsetZ
		push offsetY
		push offsetX
		push playerID
		call ebx

		popad
	}
}

void CObject::attachToVehicle( _VehicleID vehicleID, float offsetX, float offsetY, float offsetZ ) // offsetZ ?? doesn't appear in IDA
{
	__asm
	{
		pushad

		mov ecx, this
		mov ebx, FUNC_COBJECT_ATTACHTOVEHICLE
		add ebx, sampBaseAddr

		push offsetZ
		push offsetY
		push offsetX
		push vehicleID
		call ebx

		popad
	}
}

void CObject::moveObject( float toPosX, float toPosY, float toPosZ, float speed, float rotX, float rotY, float rotZ )
{
	__asm
	{
		pushad

		mov ecx, this
		mov ebx, FUNC_COBJECT_MOVEOBJECT
		add ebx, sampBaseAddr

		push rotZ
		push rotY
		push rotX
		push speed
		push toPosZ
		push toPosY
		push toPosX
		call ebx

		popad
	}
}

void CObject::stopObject( )
{
	__asm
	{
		pushad

		mov ecx, this
		mov ebx, FUNC_COBJECT_STOPOBJECT
		add ebx, sampBaseAddr
		call ebx
	
		popad
	}

}

void CObject::setObjectRotation( float x, float y, float z )
{
	__asm
	{
		pushad

		mov ecx, this
		mov ebx, FUNC_COBJECT_SETOBJECTROTATION
		add ebx, sampBaseAddr
		push z
		push y
		push x
		call ebx
	
		popad
	}

}