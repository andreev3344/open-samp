//----------------------------------------------------------
//
//   SA:MP Multiplayer Modification For GTA:SA
//   Copyright 2004-2007 SA:MP Team
//
//----------------------------------------------------------

#include "../SDK/amx/amx.h"
#include "../SDK/plugincommon.h"

#include "main.h"
#include "pool/class_pickuppool.h"
#include "pool/class_gangzonepool.h"

#include "script/func_amx.h"

//----------------------------------------------------------



logprintf_t logprintf;

typedef CNetGame* (*getNetGame_t)();
getNetGame_t GetNetGame;


int ( __thiscall* CNetGame__RPC_SendToEveryPlayer )( uint32_t a_NetGame, uint32_t* a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown ) = ( int ( __thiscall* )( uint32_t, uint32_t*, RakNet::BitStream*, uint16_t, uint32_t ) )0x00499020;
int ( __thiscall* CNetGame__RPC_SendToPlayer )( uint32_t a_NetGame, uint32_t* a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown ) = ( int ( __thiscall* )( uint32_t, uint32_t*, RakNet::BitStream*, uint16_t, uint32_t ) )0x00499240;
int ( __thiscall* CNetGame__RPC_SendToUnknown )( uint32_t a_NetGame, uint32_t* a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown ) = ( int ( __thiscall* )( uint32_t, uint32_t*, RakNet::BitStream*, uint16_t, uint32_t ) )0x004990D0;
int ( __thiscall* CNetGame__RPC_SendToPlayerVehicle )( uint32_t a_NetGame, uint32_t* a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint16_t a_Exclude, uint32_t a_Unknown ) = ( int ( __thiscall* )( uint32_t, uint32_t*, RakNet::BitStream*, uint16_t, uint16_t, uint32_t ) )0x00499180;

void **ppPluginData;
extern void *pAMXFunctions;

CPickupPool* __PickupPool = NULL;
CGangZonePool* __GangZonePool = NULL;
CObjectPool* __ObjectPool = NULL;
CTextDrawPool* __TextDrawPool = NULL;
CMenuPool*	__MenuPool	= NULL;

CNetGame* __NetGame = NULL;

void QuaternionToMatrix( float &quaterW, float &quaterX, float &quaterY, float &quaterZ, tVector* right, tVector* up, tVector* at )
{
	float SquarredQuaterW = 0.0f, SquarredQuaterX = 0.0f, SquarredQuaterY = 0.0f, SquarredQuaterZ = 0.0f;

	SquarredQuaterW = quaterW * quaterW;
	SquarredQuaterX = quaterX * quaterX;
	SquarredQuaterY = quaterY * quaterY;
	SquarredQuaterZ = quaterZ * quaterZ;
	right->X	= SquarredQuaterX - SquarredQuaterY - SquarredQuaterZ + SquarredQuaterW;
	up->Y		= SquarredQuaterY - SquarredQuaterX - SquarredQuaterZ + SquarredQuaterW;
	at->Z		= SquarredQuaterZ - (SquarredQuaterY + SquarredQuaterX) + SquarredQuaterW;

	float multXY = quaterX * quaterY;
	float multWZ = quaterW * quaterZ;
	up->X		= multWZ + multXY + multWZ + multXY;
	right->Y	= multXY - multWZ + multXY - multWZ;

	float multXZ = quaterX * quaterZ;
	float multWY = quaterW * quaterY;
	at->X		= multXZ - multWY + multXZ - multWY;
	right->Z	= multWY + multXZ + multWY + multXZ;

	float multYZ = quaterY * quaterZ;
	float multWX = quaterW * quaterX;
	at->Y = multWX + multYZ + multWX + multYZ;
	up->Z = multYZ - multWX + multYZ - multWX;
}

void QuaternionToMatrix( tQuaternionVector* quaternion, MATRIX4X4* matrix )
{
	QuaternionToMatrix( quaternion->W, quaternion->X, quaternion->Y, quaternion->Z,
		&matrix->right, &matrix->up, &matrix->at );
}

//----------------------------------------------------------
// The Support() function indicates what possibilities this
// plugin has. The SUPPORTS_VERSION flag is required to check
// for compatibility with the server. 

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

//----------------------------------------------------------
// The Load() function gets passed on exported functions from
// the SA-MP Server, like the AMX Functions and logprintf().
// Should return true if loading the plugin has succeeded.


void HookFunction ( uint32_t a_uint32_Address, uint32_t a_uint32_Function )
{
	uint32_t l_uint32_OldProtect = 0;
    VirtualProtect ( ( LPVOID )a_uint32_Address, 5, PAGE_READWRITE, &l_uint32_OldProtect );

	*( uint8_t* )( a_uint32_Address ) = 0xE9;
	*( uint32_t* )( a_uint32_Address + 0x01 ) = a_uint32_Function - ( a_uint32_Address + 5 );
}

