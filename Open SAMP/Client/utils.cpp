#include "main.h"



void DetournCall( uint32_t address, uint32_t functiontoCall )
{
	if( *(uint8_t*)address == 0xE8 ) 
	{
		*(uint32_t*)( address + 0x01 ) = functiontoCall - address + 5;
	}
}

void HookFunction ( uint32_t a_uint32_Address, uint32_t a_uint32_Function )
{
	*( uint8_t* )( a_uint32_Address ) = 0xE9;
	*( uint32_t* )( a_uint32_Address + 0x01 ) = a_uint32_Function - ( a_uint32_Address + 5 );
}