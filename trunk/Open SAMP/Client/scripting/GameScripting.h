/*
	file:
		GameScripting.h
	desc:
		This is the header file for GameScripting.cpp.
*/

#ifndef GAMESCRIPTING_H
#define GAMESCRIPTING_H

#include <Windows.h>
//#include "GameDefines.h"	// Include GameScripting.h and get the game defines too.

// ******


#define MODEL_BGA			"BGA"
#define MODEL_BOUNCA		"BOUNCA"
#define MODEL_BURGER		"BURGER"
#define MODEL_CDRIVRA		"CDRIVRA"
#define MODEL_CDRIVRB		"CDRIVRB"
#define MODEL_CGONA			"CGONA"
#define MODEL_CGONB			"CGONB"
#define MODEL_CHEF			"CHEF"
#define MODEL_CMRAMAN		"CMRAMAN"
#define MODEL_COURIER		"COURIER"
#define MODEL_CREWA			"CREWA"
#define MODEL_CREWB			"CREWB"
#define MODEL_DGOONA		"DGOONA"
#define MODEL_DGOONB		"DGOONB"
#define MODEL_DGOONC		"DGOONC"
#define MODEL_FLOOZYA		"FLOOZYA"
#define MODEL_FLOOZYB		"FLOOZYB"
#define MODEL_FLOOZYC		"FLOOZYC"
#define MODEL_FSFA			"FSFA"
#define MODEL_IGALSCB		"IGALSCB"
#define MODEL_IGBUDDY		"IGBUDDY"
#define MODEL_IGBUDY2		"IGBUDY2"
#define MODEL_IGCANDY		"IGCANDY"
#define MODEL_IGCOLON		"IGCOLON"
#define MODEL_IGDIAZ		"IGDIAZ"
#define MODEL_IGGONZ		"IGGONZ"
#define MODEL_IGHLARY		"IGHLARY"
#define MODEL_IGHLRY2		"IGHLRY2"
#define MODEL_IGKEN			"IGKEN"
#define MODEL_IGMERC		"IGMERC"
#define MODEL_IGMERC2		"IGMERC2"
#define MODEL_IGMIKE		"IGMIKE"
#define MODEL_IGMIKE2		"IGMIKE2"
#define MODEL_IGPHIL		"IGPHIL"
#define MODEL_IGPHIL2		"IGPHIL2"
#define MODEL_IGPHIL3		"IGPHIL3"
#define MODEL_IGSONNY		"IGSONNY"
#define MODEL_MBA			"MBA"
#define MODEL_MBB			"MBB"
#define MODEL_MGOONA		"MGOONA"
#define MODEL_MPORNA		"MPORNA"
#define MODEL_MSERVER		"MSERVER"
#define MODEL_PLAYER		"PLAYER"
#define MODEL_PLAYER1		"PLAYER1"
#define MODEL_PLAYER2		"PLAYER2"
#define MODEL_PLAYER3		"PLAYER3"
#define MODEL_PLAYER4		"PLAYER4"
#define MODEL_PLAYER5		"PLAYER5"
#define MODEL_PLAYER6		"PLAYER6"
#define MODEL_PRINTRA		"PRINTRA"
#define MODEL_PRINTRB		"PRINTRB"
#define MODEL_PRINTRC		"PRINTRC"
#define MODEL_PSYCHO		"PSYCHO"
#define MODEL_S_KEEP		"S_KEEP"
#define MODEL_SAM			"SAM"
#define MODEL_SGC			"SGC"
#define MODEL_SGOONA		"SGOONA"
#define MODEL_SGOONB		"SGOONB"
#define MODEL_SHOOTRA		"SHOOTRA"
#define MODEL_SHOOTRB		"SHOOTRB"
#define MODEL_SPANDXA		"SPANDXA"
#define MODEL_SPANDXB		"SPANDXB"
#define MODEL_STRIPA		"STRIPA"
#define MODEL_STRIPB		"STRIPB"
#define MODEL_SSTRIPC		"STRIPC"