void HookFunctionCall ( uint32_t a_uint32_Address, uint32_t a_uint32_Function )
{
	uint32_t l_uint32_OldProtect = 0;
    VirtualProtect ( ( LPVOID )a_uint32_Address, 5, PAGE_READWRITE, &l_uint32_OldProtect );

	*( uint8_t* )( a_uint32_Address ) = 0xE8;
	*( uint32_t* )( a_uint32_Address + 0x01 ) = a_uint32_Function - ( a_uint32_Address + 5 );
}


//void __cdecl RPC_ClientJoin( RPCParameters* params )
//{
//	logprintf( "Un client à rejoint le serveur, it's now the time to read some informations ;)" );
//
//	RakNet::BitStream bStream( params->input, params->numberOfBitsOfData / 8 + 1, false );
//
//	uint32_t value32;
//	uint16_t value16;
//	uint8_t value8;
//	char str[ 256 ] = "";
//
//	bStream.Read( ( uint32_t ) value32 ); // NetGame version
//	logprintf( "1st value %d 0x%X", value32, value32 );
//	bStream.Read( ( uint8_t ) value8 ); // mod version ? correspond to 1 for San Andreas et 2 or 0 for Myriad ?
//	logprintf( "2nd value %d 0x%X", value8, value8 );
//	bStream.Read( ( uint8_t ) value8 ); // length of the nickname
//	logprintf( "3rd value %d 0x%X", value8, value8 );
//	bStream.Read( str, value8 ); // nickname
//	logprintf( "4th value %s", str );
//	bStream.Read( value32 );		// server ticket
//	logprintf( "5th value %d 0x%X", value32, value32 );
//	bStream.Read( value8 );			// serial len
//	logprintf( "6th value %d 0x%X", value8, value8 );
//	bStream.Read( str, value8 );	// serial
//	logprintf( "7th value %s\n", str );
//	
//
//	__NetGame->playerPool->New( 0, str, "" );
//
//}


PLUGIN_EXPORT bool PLUGIN_CALL Load( void **ppData ) 
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	GetNetGame = (getNetGame_t)ppData[0xE1];

	logprintf( "WE GONNA KILL YOU" );
	
	//uint32_t l_uint32_OldProtect = 0;
 //   VirtualProtect ( ( LPVOID )0x004A0526, 4, PAGE_READWRITE, &l_uint32_OldProtect );


	/* Seulement pour tester quelques petits truc ;) */
	//*( uint32_t* )0x4A0526 = ( uint32_t ) RPC_ClientJoin;

	__PickupPool = new CPickupPool();
	__GangZonePool = new CGangZonePool();
	__ObjectPool = new CObjectPool();
	__TextDrawPool = new CTextDrawPool();
	__MenuPool = new CMenuPool( );
	

	/***
	*	HOOKING PARTY =D
	*
	*/
	/**
	 *	Hook Script.
	 */
	HookFunctionCall ( 0x004807B7, ( uint32_t )amx_CustomInit );
	HookFunctionCall ( 0x00480902, ( uint32_t )amx_CustomInit );
	HookFunctionCall ( 0x00483E7F, ( uint32_t )amx_CustomInit );


	
	
	/*******************************
			DETOURNEMENT SCRIPT
	for ( int i = 0; i < 350; i++ )
	{
		try 
		{
			
			FILE* __File = fopen ( "define.txt", "a" );
			if ( __File )
			{
				fprintf ( __File, "#define FUNC_%s\t\t\t\t\t0x%.8X\n", __NativeList[ i ].name, __NativeList[ i ].func );
				//fprintf ( __File, "#define FUNC_%s\t\t\t\t\t0x00000000\n", __AmxScriptNative[ i ].Name );
				fclose ( __File );
			}

			
			__File = fopen ( "extern_h.txt", "a" );
			if ( __File )
			{
				//printf ( "extern cell ( __cdecl* _%s )( AMX* a_AmxInterface, cell* a_Params );\n", __AmxScriptNative[ i ].funName );
				fprintf ( __File, "extern cell ( __cdecl* _func%s )( AMX* a_AmxInterface, cell* a_Params );\n", __NativeList[ i ].name );
				fclose ( __File );
			}

			__File = fopen ( "proto_h.txt", "a" );
			if ( __File )
			{
				//printf ( "cell AMX_NATIVE_CALL %s ( AMX* a_AmxInterface, cell* a_Params );\n", __AmxScriptNative[ i ].funName );
				fprintf ( __File, "cell AMX_NATIVE_CALL func%s ( AMX* a_AmxInterface, cell* a_Params );\n", __NativeList[ i ].name );
				fclose ( __File );
			}

			__File = fopen ( "proto_c.txt", "a" );
			if ( __File )
			{
				//printf ( "cell ( __cdecl* _%s )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_%s;\n", __AmxScriptNative[ i ].funName, __AmxScriptNative[ i ].Name );
				fprintf ( __File, "cell ( __cdecl* _func%s )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_%s;\n", __NativeList[ i ].name, __NativeList[ i ].name );
				fclose ( __File );
			}

			__File = fopen ( "definition_c.txt", "a" );
			if ( __File )
			{
				//printf ( "cell ( __cdecl* _%s )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_%s;\n", __AmxScriptNative[ i ].funName, __AmxScriptNative[ i ].Name );
			
				fprintf ( __File, "cell AMX_NATIVE_CALL func%s ( AMX* a_AmxInterface, cell* a_Params )\n", __NativeList[ i ].name );
				fprintf ( __File, "{\n" );
				fprintf ( __File, "\tlogprintf ( \"[Call]-> func%s()\" );\n", __NativeList[ i ].name );
				fprintf ( __File, "\treturn _func%s ( a_AmxInterface, a_Params );\n", __NativeList[ i ].name );
				fprintf ( __File, "}\n" );
				fclose ( __File );
			}

			__File = fopen ( "array_c.txt", "a" );
			if ( __File )
			{
				//printf ( "cell ( __cdecl* _%s )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_%s;\n", __AmxScriptNative[ i ].funName, __AmxScriptNative[ i ].Name );
			
				fprintf ( __File, "{ \"%s\",\t\t\t\t\tfunc%s },\t\t\t\t\t// %d\n", __NativeList[ i ].name, __NativeList[ i ].name, i );
				
				fclose ( __File );
			}


			//logprintf ( "Function: %s", __NativeList[ i ].name );
		}
		catch ( ... )
		{

		}
	}

	*******************/
	//*( uint8_t* )( 0x00404D30 ) = 0xE9;
    //*( uint32_t* )( 0x00404D30 + 0x01 ) = ( ( uint32_t )Custom_Amx_Register ) - ( 0x00404D30 + 5 );

	//*( uint8_t* )( 0x00404D30 + 6 ) = 0xC3;

	//memcpy ( ( void* )( __NetGame + 16 ), __PickupPool, 4 );
	//__NetGamePickupPool = __PickupPool;
