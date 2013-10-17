#ifndef __ADDR_H__
#define __ADDR_H__

#define Addr_pNetGame						0x2071A8 // CNetGame class
#define Addr_pChatBox						0x2071B8 // CChatWindow class
#define Addr_pCmdWindow						0x2071BC // CcmdWindow class
#define Addr_pDeathWindow					0x2071C0 // CDeathWindow class
#define Addr_pConsole						0x2071B4 // CConsole class
#define Addr_pScriptDialog					0x2071CC // CScriptDialog class
#define Addr_pGame							0x2071E8 // CGame class
#define Addr_pDxutDialog					0x207220 // CDxutDialog class
#define Addr_pDialogResourceManager			0x20721C // CDialogResourceManager class
#define Addr_pSpawnScreen					0x2071A4 // CSpawnScreen class
#define Addr_pAudioStream					0x2071E4 // CAudioStream class
#define Addr_pScoreBoard					0x2071C8 // CScoreBoard class

#define Addr_CGame_DisplayHud_Call			0x0667C8
#define Addr_CChatWindow_AddDebugHook		0x05F570
#define Addr_CNetGame_JmpConnectionSuceeded 0x008F30
#define Addr_CNetGame_CallConnectionLost	0x0094C2


#define CNetGame_ConnectionLost				0x008EB0

#define ArrayRadarColors					0x2046C8
#define Addr_GetRadarColorsPatch			0x9E644

#endif