#define CAR_LANDSTAL		130
#define CAR_IDAHO			131
#define CAR_STINGER			132
#define CAR_LINERUN			133
#define CAR_PEREN			134
#define CAR_SENTINEL		135
#define BOAT_RIO			136
#define CAR_FIRETRUK		137
#define CAR_TRASH			138
#define CAR_STRETCH			139
#define CAR_MANANA			140
#define CAR_INFERNUS		141
#define CAR_VOODOO			142
#define CAR_PONY			143
#define CAR_MULE			144
#define CAR_CHEETAH			145
#define CAR_AMBULAN			146
#define CAR_FBICAR			147
#define CAR_MOONBEAM		148
#define CAR_ESPERANT		149
#define CAR_TAXI			150
#define CAR_WASHING			151
#define CAR_BOBCAT			152
#define CAR_MRWHOOP			153
#define CAR_BFINJECT		154
#define CAR_HUNTER			155
#define CAR_POLICE			156
#define CAR_ENFORCER		157
#define CAR_SECURICA		158
#define CAR_BANSHEE			159
#define BOAT_PREDATOR		160
#define CAR_BUS				161
#define CAR_RHINO			162
#define CAR_BARRACKS		163
#define CAR_CUBAN			164
#define HELI_CHOPPER		165
#define BIKE_ANGEL			166
#define CAR_COACH			167
#define CAR_CABBIE			168
#define CAR_STALLION		169
#define CAR_RUMPO			170
#define CAR_RCBANDIT		171
#define CAR_ROMERO			172
#define CAR_PACKER			173
#define CAR_SENTXS			174
#define CAR_ADMIRAL			175
#define BOAT_SQUALO			176
#define CAR_SEASPAR			177
#define BIKE_PIZZABOY		178
#define CAR_GANGBUR			179
#define BOAT_SPEEDER		182
#define BOAT_REEFER			183
#define BOAT_TROPIC			184
#define CAR_FLATBED			185
#define CAR_YANKEE			186
#define CAR_CADDY			187
#define CAR_ZEBRA			188
#define CAR_TOPFUN			189
#define BOAT_SKIMMER		190
#define BIKE_PCJ600			191
#define BIKE_FAGGIO			192
#define BIKE_FREEWAY		193
#define CAR_RCBARON			194
#define CAR_RCRAIDER		195
#define CAR_GLENDALE		196
#define CAR_OCEANIC			197
#define BIKE_SANCHEZ		198
#define CAR_SPARROW			199
#define CAR_PATRIOT			200
#define CAR_LOVEFIST		201
#define BOAT_COASTG			202
#define BOAT_DINGHY			203
#define CAR_HERMES			204
#define CAR_SABRE			205
#define CAR_SABRETUR		206
#define CAR_PHEONIX			207
#define CAR_WALTON			208
#define CAR_REGINA			209
#define CAR_COMET			210
#define CAR_DELUXO			211
#define CAR_BURRITO			212
#define CAR_SPAND			213
#define BOAT_MARQUIS		214
#define CAR_BAGGAGE			215
#define CAR_KAUFMAN			216
#define CAR_MAVERICK		217
#define CAR_VCNMAV			218
#define CAR_RANCHER			219
#define CAR_FBIRANCH		220
#define CAR_VIRGO			221
#define CAR_GREENWOO		222
#define BOAT_JETMAX			223
#define CAR_HOTRING			224
#define CAR_SANDKING		225
#define CAR_BLISTAC			226
#define CAR_POLMAV			227
#define CAR_BOXVILLE		228
#define CAR_BENSON			229
#define CAR_MESA			230
#define CAR_RCGOBLIN		231
#define CAR_HOTRINA			232
#define CAR_HOTRINB			233
#define CAR_BLOODRA			234
#define CAR_BLOODRB			235
#define CAR_VICECHEE		236

#define WEAPON_NONE			0
#define WEAPON_BRASSKNUCKLE	1
#define WEAPON_SCREWDRIVER	2
#define WEAPON_GOLFCLUB		3
#define WEAPON_NITESTICK	4
#define WEAPON_KNIFECUR		5
#define WEAPON_BAT			6
#define WEAPON_HAMMER		7
#define WEAPON_CLEAVER		8
#define WEAPON_MACHETE		9
#define WEAPON_KATANA		10
#define WEAPON_CHNSAW		11
#define WEAPON_GRENADE		12
#define WEAPON_BOMB			13
#define WEAPON_TEARGAS		14
#define WEAPON_MOLOTOV		15
#define WEAPON_MISSILE		16
#define WEAPON_COLT45		17
#define WEAPON_PYTHON		18
#define WEAPON_CHROMEGUN	19
#define WEAPON_SHOTGSPA		20
#define WEAPON_BUDDYSHOT	21
#define WEAPON_TEC9			22
#define WEAPON_UZI			23
#define WEAPON_INGRAMS1		24
#define WEAPON_MP5LGN		25
#define WEAPON_M4			26
#define WEAPON_RUGER		27
#define WEAPON_SNIPER		28
#define WEAPON_LASER		29
#define WEAPON_ROCKETLA		30
#define WEAPON_FLAME		31
#define WEAPON_M60			32
#define WEAPON_MINIGUN		33

