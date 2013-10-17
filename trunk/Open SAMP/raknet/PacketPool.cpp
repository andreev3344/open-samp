/// \file
///
/// This file is part of RakNet Copyright 2003 Kevin Jenkins.
///
/// Usage of RakNet is subject to the appropriate license agreement.
/// Creative Commons Licensees are subject to the
/// license found at
/// http://creativecommons.org/licenses/by-nc/2.5/
/// Single application licensees are subject to the license found at
/// http://www.rakkarsoft.com/SingleApplicationLicense.html
/// Custom license users are subject to the terms therein.
/// GPL license users are subject to the GNU General Public
/// License as published by the Free
/// Software Foundation; either version 2 of the License, or (at your
/// option) any later version.

/*
#include "PacketPool.h"
#include "NetworkTypes.h"
#include <assert.h>

PacketPool *PacketPool::I=0;
int PacketPool::referenceCount=0;

void PacketPool::AddReference(void)
{
	if (referenceCount==0)
		I = new PacketPool;
	referenceCount++;
}
void PacketPool::RemoveReference(void)
{
	if (referenceCount==1)
	{
		delete I;
		I=0;
	}
	referenceCount--;
}
PacketPool::PacketPool()
{
#ifdef _DEBUG
	packetsReleased = 0;
#endif
}

PacketPool::~PacketPool()
{
#ifdef _DEBUG
	// If this assert hits then not all packets given through GetPointer have been returned to ReleasePointer.
	// Either
	// 1. You got a packet from Receive and didn't give it back to DeallocatePacket when you were done with it
	// 2. You didn't call Disconnect before shutdown, and the order of destructor calls happened to hit the PacketPool singleton before it hit the RakPeer class(es).
//	assert( packetsReleased == 0 );
#endif

	ClearPool();
}

void PacketPool::ClearPool( void )
{
	Packet * p;
	poolMutex.Lock();

	while ( pool.Size() )
	{
		p = pool.Pop();
		delete [] p->data;
		delete p;
	}

	poolMutex.Unlock();
}

Packet* PacketPool::GetPointer( void )
{
	Packet * p = 0;
	poolMutex.Lock();

#ifdef _DEBUG

	packetsReleased++;
#endif

	if ( pool.Size() )
		p = pool.Pop();

	poolMutex.Unlock();

	if ( p )
		return p;

	p = new Packet;

	p->data = 0;

	return p;
}

void PacketPool::ReleasePointer( Packet *p )
{
	if ( p == 0 )
	{
		// Releasing a null pointer?
#ifdef _DEBUG
		assert( 0 );
#endif

		return ;
	}

	delete [] p->data;
	p->data = 0;

	poolMutex.Lock();
	pool.Push( p );
#ifdef _DEBUG

//	assert( packetsReleased > 0 );
	packetsReleased--;
#endif

	poolMutex.Unlock();
}
*/
