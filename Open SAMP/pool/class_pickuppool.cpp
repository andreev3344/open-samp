#include "../main.h"
#include "class_pickuppool.h"





CPickupPool::CPickupPool()
{
	memset( pickups, 0x00, sizeof( tPickup ) * LIMIT_MAX_PICKUPS );
	memset( isActive, 0x00, sizeof( BOOL ) * LIMIT_MAX_PICKUPS );
	memset( virtualWorld, 0x00, sizeof( uint32_t ) * LIMIT_MAX_PICKUPS );
	pickupCount = 0;
}

void CPickupPool::ComputePickupCount()
{
	uint16_t pickupID = 0;
	pickupCount = 0;
	while( pickupID < LIMIT_MAX_PICKUPS )
	{
		if( isActive[ pickupID ] == TRUE )
		{
			pickupCount  ++;
		}
		pickupID++;
	}

}

uint16_t CPickupPool::New( int model, int type, float X, float Y, float Z, int Virtualworld )
{
	uint16_t pickupID = 0;
	
	for( pickupID = 0; pickupID < LIMIT_MAX_PICKUPS; pickupID++ )
	{
		if( this->isActive[ pickupID ] == FALSE ) break;
	}
	
	if( pickupID >= LIMIT_MAX_PICKUPS ) return 0xFFFF;


	this->pickups[ pickupID ].model			= model;
	this->pickups[ pickupID ].type			= type;
	this->pickups[ pickupID ].position.X	= X;
	this->pickups[ pickupID ].position.Y	= Y;
	this->pickups[ pickupID ].position.Z	= Z;
	this->virtualWorld[ pickupID ]			= Virtualworld;
	this->isActive[ pickupID ]				= TRUE;

	ComputePickupCount();
	
	return pickupID;
}

void CPickupPool::Delete( uint16_t pickupID )
{
	if( 0 > pickupID || pickupID >= LIMIT_MAX_PICKUPS ) return;
	if( this->isActive[ pickupID ] == FALSE ) return;

	for( _PlayerID playerID = 0; playerID < MAX_PLAYERS; playerID ++ )
	{
		if( __NetGame->playerPool->GetSlotState( playerID ) )
		{
			CPlayer* player = __NetGame->playerPool->GetPlayer( playerID );
			if( player != 0 )
			{
				if( player->isPickupStreamedIn( pickupID ) )
				{
					player->streamOutPickup( pickupID );
				}
			}
		}
	}
	this->virtualWorld[ pickupID ]			= 0;
	this->isActive[ pickupID ]				= FALSE;
	memset( &this->pickups[ pickupID ], 0x00, sizeof( tPickup ) );
	ComputePickupCount( );
}

void CPickupPool::hideForPlayer( uint16_t pickupID, _PlayerID playerID )
{
	if( 0 > pickupID || pickupID >= LIMIT_MAX_PICKUPS ) return;
	if( this->isActive[ pickupID ] == FALSE ) return;

	RakNet::BitStream bStream;
	bStream.Write( ( uint32_t ) pickupID );
	__NetGame->PlayerRPC( RPC_HidePickupForPlayer, &bStream, playerID );
}
void CPickupPool::showForPlayer( uint16_t pickupID, _PlayerID playerID )
{
	if( 0 > pickupID || pickupID >= LIMIT_MAX_PICKUPS ) return;
	if( this->isActive[ pickupID ] == FALSE ) return;

	RakNet::BitStream bStream;
	bStream.Write( ( uint32_t ) pickupID );
#ifdef _BIG_ENDIAN_SYSTEM
	bStream.Write(pickups[ pickupID ].model);
	bStream.Write(pickups[ pickupID ].type);
	bStream.Write(pickups[ pickupID ].position.X), bStream.Write(pickups[ pickupID ].position.Y), bStream.Write(pickups[ pickupID ].position.Z);
#else
	bStream.Write( ( char* )&pickups[ pickupID ], sizeof( tPickup ) );
#endif
	__NetGame->PlayerRPC( RPC_ShowPickupForPlayer, &bStream, playerID );

}


