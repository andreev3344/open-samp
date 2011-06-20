#ifndef __MAIN_H_
#define __MAIN_H_

#include "stdio.h"
#include <Windows.h>



typedef void (*logprintf_t)(char* format, ...);
extern logprintf_t logprintf;

typedef unsigned long	uint32_t;
typedef long			int32_t;
typedef unsigned short	uint16_t;
typedef short			int16_t;
typedef unsigned char	uint8_t;
typedef char			int8_t;


#include "pool/class_pickuppool.h"
#include "pool/class_gangzonepool.h"


#include "raknet/BitStream.h"

extern CPickupPool* __PickupPool;
extern CGangZonePool* __GangZonePool;

extern uint32_t __NetGame;

// __MAIN_H_
#endif