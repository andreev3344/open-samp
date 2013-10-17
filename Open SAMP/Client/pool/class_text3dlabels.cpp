#include "../main.h"


BOOL CText3DLabelsPool::Delete( _Text3DID labelID )
{
	uint32_t returned = 0;

	_asm
	{
		pushad
		mov edx, FUNC_CTEXT3DLABELSPOOL_Delete
		add edx, sampBaseAddr
		mov ecx, this
		push labelID
		call edx
		mov returned, eax
		popad
	}

	return returned;
}

void CText3DLabelsPool::CreateTextLabel( _Text3DID labelID, char* text, uint32_t color, float posX, float posY, float posZ, float drawDistance, bool useLOS, _PlayerID attachedToPlayerID, _VehicleID attachedToVehicleID )
{

	uint32_t function = sampBaseAddr + FUNC_CTEXT3DLABELSPOOL_CreateTextLabel;
	uint32_t dwThis = ( uint32_t ) this;

	if( dwThis != ( uint32_t )__NetGame->getText3DPool() )
	{
		__ChatBox->addDebugMessage( "error" );
		return;
	}
	_asm
	{
		pushad
		push attachedToVehicleID
		push attachedToPlayerID
		movzx eax, useLOS
		push eax
		push drawDistance
		push posZ
		push posY
		push posX
		push color
		push text
		push labelID
		mov ecx, dwThis
		call function
		popad
	}


	//uint32_t returned = 0; // useless
	//__asm
	//{
	//	pushad
	//	mov edx, FUNC_CTEXT3DLABELSPOOL_CreateTextLabel
	//	add edx, sampBaseAddr
	//	mov ecx, this

	//	push attachedToVehicleID
	//	push attachedToPlayerID
	//	push useLOS
	//	push drawDistance
	//	push posZ
	//	push posY
	//	push posX
	//	push color
	//	push text
	//	push labelID
	//	call edx

	//	mov returned, eax
	//	popad
	//}

	/*		Facilement reprogrammable en C++	*/


}
