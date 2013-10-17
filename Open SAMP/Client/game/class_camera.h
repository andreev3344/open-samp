#ifndef __CLASS_CAMERA_H__
#define __CLASS_CAMERA_H__


#define CAMERA_SA_STRUCT	0xB6F028

class CCamera
{
#pragma pack( 1 )
public:

	CCamera( );
	~CCamera( );

	void SetBeforePlayer( );
	void SetBehindPlayer( );
	void SetFade( float duration, uint32_t inOut );
	void SetFadeColor( uint32_t colorR, uint32_t colorG, uint32_t colorB );

private:
	
};





#endif