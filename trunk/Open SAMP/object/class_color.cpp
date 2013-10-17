#include "../main.h"

tColor::tColor()
{
	this->R = 0;
	this->G = 0;
	this->B = 0;
	this->A = 0;
	this->RGBA = 0x00000000;
}

tColor::tColor ( uint8_t a_uint8_R, uint8_t a_uint8_G, uint8_t a_uint8_B, uint8_t a_uint8_A )
{
	this->R = a_uint8_R;
	this->G = a_uint8_G;
	this->B = a_uint8_B;
	this->A = a_uint8_A;
	this->RGBA = ( ( ( a_uint8_R & 0xFF ) << 24 ) | ( ( a_uint8_G & 0xFF ) << 16 ) | ( ( a_uint8_B & 0xFF ) << 8 ) | ( a_uint8_A & 0xFF ) );
};

tColor::tColor ( uint32_t a_uint32_RGBA )
{
	this->R = a_uint32_RGBA >> 24;
	this->G = ( a_uint32_RGBA >> 16 ) & 0xFF;
	this->B = ( a_uint32_RGBA >> 8 ) & 0xFF;
	this->A = a_uint32_RGBA & 0xFF;
	this->RGBA = a_uint32_RGBA;
}

tColor::~tColor()
{

}
