#ifndef __CLASS_REFERENCE_COUNTER_H_
#define __CLASS_REFERENCE_COUNTER_H_

class CReferenceCounter
{
private:

	uint32_t m_uint32_ReferenceCount;

public:
	
	CReferenceCounter()
	{
		this->m_uint32_ReferenceCount = 1;
	};

	virtual ~CReferenceCounter()
	{

	};

	void Grab ( void );
	bool Drop ( void );
	uint32_t GetReferenceCount ( void );
};

// __CLASS_REFERENCE_COUNTER_H_
#endif