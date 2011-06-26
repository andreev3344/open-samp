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


#include "raknet/BitStream.h"


extern int ( __thiscall* CNetGame__RPC_SendToEveryPlayer )( uint32_t a_NetGame, uint32_t* a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown );
extern int ( __thiscall* CNetGame__RPC_SendToPlayer )( uint32_t a_NetGame, uint32_t* a_Rpc, RakNet::BitStream* a_BitStream, uint16_t a_Broadcast, uint32_t a_Unknown );


#include "pool/class_pickuppool.h"
#include "pool/class_gangzonepool.h"
#include "pool/class_textdrawpool.h"
#include "pool/class_text3dlabels.h"

#include "object/class_object.h"
#include "pool/class_objectpool.h"






extern CPickupPool* __PickupPool;
extern CGangZonePool* __GangZonePool;
extern CObjectPool* __ObjectPool;
extern CTextDrawPool* __TextDrawPool;

extern uint32_t __NetGame;


// __MAIN_H_
#endif