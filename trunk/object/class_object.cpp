#include "../main.h"
#include "class_object.h"

void CObject::SpawnForPlayer ( uint16_t a_PlayerIndex )
{
	RakNet::BitStream 
		l_BitStream;
		l_BitStream.Write ( this->m_uint16_ObjectIndex );
		l_BitStream.Write ( this->m_uint32_ModelIndex );
		l_BitStream.Write ( this->m_Position.X );
		l_BitStream.Write ( this->m_Position.Y );
		l_BitStream.Write ( this->m_Position.Z );
		l_BitStream.Write ( this->m_Rotation.X );
		l_BitStream.Write ( this->m_Rotation.Y );
		l_BitStream.Write ( this->m_Rotation.Z );


}
/*
  void *this; // esi@1
  int v3; // eax@1
  int v4; // [sp+4h] [bp-124h]@1
  char v5; // [sp+8h] [bp-120h]@1
  int v6; // [sp+124h] [bp-4h]@1

  this = a_This;
  BitStream__New(&v5);
  v3 = *(_WORD *)this;
  v6 = 0;
  v4 = v3;
  BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x10, 1); // ObjectIndex

  v4 = *(_DWORD *)((char *)this + 2);
  BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1); // ModelIndex

  v4 = *(_DWORD *)((char *)this + 58);
  BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1); // +0x58 Position X

  v4 = *(_DWORD *)((char *)this + 62);
  BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1); // +0x62 Position Y

  v4 = *(_DWORD *)((char *)this + 66);
  BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1); // +0x66 Position Z

  v4 = *(_DWORD *)((char *)this + 74);
  BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1); // +0x74 Rotation X

  v4 = *(_DWORD *)((char *)this + 78);
  BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1); // +0x78 Rotation Y

  v4 = *(_DWORD *)((char *)this + 82);
  BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1); // +0x82 Rotation Z

  v4 = *(_DWORD *)((char *)this + 159);
  BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1);

  v4 = *(_WORD *)((char *)this + 163);
  BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x10, 1);


  if ( *(_WORD *)((char *)this + 163) != -1 )
  {
    v4 = *(_DWORD *)((char *)this + 165);
    BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1);
    v4 = *(_DWORD *)((char *)this + 169);
    BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1);
    v4 = *(_DWORD *)((char *)this + 173);
    BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1);
    v4 = *(_DWORD *)((char *)this + 177);
    BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1);
    v4 = *(_DWORD *)((char *)this + 181);
    BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1);
    v4 = *(_DWORD *)((char *)this + 185);
    BitStream__Write((int)&v5, (unsigned __int8 *)&v4, (void *)0x20, 1);
  }
  CNetGame__RPC_SendToPlayer(_NetGame, (int)L"0", (int)&v5, a2, 2);
  v6 = -1;
  BitStream__Delete((int)&v5);
  */

void CObject::SetRotation ( tVector* a_Rotation )
{
	this->m_Rotation.X = a_Rotation->X;
	this->m_Rotation.Y = a_Rotation->Y;
	this->m_Rotation.Z = a_Rotation->Z;
}