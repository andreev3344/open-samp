#include "../../main.h"
#include "../../../SDK/amx/amx.h"

#include "../func_amx.h"
#include "func_amx_object.h"

cell ( __cdecl* _funcCreateObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_CreateObject;
cell ( __cdecl* _funcAttachObjectToVehicle )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AttachObjectToVehicle;
cell ( __cdecl* _funcSetObjectPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetObjectPos;
cell ( __cdecl* _funcSetObjectRot )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetObjectRot;
cell ( __cdecl* _funcGetObjectPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetObjectPos;
cell ( __cdecl* _funcGetObjectRot )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetObjectRot;
cell ( __cdecl* _funcIsValidObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsValidObject;
cell ( __cdecl* _funcDestroyObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DestroyObject;
cell ( __cdecl* _funcMoveObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_MoveObject;
cell ( __cdecl* _funcStopObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_StopObject;
cell ( __cdecl* _funcCreatePlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_CreatePlayerObject;
cell ( __cdecl* _funcSetPlayerObjectPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerObjectPos;
cell ( __cdecl* _funcSetPlayerObjectRot )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_SetPlayerObjectRot;
cell ( __cdecl* _funcGetPlayerObjectPos )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerObjectPos;
cell ( __cdecl* _funcGetPlayerObjectRot )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_GetPlayerObjectRot;
cell ( __cdecl* _funcIsValidPlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_IsValidPlayerObject;
cell ( __cdecl* _funcDestroyPlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_DestroyPlayerObject;
cell ( __cdecl* _funcMovePlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_MovePlayerObject;
cell ( __cdecl* _funcStopPlayerObject )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_StopPlayerObject;
cell ( __cdecl* _funcAttachObjectToPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AttachObjectToPlayer;
cell ( __cdecl* _funcAttachPlayerObjectToPlayer )( AMX* a_AmxInterface, cell* a_Params ) = ( cell ( __cdecl* )( AMX*, cell* ) )FUNC_AttachPlayerObjectToPlayer;


cell AMX_NATIVE_CALL funcCreateObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCreateObject()" );
/*
  unsigned __int16 l_ObjectIndex; // bp@3
  void *l_Object; // ebx@5
  int l_PlayerPool; // edi@7
  signed int l_PlayerIndex; // esi@9
  int a_Rotation; // [sp+4h] [bp-18h]@3
  int v8; // [sp+8h] [bp-14h]@3
  int v9; // [sp+Ch] [bp-10h]@3
  int a_Position; // [sp+10h] [bp-Ch]@3
  int v11; // [sp+14h] [bp-8h]@3
  int v12; // [sp+18h] [bp-4h]@3

  if ( !*(_DWORD *)(_NetGame + 20) )
    return 0;
  a_Position = a_Params[2];
  v11 = a_Params[3];
  v12 = a_Params[4];
  a_Rotation = a_Params[5];
  v8 = a_Params[6];
  v9 = a_Params[7];
  l_ObjectIndex = CObjectPool__New(a_Params[1], (VECTOR *)&a_Position, (VECTOR *)&a_Rotation, a_Params[8]);
  if ( l_ObjectIndex == -1 )
    return l_ObjectIndex;
  if ( l_ObjectIndex < 400u )
    l_Object = *(void **)(*(_DWORD *)(_NetGame + 20) + 4 * l_ObjectIndex + 1600);
  else
    l_Object = 0;
  l_PlayerPool = *(_DWORD *)(_NetGame + 4);
  if ( l_Object && l_PlayerPool )
  {
    l_PlayerIndex = 0;
    do
    {
      if ( (_WORD)l_PlayerIndex < 500u )
      {
        if ( *(_DWORD *)(l_PlayerPool + 4 * (unsigned __int16)l_PlayerIndex) )
          sub_4A0800(l_Object, l_PlayerIndex);
      }
      ++l_PlayerIndex;
    }
    while ( l_PlayerIndex < 500 );
    return l_ObjectIndex;
  }
  return 0;
  */

	return _funcCreateObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcAttachObjectToVehicle ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAttachObjectToVehicle()" );
	return _funcAttachObjectToVehicle ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetObjectPos()" );
	/*
  int l_ObjectPool; // ecx@1
  int result; // eax@2
  unsigned __int16 l_ObjectIndex; // ax@3
  int l_Object; // eax@4
  long double l_PositionX; // fst7@5
  int l_PositionZ; // ecx@5
  long double l_PositionY; // fst6@5
  int l_ObjectIndexEx; // eax@5
  int v10; // [sp+0h] [bp-130h]@5
  int v11; // [sp+4h] [bp-12Ch]@5
  int v12; // [sp+8h] [bp-128h]@5
  int v13; // [sp+Ch] [bp-124h]@5
  char l_Bitstream; // [sp+10h] [bp-120h]@5
  int v15; // [sp+12Ch] [bp-4h]@5

  l_ObjectPool = *(_DWORD *)(_NetGame + 20);
  if ( l_ObjectPool )
  {
    l_ObjectIndex = *((_WORD *)a_Params + 2);
    if ( l_ObjectIndex < 400u )
    {
      l_Object = *(_DWORD *)(l_ObjectPool + 4 * l_ObjectIndex + 1600);
      if ( l_Object )
      {
        l_PositionX = *((float *)a_Params + 2);
        l_PositionZ = a_Params[4];
        *(float *)&v11 = *((float *)a_Params + 2);
        l_PositionY = *((float *)a_Params + 3);
        v13 = l_PositionZ;
        *(float *)&v12 = l_PositionY;
        *(_DWORD *)(l_Object + 66) = l_PositionZ;
        *(float *)(l_Object + 58) = l_PositionX;
        *(float *)(l_Object + 62) = l_PositionY;
        BitStream__New(&l_Bitstream);
        l_ObjectIndexEx = *((_WORD *)a_Params + 2);
        v15 = 0;
        v10 = l_ObjectIndexEx;
        BitStream__Write((int)&l_Bitstream, (unsigned __int8 *)&v10, (void *)0x10, 1);
        v10 = v11;
        BitStream__Write((int)&l_Bitstream, (unsigned __int8 *)&v10, (void *)0x20, 1);
        v10 = v12;
        BitStream__Write((int)&l_Bitstream, (unsigned __int8 *)&v10, (void *)0x20, 1);
        v10 = v13;
        BitStream__Write((int)&l_Bitstream, (unsigned __int8 *)&v10, (void *)0x20, 1);
        CNetGame__RPC_SendToEveryPlayer(_NetGame, (int)L"1", (int)&l_Bitstream, 0xFFFFu, 2);
        v15 = -1;
        BitStream__Delete((int)&l_Bitstream);
      }
    }
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;

  */
	return _funcSetObjectPos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetObjectRot ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetObjectRot()" );
/*
  int l_ObjectPool; // ecx@1
  int result; // eax@2
  unsigned __int16 l_ObjectIndex; // ax@3
  int l_Object; // ecx@4
  int v6; // edx@6
  int v7; // eax@6
  int v8; // eax@7
  int v9; // [sp+0h] [bp-130h]@7
  VECTOR a_Position; // [sp+4h] [bp-12Ch]@6
  char v11; // [sp+10h] [bp-120h]@7
  int v12; // [sp+12Ch] [bp-4h]@7

  l_ObjectPool = *(_DWORD *)(_NetGame + 20);
  if ( l_ObjectPool )
  {
    l_ObjectIndex = *((_WORD *)a_Params + 2);
    if ( l_ObjectIndex < 400u )
      l_Object = *(_DWORD *)(l_ObjectPool + 4 * l_ObjectIndex + 1600);
    else
      l_Object = 0;
    v6 = a_Params[3];
    a_Position.X = a_Params[2];
    v7 = a_Params[4];
    a_Position.Y = v6;
    a_Position.Z = v7;
    if ( l_Object )
    {
      CObject__SetRotation(&a_Position);
      BitStream__New(&v11);
      v8 = *((_WORD *)a_Params + 2);
      v12 = 0;
      v9 = v8;
      BitStream__Write((int)&v11, (unsigned __int8 *)&v9, (void *)0x10, 1);
      v9 = a_Position.X;
      BitStream__Write((int)&v11, (unsigned __int8 *)&v9, (void *)0x20, 1);
      v9 = a_Position.Y;
      BitStream__Write((int)&v11, (unsigned __int8 *)&v9, (void *)0x20, 1);
      v9 = a_Position.Z;
      BitStream__Write((int)&v11, (unsigned __int8 *)&v9, (void *)0x20, 1);
      CNetGame__RPC_SendToEveryPlayer(_NetGame, (int)&unk_4C1084, (int)&v11, 0xFFFFu, 2);
      v12 = -1;
      BitStream__Delete((int)&v11);
    }
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;

*/
	return _funcSetObjectRot ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetObjectPos()" );

	/*
	  int v2; // ecx@1
  int v3; // ecx@1
  int result; // eax@2
  unsigned __int16 v5; // ax@3
  int v6; // esi@4
  int a_Pointer; // [sp+0h] [bp-4h]@1

  a_Pointer = v3;
  v2 = *(_DWORD *)(_NetGame + 20);
  if ( v2 )
  {
    v5 = *((_WORD *)a_Params + 2);
    if ( v5 < 400 && (v6 = *(_DWORD *)(v2 + 4 * v5 + 1600)) != 0 )
    {
      amx_GetAddr(a_AmxInterface, (int *)a_Params[2], &a_Pointer);
      *(_DWORD *)a_Pointer = *(_DWORD *)(v6 + 58);
      amx_GetAddr(a_AmxInterface, (int *)a_Params[3], &a_Pointer);
      *(_DWORD *)a_Pointer = *(_DWORD *)(v6 + 62);
      amx_GetAddr(a_AmxInterface, (int *)a_Params[4], &a_Pointer);
      *(_DWORD *)a_Pointer = *(_DWORD *)(v6 + 66);
      result = 1;
    }
    else
    {
      result = 0;
    }
  }
  else
  {
    result = 0;
  }
  return result;

	*/

	return _funcGetObjectPos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetObjectRot ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetObjectRot()" );

/*
  int v2; // ecx@1
  int v3; // ecx@1
  int result; // eax@2
  unsigned __int16 v5; // ax@3
  void *v6; // ecx@4
  char *v7; // esi@5
  int a_Pointer; // [sp+0h] [bp-4h]@1

  a_Pointer = v3;
  v2 = *(_DWORD *)(_NetGame + 20);
  if ( v2 )
  {
    v5 = *((_WORD *)a_Params + 2);
    if ( v5 < 0x190u && (v6 = *(void **)(v2 + 4 * v5 + 1600)) != 0 )
    {
      v7 = CObject__GetRotation(v6);
      amx_GetAddr(a_AmxInterface, (int *)a_Params[2], &a_Pointer);
      *(_DWORD *)a_Pointer = *(_DWORD *)v7;
      amx_GetAddr(a_AmxInterface, (int *)a_Params[3], &a_Pointer);
      *(_DWORD *)a_Pointer = *((_DWORD *)v7 + 1);
      amx_GetAddr(a_AmxInterface, (int *)a_Params[4], &a_Pointer);
      *(_DWORD *)a_Pointer = *((_DWORD *)v7 + 2);
      result = 1;
    }
    else
    {
      result = 0;
    }
  }
  else
  {
    result = 0;
  }
  return result;

*/


	return _funcGetObjectRot ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsValidObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsValidObject()" );

/*
  int l_ObjectPool; // eax@1
  unsigned __int16 l_ObjectIndex; // cx@2

  l_ObjectPool = *(_DWORD *)(_NetGame + 20);
  return l_ObjectPool
      && (l_ObjectIndex = *((_WORD *)a_Params + 2), l_ObjectIndex < 400u)
      && *(_DWORD *)(l_ObjectPool + 4 * l_ObjectIndex + 1600);

*/

	return _funcIsValidObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcDestroyObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDestroyObject()" );
	return _funcDestroyObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcMoveObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcMoveObject()" );
	return _funcMoveObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcStopObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcStopObject()" );
	return _funcStopObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcCreatePlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcCreatePlayerObject()" );
	return _funcCreatePlayerObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerObjectPos()" );
	return _funcSetPlayerObjectPos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcSetPlayerObjectRot ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcSetPlayerObjectRot()" );
	return _funcSetPlayerObjectRot ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerObjectPos ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerObjectPos()" );
	return _funcGetPlayerObjectPos ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcGetPlayerObjectRot ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcGetPlayerObjectRot()" );
	return _funcGetPlayerObjectRot ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcIsValidPlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcIsValidPlayerObject()" );
	return _funcIsValidPlayerObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcDestroyPlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcDestroyPlayerObject()" );
	return _funcDestroyPlayerObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcMovePlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcMovePlayerObject()" );
	return _funcMovePlayerObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcStopPlayerObject ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcStopPlayerObject()" );
	return _funcStopPlayerObject ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcAttachObjectToPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAttachObjectToPlayer()" );
	return _funcAttachObjectToPlayer ( a_AmxInterface, a_Params );
}
cell AMX_NATIVE_CALL funcAttachPlayerObjectToPlayer ( AMX* a_AmxInterface, cell* a_Params )
{
	logprintf ( "[Call]-> funcAttachPlayerObjectToPlayer()" );
	return _funcAttachPlayerObjectToPlayer ( a_AmxInterface, a_Params );
}