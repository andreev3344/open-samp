#include "../../main.h"

#ifndef _STANDALONE
#include "../../../SDK/amx/amx.h"
#endif

#include "../func_amx.h"
#include "func_amx_textdraw.h"



cell AMX_NATIVE_CALL funcTextDrawCreate ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 3 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawCreate()" );
	/*
		Je ne test pas volontairement si il y a bien eu du texte entrée, vu que sur le serveur "original", il n'y a pas ce test
	*/
	char* str = 0; 
	amx_StrParam( a_AmxInterface, a_Params[3], str );	
	
	return __NetGame->textDrawPool->Create( amx_ctof( a_Params[1] ), amx_ctof( a_Params[2] ), str );
}
cell AMX_NATIVE_CALL funcTextDrawSetString ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawSetString()" );
	char* str = 0; 
	amx_StrParam( a_AmxInterface, a_Params[2], str );
	return __NetGame->textDrawPool->setString( (uint16_t)a_Params[1], str );
}
cell AMX_NATIVE_CALL funcTextDrawLetterSize ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 3 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawLetterSize()" );
	return __NetGame->textDrawPool->setLetterSize( (uint16_t)a_Params[1], amx_ctof( a_Params[2] ), amx_ctof( a_Params[3] ) );
}
cell AMX_NATIVE_CALL funcTextDrawTextSize ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 3 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawTextSize()" );
	return __NetGame->textDrawPool->setTextSize( (uint16_t)a_Params[1], amx_ctof( a_Params[2] ), amx_ctof( a_Params[3] ) );
}
cell AMX_NATIVE_CALL funcTextDrawAlignment ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawAlignment()" );
	return __NetGame->textDrawPool->setAlignement( (uint16_t)a_Params[1], (uint8_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawColor ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawColor()" );
	return __NetGame->textDrawPool->setColor( (uint16_t)a_Params[1], a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawUseBox ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawUseBox()" );
	return __NetGame->textDrawPool->setUseBox( (uint16_t)a_Params[1], (uint8_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawBoxColor ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawBoxColor()" );
	return __NetGame->textDrawPool->setDrawBoxColor( (uint16_t)a_Params[1], a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawSetShadow ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawSetShadow()" );
	return __NetGame->textDrawPool->setShadow( (uint16_t)a_Params[1], (uint8_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawSetOutline ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawSetOutline()" );
	return __NetGame->textDrawPool->setOutline( (uint16_t)a_Params[1], (uint8_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawBackgroundColor ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawBackgroundColor()" );
	return __NetGame->textDrawPool->setBackgroundColor( (uint16_t)a_Params[1], a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawFont ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawFont()" );
	return __NetGame->textDrawPool->setFont( (uint16_t)a_Params[1], (uint8_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawSetProportional ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawSetProportional()" );
	return __NetGame->textDrawPool->setProportional( (uint16_t)a_Params[1], (uint8_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawShowForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawShowForPlayer()" );
	return __NetGame->textDrawPool->showForPlayer( (uint16_t)a_Params[1], (uint16_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawShowForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 1 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawShowForAll()" );
	return __NetGame->textDrawPool->showForAll( (uint16_t)a_Params[1] );
}
cell AMX_NATIVE_CALL funcTextDrawHideForPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 2 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawHideForPlayer()" );
	return __NetGame->textDrawPool->hideForPlayer( (uint16_t)a_Params[1], (uint16_t)a_Params[2] );
}
cell AMX_NATIVE_CALL funcTextDrawHideForAll ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 1 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawHideForAll()" );
	return __NetGame->textDrawPool->hideForAll( (uint16_t)a_Params[1] );
}
cell AMX_NATIVE_CALL funcTextDrawDestroy ( AMX* a_AmxInterface, cell* a_Params )
{
	CHECK_PARAMS( 1 );
	if(bScriptDebug) logprintf ( "[Call]-> funcTextDrawDestroy()" );
	return __NetGame->textDrawPool->Destroy( a_Params[1] );
}