#define PEDTYPE_PLAYER1		0
#define PEDTYPE_PLAYER2		1
#define PEDTYPE_PLAYER3		2
#define PEDTYPE_PLAYER4		3
#define PEDTYPE_CIVMALE		4
#define PEDTYPE_CIVFEMALE	5
#define PEDTYPE_COP			6
#define PEDTYPE_GANG1		7
#define PEDTYPE_GAMG2		8
#define PEDTYPE_GANG3		9
#define PEDTYPE_GANG4		10
#define PEDTYPE_GANG5		11
#define PEDTYPE_GANG6		12
#define PEDTYPE_GANG7		13
#define PEDTYPE_GANG8		14
#define PEDTYPE_GANG9		15
#define PEDTYPE_EMERGENCY	16
#define PEDTYPE_FIREMAN		17
#define PEDTYPE_CRIMINAL	18
#define PEDTYPE_SPECIAL		19

#define WEATHER_SUNNY		0
#define WEATHER_CLOUDY		1
#define WEATHER_RAINING		2
#define WEATHER_FOGGY		3
#define WEATHER_EXTRASUNNY	4
#define WEATHER_STORM		5
#define WEATHER_INTERIOR	6

#define INTERIOR_OUTSIDE	0
#define INTERIOR_HOTEL		1
#define INTERIOR_MANSION	2
#define INTERIOR_BANK		3
#define INTERIOR_MALL		4
#define INTERIOR_STRIPCLUB	5
#define INTERIOR_LAWYERS	6
#define INTERIOR_CAFEROBINA	7
#define INTERIOR_CONCERT	8
#define INTERIOR_STUDIO		9
#define INTERIOR_AMMUNATION	10
#define INTERIOR_APPARTMENT	11
#define INTERIOR_POLICEHQ	12
#define INTERIOR_UNKNOWN	12
#define INTERIOR_STADIUM1	14
#define INTERIOR_STADIUM2	15
#define INTERIOR_STADIUM3	16
#define INTERIOR_CLUB		17
#define INTERIOR_PRINTWORKS	18

#define FADE_OUT			0
#define FADE_IN				1










// *******

#define MAX_SCRIPT_VARS	16	// Size of our variable saving array
#define MAX_SCRIPT_SIZE	255	// Size of ScriptBuf - Max is really (2+(13*5))

struct GAME_SCRIPT_THREAD	// 0x88 bytes total.
{							// - Credit to CyQ & PatrickW
	void* pNext;			// 0x00
	void* pPrev;			// 0x04
	char strName[8];		// 0x08
	DWORD dwScriptIP;		// 0x10
	DWORD dwReturnStack[6];	// 0x14
	DWORD dwStackPointer;	// 0x2C
	DWORD dwLocalVar[18];	// 0x30
	BYTE bStartNewScript;	// 0x78
	BYTE bJumpFlag;			// 0x79
	BYTE bWorky;			// 0x7A
	BYTE bAwake;			// 0x7B
	DWORD dwWakeTime;		// 0x7C
	WORD wIfParam;			// 0x80
	BYTE bNotFlag;			// 0x82
	BYTE bWastedBustedCheck;// 0x83
	BYTE bWastedBustedFlag;	// 0x84
	BYTE bMissionThread;	// 0x85
	BYTE pad[2];			// 0x86
};

struct SCRIPT_COMMAND		//	Params
{							//		i = integer
	WORD OpCode;			//		f = float
	char Params[13];		//		v = variable
};							//		s = string

struct VEHICLE_STRUCT		// 0x5DC bytes total.
{

};

struct ACTOR_STRUCT			// 0x6D8 bytes total.
{
	BYTE Ukn00[0x14];		// 0x00
	float fVelocityX;		// 0x14
	float fVelocityY;		// 0x18
	float fVelocityZ;		// 0x1C
	BYTE Ukn20[0x14];		// 0x20
	float fPositionX;		// 0x34
	float fPositionY;		// 0x38
	float fPositionZ;		// 0x3C
	BYTE Ukn40[0x204];		// 0x40
	DWORD dwAnimation;		// 0x244
	BYTE Ukn248[0x10C];		// 0x248
	float fHealth;			// 0x354
	float fArmor;			// 0x358
	BYTE Ukn35C[0x4C];		// 0x35C
	DWORD dwCarID;			// 0x3A8
	BYTE bInCar;			// 0x3AC
	BYTE Ukn3AB[0x32D];		// 0x3AB
};

struct OBJECT_STRUCT
{

};

