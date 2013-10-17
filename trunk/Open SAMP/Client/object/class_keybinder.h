#ifndef __CLASS_KEYBINDER_H__
#define __CLASS_KEYBINDER_H__

#define MAX_KEYBIND		40

#define KEY_STATE_RELEASED	0x40000000
#define KEY_STATE_PRESSED	0x00000000


typedef struct KeyBind_t
{
#pragma pack( 1 )
	uint8_t		keyCode;						// Code de la touche
	bool		callOnPushed;					// Informer le serveur que la touche a été appuye = true, a été laché = false
	bool		hasBeenPressed;
} stKeyBind;


class CKeyBinder
{
public:

	CKeyBinder( );
	~CKeyBinder( );


	void Clear( );

	bool IsValidSlot( uint32_t keyIndex );
	bool IsSlotUsed( uint32_t keyIndex );

	bool BindKey( uint32_t keyIndex, uint8_t keyCode, bool CallOnPush );
	bool UnBindKey( uint32_t KeyIndex );

	void KeyProcessing( uint32_t keycode, uint32_t key_flags ); // http://msdn.microsoft.com/en-us/library/windows/desktop/ms644984%28v=vs.85%29.aspx

	void KeyPressed( uint32_t keyIndex );

private:
	
	stKeyBind*	m_KeyBinds[ MAX_KEYBIND ]; // je peux limite éviter de faire un tableau de pointeur qui bouffe plus que si je fais ça en statique

};


#endif