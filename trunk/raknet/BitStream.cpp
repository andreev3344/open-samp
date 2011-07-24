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

#include "BitStream.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#ifdef _COMPATIBILITY_1
#include "Compatibility1Includes.h"
#elif defined(_WIN32)
#include <winsock2.h> // htonl
#else
#include <arpa/inet.h>
#endif


#if defined ( __APPLE__ ) || defined ( __APPLE_CC__ )
	#include <malloc/malloc.h>
#else
	#include <malloc.h>
#endif

// MSWin uses _copysign, others use copysign...
#ifndef _WIN32
#define _copysign copysign
#endif

using namespace RakNet;

BitStream::BitStream()
{
	numberOfBitsUsed = 0;
	//numberOfBitsAllocated = 32 * 8;
	numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE * 8;
	readOffset = 0;
	//data = ( unsigned char* ) malloc( 32 );
	data = ( unsigned char* ) stackData;
	
#ifdef _DEBUG	
//	assert( data );
#endif
	//memset(data, 0, 32);
	copyData = true;
}

BitStream::BitStream( int initialuint8_tsToAllocate )
{
	numberOfBitsUsed = 0;
	readOffset = 0;
	if (initialuint8_tsToAllocate <= BITSTREAM_STACK_ALLOCATION_SIZE)
	{
		data = ( unsigned char* ) stackData;
		numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE * 8;
	}
	else
	{
		data = ( unsigned char* ) malloc( initialuint8_tsToAllocate );
		numberOfBitsAllocated = initialuint8_tsToAllocate << 3;
	}
#ifdef _DEBUG
	assert( data );
#endif
	// memset(data, 0, initialuint8_tsToAllocate);
	copyData = true;
}

BitStream::BitStream( char* _data, unsigned int lengthInuint8_ts, bool _copyData )
{
	numberOfBitsUsed = lengthInuint8_ts << 3;
	readOffset = 0;
	copyData = _copyData;
	numberOfBitsAllocated = lengthInuint8_ts << 3;
	
	if ( copyData )
	{
		if ( lengthInuint8_ts > 0 )
		{
			if (lengthInuint8_ts < BITSTREAM_STACK_ALLOCATION_SIZE)
			{
				data = ( unsigned char* ) stackData;
				numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE << 3;
			}
			else
			{
				data = ( unsigned char* ) malloc( lengthInuint8_ts );
			}
#ifdef _DEBUG
			assert( data );
#endif
			memcpy( data, _data, lengthInuint8_ts );
		}
		else
			data = 0;
	}
	else
		data = ( unsigned char* ) _data;
}

// Use this if you pass a pointer copy to the constructor (_copyData==false) and want to overallocate to prevent reallocation
void BitStream::SetNumberOfBitsAllocated( const unsigned int lengthInBits )
{
#ifdef _DEBUG
	assert( lengthInBits >= ( unsigned int ) numberOfBitsAllocated );
#endif	
	numberOfBitsAllocated = lengthInBits;
}

BitStream::~BitStream()
{
	if ( copyData && numberOfBitsAllocated > BITSTREAM_STACK_ALLOCATION_SIZE << 3)
		free( data );  // Use realloc and free so we are more efficient than delete and new for resizing
}

void BitStream::Reset( void )
{
	// Note:  Do NOT reallocate memory because BitStream is used
	// in places to serialize/deserialize a buffer. Reallocation
	// is a dangerous operation (may result in leaks).
	
	if ( numberOfBitsUsed > 0 )
	{
		//  memset(data, 0, BITS_TO_uint8_tS(numberOfBitsUsed));
	}
	
	// Don't free memory here for speed efficiency
	//free(data);  // Use realloc and free so we are more efficient than delete and new for resizing
	numberOfBitsUsed = 0;
	
	//numberOfBitsAllocated=8;
	readOffset = 0;
	
	//data=(unsigned char*)malloc(1);
	// if (numberOfBitsAllocated>0)
	//  memset(data, 0, BITS_TO_uint8_tS(numberOfBitsAllocated));
}

