#include "../main.h"


CCamera::CCamera( )
{
}

CCamera::~CCamera( )
{
}

void CCamera::SetBeforePlayer( )
{
	uint32_t CCamera_SetBeforePlayer = 0x50BD70;
	_asm
	{
		pushad
		mov ecx, CAMERA_SA_STRUCT
		call CCamera_SetBeforePlayer
		popad
	}
}

void CCamera::SetBehindPlayer( )
{
	uint32_t CCamera_SetBehindPlayer = 0x50BD40;
	_asm
	{
		pushad
		mov ecx, CAMERA_SA_STRUCT
		call CCamera_SetBehindPlayer
		popad
	}
}

void CCamera::SetFade( float duration, uint32_t inOut )
{
	uint32_t CCamera_SetFade = 0x50AC20;
	_asm
	{
		pushad
		mov ecx, CAMERA_SA_STRUCT
		push inOut
		push duration
		call CCamera_SetFade
		popad
	}
}

void CCamera::SetFadeColor( uint32_t colorR, uint32_t colorG, uint32_t colorB )
{
	uint32_t CCamera_SetFadeColor = 0x50BF00;
	_asm
	{
		pushad
		mov ecx, CAMERA_SA_STRUCT
		push colorB
		push colorG
		push colorR
		call CCamera_SetFadeColor
		popad
	}
}