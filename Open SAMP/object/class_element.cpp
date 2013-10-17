#include "../main.h"
#include "class_element.h"

CElement::~CElement()
{
	this->Remove();

	list< CElement* >::iterator l_IterChildren = this->m_Children.begin();
	for ( ; l_IterChildren != this->m_Children.end(); l_IterChildren++ )
	{
		delete ( *l_IterChildren );
	}
}

void CElement::SetElementIndex ( uint32_t a_uint32_ElementIndex )
{
	this->m_uint32_ElementIndex = a_uint32_ElementIndex;
}

uint32_t CElement::GetElementIndex ( void )
{
	return this->m_uint32_ElementIndex;
}

void CElement::SetElementType ( uint8_t a_uint8_ElementType )
{
	this->m_uint8_ElementType = a_uint8_ElementType;
}

uint8_t CElement::GetElementType ( void )
{
	return this->m_uint8_ElementType;
}

void CElement::SetElementOwner ( uint16_t a_uint16_ElementOwner )
{
	this->m_uint16_ElementOwner = a_uint16_ElementOwner;

	list< CElement* > ::iterator l_IterChildren = this->m_Children.begin();
	for ( ; l_IterChildren != this->m_Children.end(); l_IterChildren++ )
	{
		( *l_IterChildren )->SetElementOwner ( a_uint16_ElementOwner );
	}
}

uint16_t CElement::GetElementOwner ( void )
{
	return this->m_uint16_ElementOwner;
}

bool CElement::SetElementModel ( uint32_t a_uint32_ModelIndex )
{
	//TODO: Check modelindex
	this->m_uint32_ModelIndex = a_uint32_ModelIndex;

	return true;
}

uint32_t CElement::GetElementModel ( void )
{
	return this->m_uint32_ModelIndex;
}

void CElement::SetParent ( CElement* a_Element )
{
	this->m_Parent = a_Element;
}

CElement* CElement::GetParent ( void )
{
	return this->m_Parent;
}

void CElement::AddChild ( CElement* a_Element )
{
	if ( a_Element && ( a_Element != this ) )
	{
		a_Element->Grab();
		a_Element->Remove();
		a_Element->SetParent ( this );

		this->m_Children.push_back ( a_Element );
	}
}

void CElement::Remove ( void )
{
	if ( this->m_Parent )
		this->m_Parent->RemoveChild ( this );
}
	
void CElement::RemoveChildren ( void )
{	
	list< CElement* > ::iterator l_IterChildren = this->m_Children.begin();
	for ( ; l_IterChildren != this->m_Children.end(); l_IterChildren++ )
	{
		( *l_IterChildren )->SetParent ( NULL );
		( *l_IterChildren )->Drop();
	}

	this->m_Children.clear();
}

void CElement::RemoveChild ( CElement* a_Element )
{
	list< CElement* > ::iterator l_IterChildren = this->m_Children.begin();
	for ( ; l_IterChildren != this->m_Children.end(); l_IterChildren++ )
	{
		if ( ( *l_IterChildren ) == a_Element )
		{
			( *l_IterChildren )->SetParent ( NULL );
			( *l_IterChildren )->Drop();

			this->m_Children.erase ( l_IterChildren );
			return;
		}
	}
}


TiXmlElement* CElement::SerializeAttribute ( void )
{
	TiXmlElement* l_XmlElement = NULL;

	if ( this->m_uint8_ElementType == ELEMENT_TYPE_VIRTUAL )
		l_XmlElement = new TiXmlElement ( "virtual" );

	if ( l_XmlElement )
	{
		l_XmlElement->SetDoubleAttribute ( "x", this->m_Position.X );
		l_XmlElement->SetDoubleAttribute ( "y", this->m_Position.Y );
		l_XmlElement->SetDoubleAttribute ( "z", this->m_Position.Z );
		l_XmlElement->SetDoubleAttribute ( "rx", this->m_Rotation.X );
		l_XmlElement->SetDoubleAttribute ( "ry", this->m_Rotation.Y );
		l_XmlElement->SetDoubleAttribute ( "rz", this->m_Rotation.Z );

		return l_XmlElement;
	}
	return NULL;
}
	
void CElement::UnSerializeAttribute ( TiXmlElement* a_XmlElement )
{
	tVector* l_Position = new tVector();
	if ( l_Position )
	{
		a_XmlElement->QueryFloatAttribute ( "x", &l_Position->X );
		a_XmlElement->QueryFloatAttribute ( "y", &l_Position->Y );
		a_XmlElement->QueryFloatAttribute ( "z", &l_Position->Z );

		this->SetPosition ( l_Position );
	}

	tVector* l_Rotation = new tVector();
	if ( l_Rotation )
	{
		a_XmlElement->QueryFloatAttribute ( "rx", &l_Rotation->X );
		a_XmlElement->QueryFloatAttribute ( "ry", &l_Rotation->Y );
		a_XmlElement->QueryFloatAttribute ( "rz", &l_Rotation->Z );

		this->SetRotation ( l_Rotation );
	}
}

void CElement::SetRotation ( tVector* a_Rotation )
{
	/*
	float l_Degrees_X = a_Rotation->X * ( 3.14159265359f / 180.0f );
	float l_Cos_X = cos ( l_Degrees_X );
	float l_Sin_X = sin ( l_Degrees_X );
	
	this->m_Position.Z -= this->m_Parent->GetPosition()->Z;
	this->m_Position.Y -= this->m_Parent->GetPosition()->Y;

	this->m_Position.Y = ( float )( m_Position.Y * l_Cos_X - m_Position.Z * l_Sin_X );
	this->m_Position.Z = ( float )( m_Position.Y * l_Cos_X + m_Position.Z * l_Sin_X );

	this->m_Position.Z += this->m_Parent->GetPosition()->Z;
	this->m_Position.Y += this->m_Parent->GetPosition()->Y;
	*/
	this->m_Rotation.X = a_Rotation->X;
	this->m_Rotation.Y = a_Rotation->Y;
	this->m_Rotation.Z = a_Rotation->Z;
}
	