// Write an array or casted stream
void BitStream::Write( const char* input, const int numberOfuint8_ts )
{
	WriteBits( ( unsigned char* ) input, numberOfuint8_ts * 8, true );
}
void BitStream::Write( BitStream *bitStream )
{
	if (bitStream->GetReadOffset()==0)
	{
		// Fast uint8_t based write
		Write((const char*)bitStream->GetData(), bitStream->GetNumberOfuint8_tsUsed());
		// Subtract unused bits
		numberOfBitsUsed-=bitStream->GetNumberOfuint8_tsUsed()*8-bitStream->GetNumberOfBitsUsed();
		return;
	}

	// TODO - this is inefficient
	bool b;
	int offset = bitStream->GetReadOffset();
	while (bitStream->GetNumberOfUnreadBits()>0)
	{
		bitStream->Read(b);
		Write(b);
	}
	bitStream->SetReadOffset(offset);
}

// Read an array or casted stream
bool BitStream::Read( char* output, const int numberOfuint8_ts )
{
	return ReadBits( ( unsigned char* ) output, numberOfuint8_ts * 8 );
}

// Sets the read pointer back to the beginning of your data.
void BitStream::ResetReadPointer( void )
{
	readOffset = 0;
}

// Sets the write pointer back to the beginning of your data.
void BitStream::ResetWritePointer( void )
{
	numberOfBitsUsed = 0;
}

// Write a 0
void BitStream::Write0( void )
{
	AddBitsAndReallocate( 1 );
	
	// New uint8_ts need to be zeroed
	
	if ( ( numberOfBitsUsed % 8 ) == 0 )
		data[ numberOfBitsUsed >> 3 ] = 0;
		
	numberOfBitsUsed++;
}

// Write a 1
void BitStream::Write1( void )
{
	AddBitsAndReallocate( 1 );
	
	int numberOfBitsMod8 = numberOfBitsUsed % 8;
	
	if ( numberOfBitsMod8 == 0 )
		data[ numberOfBitsUsed >> 3 ] = 0x80;
	else
		data[ numberOfBitsUsed >> 3 ] |= 0x80 >> ( numberOfBitsMod8 ); // Set the bit to 1
		
	numberOfBitsUsed++;
}

// Returns true if the next data read is a 1, false if it is a 0
bool BitStream::ReadBit( void )
{
#ifdef _MSC_VER
#pragma warning( disable : 4800 ) // warning C4100: <variable name> : unreferenced formal parameter
#endif
	return ( bool ) ( data[ readOffset >> 3 ] & ( 0x80 >> ( readOffset++ % 8 ) ) );
}

// Align the bitstream to the uint8_t boundary and then write the specified number of bits.
// This is faster than WriteBits but wastes the bits to do the alignment and requires you to call
// SetReadTouint8_tAlignment at the corresponding read position
void BitStream::WriteAligneduint8_ts( const unsigned char* input,
	const int numberOfuint8_tsToWrite )
{
#ifdef _DEBUG
	assert( numberOfuint8_tsToWrite > 0 );
#endif
	
	AlignWriteTouint8_tBoundary();
	// Allocate enough memory to hold everything
	AddBitsAndReallocate( numberOfuint8_tsToWrite << 3 );
	
	// Write the data
	memcpy( data + ( numberOfBitsUsed >> 3 ), input, numberOfuint8_tsToWrite );
	
	numberOfBitsUsed += numberOfuint8_tsToWrite << 3;
}

// Read bits, starting at the next aligned bits. Note that the modulus 8 starting offset of the
// sequence must be the same as was used with WriteBits. This will be a problem with packet coalescence
// unless you uint8_t align the coalesced packets.
bool BitStream::ReadAligneduint8_ts( unsigned char* output,
	const int numberOfuint8_tsToRead )
{
#ifdef _DEBUG
	assert( numberOfuint8_tsToRead > 0 );
#endif
	
	if ( numberOfuint8_tsToRead <= 0 )
		return false;
		
	// uint8_t align
	AlignReadTouint8_tBoundary();
	
	if ( readOffset + ( numberOfuint8_tsToRead << 3 ) > numberOfBitsUsed )
		return false;
		
	// Write the data
	memcpy( output, data + ( readOffset >> 3 ), numberOfuint8_tsToRead );
	
	readOffset += numberOfuint8_tsToRead << 3;
	
	return true;
}

