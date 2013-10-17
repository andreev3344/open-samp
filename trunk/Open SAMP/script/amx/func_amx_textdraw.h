#ifndef __FUNC_AMX_TEXTDRAW_H_
#define __FUNC_AMX_TEXTDRAW_H_
/*
#define FUNC_TextDrawCreate					0x00488490
#define FUNC_TextDrawSetString					0x00488530
#define FUNC_TextDrawLetterSize					0x004885F0
#define FUNC_TextDrawTextSize					0x00488630
#define FUNC_TextDrawAlignment					0x00488670
#define FUNC_TextDrawColor					0x004886B0
#define FUNC_TextDrawUseBox					0x004886F0
#define FUNC_TextDrawBoxColor					0x00488740
#define FUNC_TextDrawSetShadow					0x00488780
#define FUNC_TextDrawSetOutline					0x004887C0
#define FUNC_TextDrawBackgroundColor					0x00488800
#define FUNC_TextDrawFont					0x00488840
#define FUNC_TextDrawSetProportional					0x00488880
#define FUNC_TextDrawShowForPlayer					0x004888D0
#define FUNC_TextDrawShowForAll					0x00488990
#define FUNC_TextDrawHideForPlayer					0x00488930
#define FUNC_TextDrawHideForAll					0x004889D0
#define FUNC_TextDrawDestroy					0x00488A10
*/

/*
extern cell ( __cdecl* _funcTextDrawCreate )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawSetString )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawLetterSize )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawTextSize )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawAlignment )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawColor )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawUseBox )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawBoxColor )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawSetShadow )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawSetOutline )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawBackgroundColor )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawFont )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawSetProportional )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawShowForPlayer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawShowForAll )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawHideForPlayer )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawHideForAll )( AMX* a_AmxInterface, cell* a_Params );
extern cell ( __cdecl* _funcTextDrawDestroy )( AMX* a_AmxInterface, cell* a_Params );
*/


cell AMX_NATIVE_CALL funcTextDrawCreate ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawSetString ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawLetterSize ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawTextSize ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawAlignment ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawColor ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawUseBox ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawBoxColor ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawSetShadow ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawSetOutline ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawBackgroundColor ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawFont ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawSetProportional ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawShowForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawShowForAll ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawHideForPlayer ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawHideForAll ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcTextDrawDestroy ( AMX* a_AmxInterface, cell* a_Params );


#endif