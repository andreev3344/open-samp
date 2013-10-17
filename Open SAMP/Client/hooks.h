#ifndef __HOOKS_H__
#define __HOOKS_H__


void installGTAHooks( );
void installSAMPHooks( );
void __declspec () CChatWindow_AddDebugMessage_Hook();
void __stdcall Packet_ConnectionSucceeded( Packet* packet );
void __stdcall Packet_ConnectionLost( uint32_t netgame_ptr, Packet* packet );
void CGame__DisplayHud(BOOL bDisp);
void CGame__ToggleRadar(int iToggle);

#endif