// Align the next write and/or read to a uint8_t boundary.  This can be used to 'waste' bits to uint8_t align for efficiency reasons
void BitStream::AlignWriteTouint8_tBoundary( void )
{
	if ( numberOfBitsUsed )
		numberOfBitsUsed += 8 - ( ( numberOfBitsUsed - 1 ) % 8 + 1 );
}

// Align the next write and/or read to a uint8_t boundary.  This can be used to 'waste' bits to uint8_t align for efficiency reasons
void BitStream::AlignReadTouint8_tBoundary( void )
{
	if ( readOffset )
		readOffset += 8 - ( ( readOffset - 1 ) % 8 + 1 );
}

// Write numberToWrite bits from the input source
void BitStream::WriteBits( const unsigned char *input, int numberOfBitsToWrite, const bool rightAlignedBits )
{
	// if (numberOfBitsToWrite<=0)
	//  return;
	
	AddBitsAndReallocate( numberOfBitsToWrite );
	int offset = 0;
	unsigned char datauint8_t;
	int numberOfBitsUsedMod8;
	
	numberOfBitsUsedMod8 = numberOfBitsUsed % 8;
	
	// Faster to put the while at the top surprisingly enough
	while ( numberOfBitsToWrite > 0 )
		//do
	{
		datauint8_t = *( input + offset );
		
		if ( numberOfBitsToWrite < 8 && rightAlignedBits )   // rightAlignedBits means in the case of a partial uint8_t, the bits are aligned from the right (bit 0) rather than the left (as in the normal internal representation)
			datauint8_t <<= 8 - numberOfBitsToWrite;  // shift left to get the bits on the left, as in our internal representation
			
		// Writing to a new uint8_t each time
		if ( numberOfBitsUsedMod8 == 0 )
			* ( data + ( numberOfBitsUsed >> 3 ) ) = datauint8_t;
		else
		{
			// Copy over the new data.
			*( data + ( numberOfBitsUsed >> 3 ) ) |= datauint8_t >> ( numberOfBitsUsedMod8 ); // First half
			
			if ( 8 - ( numberOfBitsUsedMod8 ) < 8 && 8 - ( numberOfBitsUsedMod8 ) < numberOfBitsToWrite )   // If we didn't write it all out in the first half (8 - (numberOfBitsUsed%8) is the number we wrote in the first half)
			{
				*( data + ( numberOfBitsUsed >> 3 ) + 1 ) = (unsigned char) ( datauint8_t << ( 8 - ( numberOfBitsUsedMod8 ) ) ); // Second half (overlaps uint8_t boundary)
			}
		}
		
		if ( numberOfBitsToWrite >= 8 )
			numberOfBitsUsed += 8;
		else
			numberOfBitsUsed += numberOfBitsToWrite;
		
		numberOfBitsToWrite -= 8;
		
		offset++;
	}
	// } while(numberOfBitsToWrite>0);
}

// Set the stream to some initial data.  For internal use
void BitStream::SetData( const unsigned char* input, const int numberOfBits )
{
#ifdef _DEBUG
	assert( numberOfBitsUsed == 0 ); // Make sure the stream is clear
#endif
	
	if ( numberOfBits <= 0 )
		return ;
		
	AddBitsAndReallocate( numberOfBits );
	
	memcpy( data, input, BITS_TO_uint8_tS( numberOfBits ) );
	
	numberOfBitsUsed = numberOfBits;
}

