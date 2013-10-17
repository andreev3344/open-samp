#ifndef __MAIN_H_
#define __MAIN_H_

#define _STANDALONE // comment in for plugin version

// #define _BIG_ENDIAN_SYSTEM // comment out for big endian compatibility

// compiled with unicode modifications

#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#ifndef _STANDALONE 
	#include <Windows.h> 
#endif
#include <time.h>
#include <malloc.h>

#include <list>

using namespace std;

#ifdef WIN32
typedef unsigned long	uint32_t;
typedef long			int32_t;
typedef unsigned short	uint16_t;
typedef short			int16_t;
typedef unsigned char	uint8_t;
typedef char			int8_t;
#else
typedef unsigned long	DWORD;
typedef unsigned short	WORD;
typedef unsigned char	BYTE;
typedef int				BOOL;
#endif

#ifdef _STANDALONE

#include "amx/amx.h"

#ifdef WIN32

	#define SLEEP(x) { Sleep(x); }

	#define WIN32_LEAN_AND_MEAN // anti winsock
	#include <Windows.h>
	#include <ShellAPI.h>
	#include <MMSystem.h>
	#include <direct.h>

#elif defined LINUX
	#define SLEEP(x) { usleep(x * 1000); }
	#define MAX_PATH 260

	#include <stdarg.h>

	#include <dlfcn.h>
	#include <unistd.h>
	#include <sys/time.h>
	#include <sys/times.h>
	#include <signal.h>
	#include <execinfo.h>
	#include <ucontext.h>
	#include <sys/types.h>
	#include <sys/sysinfo.h>
	#include <dirent.h>
	#include <sys/mman.h>

	typedef int SOCKET;

	void SignalHandler(int sig, siginfo_t* siginfo, void* uc);
	long GetTickCount();
	char* strlwr(char* str);

	char* itoa(int value, char* result, int base);

	#ifndef stricmp
		#define stricmp strcasecmp
	#endif
#endif


#include "raknet/RakServer.h"
#include "raknet/RakNetworkFactory.h"
#include "raknet/PacketEnumerations.h"
#include "raknet/StringCompressor.h"

#define NETGAME_VERSION		8910
#define SAMP_VERSION "0.3d Open"

void logprintf(char* format, ...);

void RconReply(in_addr clientAddr, SOCKET clientSocket, char* clientData, int clientDataLen, char* reply);
extern uint16_t RconUser;
extern bool bRconReply;

float GetElapsedTime();
/*
int CNetGame__RPC_SendToEveryPlayer( uint32_t a_NetGame, char** a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown );
int CNetGame__RPC_SendToPlayer( uint32_t a_NetGame, char** a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown );
int CNetGame__RPC_SendToStreamedPlayer( uint32_t a_NetGame, char** a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown );
int CNetGame__RPC_SendToPlayerVehicle( uint32_t a_NetGame, char** a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint16_t a_Exclude, uint32_t a_Unknown );
*/
void RegisterRPCs(RakServerInterface* pRakServer);
void UnRegisterRPCs(RakServerInterface* pRakServer);

#define SAFE_DELETE(p)	{ if (p) { delete (p); (p) = NULL; } }
#define SAFE_RELEASE(p)	{ if (p) { (p)->Release(); (p) = NULL; } }
#define ARRAY_SIZE(a)	( sizeof((a)) / sizeof(*(a)) )

#endif

#ifndef _STANDALONE

typedef void (*logprintf_t)(char* format, ...);
extern logprintf_t logprintf;

#endif
/*
typedef struct Vector_t
{
	float X, Y, Z;
} tVector;
*/
class tVector
{
public:

	float X, Y, Z;

	tVector()	{ this->X = 0.0f; this->Y = 0.0f; this->Z = 0.0f; };
	tVector ( float a_float_X, float a_float_Y, float a_float_Z )	{ this->X = a_float_X; this->Y = a_float_Y; this->Z = a_float_Z; };

	tVector& operator= ( const tVector& a_Vector ) { this->X = a_Vector.X; this->Y = a_Vector.Y; this->Z = a_Vector.Z; return *this; }

	tVector operator+ ( const tVector& a_Vector ) const { return tVector ( this->X + a_Vector.X, this->Y + a_Vector.Y, this->Z + a_Vector.Z ); }
	tVector& operator+= ( const tVector& a_Vector ) { this->X += a_Vector.X; this->Y += a_Vector.Y; this->Z+= a_Vector.Z; return *this; };

	tVector operator- ( const tVector& a_Vector ) const { return tVector ( this->X - a_Vector.X, this->Y - a_Vector.Y, this->Z - a_Vector.Z ); }
	tVector& operator-= ( const tVector& a_Vector ) { this->X -= a_Vector.X; this->Y -= a_Vector.Y; this->Z -= a_Vector.Z; return *this; };

	tVector operator* ( const tVector& a_Vector ) const { return tVector ( this->X * a_Vector.X, this->Y * a_Vector.Y, this->Z * a_Vector.Z ); }
	tVector& operator*= ( const tVector& a_Vector ) { this->X *= a_Vector.X; this->Y *= a_Vector.Y; this->Z *= a_Vector.Z; return *this; };

