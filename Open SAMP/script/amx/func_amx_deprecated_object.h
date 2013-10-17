#ifndef __FUNC_AMX_DEPRECATED_OBJECT_H_
#define __FUNC_AMX_DEPRECATED_OBJECT_H_

//#define FUNC_CreateObject					0x00487A20
//#define FUNC_AttachObjectToVehicle		0x00487AF0
//#define FUNC_SetObjectPos					0x0048D950
//#define FUNC_SetObjectRot					0x0048DAB0
//#define FUNC_GetObjectPos					0x00487B70
//#define FUNC_GetObjectRot					0x00487C00
//#define FUNC_IsValidObject				0x00487CA0
//#define FUNC_DestroyObject				0x0048DC00
//#define FUNC_MoveObject					0x0048DD10
//#define FUNC_StopObject					0x0048DEF0

//#define FUNC_CreatePlayerObject			0x00487CE0
//#define FUNC_DestroyPlayerObject			0x0048E3D0

//#define FUNC_SetPlayerObjectPos			0x0048E040
//#define FUNC_SetPlayerObjectRot			0x0048E200

//#define FUNC_GetPlayerObjectPos			0x00487DB0
//#define FUNC_GetPlayerObjectRot			0x00487E60
//#define FUNC_IsValidPlayerObject			0x00487F30
//#define FUNC_MovePlayerObject				0x0048E500
//#define FUNC_StopPlayerObject				0x0048E710
//#define FUNC_AttachObjectToPlayer			0x0048E990

//extern cell ( __cdecl* _funcCreateObject )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcAttachObjectToVehicle )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcSetObjectPos )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcSetObjectRot )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGetObjectPos )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGetObjectRot )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcIsValidObject )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcDestroyObject )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcMoveObject )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcStopObject )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcCreatePlayerObject )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcSetPlayerObjectPos )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcSetPlayerObjectRot )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGetPlayerObjectPos )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcGetPlayerObjectRot )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcIsValidPlayerObject )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcDestroyPlayerObject )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcMovePlayerObject )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcStopPlayerObject )( AMX* a_AmxInterface, cell* a_Params );
//extern cell ( __cdecl* _funcAttachObjectToPlayer )( AMX* a_AmxInterface, cell* a_Params );

cell AMX_NATIVE_CALL funcCreateObject ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAttachObjectToVehicle ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetObjectPos ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetObjectRot ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetObjectPos ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetObjectRot ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsValidObject ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDestroyObject ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcMoveObject ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcStopObject ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcCreatePlayerObject ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerObjectPos ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcSetPlayerObjectRot ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerObjectPos ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcGetPlayerObjectRot ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcIsValidPlayerObject ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcDestroyPlayerObject ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcMovePlayerObject ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcStopPlayerObject ( AMX* a_AmxInterface, cell* a_Params );
cell AMX_NATIVE_CALL funcAttachObjectToPlayer ( AMX* a_AmxInterface, cell* a_Params );


// __FUNC_AMX_DEPRECATED_OBJECT_H_
#endif