// Assume the input source points to a native type, compress and write it
void BitStream::WriteCompressed( const unsigned char* input,
	const int size, const bool unsignedData )
{
	int currentuint8_t = ( size >> 3 ) - 1; // PCs
	
	unsigned char uint8_tMatch;
	
	if ( unsignedData )
	{
		uint8_tMatch = 0;
	}
	
	else
	{
		uint8_tMatch = 0xFF;
	}
	
	// Write upper uint8_ts with a single 1
	// From high uint8_t to low uint8_t, if high uint8_t is a uint8_tMatch then write a 1 bit. Otherwise write a 0 bit and then write the remaining uint8_ts
	while ( currentuint8_t > 0 )
	{
		if ( input[ currentuint8_t ] == uint8_tMatch )   // If high uint8_t is uint8_tMatch (0 of 0xff) then it would have the same value shifted
		{
			bool b = true;
			Write( b );
		}
		else
		{
			// Write the remainder of the data after writing 0
			bool b = false;
			Write( b );
			
			WriteBits( input, ( currentuint8_t + 1 ) << 3, true );
			//  currentuint8_t--;
			
			
			return ;
		}
		
		currentuint8_t--;
	}
	
	// If the upper half of the last uint8_t is a 0 (positive) or 16 (negative) then write a 1 and the remaining 4 bits.  Otherwise write a 0 and the 8 bites.
	if ( ( unsignedData && ( ( *( input + currentuint8_t ) ) & 0xF0 ) == 0x00 ) ||
		( unsignedData == false && ( ( *( input + currentuint8_t ) ) & 0xF0 ) == 0xF0 ) )
	{
		bool b = true;
		Write( b );
		WriteBits( input + currentuint8_t, 4, true );
	}
	
	else
	{
		bool b = false;
		Write( b );
		WriteBits( input + currentuint8_t, 8, true );
	}
}

// Read numberOfBitsToRead bits to the output source
// alignBitsToRight should be set to true to convert internal bitstream data to userdata
// It should be false if you used WriteBits with rightAlignedBits false
bool BitStream::ReadBits( unsigned char* output,
	int numberOfBitsToRead, const bool alignBitsToRight )
{
#ifdef _DEBUG
	assert( numberOfBitsToRead > 0 );
#endif
	if (numberOfBitsToRead<=0)
	  return false;
	
	if ( readOffset + numberOfBitsToRead > numberOfBitsUsed )
		return false;
		
	int readOffsetMod8;
	
	int offset = 0;
	
	memset( output, 0, BITS_TO_uint8_tS( numberOfBitsToRead ) );
	
	readOffsetMod8 = readOffset % 8;
	
	// do
	// Faster to put the while at the top surprisingly enough
	while ( numberOfBitsToRead > 0 )
	{
		*( output + offset ) |= *( data + ( readOffset >> 3 ) ) << ( readOffsetMod8 ); // First half
		
		if ( readOffsetMod8 > 0 && numberOfBitsToRead > 8 - ( readOffsetMod8 ) )   // If we have a second half, we didn't read enough uint8_ts in the first half
			*( output + offset ) |= *( data + ( readOffset >> 3 ) + 1 ) >> ( 8 - ( readOffsetMod8 ) ); // Second half (overlaps uint8_t boundary)
			
		numberOfBitsToRead -= 8;
		
		if ( numberOfBitsToRead < 0 )   // Reading a partial uint8_t for the last uint8_t, shift right so the data is aligned on the right
		{
		
			if ( alignBitsToRight )
				* ( output + offset ) >>= -numberOfBitsToRead;
				
			readOffset += 8 + numberOfBitsToRead;
		}
		else
			readOffset += 8;
			
		offset++;
		
	}
	
	//} while(numberOfBitsToRead>0);
	
	return true;
}