/*
	uint32_t l_uint32_OldProtect = 0;
    VirtualProtect ( ( LPVOID )0x00484AF9, 5, PAGE_READWRITE, &l_uint32_OldProtect );

	*( uint8_t* )( 0x00484AF9 ) = 0xE9;
    *( uint32_t* )( 0x00484AF9 + 0x01 ) = ( uint32_t )CPickupPool__New - ( 0x00484AF9 + 5 );
/*
	
    VirtualProtect ( ( LPVOID )0x00484AF9, 5, PAGE_READWRITE, &l_uint32_OldProtect );
	*( uint8_t* )( 0x00484B59 ) = 0xE9;
    *( uint32_t* )( 0x00484B59 + 0x01 ) = ( uint32_t )CPickupPool__New - ( 0x00484B59 + 5 );
*/
	return true;
}

//----------------------------------------------------------
// The Unload() function is called when the server shuts down,
// meaning this plugin gets shut down with it.

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
	if ( __PickupPool )
		delete __PickupPool;

	if ( __ObjectPool )
		delete __ObjectPool;

	if ( __GangZonePool )
		delete __GangZonePool;

	if( __MenuPool )
		delete __MenuPool;

	logprintf( "Plugin helloworld.dll got unloaded." );
}

//----------------------------------------------------------
// This is the sourcecode of the HelloWorld pawn native that we
// will be adding. "amx" is a pointer to the AMX-instance that's
// calling the function (e.g. a filterscript) and "params" is
// an array to the passed parameters. The first entry (params[0])
// is equal to  4 * PassedParameters, e.g. 16 for 4 parameters.

// native HelloWorld();
static cell AMX_NATIVE_CALL n_HelloWorld( AMX* amx, cell* params )
{
	logprintf( "Hello World, from the HelloWorld plugin!" );
	return 1;
}

// And an array containing the native function-names and the functions
// specified with them, e.g. HelloWorld -> n_HelloWorld in this example.
AMX_NATIVE_INFO HelloWorldNatives[ ] =
{
	{ "HelloWorld",			n_HelloWorld },
	{ 0,					0 }
};

//----------------------------------------------------------
// The AmxLoad() function gets called when a new gamemode or
// filterscript gets loaded with the server. In here we register
// the native functions we like to add to the scripts.

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) 
{
	if(!__NetGame) __NetGame = GetNetGame();
	//__NetGame = (CNetGame*)( 0x4F6270 );
	return amx_Register( amx, HelloWorldNatives, -1 );
}

//----------------------------------------------------------
// When a gamemode is over or a filterscript gets unloaded, this
// function gets called. No special actions needed in here.

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) 
{
	return AMX_ERR_NONE;
}