	tVector operator/ ( const tVector& a_Vector ) const { return tVector ( this->X / a_Vector.X, this->Y / a_Vector.Y, this->Z / a_Vector.Z ); }
	tVector& operator/= ( const tVector& a_Vector ) { this->X /= a_Vector.X; this->Y /= a_Vector.Y; this->Z /= a_Vector.Z; return *this; };

	tVector operator/ ( const float a_Value ) const { return tVector ( this->X / a_Value, this->Y / a_Value, this->Z / a_Value ); }
	tVector& operator/= ( const float a_Value ) { this->X /= a_Value; this->Y /= a_Value; this->Z /= a_Value; return *this; };

	float GetLength ( void )
	{
		return sqrt ( X * X + Y * Y + Z * Z );
	};
		
	float GetDistanceFrom ( tVector* a_Vector )
	{
		return tVector ( X - a_Vector->X, Y - a_Vector->Y, Z - a_Vector->Z ).GetLength();
	}
};

typedef struct QuaternionVector_t
{
	float W, X, Y, Z;
} tQuaternionVector;

typedef struct _MATRIX4X4
{
	tVector  right;
	uint32_t   flags;
	tVector  up;
	float   pad_u;
	tVector  at;
	float   pad_a;
	tVector  pos;
	float   pad_p;
} MATRIX4X4, *PMATRIX4X4;


typedef uint16_t	_PlayerID;
typedef uint16_t	_VehicleID;
typedef uint16_t	_Text3DID;


#include "raknet/BitStream.h"
#include "raknet/GetTime.h"

#ifndef _STANDALONE

extern int ( __thiscall* CNetGame__RPC_SendToEveryPlayer )( uint32_t a_NetGame, uint32_t* a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown );
extern int ( __thiscall* CNetGame__RPC_SendToPlayer )( uint32_t a_NetGame, uint32_t* a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown );
extern int ( __thiscall* CNetGame__RPC_SendToStreamedPlayer )( uint32_t a_NetGame, uint32_t* a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown );
extern int ( __thiscall* CNetGame__RPC_SendToPlayerVehicle )( uint32_t a_NetGame, uint32_t* a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint16_t a_Exclude, uint32_t a_Unknown );

#endif

void QuaternionToMatrix( float &quaterW, float &quaterX, float &quaterY, float &quaterZ, tVector* right, tVector* up, tVector* at );
void QuaternionToMatrix( tQuaternionVector* quaternion, MATRIX4X4* matrix );
void MatrixToQuaternion( MATRIX4X4* matrix, tQuaternionVector* quaternion );
void MatrixToQuaternion( tVector* right, tVector* up, tVector* at, float &quaterW, float &quaterX, float &quaterY, float &quaterZ );

char* GetAnimationNameByIndex( uint32_t index );


#define MAX_PLAYER_NAME		0x18
#define MAX_PLAYERS			500
#define MAX_VEHICLES		2000
#define MAX_TEXT_LABELS		1024
#define LIMIT_MAX_PICKUPS	2048
#define MAX_MAP_ICON		100
#define MAX_CLIENT_VEHICLES 700
#define MAX_OBJECTS			1000

#define INVALID_PLAYER_ID	0xFFFF

#define PI 3.14159265f


		

#include "RPC.h"

#include "tinyxml/tinyxml.h"

#include "plugin/class_plugins.h"

#include "script/class_scripttimers.h"
#include "script/class_httpclient.h"
#include "script/class_scripthttp.h"

#include "script/class_gmmanager.h"
#include "script/class_fsmanager.h"

#include "object/class_keybinder.h"

#include "object/class_color.h"

#include "object/class_referencecounter.h"

#include "object/class_player_text3dlabels.h"
#include "object/class_player_var.h"
#include "object/class_menu.h"
#include "object/class_element.h"
#include "object/class_deprecated_object.h"
#include "object/class_player.h"
#include "object/class_vehicle.h"

#include "object/class_object.h"
#include "object/class_pickup.h"
#include "object/class_radaricon.h"
#include "object/class_radarzone.h"
#include "object/class_spawnpoint.h"

#include "pool/class_pickuppool.h"
#include "pool/class_deprecated_gangzonepool.h"
#include "pool/class_textdrawpool.h"
#include "pool/class_text3dlabels.h"
#include "pool/class_deprecated_objectpool.h"
#include "pool/class_menupool.h"
#include "pool/class_playerpool.h"
#include "pool/class_vehiclepool.h"

#include "factory/class_element_factory.h"

#include "class_netgame.h"
#include "class_console.h"






extern CPickupPool* __PickupPool;
extern CElementFactory* __ElementFactory;


extern CNetGame*	 __NetGame;
extern CConsole*	 __Console;
extern CPlugins*	 __Plugins;


extern BOOL isGamemodeFinished;

extern bool bScriptDebug;


// __MAIN_H_
#endif