// Assume the input source points to a compressed native type. Decompress and read it
bool BitStream::ReadCompressed( unsigned char* output,
	const int size, const bool unsignedData )
{
	int currentuint8_t = ( size >> 3 ) - 1;
	
	
	unsigned char uint8_tMatch, halfuint8_tMatch;
	
	if ( unsignedData )
	{
		uint8_tMatch = 0;
		halfuint8_tMatch = 0;
	}
	
	else
	{
		uint8_tMatch = 0xFF;
		halfuint8_tMatch = 0xF0;
	}
	
	// Upper uint8_ts are specified with a single 1 if they match uint8_tMatch
	// From high uint8_t to low uint8_t, if high uint8_t is a uint8_tMatch then write a 1 bit. Otherwise write a 0 bit and then write the remaining uint8_ts
	while ( currentuint8_t > 0 )
	{
		// If we read a 1 then the data is uint8_tMatch.
		
		bool b;
		
		if ( Read( b ) == false )
			return false;
			
		if ( b )   // Check that bit
		{
			output[ currentuint8_t ] = uint8_tMatch;
			currentuint8_t--;
		}
		else
		{
			// Read the rest of the uint8_ts
			
			if ( ReadBits( output, ( currentuint8_t + 1 ) << 3 ) == false )
				return false;
				
			return true;
		}
	}
	
	// All but the first uint8_ts are uint8_tMatch.  If the upper half of the last uint8_t is a 0 (positive) or 16 (negative) then what we read will be a 1 and the remaining 4 bits.
	// Otherwise we read a 0 and the 8 uint8_ts
	//assert(readOffset+1 <=numberOfBitsUsed); // If this assert is hit the stream wasn't long enough to read from
	if ( readOffset + 1 > numberOfBitsUsed )
		return false;
		
	bool b;
	
	if ( Read( b ) == false )
		return false;
		
	if ( b )   // Check that bit
	{
	
		if ( ReadBits( output + currentuint8_t, 4 ) == false )
			return false;
			
		output[ currentuint8_t ] |= halfuint8_tMatch; // We have to set the high 4 bits since these are set to 0 by ReadBits
	}
	else
	{
		if ( ReadBits( output + currentuint8_t, 8 ) == false )
			return false;
	}
	
	return true;
}

// Reallocates (if necessary) in preparation of writing numberOfBitsToWrite
void BitStream::AddBitsAndReallocate( const int numberOfBitsToWrite )
{
	if ( numberOfBitsToWrite <= 0 )
		return;

	int newNumberOfBitsAllocated = numberOfBitsToWrite + numberOfBitsUsed;
	
	if ( numberOfBitsToWrite + numberOfBitsUsed > 0 && ( ( numberOfBitsAllocated - 1 ) >> 3 ) < ( ( newNumberOfBitsAllocated - 1 ) >> 3 ) )   // If we need to allocate 1 or more new uint8_ts
	{
#ifdef _DEBUG
		// If this assert hits then we need to specify true for the third parameter in the constructor
		// It needs to reallocate to hold all the data and can't do it unless we allocated to begin with
		assert( copyData == true );
#endif

		// Less memory efficient but saves on news and deletes
		newNumberOfBitsAllocated = ( numberOfBitsToWrite + numberOfBitsUsed ) * 2;
//		int newuint8_tOffset = BITS_TO_uint8_tS( numberOfBitsAllocated );
		// Use realloc and free so we are more efficient than delete and new for resizing
		int amountToAllocate = BITS_TO_uint8_tS( newNumberOfBitsAllocated );
		if (data==(unsigned char*)stackData)
		{
			 if (amountToAllocate > BITSTREAM_STACK_ALLOCATION_SIZE)
			 {
				 data = ( unsigned char* ) malloc( amountToAllocate );

				 // need to copy the stack data over to our new memory area too
				 memcpy ((void *)data, (void *)stackData, BITS_TO_uint8_tS( numberOfBitsAllocated )); 
			 }
		}
		else
		{
			data = ( unsigned char* ) realloc( data, amountToAllocate );
		}

#ifdef _DEBUG
		assert( data ); // Make sure realloc succeeded
#endif
		//  memset(data+newuint8_tOffset, 0,  ((newNumberOfBitsAllocated-1)>>3) - ((numberOfBitsAllocated-1)>>3)); // Set the new data block to 0
	}
	
	if ( newNumberOfBitsAllocated > numberOfBitsAllocated )
		numberOfBitsAllocated = newNumberOfBitsAllocated;
}

