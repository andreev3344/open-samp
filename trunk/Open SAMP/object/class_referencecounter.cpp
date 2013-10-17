#include "../main.h"
#include "class_referencecounter.h"

void CReferenceCounter::Grab ( void )
{
	this->m_uint32_ReferenceCount++;
}

bool CReferenceCounter::Drop ( void )
{
	if ( this->m_uint32_ReferenceCount <= 0 )
		return false;

	this->m_uint32_ReferenceCount--;
	if ( !( this->m_uint32_ReferenceCount ) )
	{
		delete this;
		return true;
	}
	return false;
}

uint32_t CReferenceCounter::GetReferenceCount ( void )
{
	return this->m_uint32_ReferenceCount;
}