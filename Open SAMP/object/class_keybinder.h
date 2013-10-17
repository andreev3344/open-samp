#ifndef __CLASS_KEYBINDER_H__
#define __CLASS_KEYBINDER_H__

#define MAX_KEYBIND		40 // je veux pas vraiment imposer de limite, mais pour l'instant on gère comme ça

#define GAMEMODE_KEYBIND_SCRIPT	0x1F

typedef struct KeyBind_t
{
#pragma pack( 1 )

	uint8_t		keyCode;						// Code de la touche

	uint8_t		scriptIdentifier : 5;			// 5 bits pour l'id du filterscript si la touche est enregistré dans un FS ;) 0x1F = GameMode
	uint8_t		isCalledOnPushed : 1;			// 1 - si on dois appeler la fonction quand on appuie sur la touche, 0 - si on l'appele quand on la lache.
	uint8_t		padding : 2;					// ...

	uint32_t	funcIdx;						// Index de la fonction pawn.

} stKeyBind;

class CKeyBinder
{
public:
	CKeyBinder( _PlayerID p_ownerID );
	~CKeyBinder( );

	bool IsValidSlot( uint32_t keyIndex );
	bool IsSlotUsed( uint32_t keyIndex );

	uint32_t BindKey( uint8_t keyCode, bool CallOnPush, uint32_t functionIndex, uint8_t fromScript = -1 ); // -1 pour le gamemode
	bool UnBindKey( uint32_t KeyIndex );

	void RegisterKeyInClient( uint32_t keyIndex );
	void UnregisterKeyInClient( uint32_t keyIndex );

	void KeyPressed( uint32_t keyIndex );

	void OnFilterScriptUnloaded( uint32_t scriptID );
	void OnGameModeUnloaded( );

private:


	_PlayerID	ownerID;
	stKeyBind*	m_KeyBinds[ MAX_KEYBIND ];

};




#endif