// Should hit if reads didn't match writes
void BitStream::AssertStreamEmpty( void )
{
	assert( readOffset == numberOfBitsUsed );
}

void BitStream::PrintBits( void ) const
{
	if ( numberOfBitsUsed <= 0 )
	{
		printf( "No bits\n" );
		return ;
	}
	
	for ( int counter = 0; counter < BITS_TO_uint8_tS( numberOfBitsUsed ); counter++ )
	{
		int stop;
		
		if ( counter == ( numberOfBitsUsed - 1 ) >> 3 )
			stop = 8 - ( ( ( numberOfBitsUsed - 1 ) % 8 ) + 1 );
		else
			stop = 0;
			
		for ( int counter2 = 7; counter2 >= stop; counter2-- )
		{
			if ( ( data[ counter ] >> counter2 ) & 1 )
				putchar( '1' );
			else
				putchar( '0' );
		}
		
		putchar( ' ' );
	}
	
	putchar( '\n' );
}


// Exposes the data for you to look at, like PrintBits does.
// Data will point to the stream.  Returns the length in bits of the stream.
int BitStream::CopyData( unsigned char** _data ) const
{
#ifdef _DEBUG
	assert( numberOfBitsUsed > 0 );
#endif
	
	*_data = new unsigned char [ BITS_TO_uint8_tS( numberOfBitsUsed ) ];
	memcpy( *_data, data, sizeof(unsigned char) * ( BITS_TO_uint8_tS( numberOfBitsUsed ) ) );
	return numberOfBitsUsed;
}

// Ignore data we don't intend to read
void BitStream::IgnoreBits( const int numberOfBits )
{
	readOffset += numberOfBits;
}

// Move the write pointer to a position on the array.  Dangerous if you don't know what you are doing!
void BitStream::SetWriteOffset( const int offset )
{
	numberOfBitsUsed = offset;
}

// Returns the length in bits of the stream
int BitStream::GetNumberOfBitsUsed( void ) const
{
	return numberOfBitsUsed;
}

// Returns the length in uint8_ts of the stream
int BitStream::GetNumberOfuint8_tsUsed( void ) const
{
	return BITS_TO_uint8_tS( numberOfBitsUsed );
}

// Returns the number of bits into the stream that we have read
int BitStream::GetReadOffset( void ) const
{
	return readOffset;
}

// Sets the read bit index
void BitStream::SetReadOffset( int newReadOffset )
{
	readOffset=newReadOffset;
}

// Returns the number of bits left in the stream that haven't been read
int BitStream::GetNumberOfUnreadBits( void ) const
{
	return numberOfBitsUsed - readOffset;
}

// Exposes the internal data
unsigned char* BitStream::GetData( void ) const
{
	return data;
}

// If we used the constructor version with copy data off, this makes sure it is set to on and the data pointed to is copied.
void BitStream::AssertCopyData( void )
{
	if ( copyData == false )
	{
		copyData = true;
		
		if ( numberOfBitsAllocated > 0 )
		{
			unsigned char * newdata = ( unsigned char* ) malloc( BITS_TO_uint8_tS( numberOfBitsAllocated ) );
#ifdef _DEBUG
			
			assert( data );
#endif
			
			memcpy( newdata, data, BITS_TO_uint8_tS( numberOfBitsAllocated ) );
			data = newdata;
		}
		
		else
			data = 0;
	}
}
void BitStream::Reverseuint8_ts(unsigned char *input, unsigned char *output, int length)
{
	for (int i=0; i < length; i++)
		output[i]=input[length-i-1];
}
bool BitStream::DoEndianSwap(void) const
{
#ifndef __BITSTREAM_NATIVE_END
	static bool swap=htonl(12345) == 12345;
	return swap;
#else
	return false;
#endif
}
