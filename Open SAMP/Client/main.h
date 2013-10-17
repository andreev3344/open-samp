#ifndef __MAIN_H__
#define __MAIN_H__



#include <iostream>
#include <Windows.h>
#include <time.h>
#include <process.h>

#include "d3d9/d3d9.h"
#include "d3d9/d3dx9core.h"
#include "d3d9/DXUT/dxstdafx.h"



#include "addr.h"

#include "../raknet/RakClientInterface.h"
#include "../raknet/RakNetworkFactory.h"
#include "../raknet/BitStream.h"
#include "../raknet/PacketEnumerations.h"
#include "RPC.h"

using namespace std;

typedef unsigned long	uint32_t;
typedef long			int32_t;
typedef unsigned short	uint16_t;
typedef short			int16_t;
typedef unsigned char	uint8_t;
typedef char			int8_t;


typedef struct Vector_t
{
	float X, Y, Z;
} tVector;

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

#define GAME_BYTE_MOD		1
#define MAX_PLAYER_NAME		0x18
#define MAX_PLAYERS			1001
#define MAX_VEHICLES		2000
#define MAX_TEXT_LABELS		2048
#define LIMIT_MAX_PICKUPS	4096
#define MAX_MAP_ICON		100
#define MAX_CLIENT_VEHICLES 700
#define MAX_OBJECTS			1000

#define INVALID_PLAYER_ID	0xFFFF
#define NETGAME_VERSION		8910
#define OPEN_SAMP_VERSION	"dev-0.1"

extern uint32_t			sampBaseAddr;
extern void outputDebugText( char* text );

#include "scripting/GameScripting.h"

#include "utils.h"
#include "RPC.h"



#include "game/class_placeable.h"
#include "game/class_entity.h"
#include "game/class_physical.h"

#include "game/class_marker.h"
#include "game/class_camera.h"
#include "game/class_playerped.h"
#include "game/class_game.h"

#include "object/class_vehicle.h"
#include "object/class_localplayer.h"
#include "object/class_player.h"
#include "object/class_chatbox.h"
#include "object/class_cmdwindow.h"
#include "object/class_scriptdialog.h"
#include "object/class_object.h"
#include "object/class_keybinder.h"

#include "pool/class_vehiclepool.h"
#include "pool/class_text3dlabels.h"
#include "pool/class_playerpool.h"
#include "pool/class_objectpool.h"

#include "class_netgame.h" // à inclure en dernier pour quelle ai accès à toute les autres class etc...
#include "hooks.h"

extern CNetGame*					__NetGame;
extern CChatBox*					__ChatBox;
extern CCmdWindow*					__CmdWindow;
extern CDXUTDialog*					__ScriptDialog;
extern CKeyBinder*					__KeyBinder;
extern CDXUTDialogResourceManager* __DialogResourceManager;
extern CGame*						__Game;

extern HINSTANCE					h_dllHistance;
#endif