tVector* CElement::GetRotation ( void )
{
	return &( this->m_Rotation );
}
	
void RotateVector ( tVector& vecLine, const tVector& vecRotation )
{
    // Rotate it along the X axis
    // [ 1     0        0    0 ]
    // [ 0   cos a   sin a   0 ]
    // [ 0  -sin a   cos a   0 ]

    float fLineY = vecLine.Y;
    vecLine.Y = cos ( vecRotation.X ) * fLineY  + sin ( vecRotation.X ) * vecLine.Z;
    vecLine.Z = -sin ( vecRotation.X ) * fLineY + cos ( vecRotation.X ) * vecLine.Z;

    // Rotate it along the Y axis
    // [ cos a   0   -sin a   0 ]
    // [   0     1     0      0 ]
    // [ sin a   0    cos a   0 ]

    float fLineX = vecLine.X;
    vecLine.X = cos ( vecRotation.Y ) * fLineX - sin ( vecRotation.Y ) * vecLine.Z;
    vecLine.Z = sin ( vecRotation.Y ) * fLineX + cos ( vecRotation.Y ) * vecLine.Z;

    // Rotate it along the Z axis
    // [  cos a   sin a   0   0 ]
    // [ -sin a   cos a   0   0 ]
    // [    0       0     1   0 ]

    fLineX = vecLine.X;
    vecLine.X = cos ( vecRotation.Z ) * fLineX  + sin ( vecRotation.Z ) * vecLine.Y;
    vecLine.Y = -sin ( vecRotation.Z ) * fLineX + cos ( vecRotation.Z ) * vecLine.Y;
}

void CElement::SetPosition ( tVector* a_Position )
{
	this->m_RelativePosition = *a_Position;

	if ( this->m_Parent )
	{
		this->m_Position = ( *( this->m_Parent->GetAbsolutePosition() ) ) + this->m_RelativePosition;
	}
	else
	{
		this->m_Position = this->m_RelativePosition;
	}

	list< CElement* > ::iterator l_IterChildren = this->m_Children.begin();
	for ( ; l_IterChildren != this->m_Children.end(); l_IterChildren++ )
	{
		( *l_IterChildren )->UpdatePosition();
	}
}

tVector* CElement::GetPosition ( void )
{
	return &( this->m_RelativePosition );
}

void CElement::SetAbsolutePosition ( tVector* a_AbsolutePosition )
{
	this->m_Position = *a_AbsolutePosition;

	list< CElement* > ::iterator l_IterChildren = this->m_Children.begin();
	for ( ; l_IterChildren != this->m_Children.end(); l_IterChildren++ )
	{
		( *l_IterChildren )->UpdatePosition();
	}
}

tVector* CElement::GetAbsolutePosition ( void )
{
	return &( this->m_Position );
}

void CElement::SetHealth ( float a_float_Health )
{
	this->m_float_Health = a_float_Health;
}

float CElement::GetHealth ( void )
{
	return this->m_float_Health;
}

void CElement::SetVirtualWorld ( uint32_t a_uint32_VirtualWorld )
{
	this->m_uint32_VirtualWorld = a_uint32_VirtualWorld;
}

uint32_t CElement::GetVirtualWorld ( void )
{
	return this->m_uint32_VirtualWorld;
}

float CElement::GetDistanceFrom ( tVector* a_Position )
{
	return this->m_Position.GetDistanceFrom ( a_Position );
}

float CElement::GetDistanceFrom ( CElement* a_Element )
{
	return this->m_Position.GetDistanceFrom ( a_Element->GetAbsolutePosition() );
}

/*
void CElement::GetAttachedPosition ( CVector & vecPosition )
{
    if ( m_pAttachedTo )
    {
        CVector vecRotation;
        vecPosition = m_pAttachedTo->GetPosition ();
        m_pAttachedTo->GetRotation ( vecRotation );

        CVector vecPositionOffset = m_vecAttachedPosition;
        // This works when rotating around z axis. Other axes need testing.
        RotateVector ( vecPositionOffset, CVector ( vecRotation.fX, vecRotation.fY, -vecRotation.fZ ) );
        vecPosition += vecPositionOffset;
    }
}


void CElement::GetAttachedRotation ( CVector & vecRotation )
{
    if ( m_pAttachedTo )
    {
        m_pAttachedTo->GetRotation ( vecRotation );
        vecRotation += m_vecAttachedRotation;
    }
}
*/



/**
 *	CElement::ShowForPlayer()
 *		Update the network and show the object for the specified player and only. Object's Owner flag is modified.
 *	@a_uint16_PlayerIndex: The Player's Index.
 */
void CElement::ShowForPlayer ( uint16_t a_uint16_PlayerIndex )
{
	this->m_uint16_ElementOwner = a_uint16_PlayerIndex;
}

/**
 *	CElement::ShowForAll()
 *		Update the network and show the object for everyone. Reset the Object's Owner flag.
 */
void CElement::ShowForAll ( void )
{
	this->m_uint16_ElementOwner = 0;
}

void CElement::UpdatePosition()
{
	if ( this->m_Parent )
	{
		this->m_Position = ( *( this->m_Parent->GetPosition() ) ) + this->m_RelativePosition;
	}
}