bool CPickupPool::GetSlotState( uint16_t pickupID ) 
{
	if( 0 > pickupID || pickupID >= LIMIT_MAX_PICKUPS ) return false;
	return ( bool )( isActive[ pickupID ] ? true : false );
}

uint32_t CPickupPool::getVirtualWorld( uint16_t pickupID )
{
	if( GetSlotState( pickupID ) )
	{
		return virtualWorld[ pickupID ];
	}
	return 0;
} 

tPickup* CPickupPool::GetPickup( uint16_t pickupID )
{
	if( GetSlotState( pickupID ) )
	{
		return &pickups[ pickupID ];
	}
	return (tPickup*)0;
}







//tPickupPool* __PickupPoolEx = NULL;
//
//uint32_t CPickupPool::New ( uint32_t a_uint32_Model, uint32_t a_uint32_Type, float a_float_X, float a_float_Y, float a_float_Z, uint8_t a_uint8_Static )
//{
//	logprintf ( "[Call]-> CPickupPool::New ( %d, %d, %f, %f, %f, %d )", a_uint32_Model, a_uint32_Type, a_float_X, a_float_Y, a_float_Z, a_uint8_Static );
///*
//	//// TODO: Remove that Shitty !
//	__NetGame = *( uint32_t* )( 0x004F6270 );
//	__PickupPoolEx = ( tPickupPool* )( *( uint32_t* )( __NetGame + 0x10 ) );
//
//	char *v7; // eax@1
//	signed int l_PickupIndex; // esi@1
//	signed int result; // eax@12
//	char *v10; // eax@13
//
//	l_PickupIndex = 0;
//	v7 = (char *)__PickupPoolEx->m_uint8_Active;
//	while ( *((uint32_t *)v7 - 1) )
//	{
//		if ( !*(uint32_t *)v7 )
//		{
//			++l_PickupIndex;
//			break;
//		}
//		if ( !*((uint32_t *)v7 + 1) )
//		{
//			l_PickupIndex += 2;
//			break;
//		}
//		if ( !*((uint32_t *)v7 + 2) )
//		{
//			l_PickupIndex += 3;
//			break;
//		}
//		l_PickupIndex += 4;
//		v7 += 16;
//		if ( l_PickupIndex >= LIMIT_MAX_PICKUPS )
//			break;
//	}
//
//	if ( l_PickupIndex == LIMIT_MAX_PICKUPS )
//	{
//		result = -1;
//	}
//	else
//	{
//		__PickupPoolEx->m_Pickups[ i ].m_uint32_Model = a_uint32_Model;
//		__PickupPoolEx->m_Pickups[ i ].m_uint32_Type = a_uint32_Type;
//		__PickupPoolEx->m_Pickups[ i ].m_float_X = a_float_X;
//		__PickupPoolEx->m_Pickups[ i ].m_float_Y = a_float_Y;	
//		__PickupPoolEx->m_Pickups[ i ].m_float_Z = a_float_Z;
//		__PickupPoolEx->m_uint8_Active[ i ] = a_uint8_Static;
//
//		//sub_47C150((int)this);
//		result = l_PickupIndex;
//	}
//	return result;
//	*/
//
///*
//	//if ( this->m_uint32_PickupCount >= LIMIT_MAX_PICKUPS )
//	//	return -1;
//
//	if ( __PickupPoolEx->m_uint32_PickupCount >= LIMIT_MAX_PICKUPS )
//		return -1;
//
//	for ( uint32_t i = 0; i < LIMIT_MAX_PICKUPS; i++ )
//	{
//		if ( __PickupPoolEx->m_uint8_Active[ i ] == 0 )
//		{
//			__PickupPoolEx->m_Pickups[ i ].m_uint32_Model = a_uint32_Model;
//			__PickupPoolEx->m_Pickups[ i ].m_uint32_Type = a_uint32_Type;
//			__PickupPoolEx->m_Pickups[ i ].m_float_X = a_float_X;
//			__PickupPoolEx->m_Pickups[ i ].m_float_Y = a_float_Y;	
//			__PickupPoolEx->m_Pickups[ i ].m_float_Z = a_float_Z;
//			if ( a_uint8_Static )
//			{
//				// Static, Ne Peut Pas Etre Détruit ?!?
//				__PickupPoolEx->m_uint8_Active[ i ] = -1;
//			}
//			else
//			{
//				// Dynamic, Peut Etre Détruit ?!?
//				__PickupPoolEx->m_uint8_Active[ i ] = 1;
//			}
//			__PickupPoolEx->m_uint32_PickupCount++;
//			
//			/*
//			RakNet::BitStream bsPickup;
//			bsPickup.Write(i);
//			bsPickup.Write((PCHAR)&m_Pickups[i], sizeof (PICKUP));
//			pNetGame->GetRakServer()->RPC(RPC_Pickup, &bsPickup, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_PLAYER_ID, true, false);
//			*//*
//			return i;
//		}
//	}
//
//
//	/*
//	for ( uint32_t i = 0; i < LIMIT_MAX_PICKUPS; i++ )
//	{
//		if ( this->m_uint8_Active[ i ] == 0 )
//		{
//			this->m_Pickups[ i ].m_uint32_Model = a_uint32_Model;
//			this->m_Pickups[ i ].m_uint32_Type = a_uint32_Type;
//			this->m_Pickups[ i ].m_float_X = a_float_X;
//			this->m_Pickups[ i ].m_float_Y = a_float_Y;	
//			this->m_Pickups[ i ].m_float_Z = a_float_Z;
//			if ( a_uint8_Static )
//			{
//				// Static, Ne Peut Pas Etre Détruit ?!?
//				this->m_uint8_Active[ i ] = -1;
//			}
//			else
//			{
//				// Dynamic, Peut Etre Détruit ?!?
//				this->m_uint8_Active[ i ] = 1;
//			}
//			this->m_uint32_PickupCount++;
//			
//			/*
//			RakNet::BitStream bsPickup;
//			bsPickup.Write(i);
//			bsPickup.Write((PCHAR)&m_Pickups[i], sizeof (PICKUP));
//			pNetGame->GetRakServer()->RPC(RPC_Pickup, &bsPickup, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_PLAYER_ID, true, false);
//			
//			return i;
//		}
//	}
//	*/
//	return 0;
//}
//
//uint8_t CPickupPool::Destroy ( uint32_t a_uint32_PickupIndex )
//{
//	if ( ( a_uint32_PickupIndex >= 0 ) && 
//			( a_uint32_PickupIndex < LIMIT_MAX_PICKUPS ) && 
//			( this->m_uint8_Active[ a_uint32_PickupIndex ] == 1 ) )
//	{
//		this->m_uint8_Active[ a_uint32_PickupIndex ] = 0;
//		this->m_uint32_PickupCount--;
//
//		/*
//		RakNet::BitStream bsPickup;
//		bsPickup.Write(iPickup);
//		pNetGame->GetRakServer()->RPC(RPC_DestroyPickup, &bsPickup, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_PLAYER_ID, true, false);
//		*/
//		return 1;
//	}
//	return 0;
//}
//
//void CPickupPool::InitForPlayer ( _PlayerID a_uint8_PlayerIndex )
//{	
//	/*
//	//RakNet::BitStream *pbsPickup;
//
//	uint32_t x = 0;
//
//	pbsPickup = new RakNet::BitStream();
//
//	while(x != MAX_PICKUPS)
//	{
//		if (m_bActive[x])
//		{
//			pbsPickup->Write(x);
//			pbsPickup->Write((PCHAR)&m_Pickups[x], sizeof (PICKUP));
//		
//			pNetGame->GetRakServer()->RPC(RPC_Pickup,pbsPickup,HIGH_PRIORITY,RELIABLE,
//				0,pNetGame->GetRakServer()->GetPlayerIDFromIndex(uint8_tPlayerID),false,false);
//
//			pbsPickup->Reset();
//		}
//
//		x++;
//	}
//
//	delete pbsPickup;
//	*/
//}
