#ifndef __MAIN_H_
#define __MAIN_H_

#include "stdio.h"
#include <Windows.h>
#include <malloc.h>



typedef void (*logprintf_t)(char* format, ...);
extern logprintf_t logprintf;

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




typedef uint16_t	_PlayerID;

#include "raknet/BitStream.h"
#include "raknet/GetTime.h"

extern int ( __thiscall* CNetGame__RPC_SendToEveryPlayer )( uint32_t a_NetGame, uint32_t* a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown );
extern int ( __thiscall* CNetGame__RPC_SendToPlayer )( uint32_t a_NetGame, uint32_t* a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown );
extern int ( __thiscall* CNetGame__RPC_SendToUnknown )( uint32_t a_NetGame, uint32_t* a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown );

#define MAX_PLAYER_NAME		0x18
#define MAX_PLAYERS			500
#define MAX_VEHICLES		2000
#define MAX_TEXT_LABELS		1024
#define LIMIT_MAX_PICKUPS	2048

#include "object/class_menu.h"
#include "object/class_object.h"
#include "object/class_player.h"


#include "pool/class_pickuppool.h"
#include "pool/class_gangzonepool.h"
#include "pool/class_textdrawpool.h"
#include "pool/class_text3dlabels.h"
#include "pool/class_objectpool.h"
#include "pool/class_menupool.h"
#include "pool/class_playerpool.h"

#include "class_netgame.h"






extern CPickupPool* __PickupPool;
extern CGangZonePool* __GangZonePool;
extern CObjectPool* __ObjectPool;
extern CTextDrawPool* __TextDrawPool;
extern CMenuPool*	__MenuPool;


extern CNetGame*	 __NetGame;


// __MAIN_H_
#endif