typedef OBJECT_STRUCT* (*GameGetObject_t)(int ObjectID);		// Typedef for game GetObjectPointer function.
typedef VEHICLE_STRUCT* (*GameGetVehicle_t)(int VehicleID);		// Typedef for game GetVehiclePointer function.
typedef ACTOR_STRUCT* (*GameGetActor_t)(int ActorID);			// Typedef for game GetActorPointer function.

int ScriptCommand(const SCRIPT_COMMAND* ScriptCommand, ...);	// The main scripting function. See notes.

/*	Below are some opcodes i've defined, but it's still missing
	about 95% of them ;) See http://vc-db.webtools4you.net/		*/
const SCRIPT_COMMAND request_model				= { 0x0247, "i" };		// (CAR_*|BIKE_*|BOAT_*|WEAPON_*|OBJECT_*)
const SCRIPT_COMMAND load_requested_models		= { 0x038B, "" };		// -/-
const SCRIPT_COMMAND create_car					= { 0x00A5, "ifffv" };	// (CAR_*|BIKE_*|BOAT_*), x, y, z, var_car
const SCRIPT_COMMAND load_special_actor			= { 0x023C, "is" };		// SPECIAL_*, MODEL_*
const SCRIPT_COMMAND create_actor				= { 0x009A, "iifffv" };	// PEDTYPE_*, #MODEL, x, y, z, var_actor
const SCRIPT_COMMAND destroy_actor_fading		= { 0x034F, "v" };		// var_actor
const SCRIPT_COMMAND kill_actor					= { 0x0321, "v" };		// var_actor
const SCRIPT_COMMAND kill_player				= { 0x0322, "v" };		// player_char
const SCRIPT_COMMAND force_weather				= { 0x01B5, "i" };		// WEATHER_*
const SCRIPT_COMMAND set_weather				= { 0x01B6, "i" };		// WEATHER_*
const SCRIPT_COMMAND release_weather			= { 0x01B7, "" };		// -/-
const SCRIPT_COMMAND set_fade_color				= { 0x0169, "iii" };	// Red(0-255), Green(0-255), Blue(0-255)
const SCRIPT_COMMAND fade						= { 0x016A, "ii" };		// (time in ms), FADE_*
const SCRIPT_COMMAND is_fading					= { 0x016B, "" };		// -/-
const SCRIPT_COMMAND set_actor_immunities		= { 0x02AB, "viiiii" };	// var_actor, Bullet(1/0), Fire(1/0), Explosion(1/0), Damage(1/0), Water(1/0)
const SCRIPT_COMMAND freeze_player				= { 0x01B4, "vi" };		// PLAYER_CHAR, Freeze(1/0)
const SCRIPT_COMMAND set_max_wanted_level		= { 0x01F0, "i" };		// MaxLevel
const SCRIPT_COMMAND set_wasted_busted_check	= { 0x0111, "i" };		// Check(1/0)
const SCRIPT_COMMAND set_current_time			= { 0x00C0, "ii" };		// Hours, Minutes
const SCRIPT_COMMAND set_camera					= { 0x03CB, "fff" };	// x, y, z
const SCRIPT_COMMAND create_player				= { 0x0053, "ifffv" };	// 0, x, y, z, PLAYER_CHAR
const SCRIPT_COMMAND create_actor_from_player	= { 0x01F5, "vv" };		// PLAYER_CHAR, PLAYER_ACTOR
const SCRIPT_COMMAND set_actor_skin				= { 0x0352, "vs" };		// var_actor, MODEL_*
const SCRIPT_COMMAND refresh_actor_skin			= { 0x0353, "v" };		// var_actor
const SCRIPT_COMMAND select_interior			= { 0x04BB, "i" };		// INTERIOR_*
const SCRIPT_COMMAND player_in_car				= { 0x0443, "v" };		// PLAYER_CHAR
const SCRIPT_COMMAND get_player_car				= { 0x03C1, "vv" };		// PLAYER_CHAR, var_car
const SCRIPT_COMMAND car_stopped				= { 0x01C1, "v" };		// var_car
const SCRIPT_COMMAND get_car_speed				= { 0x02E3, "vv" };		// var_car var_speed
//const SCRIPT_COMMAND get_car_speed				= { 0x02E3, "vv" };		// var_car var_speed
const SCRIPT_COMMAND toggleVehicleCollision		= { 0x099A, "ii" };
const SCRIPT_COMMAND set_car_immunities			= { 0x02ac, "iiiiii" };
int ScriptCommand(const SCRIPT_COMMAND* ScriptCommand, ...);

#endif