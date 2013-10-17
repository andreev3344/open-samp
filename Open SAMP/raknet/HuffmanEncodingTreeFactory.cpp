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

#include "DS_HuffmanEncodingTreeFactory.h"
#include "DS_HuffmanEncodingTreeNode.h"
#include "DS_HuffmanEncodingTree.h"
#include <memory.h>

HuffmanEncodingTreeFactory::HuffmanEncodingTreeFactory()
{
	Reset();
}

// Reset the frequency table.  You don't need to call this unless you want to reuse the class for a new tree
void HuffmanEncodingTreeFactory::Reset( void )
{
	for ( int counter = 0; counter < 256; counter++ )
		frequency[ counter ] = 0;
}

// Pass an array of bytes to this to add those elements to the frequency table
void HuffmanEncodingTreeFactory::AddToFrequencyTable( unsigned char *array, int size )
{
	while ( size-- > 0 )
		frequency[ array[ size ] ] ++;
}

// Copies the frequency table to the array passed
void HuffmanEncodingTreeFactory::GetFrequencyTable( unsigned int _frequency[ 256 ] )
{
	memcpy( _frequency, frequency, sizeof( unsigned int ) * 256 );
}

unsigned int * HuffmanEncodingTreeFactory::GetFrequencyTable( void )
{
	return frequency;
}

// Generate a HuffmanEncodingTree.
// You can also use GetFrequencyTable and GenerateFromFrequencyTable in the tree itself
HuffmanEncodingTree * HuffmanEncodingTreeFactory::GenerateTree( void )
{
	HuffmanEncodingTree * huffmanEncodingTree = new HuffmanEncodingTree;
	huffmanEncodingTree->GenerateFromFrequencyTable( frequency );
	return huffmanEncodingTree;
}
