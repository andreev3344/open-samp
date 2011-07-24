#include "../../main.h"
#include "../../../SDK/amx/amx.h"

#include "../func_amx.h"
#include "func_amx_textdraw.h"



cell AMX_NATIVE_CALL funcTextDrawCreate ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 3 );
	logprintf ( "[Call]-> funcTextDrawCreate()" );
	/*
		Je ne test pas volontairement si il y a bien eu du texte entrée, vu que sur le serveur "original", il n'y a pas ce test
	*/
	char* str = 0; 
	amx_StrParam( a_AmxInterface, a_Params[3], str );	
	return __TextDrawPool->Create( amx_ctof( a_Params[1] ), amx_ctof( a_Params[2] ), str );
}
cell AMX_NATIVE_CALL funcTextDrawSetString ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	logprintf ( "[Call]-> funcTextDrawSetString()" );
	char* str = 0; 
	amx_StrParam( a_AmxInterface, a_Params[2], str );
	return __TextDrawPool->setString( (uint16_t)a_Params[1], str );
}
cell AMX_NATIVE_CALL funcTextDrawLetterSize ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 3 );
	logprintf ( "[Call]-> funcTextDrawLetterSize()" );
	return __TextDrawPool->setLetterSize( (uint16_t)a_Params[1], amx_ctof( a_Params[2] ), amx_ctof( a_Params[3] ) );
}
cell AMX_NATIVE_CALL funcTextDrawTextSize ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 3 );
	logprintf ( "[Call]-> funcTextDrawTextSize()" );
	return __TextDrawPool->setTextSize( (uint16_t)a_Params[1], amx_ctof( a_Params[2] ), amx_ctof( a_Params[3] ) );
}
cell AMX_NATIVE_CALL funcTextDrawAlignment ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	logprintf ( "[Call]-> funcTextDrawAlignment()" );
	return __TextDrawPool->setAlignement( (uint16_t)a_Params[1], (uint8_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawColor ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	logprintf ( "[Call]-> funcTextDrawColor()" );
	return __TextDrawPool->setColor( (uint16_t)a_Params[1], a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawUseBox ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	logprintf ( "[Call]-> funcTextDrawUseBox()" );
	return __TextDrawPool->setUseBox( (uint16_t)a_Params[1], (uint8_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawBoxColor ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	logprintf ( "[Call]-> funcTextDrawBoxColor()" );
	return __TextDrawPool->setDrawBoxColor( (uint16_t)a_Params[1], a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawSetShadow ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	logprintf ( "[Call]-> funcTextDrawSetShadow()" );
	return __TextDrawPool->setShadow( (uint16_t)a_Params[1], (uint8_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawSetOutline ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	logprintf ( "[Call]-> funcTextDrawSetOutline()" );
	return __TextDrawPool->setOutline( (uint16_t)a_Params[1], (uint8_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawBackgroundColor ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	logprintf ( "[Call]-> funcTextDrawBackgroundColor()" );
	return __TextDrawPool->setBackgroundColor( (uint16_t)a_Params[1], a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawFont ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	logprintf ( "[Call]-> funcTextDrawFont()" );
	return __TextDrawPool->setFont( (uint16_t)a_Params[1], (uint8_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawSetProportional ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	logprintf ( "[Call]-> funcTextDrawSetProportional()" );
	return __TextDrawPool->setProportional( (uint16_t)a_Params[1], (uint8_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawShowForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	logprintf ( "[Call]-> funcTextDrawShowForPlayer()" );
	return __TextDrawPool->showForPlayer( (uint16_t)a_Params[1], (uint16_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawShowForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 1 );
	logprintf ( "[Call]-> funcTextDrawShowForAll()" );
	return __TextDrawPool->showForAll( (uint16_t)a_Params[1] );
}
cell AMX_NATIVE_CALL funcTextDrawHideForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	logprintf ( "[Call]-> funcTextDrawHideForPlayer()" );
	return __TextDrawPool->hideForPlayer( (uint16_t)a_Params[1], (uint16_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawHideForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 1 );
	logprintf ( "[Call]-> funcTextDrawHideForAll()" );
	return __TextDrawPool->hideForAll( (uint16_t)a_Params[1] );
}
cell AMX_NATIVE_CALL funcTextDrawDestroy ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 1 );
	logprintf ( "[Call]-> funcTextDrawDestroy()" );
	return __TextDrawPool->Destroy( a_Params[1] );
}