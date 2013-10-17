#ifndef __CLASS_COLOR_H_
#define __CLASS_COLOR_H_

#define RGBA_HEX(r,g,b,a) ( ( ( r & 0xFF ) << 24 ) | ( ( g & 0xFF ) << 16 ) | ( ( b & 0xFF ) << 8 ) | ( a & 0xFF ) )

class tColor
{
public:

	uint8_t R, G, B, A;
	uint32_t RGBA;

public:

	tColor();
	tColor ( uint8_t a_uint8_R, uint8_t a_uint8_G, uint8_t a_uint8_B, uint8_t a_uint8_A );
	tColor ( uint32_t a_uint32_RGBA );

	~tColor();

	tColor& operator= ( const tColor& a_Color )
	{
		this->R = a_Color.R;
		this->G = a_Color.G;
		this->B = a_Color.B;
		this->A = a_Color.A;
		this->RGBA = a_Color.RGBA;
		return *this;
	}

};

// __CLASS_COLOR_H_
#endif